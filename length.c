#include "length.h"

bool maxSeconds(Length len)
{
	return(len.seconds < 60);
}

bool maxMinutes(Length len)
{
	return(len.minutes < 60);
}

bool limit(Length len)
{
	return(len.hours <= 10);
}
