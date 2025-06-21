#ifndef _PSYSTEM_H_
#define _PSYSTEM_H_

#include "spritlib.h"
#define NumberOfSixShooters 6
#define NumberOfPeaShooters NumberOfSixShooters

#ifdef __cplusplus
extern "C" {
#endif

void makedust(Psystem** dust, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT  *lpdusttexturestruct);
void MakeExplosion(Psystem** explo, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera);
CxSprite* CreateZap(LPDIRECT3DRMFRAME parent);
CxSprite* CreateRobotZap(LPDIRECT3DRMFRAME parent, LPSTR ppmfile);
void CreateSonicShooter(Psystem** sixshooter, 
				LPDIRECT3DRMFRAME theframe, LPSTR ppmfile);
void CreateSixPeaAndCussinShooter(Psystem **sixshooter, 
				Psystem** peashooter, Psystem **cussin, 
				LPDIRECT3DRMFRAME theframe, LPSTR ppmfile);
void makeclouds(Psystem** cloud, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera, int numclouds);
void makeedges(Psystem** edge, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera);
void makefire(Psystem** fire, LPDIRECT3DRMFRAME theframe, 
			  LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT *lplpFireTexStruct);
void makesmoke(Psystem** smoke, LPDIRECT3DRMFRAME theframe, 
			   LPDIRECT3DRMFRAME camera, LPTEXTURESTRUCT *lplpFireTexStruct);
void MakeSplat(Psystem** splat, LPDIRECT3DRMFRAME theframe, 
				LPDIRECT3DRMFRAME camera);
void MakeSpiritSprite(Psystem** spirits, 
				LPDIRECT3DRMFRAME theframe, LPSTR  suffix);
void dustcloud(LPDIRECT3DRMFRAME dustmaker, void* arg, D3DVALUE delta);
#ifdef __cplusplus
};
#endif

#endif