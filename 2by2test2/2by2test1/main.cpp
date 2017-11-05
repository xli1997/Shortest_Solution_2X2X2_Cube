#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "rotate.h"
#include "base.h"

#define POOL_SIZE  11022480 //3^7*7! = 2187 x 5040 = 11022480
#define TANK_LEVEL  7
#define COLLECT_DATA_NO_ANALYSIS 0
#define FAST_HASH_MAPPING 0

unsigned NORMAL;
struct snapshot normal = { { 0, 1, 2, 3, 4, 5, 6, 7, 8 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
char moveToStr[9][4] = { "D", "D'", "D2", "R", "R'", "R2", "F", "F'", "F2" };
char revMoveToStr[9][4] = { "D'", "D", "D2", "R'", "R", "R2", "F'", "F", "F2" };

char pool[POOL_SIZE];
char level[POOL_SIZE];

char solution[2][10][4] = {};

#if FAST_HASH_MAPPING


char pool_temp[POOL_SIZE];


void insert_to_pool(unsigned val)
{
	pool[val / 9] = val % 9;
}


#elif COLLECT_DATA_NO_ANALYSIS

struct TanksInfo
{
	unsigned* pos;
	unsigned n;
};

unsigned tank0[1] = {};
unsigned tank1[9] = {};
unsigned tank2[54] = {};
unsigned tank3[321] = {};
unsigned tank4[1847] = {};
unsigned tank5[9992] = {};
unsigned tank6[50136] = {};

struct TanksInfo tanks[TANK_LEVEL];

bool isUniq(struct TanksInfo tanks[], unsigned val)
{
	unsigned i, j;
	for (j = 0; j < TANK_LEVEL; j++)
	{
		unsigned* tank = tanks[j].pos;
		for (i = 0; i < tanks[j].n; i++)
		{
			if (equal(val, tank[i])) return false;
		}
	}
	return true;
}

void populate_next_level(struct TanksInfo tanks[], int level)
{
	unsigned i;
	unsigned* parent = tanks[level].pos;
	unsigned* tank = tanks[level + 1].pos;

	unsigned val;
	unsigned index = tanks[level + 1].n = 0;

	for (i = 0; i < tanks[level].n; i++)
	{
		val = parent[i];
		set<unsigned> collect;
		collect = permute_one_step(val);

		set<unsigned>::iterator it;
		for (it = collect.begin(); it != collect.end(); ++it)
		{
			if (isUniq(tanks, *it))
			{
				tank[index++] = *it; // Note the "*" here
				tanks[level + 1].n = index;
			}
		}
	}
}

#else

static bool find_stateN_in_pool(unsigned val)
{
	if (pool[val / 9] == 9) return false;
	else return true;
}

// return # of steps

static int solve_stateN_backto_Normal(unsigned sN)
{
	int count = 0;
	while (find_stateN_in_pool(sN))
	{
		display_stateN(sN);
		if (sN < 9)
		{
			printf("Origin reached!\n");
			break;
		}
		else
		{
			MOVE m = (MOVE)pool[sN / 9];
			m = reserve_move(m);
			unsigned tr = get_transform_from_move(m);
			printf("%u rotate = %u  %s\n", sN, m, moveToStr[m]);
			strcpy_s(solution[0][count], moveToStr[m]);
			count++;
			sN = transform_stateN(sN, tr);
		}
		printf("---------------------------------------\n");
	}
	return count;
}

static int solve_stateN_backto_Start(unsigned sN, unsigned start)
{
	int count = 0;
	unsigned buffer[10];
	while (find_stateN_in_pool(sN))
	{
		buffer[count] = sN;
		if (sN < 9)
		{
			printf("Starting point reached!\n");
			break;
		}
		else
		{
			MOVE m = (MOVE)pool[sN / 9];
			strcpy_s(solution[1][count], moveToStr[m]);
			m = reserve_move(m);
			unsigned tr = get_transform_from_move(m);
			count++;
			sN = transform_stateN(sN, tr);
		}
		printf("---------------------------------------\n");
	}

	for (int i = 0; i < count; i++)
	{
		MOVE m = (MOVE)pool[buffer[i] / 9];
		printf("%u rotate = %u  %s\n", sN, m, moveToStr[m]);
		display_stateN(transform_stateN(start, buffer[i]));
		printf("---------------------------------------\n");
	}
	return count;
}


#endif

int main()
{
	unsigned a;
	unsigned aa;
	unsigned i;
	//unsigned d;


	struct snapshot b = {};
	struct snapshot c = {};
	struct snapshot r = {};
/*	b = { { 0, 1, 8, 3, 4, 5, 2, 6, 7 }, { 0, 0, 1, 2, 1, 0, 1, 2, 0 } };
	a = get_stateN_from_snapshot(b, 4);
	printf("a = %u\n", a);
	get_snapshot_from_stateN(a, c);
	display_snapshot(c);

	NORMAL = get_stateN_from_snapshot(normal, 0);
	printf("NORMAL = %u\n", NORMAL);
	display_snapshot(normal);*/
	printf("---------------------------------------\n");
#if FAST_HASH_MAPPING

	for (int j = 0; j < POOL_SIZE; j++)
	{
		pool[j] = 9;
		level[j] = 9;
	}

	insert_to_pool(NORMAL);
	level[0] = 0;
	for (int i = 1; i <= 8; i++)
	{
		unsigned leftover = 0;
		for (int j = 0; j < POOL_SIZE; j++)
		{
			pool_temp[j] = pool[j];
		}

		for (int j = 0; j < POOL_SIZE; j++)
		{
			if (pool_temp[j] != 9)
			{
				set<unsigned> collect;
				collect = permute_one_step(j * 9);
				unsigned index;
				set<unsigned>::iterator it;
				for (it = collect.begin(); it != collect.end(); ++it)
				{
					index = *it / 9;
					if (pool[index] == 9)
					{
						pool[index] = *it % 9; // Note the "*" here
						level[index] = i;
					}
				}
			}
			else
			{
				leftover++;
			}
		}
		int count = 0;
		for (int j = 0; j < POOL_SIZE; j++)
		{
			if (pool[j] != 9) count++;
		}
		printf("level %d = %u leftover = %d\n", i, count, leftover);
	}

	for (int j = 0; j < 10; j++)
	{
		printf("%d\n", pool[j]);
	}

	FILE* fp;
	fopen_s( &fp, "output.txt", "w");
	if (fp != NULL)
	{
		for (i = 0; i < POOL_SIZE; i++)
			fprintf(fp, "%c", pool[i]+'0');
		fclose(fp);
	}

	FILE* fl;
	fopen_s( &fl, "level.txt", "w");
	if (fl != NULL)
	{
		for (i = 0; i < POOL_SIZE; i++)
			fprintf(fl, "%c", level[i]+'0');
		fclose(fl);
	}
#elif COLLECT_DATA_NO_ANALYSIS


	tanks[0].pos = tank0;
	tanks[0].n = 1;
	tanks[1].pos = tank1;
	tanks[2].pos = tank2;
	tanks[3].pos = tank3;
	tanks[4].pos = tank4;
	tanks[5].pos = tank5;
	tanks[6].pos = tank6;

	tank0[0] = { NORMAL };
	for (int i = 0; i <= 6; i++)
	{
		populate_next_level(tanks, i);
		printf("level %u %u\n", i, tanks[i].n);
	}

#else

	struct friendly_state state;
	//state = { { "DRG", "DPB", "DGP", "YRG", "YRB", "YGP", "DRB", "YBP" }, { '0', '+', '+', '-', '0', '-', '-', '+' } };
	//state = { { "DRG", "YPG", "YPB", "YRB", "YRG", "DBR", "DPG", "DBP" }, { '0', '+', '-', '0', '+', '0', '-', '0' } };
	//state = { { "DRG", "YPB", "YRG", "YGP", "DRB", "YBR", "DPG", "DPB" }, { '0', '+', '-', '-', '+', '+', '-', '0' } };

	//state = { { "DRG", "YRB", "DGP", "YPB", "YRG", "YGP", "DBP", "DRB" }, { '0', '-', '+', '-', '-', '-', '+', '-' } };
	//state = { { "DRG", "YRB", "DGP", "YPB", "DRB", "YRG", "YGP", "DBP" }, { '0', '-', '+', '-', '-', '-', '-', '+' } };
	//state = { { "DRG", "DBP", "DPG", "YPG", "YRB", "YBP", "YRG", "DRB" }, { '0', '+', '-', '0', '+', '0', '0', '-' } };

	state = { { "DRG", "DRB", "YRG", "YGP", "DBP", "YBP", "YRB", "DGP" }, { '0', '+', '0', '-', '+', '-', '+', '-' } };
	struct snapshot s;
	if (translate_friendly_state_into_snapshot(state, s) ==  false)
	{
		printf("found error in input state\n");
	};
	display_snapshot(s);
	printf("---------------------------------------\n");

	FILE* fp;
	fopen_s(&fp, "cache-output.txt", "r");
	if (fp != NULL)
	{
		for (i = 0; i < POOL_SIZE; i++)
			pool[i] = fgetc(fp) - '0';
		fclose(fp);
	}

	
	FILE* fl;
	fopen_s(&fl, "cache-level.txt", "r");
	if (fl != NULL)
	{
		for (i = 0; i < POOL_SIZE; i++)
			level[i] = fgetc(fl) - '0';
		fclose(fl);
	}

	for (int j = 0; j < 8; j++)
	{
		int k = 0;
		for (int i = 0; i < POOL_SIZE; i++)
		{
			if (level[i] == j)k++;
		}
		printf("%d\n", k);
	}

	c = { { 0, 1, 2, 3, 4, 7, 8, 5, 6 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	b = { { 0, 1, 4, 3, 8, 5, 2, 6, 7 }, { 0, 0, 2, 1, 2, 0, 2, 1, 1 } };
	aa = get_stateN_from_snapshot(s, R1);

	// unsolvable in pool, use transform method
	if (find_stateN_in_pool(aa))
	{
		solve_stateN_backto_Normal(aa);
	}
	else 
	{
		for (int k = 1; k <= 8; k++)
		{
			for (unsigned j = 0; j < POOL_SIZE; j++)
			{
				if (level[j] == k)
				{
					unsigned n = j*9;
					a = transform_stateN(aa, n);
					if (find_stateN_in_pool(a))
					{
						printf("results found %u %u\n", j, pool[j]);
						solve_stateN_backto_Start(n, aa);
						solve_stateN_backto_Normal(a);
						goto fin;
					}
				}
			}
		}
	}

fin:	printf("\n---------------------------------------\n");

	for (int i = 9; i >= 0; i--)
	{
		printf("%s\n", solution[1][i]);
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%s\n", solution[0][i]);
	}

/*	a = transform_stateN(91887841, 91887841);
	display_stateN(a);

	b = { {0,1,8,3,4,5,2,6,7}, {0,0,1,2,1,0,1,2,0} };
	a = get_stateN_from_snapshot(b, 4);
	r = { { 0, 1, 2,3,4,6,7,8,5 }, { 0, 0, 0,0,0,0,0,0,0 } };
	d = get_stateN_from_snapshot(r, 4);
	display_snapshot(b);
	display_snapshot(r);
	printf("%u\n", a);
	printf("%u\n", d);
	get_snapshot_from_stateN(a, c);
	display_snapshot(c);
	get_snapshot_from_stateN(d, r);
	display_snapshot(r);
	printf("-------------\n ");
	i = rotate_D(a);
	get_snapshot_from_stateN(i, c);
	display_snapshot(c);

	printf("-------------\n ");
	a = transform(a, d);
	get_snapshot_from_stateN(a, c);
	display_snapshot(c);

	printf("equal %d\n ", equal(a, i));
	display_snapshot(c);
	display_snapshot(r);
	a = rotate_D2(a);
	a = transform(a, i);
	a = transform(a, i);
	printf("-------------\n ");
	printf("equal %d\n ", equal(a, i));
	printf("%u %u %d\n ", a, i, equal(a, i));
	get_snapshot_from_stateN(a, c);*/
	

/*	struct snapshot ss1 = { { 0, 1, 2, 4, 8, 5, 6, 3, 7 }, { 0, 0, 0, 1, 2, 0, 0, 2, 1 } };
	struct snapshot rot = { { 0, 1, 3, 7, 4, 5, 2, 6, 8 }, { 0, 0, 1, 2, 0, 0, 2, 1, 0 } };
	transform(ss1, rot);
	//struct snapshot temp = {};
	//snapshot_invertion(ss1, temp);
	display_snapshot(ss1);*/

#endif
	system("PAUSE");
	return 0;
}
