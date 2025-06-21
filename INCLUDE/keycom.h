//This function reconfigures the keyboard, from user input.  It doesn't work.
void ChangeKeyConfig();
//This function looks at the appropriate keys on the keyboard, and checks to see if they're down.
//It then translates that into InputInt.
void PollInput();
//These integers hold the current input.
extern volatile long int InputInt;
extern volatile long int InputInt2;
extern volatile long int InputIntDevNull;
//This function gets the keyboard ready to rock and roll.
void InitInputDevice();
//This function sets the keyboard back the way you liked it.
void ResetInputDevice();

#define PADobit       0
#define PADmbit       1
#define PADnbit       2
#define PADlbit       3
#define PADRupbit     4
#define PADRrightbit  5
#define PADRdownbit   6
#define PADRleftbit   7
#define PADkbit       8
#define PADibit       9
#define PADjbit       10
#define PADhbit       11
#define PADLupbit     12
#define PADLrightbit  13
#define PADLdownbit   14
#define PADLleftbit   15


#define PADLup     (1<<PADLupbit)
#define PADLdown   (1<<PADLdownbit)
#define PADLleft   (1<<PADLleftbit)
#define PADLright  (1<<PADLrightbit)
#define PADRup     (1<<PADRupbit)
#define PADRdown   (1<<PADRdownbit)
#define PADRleft   (1<<PADRleftbit)
#define PADRright  (1<<PADRrightbit)
#define PADi       (1<<PADibit)
#define PADj       (1<<PADjbit)
#define PADk       (1<<PADkbit)
#define PADl       (1<<PADlbit)
#define PADm       (1<<PADmbit)
#define PADn       (1<<PADnbit)
#define PADo       (1<<PADobit)
#define PADh       (1<<PADhbit)

#define COMMANDForwardbit 0
#define COMMANDBackbit 1
#define COMMANDLeftbit 2
#define COMMANDRightbit 3
#define COMMANDJumpbit 4
#define COMMANDCrouchbit 5
#define COMMANDHighAttackbit 6
#define COMMANDLowAttackbit 7
#define COMMANDWeakShiftbit 8
#define COMMANDMediumShiftbit 9
#define COMMANDStrongShiftbit 10
#define COMMANDDefenseShiftbit 11
#define COMMANDSelectbit 12
#define COMMANDStartbit 13
#define COMMANDShurikenbit 14
#define COMMANDPhotonCannonbit 15
#define COMMANDPlasmaBladesbit 16
#define COMMANDUltraBlastbit 17
#define COMMANDVisorBeambit 18
#define COMMANDJetLeftbit	19
#define COMMANDJetRightbit	20

#define COMMANDForward (1<<COMMANDForwardbit)
#define COMMANDBack (1<<COMMANDBackbit)
#define COMMANDLeft (1<<COMMANDLeftbit)
#define COMMANDRight (1<<COMMANDRightbit)
#define COMMANDJump (1<<COMMANDJumpbit)
#define COMMANDCrouch (1<<COMMANDCrouchbit)
#define COMMANDHighAttack (1<<COMMANDHighAttackbit)
#define COMMANDLowAttack (1<<COMMANDLowAttackbit)
#define COMMANDWeakShift (1<<COMMANDWeakShiftbit)
#define COMMANDMediumShift (1<<COMMANDMediumShiftbit)
#define COMMANDStrongShift (1<<COMMANDStrongShiftbit)
#define COMMANDDefenseShift (1<<COMMANDDefenseShiftbit)
#define COMMANDSelect (1<<COMMANDSelectbit)
#define COMMANDStart (1<<COMMANDStartbit)

#define COMMANDShuriken 	(1<<COMMANDShurikenbit)
#define COMMANDPhotonCannon (1<<COMMANDPhotonCannonbit)
#define COMMANDPlasmaBlades (1<<COMMANDPlasmaBladesbit)
#define COMMANDUltraBlast   (1<<COMMANDUltraBlastbit)
#define COMMANDVisorBeam    (1<<COMMANDVisorBeambit)
#define	COMMANDJetLeft		(1<<COMMANDJetLeftbit)
#define COMMANDJetRight		(1<<COMMANDJetRightbit)

#define COMMANDZapper 		(1<<COMMANDShurikenbit)
#define COMMANDSpecialOne	(1<<COMMANDPhotonCannonbit)
#define COMMANDSpecialTwo	(1<<COMMANDPlasmaBladesbit)

//#define COMMANDShuriken     (COMMANDHighAttack|COMMANDStrongShift)
//#define COMMANDPhotonCannon (COMMANDHighAttack|COMMANDWeakShift)
//#define COMMANDPlasmaBlades (COMMANDHighAttack|COMMANDMediumShift)
//#define COMMANDUltraBlast   (COMMANDLowAttack|COMMANDWeakShift)
//#define COMMANDVisorBeam    (COMMANDLowAttack)


