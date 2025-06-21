/*
$Header:   H:/pvcs/pvcsproj/gomand3d.prj/WRAPDATA.H_V   1.14   12 May 1997 13:23:56   Jeremiah  $

$Log:   H:/pvcs/pvcsproj/gomand3d.prj/WRAPDATA.H_V  $
 * 
 *    Rev 1.14   12 May 1997 13:23:56   Jeremiah
 * Added "STRETCHED" to window size
 * array.
 * 
 *    Rev 1.13   12 Mar 1997 14:30:08   JEREMIAH
 * Changed by Bo.
 * modified data to fix the timer refresh problem in letterbox case
 * 
 *    Rev 1.12   25 Feb 1997 15:15:42   BO
 * changed button 7 action to Shield for Sidewinder
 * 3D Pro joystick
 * 
 *    Rev 1.11   25 Feb 1997 11:10:16   BO
 * added 3 avis in avi file array
 * adjust Robot life and energy bar position
 * 
 *    Rev 1.10   14 Feb 1997 16:46:16   JEREMIAH
 * Changed by Bo.
 * - modified ActTable to add more actions to it.
 * - define joystick and game pad configuration for MS input devices
 * 
 * 
 *    Rev 1.9   10 Feb 1997 12:23:56   JEREMIAH
 * Changed by Bo.
 * - modified MIDFiles' definition, added 10 more midi file names. 
 * 
 *    Rev 1.8   05 Feb 1997 17:42:38   JEREMIAH
 * Changed by Bo.
 * added necessary data for mouse and joystick reconfiguration
 * 
 * 
 *    Rev 1.7   09 Jan 1997 14:57:40   BO
 * added new data definitions for mouse 
 * event handling.  Also modified a few 
 * data for new wrapper UI.
 * 
 *    Rev 1.6   07 Jan 1997 15:43:58   BO
 * added two more variables for screen selection
 * 
 *    Rev 1.5   07 Jan 1997 14:26:06   BO
 * modified coordinates for screen resolution
 * 
 *    Rev 1.4   07 Jan 1997 09:30:54   BO
 * modified and added new data for netplay
 * 
 *    Rev 1.3   17 Dec 1996 11:22:42   JEREMIAH
 * Changed by Bo.  Added support for 512
 * mode.
 * 
 *    Rev 1.2   13 Nov 1996 10:01:28   BO
 * add mouse action definitions in the game
 * 
 *    Rev 1.1   Nov 01 1996 12:42:36   JEREMIAH
 * Changed by Bo.  Added new data for 
 * user interface display.  Cleaned up 
 * unused data.
*/
typedef struct o1mapcor 
{
	int   des[2];
	RECT  src;
} O1MAPCOR;

O1MAPCOR MappingCor = 
{
	0,0, 0,0,640,480
};

O1MAPCOR Map640x480 = 
{
	0,0, 0,0,640,480
};

O1MAPCOR Map512x384 = 
{
	0,0, 0,0,512,384
};

O1MAPCOR Map320x240 = 
{
	0,0, 0,0,320,240
};

typedef struct o2map1 
{
	int   titem;
	int   des[6][2];
	RECT  src[6];
	BOOL  flag[6];
} O2MAP1;

O2MAP1 O2MainMenuMap =
{
	6, 
	204,32, // des - game play
	463,29, // des - movie
	0,224,  // des - training
	110,410, // des - netplay - start
	110,410, // des - netplay - join
	28,11,  // des - option
	0,0,247,153,     // src - game play 
	0,154,176,286,   // src - movie
	177,154,479,329, // src - training
	0,331,138,390,   // src - netplay - start
	139,331,277,390,   // src - netplay - join
	248,0,412,130,   // src - option
	1,0,0,0,0,0      // flag
};

typedef struct o2map5 
{
	int   titem;
	int   tstring;
	int   des[12][2];
	RECT  src[12];
	BOOL  flag[12];
	short tpos[10][4];
	COLORREF tcol[10];
} O2MAP5;

