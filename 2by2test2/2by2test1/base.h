#ifndef BASE
#define BASE

enum MOVE { D = 0, D1, D2, R, R1, R2, F, F1, F2 };

// pos value can only be 1,2,3,4,5,6,7,8;
// pos & ori index 1,2,3,4,5,6,7,8, is valid, 0 is idle, 9 is '\0'
// ori value can only be 0,1,2, they represent '0', '+', '-',
struct snapshot
{
	char pos[10];
	char ori[10];
	MOVE move;
	int level;
};

// for human friendly IO 
// pos and ori index is 0,1,2,3,4,5,6,7, different from MOVE
struct friendly_state
{
	char pos[8][4];
	char ori[8];
};

#endif