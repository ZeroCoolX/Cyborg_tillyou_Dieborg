#include "RandomNumber.h"


int get_random_number(int mod)
{
	// returns random num between 0 and mod
	return rand() % mod;
}
