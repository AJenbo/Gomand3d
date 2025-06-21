#ifndef _BLDGBOOM_H_
#define _BLDGBOOM_H_

void InitConflagration();
void CowboyDeathMarch(building *DeadBuilding,RLVector *CollisionVector);
void Scorch(RLFrame frame, void* arg);
int CrumpleBuilding(GDPLIST* gdlist, RLVector* collision, RLValue scale, RLValue count);
void RestoreBuilding(GDPLIST *gdlist);
void FinishDestroyingBuilding(GDPLIST *gdlist, int *thisdamage);
void DestroyConflagration();

#endif