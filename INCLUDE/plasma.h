#ifndef _PLASMA_H_
#define _PLASMA_H_

#include "spritlib.h"

typedef void (*HitHandler)(RLVector *Direction, int AttackAnimation);
extern void PlasmaCallBack(RLFrame frame, void *arg);
extern void ZappaCallBack(RLFrame frame, void *arg);

typedef struct plasma_data
{
   RLValue HowBig;         //What's the radius of the ball of death?
   int HowLong;            //How many frames will it exist on screen?
   int OnScreen;           //Is it on screen? 1=yes, 0=no.
   int WhatDamage;         //Will be put in when we keep track of damage.
   Psystem *plasm;         //needed to make the thing go away, as well as controlling the movement of the balls.
   RLFrame opponent;       //Who are we trying to kill?
   HitHandler HandleHit;   //What function do we call if we hit?
}PlasmaData;

typedef struct explosion_data
{
   int HowLong;            //How many frames will it exist on screen?
   int OnScreen;           //Is it on screen? 1=yes, 0=no.
   Psystem *plasm;         //needed to make the thing go away, as well as controlling the movement of the balls.
}ExplosionData;

//Unlike the plasma systems which I conceived as working for either the Robot or the monster,
//This is a purely monster thing.  Thus, I won't have the hithandler, or the opponent.
typedef struct zappa_data
{
   int HowLong;            //How many frames will it exist on screen?
   int OnScreen;           //Is it on screen? 1=yes, 0=no.
   int HasHit;             //Should I ignore the collision detection because the Robot is already going down?
   RLValue HowBig;         //What's the radius of the zucchini of death?
   RLVector FarEnd;        //Where's the far end of the zucchini of death?
   int WhatDamage;         //Will be put in when we keep track of damage.
   RLMesh zipper;          //Don't blame me for the name.  Spudde's the only one who understands this at all.
   CxSprite* zucchini;     // Blame Bruce for this name.  Spudde had nothing to do with it.
}ZappaData;


#endif