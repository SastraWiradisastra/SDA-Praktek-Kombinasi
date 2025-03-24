#include "playlistLogic.h"
#include "display.h"

static List sortedCopy;	// Seperate list for copies that are sorted

// Maintaining the sorted list
void maintainSortedCopy(List* original, List* sorted, toSort sort) {
    deleteList(sorted); 
    copyList(*original, sorted);
    sortList(sorted, sort);
}

void initializePlaylist(List* playlist) {
    createList(playlist);
}

void addSong(List* playlist) {
    char title[256], album[256], artist[256];
    Length len;
    promptForTrackDetails(title, album, artist, &len);

    Elmt temp = {title, len, album, artist, NULL};
    elmtAddress curr = playlist->front;
    while (curr && !sameElmt(temp, *curr)) curr = curr->next;
    
    if (curr) {
        showErrorMessage("Song already exists!");
	waitForEnter();
        return;
    }

    elmtAddress newSong = allocate(title, len, album, artist);
    insRear(playlist, newSong);
    showSuccessMessage("Song added!");
    waitForEnter();
}

void removeSong(List* playlist, unsigned int pos) {
    if (pos < 1 || pos > getTotalElmt(*playlist)) {
        showErrorMessage("Invalid position!");
        waitForEnter();
	return;
    }
    delManual(playlist, pos);
    showSuccessMessage("Song removed!");
    waitForEnter();
}

// Seperate display function for sorted playlists
void sortAndDisplay(List* original, toSort sort) {
    maintainSortedCopy(original, &sortedCopy, sort);
    printf("\n--- Sorted Playlist ---\n");
    printList(sortedCopy);
    waitForEnter();
}

void searchSong(List* playlist, string query) {
    elmtAddress result = searchList(*playlist, query);
    if (result) 
	    displaySongDetails(result);
    else 
	    showErrorMessage("Song not found!");
    waitForEnter();
}

void displayPlaylist(List* playlist) {
    if (listEmpty(*playlist)) {
        displayEmptyPlaylist();
        waitForEnter();
	return;
    }
    displayPlaylistHeader();
    printList(*playlist);
    waitForEnter();
}
