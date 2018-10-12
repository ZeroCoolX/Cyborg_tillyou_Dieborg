#include "random_number.h"


int getRandomNumber(int mod)
{
	// returns random num between 0 and mod
	return rand() % mod;
}