O2MAP5 O2LoadMenuMap =
{
	12,10,
	76,33,76,98,76,164,76,229,76,295,242,65,
	242,131,242,198,242,262,242,328,285,12,285,12,

	0,20,320,51,0,52,319,83,0,84,319,114,
	0,115,320,146,0,147,319,178,0,179,318,210,
	0,211,318,241,0,242,318,272,0,273,318,304,
	0,305,318,336,0,0,51,19,52,0,99,19,

	1,0,0,0,0,0,0,0,0,0,0,0,

	138, 40,  TA_LEFT, 0, 138, 107, TA_LEFT, 0, 
	138, 172, TA_LEFT, 0, 138, 237, TA_LEFT, 0,
	138, 303, TA_LEFT, 0, 261, 73, TA_LEFT,  0,
	261, 137, TA_LEFT, 0, 261, 204, TA_LEFT, 0, 
	261, 269, TA_LEFT, 0, 261, 336, TA_LEFT, 0,

	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255),
	RGB(255, 255, 255)
};

RECT MsLoadNSaveMenuRect[10] =
{
	{121,  35, 392,  58},
	{121, 100, 392, 124},
	{121, 167, 392, 189},
	{121, 231, 392, 255},
	{121, 298, 392, 320},
	{245,  67, 516,  91},
	{245, 134, 516, 157},
	{245, 200, 516, 223},
	{245, 265, 516, 289},
	{245, 331, 516, 354}
};

RECT MsMainMenuRect[6] =
{
	{237, 0, 396, 52},    // char
	{565, 26, 627, 71},   // movie
	{238, 310, 302, 362}, // training
	{94,404,186,474},     // netplay: start
	{187,404,266,474},    // netplay: join
	{105, 0, 157, 48}     // option
};

RECT MsNetMenuRect[4] =
{
	{300,405,420,420},
	{300,422,420,435},
	{300,437,420,450},
	{300,452,420,465}
};

RECT MsMovieMenuRect[8] =
{
	{365,  98, 513, 124},
	{365, 130, 513, 154},
	{365, 160, 513, 184},
	{365, 190, 513, 214},
	{365, 220, 513, 244},
	{365, 250, 513, 274},
	{365, 280, 513, 304},
	{365, 310, 513, 334}
};  

typedef struct o2map3 
{
	int   titem;
	int   des[8][2];
	RECT  src[8];
	BOOL  flag[8];
} O2MAP3;

O2MAP3 O2MovieMenuMap =
{
	8, 
	367,99,367,129,367,159,367,189,367,219,367,249,367,279,367,309, 
	0,0,147,28,0,30,147,58,0,60,147,88,0,90,147,118,
	0,120,147,148,0,150,147,178,0,180,147,208,0,210,147,238,
	1,0,0,0,0,0,0,0 // 640x400
};

RECT MsCharMenuRect[5] =
{
	{17, 0, 129, 240},
	{130, 0, 239, 240},
	{240, 0, 359, 240},
	{360, 0, 471, 240},
	{472, 0, 598, 240}
};

RECT OptionMenuRect[17] =
{
	{97,67,147,120},
	{154,70,202,119},
	{208,73,236,115},

	{338,62,360,94},
	{364,62,378,96},
	{381,60,418,100},
	{421,56,455,105},
	{461,50,556,114},

	{310,179,394,186},
	{310,194,394,203},

	{81,249,181,309},
	{238,254,294,303},
	{337,259,388,301},

	{351,324,394,358},
	{434,326,540,366},

	{94,406,265,438}, // screen resolution  1/8/96
	{94,446,265,475}  // window size        1/8/96
};

RECT ModeSizeAreas[6] =
{
	{300,405,449,420},
	{450,405,545,420},
	{300,422,449,435},
	{450,422,545,435},
	{300,437,449,450},
	{450,437,545,450}
};

