#ifndef PLAYLISTLOGIC_H
#define PLAYLISTLOGIC_H

#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"

// Main operations for playlist management
void initializePlaylist(List* playlist);
void addSong(List* playlist);
void removeSong(List* playlist, unsigned int pos);
void sortAndDisplay(List* original, toSort sort);
void searchSong(List* playlist, string query);
void displayPlaylist(List* playlist);
void reversePlaylist(List* playlist);
void maintainSortedCopy(List* original, List* sorted, toSort sort);

#endif
