#ifndef LENGTH_H
#define LENGTH_H

#include <stdbool.h>

// Structure for length of time
typedef struct Length {
	unsigned int seconds;	// Value between 0-59
	unsigned int minutes;	// Value between 0-59
	unsigned int hours;	// Value between 0-10
} Length;

// Defining time limits
bool maxSeconds(Length len);	// Maximum seconds limit
bool maxMinutes(Length len);	// Maximum minutes limit
bool limit(Length len);		// 10 hour limit

#endif