char MethodTable[9][9] =
{
    'A', 'B', 'B', 'C', 'C', 'C', 'C', 'F', 'G',
    'B', 'A', 'B', 'C', 'C', 'C', 'C', 'F', 'G',
    'B', 'B', 'A', 'C', 'C', 'C', 'C', 'F', 'G',
    'B', 'B', 'B', 'D', 'C', 'C', 'C', 'H', 'I',
    'B', 'B', 'B', 'C', 'D', 'C', 'C', 'J', 'K',
    'B', 'B', 'B', 'C', 'C', 'E', 'C', 'F', 'G',
    'B', 'B', 'B', 'C', 'C', 'C', 'E', 'F', 'G',
	 'L', 'L', 'L', 'P', 'Q', 'L', 'L', 'E', 'N',
	 'M', 'M', 'M', 'R', 'S', 'M', 'M', 'O', 'E'
};

typedef struct o2map2 
{
	int   titem;
	int   des[5][2];
	RECT  src[5];
	BOOL  flag[5];
} O2MAP2;


typedef struct o2map4 
{
	int   titem;
	int   des[21][2];
	RECT  src[21];
	BOOL  oflag[21];
	BOOL  iflag[21];
} O2MAP4;


typedef struct o3map1 
{
	int  titem;
	int  des[5][2];
	RECT src[5];
	BOOL flag[5];
} O3MAP1;


O2MAP2 O2CharMenuMap =
{
	5, 
	17,0,130,0,240,0,360,0,472,0, 
	350,0,463,260, 0,0,109,260, 110,0,230,260,
	464, 0, 577, 260, 231, 0, 349, 260,
	0,0,0,0,0 // 640x400
};

O3MAP1 O3CharMenuMap =
{
	5,
	88,287,88,287,88,287,88,287,88,287,
	0,303,462,403,0,0,462,100,0,101,462,201,
	0,404,462,504,0,202,462,302,
	0,0,0,0,0	
};


O2MAP4 O2OptionMenuMap =
{               
	21, 
	76,65,76,65,76,65,        337,44,329,44,329,44,329,44,341,44,
	205,148,205,148,
	80,245, 80,245, 80,245,   347,319,431,319,
	388,178,388,194,388,178,388,194, 

	//112,417,112,417, // screen & resolution
	99,411,121,441,    // screen resolution & screen size

	0,0,163,63,  164,0,327,60,  328,0,491,54, 
	0,366,224,420, 0,64,236,125, 0,204,238,270, 0,128,236,203, 225,366,447,442,
	239,128,590,171, 239,172,590,231, 283,231,590,301, 283,302,590,365,
	237,68,547,127, 0,271,208,312, 0,313,125,365, 328,55,334,66,
	335,55,341,66, 342,55,348,66, 349,55,355,66,   // 640x400
    //448,367,581,412, 448,413,581,458, // screen & resolution
	0,421,162,450, 128,314,245,342,     // screen resolution & screen size

	0,1,0, 0,0,0,0,0, 0,0, 0,0,0, 0,0, 1,1, 0,0,
	0,0, // screen & resolution
	0,1,0, 0,0,1,0,0, 0,0, 1,0,0, 0,0, 0,0, 0,0,
	1,0  // screen & resolution
};

char AVIFiles[12][11] = 
{
	"INTRO0.AVI",
	"INTRO1.AVI",
	"INTRO2.AVI",
	"INTRO3.AVI",
	"INTRO4.AVI",
	"INTRO5.AVI",
	"INTRO6.AVI",
	"CREDIT.AVI",
	"ENDING.AVI",
	"HWIN.AVI  ",  // 9
	"EWIN.AVI  ",
	"DEFEAT.AVI"
};

