#define __production__
#ifdef __psx__

#ifdef __production__
#define __cd__ 1
#define CD
#define RES_PATH "\\"
#define RES_PATH_LENGTH 1
#else   // production
#define RES_PATH "sim:\\goman\\respsx\\"
#define RES_PATH_LENGTH 18
#endif  // production

#else   // __psx__

//#define RES_PATH "\\goman\\respc\\"
#define RES_PATH ""
#define RES_PATH_LENGTH 1

#endif  // __psx__

#define _DEMO_ 1
//#define PrintMemData
