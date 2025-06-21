// Test of PVCS

#include <stdio.h>
#include "d3drmwin.h"
#include "d3dapp.h"
#include "mdtex.h"
#include "wrapper.h"
#include "d3dappi.h"

#define INVALID_TEXTURE_HANDLE (unsigned long)0
#define TEXTURE_COLORS 256

extern D3DAppInfo d3dappi;
extern char BmpPath[];
extern char HDPath[];
static HRESULT LastError;
char LastErrorString[256];

//system diagnostic stuff
DDCAPS ddcaps,ddhelcaps;
CHAR lpOutput[256];



/*
 * D3DAppErrorToString
 */
extern char* D3DAppErrorToString(HRESULT error);

/*
 * D3DAppISetErrorString
 * Set the global variable which records the last error string.
 */
extern void D3DAppISetErrorString( LPSTR fmt, ... );

/*
static HRESULT
CALLBACK EnumTextureFormatsCallback(LPDDSURFACEDESC lpDDSD, LPVOID lpContext)
{
    LPDDSURFACEDESC lpformat = (LPDDSURFACEDESC)lpContext;

    // Record the DDSURFACEDESC of this texture format
    memset(lpformat, 0, sizeof(DDSURFACEDESC));
    memcpy(lpformat, lpDDSD, sizeof(DDSURFACEDESC));
    
    return DDENUMRET_CANCEL;
}
*/
HRESULT  TGSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
    DDCOLORKEY ddck;

