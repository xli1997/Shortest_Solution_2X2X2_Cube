#include"class.h"

class SnapShot
{
public:
	char pos[9];
	char ori[9];
	char move;
	char level;
};

class State
{
public:
	unsigned state;

	State(unsigned u)
	{
		state = u;
	};
	void Display()
	{

	};
	~State();
};