char MIDFiles[20][12] = 
{
	"LEVEL1.MID ",	// 0. 
	"LEVEL2.MID ", // 1.
	"LEVEL3.MID ", // 2.
	"LEVEL4.MID ", // 3.
	"LEVEL5.MID ", // 4.
	"LEVEL6.MID ", // 5.
	"TRAIN0.MID ", // 6.
	"WRAPER.MID ", // 7.
	"ONRWINX.MID",	// 8. honor MIDI for end-of-game
	"MTWINX.MID ",	// 9. empty MIDI for end-of-game
	"LOSERX.MID ",	// 10. loser MIDI for end-of-game
	"ONRWIN0.MID", // 11. honor MIDI for trainer
	"ONRWIN1.MID",	// 12. honor MIDI for level 1
	"ONRWIN2.MID", // 13.
	"ONRWIN3.MID", // 14.
	"ONRWIN4.MID", // 15.
	"ONRWIN5.MID", // 16.
	"ONRWIN6.MID", // 17. honor MIDI for level 6
	"MTWIN.MID  ",	// 18. empty MIDI for each level
	"LOSER.MID  "  // 19. loser MIDI for each level
};

typedef struct kbrddef
{
	int   tstring;
	DWORD defaultkey[17];
	DWORD currentkey[17];
	char  displaykey[17][2];
	short kpos[17][2];
} KBRDDEF;

KBRDDEF KeyData =
{
	17,

	'A', 'J', 'K', 'H', 'S',
	'D', 188, 190, 'N', 'F',  // 188 = '<', 190 = '>'
	'G', 'Z', 'B', 'C', 'V',
	'X', '?',

	'A', 'J', 'K', 'H', 'S',
	'D', 188, 190, 'N', 'F',  // 188 = '<', 190 = '>'
	'G', 'Z', 'B', 'C', 'V',
	'X', '?', 

	0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 
	0,0, 0,0, 0,0,
	0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 

	88, 131, 153, 131, 212, 131, 270, 131, 341, 131, 407, 131, 485, 131, 549, 131,
	250, 252, 326, 252, 394, 252,
	97, 371, 187, 371, 278, 371, 376, 371, 455, 371, 542, 371
};

#define DUMPITEM 5

typedef struct o3map2 
{
	int   titem;
	int   des[DUMPITEM][2];
	RECT  src[DUMPITEM];
	BOOL  flag[DUMPITEM];
} O3MAP2;

O3MAP2 Dump320 =
{
	DUMPITEM,
   77, 1,    // power and radar
   79, 2,    // Robot power bar
   79, 8,    // Robot weapon bar
   189, 2,   // mnst power bar
   189, 8,   // mnst weapon bar
   //0, 161,   // subtitle black area
   //109, 161, // subtitle black area
   //218, 161, // subtitle black area

   0, 42, 166, 87,   // power bar and radar
   0, 91, 52, 92,    // Robot green power bar
   0, 91, 52, 92,    // Robot green weapon bar
   0, 93, 52, 94,    // mnst red power bar
   0, 93, 52, 94,    // mnst red weapon bar
   //0, 100, 109, 130, // subtitle black area
   //0, 100, 109, 130, // subtitle black area
   //0, 100, 102, 130, // subtitle black area
	1,1,1,1,1//,1,1,1      
};

#define DUMPITEM512 5
#define DUMPITEM640 5

typedef struct o3map3 
{
	int   titem;
	int   des[DUMPITEM640][2];
	RECT  src[DUMPITEM640];
	BOOL  flag[DUMPITEM640];
} O3MAP3;

O3MAP3 Dump640 =
{
	DUMPITEM640,
	273,0,	  // radar
   90, 16,   //110, 16,   // Robot power bar
   90, 33,   //110, 33,   // Robot weapon bar
   399, 16,   // mnst power bar
   399, 33,   // mnst weapon bar

	53,138,136,216,
	0,43,105,46,
	0,43,105,46,
	0,47,105,50,
	0,47,105,50,
	1,1,1,1,1
};

O3MAP3 Dump512 =
{
	DUMPITEM512,
	214,0,	 // radar
   88, 17,   // Robot power bar
   88, 32,   // Robot weapon bar
   318,17,   // mnst power bar
   318,32,   // mnst weapon bar

	53,138,136,216,
	0,43,85,46,
	0,43,85,46,
	0,47,85,50,
	0,47,85,50,
	1,1,1,1,1
};

