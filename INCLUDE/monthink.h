#ifndef _MONTHINK_H_
#define _MONTHINK_H_

void InitAE(void);
void Robotruminate(void);
void cogitate(void);
void ChooseStrategy(RLVector* HuntDirection, RLVector* RobotPosition, RLVector *MonsterPosition);
void ChooseTactic(int monstergoal, RLVector* HuntDirection, RLVector* RobotPosition, RLVector *MonsterPosition);
int RobotMoveInRange(RLVector* HuntDirection, RLVector* RobotDirection, int urgency);
	
#endif
