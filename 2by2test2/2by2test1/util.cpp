#include <stdio.h>
#include "base.h"

char friendly_corners[9][4] = { "", "DRG", "DRB", "DBP", "DPG", "YRG", "YRB", "YBP", "YPG" };

#define UNSETTLED_CORNERS 7
#define N0 1;
#define N1 1;
#define N2 2;
#define N3 6;
#define N4 24;
#define N5 120;
#define N6 720;
#define N7 5040;

static unsigned Factorial(int n)
{
	unsigned ret = 0;
	switch (n)
	{
	case 0:
		ret = N0;
		break;
	case 1:
		ret = N1;
		break;
	case 2:
		ret = N2;
		break;
	case 3:
		ret = N3;
		break;
	case 4:
		ret = N4;
		break;
	case 5:
		ret = N5;
		break;
	case 6:
		ret = N6;
		break;
	}
	return ret;
}

//parameter a is the string of combination
//parameter n is the string length;
//return value: combination_order_number in unsigned int
static unsigned get_order_number_from_combination(char a[], int n)
{
	int i;
	if (n == 1) return 0;
	else if (n == 2)
	{
		if (a[0] < a[1]) return 0;
		else return 1;
	}
	else
	{
		int count = 0;
		for (i = 1; i < n; i++)
		{
			if (a[0] > a[i]) count++;
		}
		return count*Factorial(n - 1) + get_order_number_from_combination(a + 1, n - 1);
	}
}

static void swap(char & a, char & b)
{
	char temp;
	temp = a;
	a = b;
	b = temp;
}

//parameter: val is combination_order_number
//parameter: a is the string of combination as input;
//output: a carries the modified string of combination
//this function is the reverse of get_combination_order_number
static void get_combination_from_order_number(unsigned val, char a[])
{
	int i, j;
	int q, N;
	char b[UNSETTLED_CORNERS] = { 0 };

	for (i = 0; i < UNSETTLED_CORNERS; i++)
	{
		b[i] = a[i];
	}

	for (i = 0; i < UNSETTLED_CORNERS; i++)
	{
		N = Factorial(UNSETTLED_CORNERS - 1 - i);
		q = val / N;
		val = val % N;
		a[i] = b[q];
		b[q] = UNSETTLED_CORNERS + 2;
		for (j = q; j < UNSETTLED_CORNERS - 1; j++)
		{
			if (b[j] > b[j + 1])
				swap(b[j], b[j + 1]);
		}
	}
}

int equal(unsigned a, unsigned b)
{
	if (a / 9 == b / 9) return 1;
	else return 0;
}

unsigned get_stateN_from_snapshot(snapshot& ss, MOVE move)
{
	unsigned value_pos = 0;
	unsigned value_ori = 0;
	unsigned value_final;

	int i;
	value_pos = get_order_number_from_combination(ss.pos + 2, UNSETTLED_CORNERS);;
	for (i = 2; i <= 8; i++)
	{
		value_ori = value_ori * 3 + ss.ori[i];
	}

	value_final = (value_pos * 2187 + value_ori) * 9;
	value_final += move;

	//printf("inside ToIntrinsic: %d, %d, %u\n", value1, value1 * 2187 + value2, value3);
	return value_final;
}

void get_snapshot_from_stateN(unsigned val, struct snapshot & ss)
{
	ss = {};
	val = val / 9;
	unsigned value1 = val % 2187;
	unsigned value2 = val / 2187;
	unsigned sum = 0;

	int i;
	for (i = 8; i >= 1; i--)
	{
		ss.ori[i] = value1 % 3;
		value1 /= 3;
		ss.pos[i] = i;
	}

	get_combination_from_order_number(value2, ss.pos+2);

	//printf("inside from intrinsic:");
	//display_snapshot(s);
}

void display_snapshot(struct snapshot & ss)
{
	int i;
	for (i = 1; i <= 8; i++)
	{
		printf("%u", ss.pos[i]);
		switch (ss.ori[i])
		{
		case 0:
			printf("0");
			break;
		case 1:
			printf("+");
			break;
		case 2:
			printf("-");
			break;
		}
		printf(" ");
	}
	printf("  ");
	for (i = 1; i <= 8; i++)
	{
		printf("%s", friendly_corners[ss.pos[i]]);
		switch (ss.ori[i])
		{
		case 0:
			printf("0");
			break;
		case 1:
			printf("+");
			break;
		case 2:
			printf("-");
			break;
		}
		printf(" ");
	}
	printf("\n");
}

void display_stateN(unsigned sN)
{
	struct snapshot ss = {};
	get_snapshot_from_stateN(sN, ss);
	display_snapshot(ss);
}

// input snapshot ss
// output snapshot inv
static void snapshot_invertion(struct snapshot & ss, struct snapshot & inv)
{
	int i;
	struct snapshot clone = {};
	for (i = 0; i <= 8; i++)
	{
		clone.pos[i] = ss.pos[i];
		clone.ori[i] = ss.ori[i];
	}

	for (i = 0; i <= 8; i++)
	{
		inv.pos[clone.pos[i]] = i;
		inv.ori[clone.pos[i]] = clone.ori[i];
	}
}

// input snapshot ss and rotate rot
// output snapshot ss 
void transform_snapshot(struct snapshot & ss, struct snapshot & rot)
{
	int i;
	struct snapshot clone = {};
	for (i = 0; i <= 8; i++)
	{
		clone.pos[i] = ss.pos[i];
		clone.ori[i] = ss.ori[i];
	}

	struct snapshot rev_rot = {};
	snapshot_invertion(rot, rev_rot);
	struct snapshot rev_clone = {};
	snapshot_invertion(clone, rev_clone);

	for (i = 1; i <= 8; i++)
	{
		ss.pos[i] = clone.pos[rot.pos[i]];
		ss.ori[rev_rot.pos[rev_clone.pos[i]]] = (rot.ori[rev_rot.pos[rev_clone.pos[i]]] + clone.ori[rev_clone.pos[i]]) % 3;
	}
}


// unsigned version
// input unsigned a and unsigned rot
// output unsigned in return value 
unsigned transform_stateN(unsigned sN, unsigned rot)
{
	snapshot s;
	snapshot r;
	unsigned val = 0;
	get_snapshot_from_stateN(sN, s);
	get_snapshot_from_stateN(rot, r);
	transform_snapshot(s, r);
	val = get_stateN_from_snapshot(s, D1);
	return val;
}

static bool two_strings_permutation_match(char* a, char* b)
{
	int n, m;
	n = a[0] + a[1] + a[2];
	m = b[0] + b[1] + b[2];
	if (n != m) return false;
	n = a[0] * a[1] * a[2];
	m = b[0] * b[1] * b[2];
	if (n != m) return false;
	return true;
}

bool translate_friendly_state_into_snapshot(struct friendly_state & state, struct snapshot & s)
{
	for (int i = 0; i < 8; i++)
	{
		bool found = false;
		for (int j = 1; j < 9; j++)
		{
			if (two_strings_permutation_match(state.pos[i], friendly_corners[j]))
			{
				s.pos[i + 1] = j;
				found = true;
				break;
			}
		}
		if (found)
		{
		if (state.ori[i] == '+')
			s.ori[i + 1] = 1;
		else if (state.ori[i] == '-')
			s.ori[i + 1] = 2;
		else
			s.ori[i + 1] = 0;
		}
		else return false;
	}
	return true;
}