//
#define RPITEM640 7

typedef struct  
{
	int   titem;
	int   des[RPITEM640][2];
	RECT  src[RPITEM640];
	BOOL  flag[RPITEM640];
	short face[RPITEM640];
} RP640;


RP640 rp640 =
{
	RPITEM640,
   110, 16,   // Robot power bar (black)
   110, 33,   // Robot weapon bar (black)
   399, 16,   // mnst power bar (black)
   399, 33,   // mnst weapon bar (black)
	546, 6,    // population bgd des
	3,   3,    // timer bgd des, original is for subtitle bgd des: 154, 429
	268, 0,    // radar bdg des

	0,51,105,54,     // black
	0,51,105,54,     // black
	0,51,105,54,     // black
	0,51,105,54,     // black
	546,6,639,62,    // population bgd src
	3,4,65,46,       // subtitle bgd src 154,429,486,471,
	268,0,360,96,

	1,1,1,1,1,1,1,   // turn on/off switch
	2,2,2,2,0,0,0    // overlay index
};

RP640 rp512 =
{
	RPITEM640,
   88, 17,   // Robot power bar (black)
   88, 32,   // Robot weapon bar (black)
   318,17,   // mnst power bar (black)
   318,32,   // mnst weapon bar (black)
	10, 1,    // population bgd des
	1,1,      // timer. subtitle bgd des 122,343,  
	214,0,    // radar bdg des

	0,51,85,54,     // black
	0,51,85,54,     // black
	0,51,85,54,     // black
	0,51,85,54,     // black
	10,1,50,20,     // population bgd src
	1,1,52,37,      // timer. subtitle bgd src122,343,390,377, 
	214,0,297,83,

	1,1,1,1,1,1,1,   // turn on/off switch
	2,2,2,2,0,0,0    // overlay index
};

//
// The portion below can be used once the ALT-TAB problem
// for 320 mode is solved.  
/*
#define RPITEM320 3

typedef struct  
{
	int   titem;
	int   des[RPITEM320][2];
	RECT  src[RPITEM320];
	BOOL  flag[RPITEM320];
	short face[RPITEM320];
} RP320;

RP320 rp320 =
{
	RPITEM320,
	0,0,           // timer bgd des
	255,0,         // population bgd des
	0,192,         // subtitle

	0,0,65,17,     // timer bgd src
	255,0,319,17,  // population bgd src
	0,192,320,233, // subtitle bgd src

	1,1,1,         // turn on/off switch
	0,0,0          // overlay index 
}; */

// But, right now I have to use a stupid way to
// solve the ALT_TAB problem as follows:
#define RPITEM320 4

typedef struct  
{
	int   titem;
	int   des[RPITEM320][2];
	RECT  src[RPITEM320];
	BOOL  flag[RPITEM320];
	short face[RPITEM320];
} RP320;

RP320 rp320_1 =
{
	RPITEM320,
	0,0,            
	0,56,         
	243,56,         
   0,187,

	0,0,320,55,      
	0,56,75,186,
	243,56,320,186,
	0,187,320,240,

	1,1,1,1,         
	0,0,0,0       
};  

RP320 rp320_2 =
{
	RPITEM320,
	0,0,
	0,56,
	271,56,
	0,187,

	0,0,320,55,
	0,56,45,186,
	271,56,320,186,
	0,187,320,240,

	1,1,1,1,
	0,0,0,0
};

RP320 rp320_3 =
{
	RPITEM320,
	0,0,
	0,187,
	0,0,
	0,0,

	0,0,320,55,
	0,187,320,240,
	0,0,1,1,
	0,0,1,1,

	1,1,1,1,
	0,0,0,0
};