//    ddck.dwColorSpaceLowValue = DDColorMatch(lpDDSOverlay[0], rgb);
    ddck.dwColorSpaceLowValue = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->lpVtbl->SetColorKey(pdds, DDCKEY_SRCBLT, &ddck);

}

 
LPDIRECTDRAWSURFACE
LoadTextureIntoSurface(LPDIRECTDRAW lpDD, LPCSTR lpName,
					   LPDDSURFACEDESC lpFormat, DWORD memoryflag, int transbits)
{
    LPDIRECTDRAWSURFACE lpDDS, lpDDS2;
    DDSURFACEDESC ddsd, format;
    LPDIRECT3DTEXTURE    lpSourceTextureObject, lpDestTextureObject; /* texture objs */
    LPDIRECTDRAWPALETTE lpDstPalette = NULL;


	D3DCOLOR colors[256];
//    D3DCOLOR c;
    DWORD dwWidth, dwHeight;
    int i, j;
    FILE *fp;
    char *lpC;
    CHAR buf[100];
    LPDIRECTDRAWPALETTE lpDDPal;
    PALETTEENTRY ppe[256];
    int psize;
    DWORD pcaps;
//    int color_count;
    HRESULT ddrval;
    DDCOLORKEY  ddck;
//	int ret;
	int temp;

   /*
   BYDumpInfo(lpName);

	if (memoryflag==DDSCAPS_SYSTEMMEMORY) BYDumpInfo("System memory for surface");
	else if (memoryflag==DDSCAPS_VIDEOMEMORY) BYDumpInfo("Video memory for surface");
	else BYDumpInfo("No memory for surface?!?");
   */

	//Tim system diagnostics: calculate remaining video memory 
	ddcaps.dwSize = sizeof(DDCAPS);
	ddhelcaps.dwSize = sizeof(DDCAPS);
	if (FAILED(lpDD->lpVtbl->GetCaps(lpDD, &ddcaps, &ddhelcaps))) {
		lpDD->lpVtbl->Release(lpDD);
		return NULL;
	}



	// output  result to dump file
	//sprintf(lpOutput, "Video memory free = %d\n", ddcaps.dwVidMemFree);
	//BYDumpInfo(lpOutput);



    /*
     * Find the image file and open it
     */
//    fp = D3DAppIFindFile(lpName, "rb");
	fp = fopen(lpName, "rb");
    if (fp == NULL) 
	{
        D3DAppISetErrorString("Cannot find %s.\n", lpName);
        return NULL;
    }

	memcpy(&format, lpFormat, sizeof(DDSURFACEDESC));
	if (format.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) 
	{
		psize = TEXTURE_COLORS;
		pcaps = DDPCAPS_8BIT | DDPCAPS_ALLOW256;
	}
	else
	{
		psize = TEXTURE_COLORS;
		//MessageBox( NULL, "Palette Index other than 8 bit not supported yet!", "Texture Mapping Message", MB_OK );
		//return NULL;
	}

	memcpy(&ddsd, &format, sizeof(DDSURFACEDESC));

	fread(buf, 2, 1, fp);
    /*
     * Is it a PPM file?
     */
    if (buf[0] == 'P' && buf[1] == '6') 
	{

    }
    /*
     * Is it a BMP file?
     */
	else if (buf[0] == 'B' && buf[1] == 'M')
	{
		short BitCount;
		DWORD size,compress;

		fread(buf, 16, 1, fp);
		
		fread(&dwWidth, 4, 1, fp);
		fread(&dwHeight, 4, 1, fp);

		fread(buf, 2, 1, fp);
		fread(&BitCount, 2, 1, fp);

		fread(&compress, 4, 1, fp);
		if (compress) 
		{
			MessageBox( NULL, "Compressed bitmap is not supported!", "Texture Mapping Message", MB_OK );
			return NULL;
		}
		
		fread(&size, 4, 1, fp);
		/*
		 * Skip to the first position of data
		 *
		 */
		fread(buf, 16, 1, fp);

		/*
		 * Create a surface of the given format using the dimensions of the BMP
		 * file.
		 */
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;	
		ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwHeight = dwHeight;
		ddsd.dwWidth = dwWidth;

		ddrval = lpDD->lpVtbl->CreateSurface(lpDD, &ddsd, &lpDDS, NULL);
		if (ddrval != DD_OK) 
		{
			D3DAppISetErrorString("CreateSurface for texture failed (loadtex).\n%s",
								  D3DAppErrorToString(ddrval));
			return NULL;
		}

		if (transbits) 
        {
			ddck.dwColorSpaceLowValue = 0x00000000;
			ddck.dwColorSpaceHighValue = 0x00000000;
			
			ddrval = lpDDS->lpVtbl->SetColorKey(lpDDS,DDCKEY_SRCBLT, &ddck);
			if (ddrval != DD_OK) 
			{
            BYDumpInfo("Set color key failed");
							D3DAppISetErrorString("Set color key for texture surface failed (loadtex).\n%s",
							D3DAppErrorToString(ddrval));
							return NULL;
			}


        }

		/*
		* Query our source surface for a texture interface
		*/
		LastError = lpDDS->lpVtbl->QueryInterface(lpDDS,
                                             &IID_IDirect3DTexture,
                                             (LPVOID*)&lpSourceTextureObject);

		if (LastError != DD_OK) 
		{
					D3DAppISetErrorString("Failed to obtain D3D texture interface for a destination texture.\n%s",
					D3DAppErrorToString(LastError));
					return NULL;
		}



		/*
		 * Lock the surface so it can be filled with the BMP file
		 */
		memset(&ddsd, 0, sizeof(DDSURFACEDESC));
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		ddrval = lpDDS->lpVtbl->Lock(lpDDS, NULL, &ddsd, 0, NULL);
		if (ddrval != DD_OK) 
		{
			lpDDS->lpVtbl->Release(lpDDS);
			D3DAppISetErrorString("Lock failed while loading surface (loadtex).\n%s",
								  D3DAppErrorToString(ddrval));
			return NULL;
		}

		if (BitCount == 8)
		{
      
			fread(colors, sizeof(D3DCOLOR), psize, fp);

			if (d3dappi.ThisTextureFormat.bPalettized)   /* is this d3d texture format palettized */
			{
   			// 8-bit BMP into an 8-bit palettized surface
				/*
				 * Create a palette with the colors in our color table
				 */
				memset(ppe, 0, sizeof(PALETTEENTRY) * psize);
				for (i=0, j=0; i < 256; i++, j++) 
				{
					ppe[i].peBlue = *((char *)colors + j++);
					ppe[i].peGreen = *((char *)colors + j++);
					ppe[i].peRed = *((char *)colors + j++);
				}

				/*
				 * Create the palette with the DDPCAPS_ALLOW256 flag because we want to
				 * have access to all entries.
				 */
				ddrval = lpDD->lpVtbl->CreatePalette(lpDD,
													 DDPCAPS_INITIALIZE | pcaps,
													 ppe, &lpDDPal, NULL);
				if (ddrval != DD_OK) 
				{
					lpDDS->lpVtbl->Release(lpDDS);
					D3DAppISetErrorString("Create palette failed while loading surface (loadtex).\n%s",
										  D3DAppErrorToString(ddrval));
					fclose(fp);
					lpDDS->lpVtbl->Unlock(lpDDS, NULL);
					return (NULL);
				}
				/*
				 * Finally, bind the palette to the surface
				 */
				ddrval = lpDDS->lpVtbl->SetPalette(lpDDS, lpDDPal);
				if (ddrval != DD_OK) 
				{
					lpDDS->lpVtbl->Release(lpDDS);
					lpDDPal->lpVtbl->Release(lpDDPal);
					D3DAppISetErrorString("SetPalette failed while loading surface (loadtex).\n%s",
										  D3DAppErrorToString(ddrval));
					fclose(fp);
					lpDDS->lpVtbl->Unlock(lpDDS, NULL);
					return (NULL);
				}

				lpDDPal->lpVtbl->Release(lpDDPal);

				for (i=0; i<(int)dwHeight; i++)
				{
					//lpC = (char*)ddsd.lpSurface + size - (i+1) * dwWidth;
					lpC = (char*)ddsd.lpSurface + (dwWidth*dwHeight) - (i+1) * dwWidth;
					for (j=0; j<(int)dwWidth; j++)
					{
						temp = fgetc(fp);
						*lpC = (char)temp;
						lpC++;

					}
				}
			}
			else
			{
        /*
         * The texture surface is not palettized
         */
   		// 8-bit BMP into an unpalettized surface
        unsigned long* lpLP;
        unsigned short* lpSP;
        unsigned char* lpCP;
        unsigned long m;
        int s;
        int red_shift, red_scale;
        int green_shift, green_scale;
        int blue_shift, blue_scale;
        /*     
         * Determine the red, green and blue masks' shift and scale.
         */
        for (s = 0, m = ddsd.ddpfPixelFormat.dwRBitMask; !(m & 1);
                                                               s++, m >>= 1);
        red_shift = s;
        red_scale = 255 / (ddsd.ddpfPixelFormat.dwRBitMask >> s);
        for (s = 0, m = ddsd.ddpfPixelFormat.dwGBitMask; !(m & 1);
                                                               s++, m >>= 1);
        green_shift = s;
        green_scale = 255 / (ddsd.ddpfPixelFormat.dwGBitMask >> s);
        for (s = 0, m = ddsd.ddpfPixelFormat.dwBBitMask; !(m & 1);
                                                               s++, m >>= 1);
        blue_shift = s;
        blue_scale = 255 / (ddsd.ddpfPixelFormat.dwBBitMask >> s);
        /*
         * Each RGB bit count requires different pointers
         */
        switch (ddsd.ddpfPixelFormat.dwRGBBitCount) 
		{
            case 32 :
                for (j = 0; j < (int)dwHeight; j++) 
				{
                    /*
                     * Point to next row in texture surface
                     */
                    lpLP = (unsigned long*)(((char*)ddsd.lpSurface) +
                                                            ddsd.lPitch * j);
                    for (i = 0; i < (int)dwWidth; i++) 
					{
                        int r, g, b;
                        /*
                         * Read each value, scale it and shift it into position
                         */
                        r = getc(fp) / red_scale;
                        g = getc(fp) / green_scale;
                        b = getc(fp) / blue_scale;
                        *lpLP = (r << red_shift) | (g << green_shift) |
                                (b << blue_shift);
                        lpLP++;
                    }
                }
                break;
            case 16 :
                for (j = (int)(dwHeight-1); j >=0; j--) 
				{
                    lpSP = (unsigned short*)(((char*)ddsd.lpSurface) +
                                                            ddsd.lPitch * j);
                    for (i = 0; i < (int)dwWidth; i++) 
					{
                        int r, g, b, temp;
						temp = fgetc(fp);
                        r = RGB_GETRED(colors[temp]) / red_scale;
                        g = RGB_GETGREEN(colors[temp]) / green_scale;
                        b = RGB_GETBLUE(colors[temp]) / blue_scale;
						//*(ddsd.lpSurface + (dwWidth*dwHeight) - (i+1) * dwWidth + j*bytesperpixel) = 
						//	(RGB_GETRED(colors[temp])>>(8 - redbbp))<<(greenbbp+bluebbp) + 
						//	(RGB_GETGREEN(colors[temp])>>(8 - greenbbp))<<(bluebbp) + 
						//	RGB_GETBLUE(colors[temp])>>(8 - bluebbp);
                        *lpSP = (r << red_shift) | (g << green_shift) |
                                (b << blue_shift);
                        lpSP++;
                    }
                }
                break;
            case 8:
                for (j = 0; j < (int)dwHeight; j++) 
				{
                    lpCP = (unsigned char*)(((char*)ddsd.lpSurface) +
                                                            ddsd.lPitch * j);
                    for (i = 0; i < (int)dwWidth; i++) 
					{
                        int r, g, b;
                        r = getc(fp) / red_scale;
                        g = getc(fp) / green_scale;
                        b = getc(fp) / blue_scale;
                        *lpCP = (r << red_shift) | (g << green_shift) | 
                                (b << blue_shift);
                        lpCP++;
                    }
                }
                break;
            default:
                /*
                 * This wasn't a format I recognize
                 */
                lpDDS->lpVtbl->Unlock(lpDDS, NULL);
                fclose(fp);
                lpDDS->lpVtbl->Release(lpDDS);
                D3DAppISetErrorString("Unknown pixel format (loadtex).");
                return NULL;
            }
        
         }


		/*
		* Close the file and unlock the surface
		*/
		lpDDS->lpVtbl->Unlock(lpDDS, NULL);
		fclose(fp);
		//lpDDS->lpVtbl->Release(lpDDS);
		return lpDDS;
		}
		else if (BitCount == 24)
		{
			if (d3dappi.ThisTextureFormat.bPalettized)   /* is this d3d texture format palettized */
			{
	         BYDumpInfo("Attempted to load 24-bit BMP into an 8-bit surface...not supported yet");
            return NULL;
   			// 24-bit BMP into an 8-bit palettized surface
         }
         else
         {
   			// 24-bit BMP into an unpalettized surface
           unsigned long* lpLP;
           unsigned short* lpSP;
           unsigned char* lpCP;
           unsigned long m;
           int s;
           int red_shift, red_scale;
           int green_shift, green_scale;
           int blue_shift, blue_scale;
           int alpha_shift, alpha_scale;
           /*     
            * Determine the red, green and blue masks' shift and scale.
            */
           for (s = 0, m = ddsd.ddpfPixelFormat.dwRBitMask; !(m & 1);
                                                                  s++, m >>= 1);
           red_shift = s;
           red_scale = 255 / (ddsd.ddpfPixelFormat.dwRBitMask >> s);
           for (s = 0, m = ddsd.ddpfPixelFormat.dwGBitMask; !(m & 1);
                                                                  s++, m >>= 1);
           green_shift = s;
           green_scale = 255 / (ddsd.ddpfPixelFormat.dwGBitMask >> s);
           for (s = 0, m = ddsd.ddpfPixelFormat.dwBBitMask; !(m & 1);
                                                                  s++, m >>= 1);
           blue_shift = s;
           blue_scale = 255 / (ddsd.ddpfPixelFormat.dwBBitMask >> s);
			if (ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
			{
			   for (s = 0, m = ddsd.ddpfPixelFormat.dwRGBAlphaBitMask; !(m & 1);
																	  s++, m >>= 1);
			   alpha_shift = s;
			   alpha_scale = 255 / (ddsd.ddpfPixelFormat.dwRGBAlphaBitMask >> s);
			}
           /*
            * Each RGB bit count requires different pointers
            */
           switch (ddsd.ddpfPixelFormat.dwRGBBitCount) {
               case 32 :
                   for (j = (int)(dwHeight-1); j >=0; j--) {
                       lpSP = (unsigned short*)(((char*)ddsd.lpSurface) +
                                                               ddsd.lPitch * j);
                       for (i = 0; i < (int)dwWidth; i++) {
                           int r, g, b, a;
                           /*
                            * Read each value, scale it and shift it into position
                            */
                           r = getc(fp);
                           g = getc(fp);
                           b = getc(fp);
						   if (transbits && ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
						   {
							   a = (r + g + b)/3;
							   a /= alpha_scale;
						   }
                           r /= red_scale;
                           g /= green_scale;
                           b /= blue_scale;
						   if (transbits && ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
							   *lpLP = (a << alpha_shift) | (r << red_shift) | 
									   (g << green_shift) | (b << blue_shift);
						   else
							   *lpLP = (r << red_shift) | (g << green_shift) |
									   (b << blue_shift);
                           lpLP++;
                       }
                   }
                   break;
               case 16 :
                   for (j = (int)(dwHeight-1); j >=0; j--) 
				   {
                       lpSP = (unsigned short*)(((char*)ddsd.lpSurface) +
                                                               ddsd.lPitch * j);
                       for (i = 0; i < (int)dwWidth; i++) 
					   {
                           int r, g, b, a;
                           /*
                            * Read each value, scale it and shift it into position
                            */
                           b = getc(fp);
                           g = getc(fp);
                           r = getc(fp);
						   if (transbits && ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
						   {
                        if (transbits == 4)
                        {
                           a = (r + g + b)/3;
                           if (d3dapprs.transparency == SEMIFANCY)
                           {
                              a = (r > a ? r : a);
                              a = (g > a ? g : a);
                              a = (b > a ? b : a);
                              a = (int)(a * 0.75);
                           }
                        }
                        else
                        {
							      if ((r + g + b) < 10 )	// black is transparent;
									   a = 0;				// alpha channel 0 = transparent
								   else
									   a = 255;
                        }
							   a /= alpha_scale;
							   // test to force alttype
							   if (d3dapprs.transparency == ALTTRANSPARENT)
								   a = 1;
						   }
                     else
						   if (!transbits && ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
                     {
                        a=255/alpha_scale;
                     }

							r /= red_scale;
							g /= green_scale;
							b /= blue_scale;
                           
							if ((transbits == 0) && (r == 0) && (g == 0) && (b == 0))     
						   {
								// If no transparency on texture, set black to near-black
								r = g = 0;
								b = 1;
						   }
						   

//						   if (transbits && ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
						   if (ddsd.ddpfPixelFormat.dwRGBAlphaBitMask)
							   *lpSP = (a << alpha_shift) | (r << red_shift) | 
									   (g << green_shift) | (b << blue_shift);
						   else
							   *lpSP = (r << red_shift) | (g << green_shift) |
									   (b << blue_shift);
                           lpSP++;
                       }
                   }
                   break;
               case 8:
                   for (j = 0; j < (int)dwHeight; j++) 
				   {
                       lpCP = (unsigned char*)(((char*)ddsd.lpSurface) +
                                                               ddsd.lPitch * j);
                       for (i = 0; i < (int)dwWidth; i++) 
					   {
                           int r, g, b;
                           r = getc(fp) / red_scale;
                           g = getc(fp) / green_scale;
                           b = getc(fp) / blue_scale;
                           *lpCP = (r << red_shift) | (g << green_shift) | 
                                   (b << blue_shift);
                           lpCP++;
                       }
                   }
                   break;
               default:
                   /*
                    * This wasn't a format I recognize
                    */
                   lpDDS->lpVtbl->Unlock(lpDDS, NULL);
                   fclose(fp);
                   lpDDS->lpVtbl->Release(lpDDS);
                   D3DAppISetErrorString("Unknown pixel format (loadtex).");
                   return NULL;
               }
            }
			fclose(fp);
			lpDDS->lpVtbl->Unlock(lpDDS, NULL);
			//RELEASE(lpDDS);   
            
			   if (memoryflag == DDSCAPS_VIDEOMEMORY)
			   {
					/*
					* Create an empty texture surface to load the source texture into.
					* The DDSCAPS_ALLOCONLOAD flag allows the DD driver to wait until the
					* load call to allocate the texture in memory because at this point,
					* we may not know how much memory the texture will take up (e.g. it
					* could be compressed to an unknown size in video memory).
					*/
					ddrval = D3DAppIGetSurfDesc(&ddsd, lpDDS);
					if (ddrval != DD_OK) 
					{
						D3DAppISetErrorString("Could not get the surface description of the source texture.\n%s",
                            D3DAppErrorToString(LastError));
						return NULL;
					}

				   	//memset(&ddsd, 0, sizeof(DDSURFACEDESC));
					ddsd.dwSize = sizeof(DDSURFACEDESC);
					ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
					ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_ALLOCONLOAD;
					ddsd.dwHeight = dwHeight;
					ddsd.dwWidth = dwWidth;

					ddrval = lpDD->lpVtbl->CreateSurface(lpDD, &ddsd, &lpDDS2, NULL);
					if (ddrval != DD_OK) 
					{
						D3DAppISetErrorString("CreateSurface for texture failed (loadtex).\n%s",
											  D3DAppErrorToString(ddrval));
						return NULL;
					}
							
					/*
					* Query our destination surface for a texture interface
					*/
					LastError = lpDDS2->lpVtbl->QueryInterface(lpDDS2,
                                             &IID_IDirect3DTexture,
                                             (LPVOID*)&lpDestTextureObject);

					if (LastError != DD_OK) 
					{
							D3DAppISetErrorString("Failed to obtain D3D texture interface for a destination texture.\n%s",
                            D3DAppErrorToString(LastError));
							return NULL;
					}
		
					/*
					* Load the source texture into the destination.  During this call, a
					* driver could compress or reformat the texture surface and put it in
					* video memory.
					*/
					LastError = lpDestTextureObject->lpVtbl->Load(lpDestTextureObject, lpSourceTextureObject);
					if (LastError != DD_OK) 
					{
						D3DAppISetErrorString("Could not load a source texture into a destination texture.\n%s",
						D3DAppErrorToString(LastError));
						return NULL;
					}
					// Tim set transparency for destination surface
					//if (transbits && (0))
					//if (transbits && (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY))
					//if (transbits && !(d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT))
					if (transbits && (d3dappi.Driver[d3dappi.CurrDriver].Desc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY) && !(d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT))
					{
						ddck.dwColorSpaceLowValue = 0x00000000;
						ddck.dwColorSpaceHighValue = 0x00000000;
			
						ddrval = lpDDS2->lpVtbl->SetColorKey(lpDDS2,DDCKEY_SRCBLT, &ddck);
						if (ddrval != DD_OK) 
						{
							D3DAppISetErrorString("Set color key for texture surface failed (loadtex).\n%s",
							D3DAppErrorToString(ddrval));
							return NULL;
						}
					}
					else
					{
						ddck.dwColorSpaceLowValue = 0x00000000;
						ddck.dwColorSpaceHighValue = 0x00000000;
			
						ddrval = lpDDS2->lpVtbl->SetColorKey(lpDDS2,DDCKEY_SRCBLT, &ddck);
						if (ddrval != DD_OK) 
						{
							D3DAppISetErrorString("Set color key for texture surface failed (loadtex).\n%s",
							D3DAppErrorToString(ddrval));
							return NULL;
						}
					}


    				RELEASE(lpSourceTextureObject)
					RELEASE(lpDestTextureObject)
					RELEASE(lpDDS);
					return lpDDS2;
			   }

    			RELEASE(lpSourceTextureObject)
			   return lpDDS;
		}
		else
		{
		}
	}
//**********						**********
//**********						**********
//********************************************
	else
	{
		fclose(fp);
		D3DAppISetErrorString("%s's format not recognized.\n", lpName);
		return NULL;
	}
}

BOOL MarksLoadTexture(LPDIRECT3DRMDEVICE dev, LPSTR name, LPTEXTURESTRUCT lptexstruct, int transbits)
{
   LPDIRECTDRAWSURFACE  lpSrcTextureSurf = NULL;
   LPDIRECT3DTEXTURE lpSrcTexture = NULL;
   D3DTEXTUREHANDLE  TexHandle = INVALID_TEXTURE_HANDLE; 
   LPDIRECT3DDEVICE lpD3DDev = NULL;
   char filename[MAX_PATH];

	strcpy(filename, HDPath);
	strcat(filename, "\\");
	strcat(filename, name);

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
        goto generic_error;

    /*
	LastError = lpD3DDev->lpVtbl->EnumTextureFormats(lpD3DDev,
											EnumTextureFormatsCallback,
                                            (LPVOID)&format);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Enumeration of texture formats failed.\n%s",
                              D3DAppErrorToString(LastError));
        goto generic_error;
    }
	*/
   if ((transbits==4) && d3dappi.TranspTextureFormat.AlphaBPP && (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT))
   {
      lpSrcTextureSurf = LoadTextureIntoSurface(d3dappi.lpDD, filename,
	      &(d3dappi.TranspTextureFormat.ddsd), ((d3dappi.ThisDriver.Desc.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY) ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY), 4);
   }
   else
   {
      lpSrcTextureSurf = LoadTextureIntoSurface(d3dappi.lpDD, filename,
	      &(d3dappi.ThisTextureFormat.ddsd), ((d3dappi.ThisDriver.Desc.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY) ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY), transbits);
   }
	
	if(lpSrcTextureSurf == NULL)
        goto generic_error;

    LastError = lpSrcTextureSurf->lpVtbl->QueryInterface(lpSrcTextureSurf,
                                             &IID_IDirect3DTexture,
                                             (LPVOID*)&lpSrcTexture);
    if (LastError != DD_OK) 
    {
		D3DAppISetErrorString("Failed to obtain D3D texture interface for a source texture.\n%s", D3DAppErrorToString(LastError));
        goto generic_error;
	}

    LastError = lpSrcTexture->lpVtbl->GetHandle(lpSrcTexture,
                               lpD3DDev, &TexHandle);
    if (LastError != DD_OK) 
        goto generic_error;
	
	if (TexHandle==INVALID_TEXTURE_HANDLE)
        goto generic_error;

	lptexstruct->lpSrcTextureSurf = lpSrcTextureSurf;
    lptexstruct->lpSrcTexture = lpSrcTexture;
    lptexstruct->hTex = TexHandle;

    RELEASE(lpD3DDev);
	return TRUE;

generic_error:
	BYDumpInfo("*************************");
	BYDumpInfo("Failed to load texture...");
	BYDumpInfo(name);
	BYDumpInfo("Error string is:");
	BYDumpInfo(D3DAppLastErrorString());

	BYDumpInfo("*************************");
//	MessageBox(NULL, "There is one ERROR in loading texture!", "DEBUG:", MB_OK);
    RELEASE(lpSrcTextureSurf);
    RELEASE(lpSrcTexture);
    RELEASE(lpD3DDev);
    return FALSE;
}

BOOL MyLoadTexture(LPDIRECT3DRMDEVICE dev, LPSTR name, LPTEXTURESTRUCT lptexstruct, int transbits)
{
   LPDIRECTDRAWSURFACE  lpSrcTextureSurf = NULL;
   LPDIRECT3DTEXTURE lpSrcTexture = NULL;
   D3DTEXTUREHANDLE  TexHandle = INVALID_TEXTURE_HANDLE; 
   LPDIRECT3DDEVICE lpD3DDev = NULL;
   char filename[MAX_PATH];

	strcpy(filename, BmpPath);
	strcat(filename, "\\");
	strcat(filename, name);

    dev->lpVtbl->GetDirect3DDevice(dev, &lpD3DDev);
    if (!lpD3DDev)
        goto generic_error;

    /*
	LastError = lpD3DDev->lpVtbl->EnumTextureFormats(lpD3DDev,
											EnumTextureFormatsCallback,
                                            (LPVOID)&format);
    if (LastError != DD_OK) {
        D3DAppISetErrorString("Enumeration of texture formats failed.\n%s",
                              D3DAppErrorToString(LastError));
        goto generic_error;
    }
	*/
   if ((transbits==4) && d3dappi.TranspTextureFormat.AlphaBPP && (d3dapprs.transparency == FANCY || d3dapprs.transparency == SEMIFANCY || d3dapprs.transparency == TRANSLUCENT))
   {
      lpSrcTextureSurf = LoadTextureIntoSurface(d3dappi.lpDD, filename,
	      &(d3dappi.TranspTextureFormat.ddsd), ((d3dappi.ThisDriver.Desc.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY) ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY), 4);
   }
   else
   {
      lpSrcTextureSurf = LoadTextureIntoSurface(d3dappi.lpDD, filename,
	      &(d3dappi.ThisTextureFormat.ddsd), ((d3dappi.ThisDriver.Desc.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY) ? DDSCAPS_VIDEOMEMORY : DDSCAPS_SYSTEMMEMORY), transbits);
   }

	if(lpSrcTextureSurf == NULL)
        goto generic_error;



    LastError = lpSrcTextureSurf->lpVtbl->QueryInterface(lpSrcTextureSurf,
                                             &IID_IDirect3DTexture,
                                             (LPVOID*)&lpSrcTexture);
    if (LastError != DD_OK) 
    {
		D3DAppISetErrorString("Failed to obtain D3D texture interface for a source texture.\n%s", D3DAppErrorToString(LastError));
        goto generic_error;
	}

    LastError = lpSrcTexture->lpVtbl->GetHandle(lpSrcTexture,
                               lpD3DDev, &TexHandle);
    if (LastError != DD_OK) 
        goto generic_error;
	
	if (TexHandle==INVALID_TEXTURE_HANDLE)
        goto generic_error;

	lptexstruct->lpSrcTextureSurf = lpSrcTextureSurf;
    lptexstruct->lpSrcTexture = lpSrcTexture;
    lptexstruct->hTex = TexHandle;

    RELEASE(lpD3DDev);
	return TRUE;

generic_error:
	BYDumpInfo("*************************");
	BYDumpInfo("Failed to load texture...");
	BYDumpInfo(name);
	BYDumpInfo("Error string is:");
	BYDumpInfo(D3DAppLastErrorString());

	BYDumpInfo("*************************");
//	MessageBox(NULL, "There is one ERROR in loading texture!", "DEBUG:", MB_OK);
    RELEASE(lpSrcTextureSurf);
    RELEASE(lpSrcTexture);
    RELEASE(lpD3DDev);
    return FALSE;
}


void ReleaseOneTexture(LPTEXTURESTRUCT lptexstruct)
{
	if((lptexstruct != NULL) || (lptexstruct->hTex != INVALID_TEXTURE_HANDLE))
	{
		RELEASE(lptexstruct->lpSrcTextureSurf);
		RELEASE(lptexstruct->lpSrcTexture);
		lptexstruct->hTex = INVALID_TEXTURE_HANDLE;
	}
	return;
}	


BOOL MyReplaceTexture(LPDIRECT3DRMDEVICE dev, LPSTR filename, LPTEXTURESTRUCT lptexstruct, int transbits)
{
	ReleaseOneTexture(lptexstruct);	
	return MyLoadTexture(dev, filename, lptexstruct, transbits);
}	
