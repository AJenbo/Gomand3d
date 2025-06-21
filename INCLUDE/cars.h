#ifndef _CARS_H_
#define _CARS_H_

#include "rl2d3d.h"

void MakeCars(void);
void LaunchAllBadCars(void);
void KillAllBadCars(void);
void KillAllGoodCars(void);
int AvoidBuildings(RLVector car, RLVector* force);

#endif