//
#define TOTAL_REFRESH_AREA 7
// [refer video mode][total refresh area]
// video mode: 0 = debug mode, 1 = 640x480, 2 = 320x240
//RECT GameUIRefreshCoordinates[3][TOTAL_REFRESH_AREA] =
RECT ra[4][TOTAL_REFRESH_AREA] =
{
   // debug mode refresh area
   0, 0, 100, 50,   // timer
   500, 0, 600, 50, // population
   0, 350, 639, 399, // subtitle
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
   // 640x480 mode refresh area
   0, 0, 100, 50,   // timer
   500, 0, 600, 50, // population
   0, 440, 639, 475, // subtitle
	110, 16, 216, 20, // Robot life bar
	110, 33, 216, 37, // Robot engy bar
   399, 16, 505, 20, // mnst life bar
   399, 33, 505, 37, // mnst engy bar

   // 320x240 mode refresh area
   0, 0, 50, 20,     // timer
   280, 0, 319, 20,  // population
   0, 200, 319, 239, // subtitle
   79, 2, 132, 4,    // Robot power bar
   79, 8, 132, 10,   // Robot weapon bar
   189, 2, 242, 4,   // mnst power bar
   189, 8, 242, 10,  // mnst weapon bar
	// 512x384 mode refresh area
	10,1,50,20,			// timer
	450,1,500,20,
	122,343,390,377,  // subtitle
   88,17,173,20,     // Robot power bar (black)
   88,32,173,35,     // Robot weapon bar (black)
   318,17,403,20,    // mnst power bar (black)
   318,32,403,35     // mnst weapon bar (black)
};

long int MsActions[6] =
{
   (COMMANDLeft),
//   (COMMANDForward|COMMANDMediumShift), // S=4, run
   (COMMANDForward),  
   (COMMANDRight),
   (COMMANDBack),
   (COMMANDVisorBeam),
   (COMMANDForward|COMMANDStrongShift)
};

RECT ani_cursor[7] =
{
	0,0,15,15,
	11,0,20,10,
	21,0,30,10,
	31,0,40,10,
	41,0,50,10,
	51,0,60,10,
	61,0,70,10
};

char net_cntion[5][14] =
{
	"LOCAL        ",
	"MODEM CONNECT",
	"WINSOCK IPX  ",
	"INTERNET     ",
	"SERIAL       "
};

short valid_cntion[10];
short curt_cntion;
short total_cntion;
BOOL bInNetplayMenu=FALSE;

char video_modes[6][11] =
{
	"640x480x16",
	"640x480x8 ",
	"512x384x16",
	"512x384x8 ",
	"320x240x16",
	"320x240x8 "
};

short	total_modes;
short	current_mode;
short tpmode, tpsize;
short inner_mode[6];
short	valid_mode[6];
BOOL bInVModeMenu=FALSE;

char window_sizes[][12] =
{
	"SMALL      ",
	"MEDIUM     ",
	"LETTERBOX  ",
	"FULL SCREEN",
   "STRETCHED  "
};

short current_size;
BOOL bInWSize=FALSE;
//
short	total_joycfg;
short total_mscfg;
short	current_joycfg;
short current_mscfg;
short tpjoycfg, tpmscfg;

char CfgString[10][17] =
{
	"Configuration 1 ",
	"Configuration 2 ",
	"Configuration 3 ",
	"Configuration 4 ",
	"Configuration 5 ",
	"Configuration 6 ",
	"Configuration 7 ",
	"Configuration 8 ",
	"Configuration 9 ",
	"Configuration 10"
};

char ActString[12][14] =
{
	"Turn left    ",
	"Walk Forward ",
	"Turn Right   ",
	"Walk Backward",
	"Fly          ",	// 4
	"Jump         ",	// 5
	"Fire         ",	// 6
	"Run          ",	// 7
	"Homer        ",	// 8
	"X Blaster    ",	// 9
	"C Blaster    ",	// 10
	"Pea Shooter  ",  // 11
};

#define TOTALCMD 18

