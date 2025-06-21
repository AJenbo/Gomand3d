#ifdef MINIWIN
#include "miniwin/d3d.h"
#include "miniwin/direct.h"
#include "miniwin/d3drm.h"
#else
#include <d3d.h>
#include <direct.h>
#include <d3drmwin.h>
#endif
#include "d3dmacs.h"

void MultiplyMatrices(D3DRMMATRIX4D M1, D3DRMMATRIX4D M2, D3DRMMATRIX4D Result)
{
   {
      {
         Result[0][0] = D3DVAL(0.0);
         {
            Result[0][0] += M1[0][0] * M2[0][0];
            Result[0][0] += M1[0][1] * M2[1][0];
            Result[0][0] += M1[0][2] * M2[2][0];
            Result[0][0] += M1[0][3] * M2[3][0];
         }
      }
      {
         Result[0][1] = D3DVAL(0.0);
         {
            Result[0][1] += M1[0][0] * M2[0][1];
            Result[0][1] += M1[0][1] * M2[1][1];
            Result[0][1] += M1[0][2] * M2[2][1];
            Result[0][1] += M1[0][3] * M2[3][1];
         }
      }
      {
         Result[0][2] = D3DVAL(0.0);
         {
            Result[0][2] += M1[0][0] * M2[0][2];
            Result[0][2] += M1[0][1] * M2[1][2];
            Result[0][2] += M1[0][2] * M2[2][2];
            Result[0][2] += M1[0][3] * M2[3][2];
         }
      }
      {
         Result[0][3] = D3DVAL(0.0);
         {
            Result[0][3] += M1[0][0] * M2[0][3];
            Result[0][3] += M1[0][1] * M2[1][3];
            Result[0][3] += M1[0][2] * M2[2][3];
            Result[0][3] += M1[0][3] * M2[3][3];
         }
      }
   }
   {
      {
         Result[1][0] = D3DVAL(0.0);
         {
            Result[1][0] += M1[1][0] * M2[0][0];
            Result[1][0] += M1[1][1] * M2[1][0];
            Result[1][0] += M1[1][2] * M2[2][0];
            Result[1][0] += M1[1][3] * M2[3][0];
         }
      }
      {
         Result[1][1] = D3DVAL(0.0);
         {
            Result[1][1] += M1[1][0] * M2[0][1];
            Result[1][1] += M1[1][1] * M2[1][1];
            Result[1][1] += M1[1][2] * M2[2][1];
            Result[1][1] += M1[1][3] * M2[3][1];
         }
      }
      {
         Result[1][2] = D3DVAL(0.0);
         {
            Result[1][2] += M1[1][0] * M2[0][2];
            Result[1][2] += M1[1][1] * M2[1][2];
            Result[1][2] += M1[1][2] * M2[2][2];
            Result[1][2] += M1[1][3] * M2[3][2];
         }
      }
      {
         Result[1][3] = D3DVAL(0.0);
         {
            Result[1][3] += M1[1][0] * M2[0][3];
            Result[1][3] += M1[1][1] * M2[1][3];
            Result[1][3] += M1[1][2] * M2[2][3];
            Result[1][3] += M1[1][3] * M2[3][3];
         }
      }
   }
   {
      {
         Result[2][0] = D3DVAL(0.0);
         {
            Result[2][0] += M1[2][0] * M2[0][0];
            Result[2][0] += M1[2][1] * M2[1][0];
            Result[2][0] += M1[2][2] * M2[2][0];
            Result[2][0] += M1[2][3] * M2[3][0];
         }
      }
      {
         Result[2][1] = D3DVAL(0.0);
         {
            Result[2][1] += M1[2][0] * M2[0][1];
            Result[2][1] += M1[2][1] * M2[1][1];
            Result[2][1] += M1[2][2] * M2[2][1];
            Result[2][1] += M1[2][3] * M2[3][1];
         }
      }
      {
         Result[2][2] = D3DVAL(0.0);
         {
            Result[2][2] += M1[2][0] * M2[0][2];
            Result[2][2] += M1[2][1] * M2[1][2];
            Result[2][2] += M1[2][2] * M2[2][2];
            Result[2][2] += M1[2][3] * M2[3][2];
         }
      }
      {
         Result[2][3] = D3DVAL(0.0);
         {
            Result[2][3] += M1[2][0] * M2[0][3];
            Result[2][3] += M1[2][1] * M2[1][3];
            Result[2][3] += M1[2][2] * M2[2][3];
            Result[2][3] += M1[2][3] * M2[3][3];
         }
      }
   }
   {
      {
         Result[3][0] = D3DVAL(0.0);
         {
            Result[3][0] += M1[3][0] * M2[0][0];
            Result[3][0] += M1[3][1] * M2[1][0];
            Result[3][0] += M1[3][2] * M2[2][0];
            Result[3][0] += M1[3][3] * M2[3][0];
         }
      }
      {
         Result[3][1] = D3DVAL(0.0);
         {
            Result[3][1] += M1[3][0] * M2[0][1];
            Result[3][1] += M1[3][1] * M2[1][1];
            Result[3][1] += M1[3][2] * M2[2][1];
            Result[3][1] += M1[3][3] * M2[3][1];
         }
      }
      {
         Result[3][2] = D3DVAL(0.0);
         {
            Result[3][2] += M1[3][0] * M2[0][2];
            Result[3][2] += M1[3][1] * M2[1][2];
            Result[3][2] += M1[3][2] * M2[2][2];
            Result[3][2] += M1[3][3] * M2[3][2];
         }
      }
      {
         Result[3][3] = D3DVAL(0.0);
         {
            Result[3][3] += M1[3][0] * M2[0][3];
            Result[3][3] += M1[3][1] * M2[1][3];
            Result[3][3] += M1[3][2] * M2[2][3];
            Result[3][3] += M1[3][3] * M2[3][3];
         }
      }
   }
   return;
}

void RecursivelyGetManyTransforms(LPDIRECT3DRMFRAME ThisFrame, D3DRMMATRIX4D TheLocalMatrix)
{
   D3DRMMATRIX4D TheTrulyLocalMatrix, TheDummyMatrix;
   LPDIRECT3DRMFRAME parent;
   LPDIRECT3DRMFRAME scene;

   ThisFrame->lpVtbl->GetParent(ThisFrame, &parent);
   ThisFrame->lpVtbl->GetScene(ThisFrame, &scene);
   
   if (parent==NULL)
   {
      int i,j;
      for(i=0;i<4;i++)
         for(j=0;j<4;j++)
            TheLocalMatrix[i][j]=(i==j?D3DVAL(1.0):D3DVAL(0.0));
      return;
   }
   if(parent==scene)
   {
      ThisFrame->lpVtbl->GetTransform(ThisFrame,TheLocalMatrix);
      return;
   }
   RecursivelyGetManyTransforms(parent,TheTrulyLocalMatrix);
   ThisFrame->lpVtbl->GetTransform(ThisFrame,TheDummyMatrix);
   MultiplyMatrices(TheDummyMatrix,TheTrulyLocalMatrix,TheLocalMatrix);
   return;

}
