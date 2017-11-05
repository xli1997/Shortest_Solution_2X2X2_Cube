#ifndef ROTATE
#define ROTATE
#include <set>
using namespace std;

unsigned rotate_D(unsigned sN);
unsigned rotate_D1(unsigned sN);
unsigned rotate_D2(unsigned sN);

unsigned rotate_R(unsigned sN);
unsigned rotate_R1(unsigned sN);
unsigned rotate_R2(unsigned sN);

unsigned rotate_F(unsigned sN);
unsigned rotate_F1(unsigned sN);
unsigned rotate_F2(unsigned sN);

set<unsigned> permute_one_step(unsigned sN);
unsigned get_transform_from_move(MOVE m);
MOVE reserve_move(MOVE m);

#endif