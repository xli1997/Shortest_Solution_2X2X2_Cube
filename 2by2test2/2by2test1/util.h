#ifndef UTIL
#define UTIL
#include"base.h"

int equal(unsigned a, unsigned b);
void display_snapshot(struct snapshot & s);
unsigned get_stateN_from_snapshot(snapshot& ss, MOVE move);
void get_snapshot_from_stateN(unsigned val, struct snapshot & s);
void transform_snapshot(struct snapshot & s, struct snapshot & r);
unsigned transform_stateN(unsigned a, unsigned rot);
void display_stateN(unsigned i);
void snapshot_invertion(struct snapshot & s, struct snapshot & rev);
bool translate_friendly_state_into_snapshot(struct friendly_state & state, struct snapshot & s);

#endif