#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <unistd.h>
#include "playlistLogic.h"

// Menus
int showMainMenu();
void showExitMessage();
void waitForEnter();

// Messages
void showErrorMessage(const char* message);
void showSuccessMessage(const char* message);

// Playlist display
void displayPlaylistHeader();
void displaySongDetails(elmtAddress node);
void displayEmptyPlaylist();

// Input prompts
void promptForTrackDetails(char* title, char* album, char* artist, Length* len);
void promptForPosition(unsigned int* pos);
void promptForSearchQuery(char* query);
void promptForSortChoice(toSort* sort);

#endif