long int ActTable[TOTALCMD] =
{
	(COMMANDLeft),                           // 0  = turn left        
	(COMMANDForward),                        // 1  = turn forward
	(COMMANDRight),                          // 2  = turn right
	(COMMANDBack),                           // 3  = turn back
   (COMMANDForward|COMMANDStrongShift),     // 4  = D key = fly
	(COMMANDJump),			                    // 5  = F key = jump
   (COMMANDHighAttack|COMMANDDefenseShift), // 6  = N key = shield
   (COMMANDForward|COMMANDMediumShift),     // 7  = D key = run
	(COMMANDShuriken),	                    // 8  = B key
	(COMMANDUltraBlast),	                    // 9  = X key 
	(COMMANDPhotonCannon),	                 // 10 = C key 
   (COMMANDVisorBeam),	                    // 11 = Z key = visor beam = pea shooter 
   (COMMANDCrouch),                         // 12 = G key = Crouch
	(COMMANDPlasmaBlades),                   // 13 = V key = plasma blade
   (COMMANDJetLeft),								  // 14 = '<' key = thrust left
   (COMMANDJetRight),                       // 15 = '>' key = thrust right
   (COMMANDBack|COMMANDStrongShift),        // 16 = H key = thrust back
	0                                        // TOTALCMD = nothing
};

// Joy8btnConfig is defined for Sidewinder3d Pro joystick only.
// It defines an array which value point to the Action Table
// and which index is in such order as:
// rleft, forward, rright, backward, btn1, btn2, btn3, btn4, 
// btn5, btn6, btn7, btn8, thrust left, thrust right, run, fly
short Joy8btnConfig[1][17] =
{
	0,1,2,3, 11,10,5,12,  8,9,6,13,
	14,15,7,4,6 
};

// Joy10btnConfig is an array of index to the JoyActString. It
// defines the actions for SideWinder Game Pad.  
// The movement index are:
// dp(left, forward, right, backward), A, B, C, X, Y, Z, 
// left btn, right btn, start, M, A+B, B+C, dp left+Z, dp right+Z
short Joy10btnConfig[1][19] =
{
	// Note! I have no definition for the START button, so right now I just 
	// put TOTALCMD for that.  ActTable[TOTALCMD] = 0 = nothing!
	// However, M button is actually defined as a function combination key
	0,1,2,3, 11,8,10,  12,5,6, 7,4,TOTALCMD,TOTALCMD, 
	13, // A+B  14
	9,  // B+C
	14, // dp left  = '<'
	15, // dp right = '>'
	16  // dp back  = thrust back 
};

// Joy2btnConfig is an array of index to the JoyActString
// joystick movement index:
// left, forward, right, backward, btn1, btn2
short Joy2btnConfig[10][6] =
{
	0,1,2,3,4,11,
	0,1,2,3,4,8,
	0,1,2,3,4,9,
	0,1,2,3,4,10,
	0,1,2,3,4,5,
	0,1,2,3,7,11,
	0,1,2,3,7,8,
	0,1,2,3,7,9,
	0,1,2,3,7,10,
	0,1,2,3,7,5
};

short Joy4btnConfig[3][8] =
{
	0,1,2,3,4,5,11,8,
	0,1,2,3,4,5,11,9,
	0,1,2,3,4,5,11,10
};

short JoyCfgPos[8][2] =
{
	470,254,
	40,304,
	130,105,  // btn1 for 2btn joystk
	430,105,  // btn2 for 2btn joystk
	128,238,  // btn1 for 4btn joystk
	426,238,  // btn2
	128,276,  // btn3
	426,276,  // btn4
};

short MsConfig[10][6] =
{
	0,1,2,3,4,11,
	0,1,2,3,4,8,
	0,1,2,3,4,9,
	0,1,2,3,4,10,
	0,1,2,3,4,5,
	0,1,2,3,7,11,
	0,1,2,3,7,8,
	0,1,2,3,7,9,
	0,1,2,3,7,10,
	0,1,2,3,7,5
};

short MsCfgPos[6][2] =
{
	300, 60,
	300, 80,
	300, 100,
	300, 120,
	134, 114,
	431, 114
};