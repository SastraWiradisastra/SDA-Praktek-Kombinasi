#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>	// I/O control 
#include <stdlib.h>	// General memory allocation and macros
#include <stdbool.h>	// Implementing bool type
#include <string.h>	// String operations
#include "length.h"	// Implementing 'length' custom data type 

// Symbolic definition for pointer to const char (string)
typedef char* string;

// Symbolic definition for pointer to struct
typedef struct Elmt* elmtAddress;	

// Structure for list elements
typedef struct Elmt {
	string title;
	Length len;	// Track length as defined in 'length.h' 
	string album;
	string artist;
	elmtAddress next;
} Elmt;

// Structure for setting playlists
typedef struct List {
	elmtAddress front;
	elmtAddress rear;
} List;

// *Enumeration for determining subvariable to sort by (not part of main structure)
typedef enum {SORT_TITLE, SORT_LENGTH, SORT_ALBUM, SORT_ARTIST} toSort;

/* Constructors */
elmtAddress allocate(string title, Length len, string album, string artist);
void createList(List* playlist);

/* Destructors */
void deallocate(elmtAddress node);
void deleteList(List* playlist);

/* Verification */
bool listEmpty(List playlist);
bool sameElmt(Elmt node, Elmt nodeToComp);	// Check for track, album, and artist name

// *Sorting specific verification (not part of main structure)
int compareTitle(elmtAddress a, elmtAddress b);
int compareLength(elmtAddress a, elmtAddress b);
int compareAlbum(elmtAddress a, elmtAddress b);
int compareArtist(elmtAddress a, elmtAddress b);

/* Getter */
int getTotalElmt(List playlist);

/* List processing*/
// Copying
void copyList(List playlist, List* playlistCopy);

// Printing
void printElmt(elmtAddress node);
void printList(List playlist);

// *Sorting helper (not part of main structure)
void splitList(elmtAddress source, elmtAddress* front, elmtAddress* back);
elmtAddress merge(elmtAddress a, elmtAddress b, int (*compare)(elmtAddress, elmtAddress));
void mergeSort(elmtAddress* headRef, int (*compare)(elmtAddress, elmtAddress));

// Sorting 
void sortList(List* playlist, toSort sort);	// General sorting function 
void inverseList(List* playlist);		// Sorting by maximum 

// Search
elmtAddress searchList(List playlist, string query);

/* List I/O */
// Insertions
void insFront(List* playlist, elmtAddress node);
void insRear(List* playlist, elmtAddress node);
void insManual(List* playlist, elmtAddress node, unsigned int position);	// Manual insert

// Deletions
void delFront(List* playlist);
void delRear(List* playlist);
void delManual(List* playlist, unsigned int position);	// Manual delete

#endif
