#include "base.h"
#include "util.h"
#include "rotate.h"
#include <string.h>


static char clockwise(char c)
{
	return (c + 1) % 3;
}

static char counter_clockwise(char c)
{
	return (c + 2) % 3;
}

unsigned rotate_D(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[5];
	ss.pos[5] = ss.pos[8];
	ss.pos[8] = ss.pos[7];
	ss.pos[7] = ss.pos[6];
	ss.pos[6] = temp;

	temp = ss.ori[5];
	ss.ori[5] = ss.ori[8];
	ss.ori[8] = ss.ori[7];
	ss.ori[7] = ss.ori[6];
	ss.ori[6] = temp;
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, D);
}


unsigned rotate_D1(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[5];
	ss.pos[5] = ss.pos[6];
	ss.pos[6] = ss.pos[7];
	ss.pos[7] = ss.pos[8];
	ss.pos[8] = temp;

	temp = ss.ori[5];
	ss.ori[5] = ss.ori[6];
	ss.ori[6] = ss.ori[7];
	ss.ori[7] = ss.ori[8];
	ss.ori[8] = temp;
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, D1);
}


unsigned rotate_D2(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[5];
	ss.pos[5] = ss.pos[7];
	ss.pos[7] = temp;

	temp = ss.pos[6];
	ss.pos[6] = ss.pos[8];
	ss.pos[8] = temp;

	temp = ss.ori[5];
	ss.ori[5] = ss.ori[7];
	ss.ori[7] = temp;

	temp = ss.ori[6];
	ss.ori[6] = ss.ori[8];
	ss.ori[8] = temp;

	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, D2);
}

unsigned rotate_R(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[3];
	ss.pos[3] = ss.pos[7];
	ss.pos[7] = ss.pos[8];
	ss.pos[8] = ss.pos[4];
	ss.pos[4] = temp;

	temp = ss.ori[3];
	ss.ori[3] = clockwise(ss.ori[7]);
	ss.ori[7] = counter_clockwise(ss.ori[8]);
	ss.ori[8] = clockwise(ss.ori[4]);
	ss.ori[4] = counter_clockwise(temp);
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, R);
}


unsigned rotate_R1(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[3];
	ss.pos[3] = ss.pos[4];
	ss.pos[4] = ss.pos[8];
	ss.pos[8] = ss.pos[7];
	ss.pos[7] = temp;

	temp = ss.ori[3];
	ss.ori[3] = clockwise(ss.ori[4]);
	ss.ori[4] = counter_clockwise(ss.ori[8]);
	ss.ori[8] = clockwise(ss.ori[7]);
	ss.ori[7] = counter_clockwise(temp);
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, R1);
}

unsigned rotate_R2(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[3];
	ss.pos[3] = ss.pos[8];
	ss.pos[8] = temp;

	temp = ss.pos[4];
	ss.pos[4] = ss.pos[7];
	ss.pos[7] = temp;

	temp = ss.ori[3];
	ss.ori[3] = ss.ori[8];
	ss.ori[8] = temp;

	temp = ss.ori[4];
	ss.ori[4] = ss.ori[7];
	ss.ori[7] = temp;

	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, R2);
}


unsigned rotate_F(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[2];
	ss.pos[2] = ss.pos[6];
	ss.pos[6] = ss.pos[7];
	ss.pos[7] = ss.pos[3];
	ss.pos[3] = temp;

	temp = ss.ori[2];
	ss.ori[2] = clockwise(ss.ori[6]);
	ss.ori[6] = counter_clockwise(ss.ori[7]);
	ss.ori[7] = clockwise(ss.ori[3]);
	ss.ori[3] = counter_clockwise(temp);
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, F);
}

unsigned rotate_F1(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[2];
	ss.pos[2] = ss.pos[3];
	ss.pos[3] = ss.pos[7];
	ss.pos[7] = ss.pos[6];
	ss.pos[6] = temp;

	temp = ss.ori[2];
	ss.ori[2] = clockwise(ss.ori[3]);
	ss.ori[3] = counter_clockwise(ss.ori[7]);
	ss.ori[7] = clockwise(ss.ori[6]);
	ss.ori[6] = counter_clockwise(temp);
	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, F1);
}


unsigned rotate_F2(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	char temp = ss.pos[3];
	ss.pos[3] = ss.pos[6];
	ss.pos[6] = temp;

	temp = ss.pos[2];
	ss.pos[2] = ss.pos[7];
	ss.pos[7] = temp;

	temp = ss.ori[3];
	ss.ori[3] = ss.ori[6];
	ss.ori[6] = temp;

	temp = ss.ori[2];
	ss.ori[2] = ss.ori[7];
	ss.ori[7] = temp;

	//printf("I am here 4. %s\n", a);   
	return get_stateN_from_snapshot(ss, F2);
}

set<unsigned> permute_one_step(unsigned sN)
{
	set<unsigned> collect;
	collect.insert(rotate_D(sN));
	collect.insert(rotate_D1(sN));
	collect.insert(rotate_D2(sN));
	collect.insert(rotate_R(sN));
	collect.insert(rotate_R1(sN));
	collect.insert(rotate_R2(sN));
	collect.insert(rotate_F(sN));
	collect.insert(rotate_F1(sN));
	collect.insert(rotate_F2(sN));
	return collect;
}

// convert retate number into unsigned rotation intrinsic
unsigned get_transform_from_move(MOVE m)
{
	switch (m)
	{
		case D:
			return rotate_D(0);
		case D1:
			return rotate_D1(0);
		case D2:
			return rotate_D2(0);
		case R:
			return rotate_R(0);
		case R1:
			return rotate_R1(0);
		case R2:
			return rotate_R2(0);
		case F:
			return rotate_F(0);
		case F1:
			return rotate_F1(0);
		case F2:
			return rotate_F2(0);
	}
	return 0;
}

// convert retate number into unsigned reverse rotation intrinsic
MOVE reserve_move(MOVE m)
{
	switch (m)
	{
	case D:
		return D1;
	case D1:
		return D;
	case D2:
		return D2;
	case R:
		return R1;
	case R1:
		return R;
	case R2:
		return R2;
	case F:
		return F1;
	case F1:
		return F;
	case F2:
		return F2;
	}
	return D;
}



