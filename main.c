#include "playlistLogic.h"
#include "display.h"
#include "input.h"

int main() {
    List playlist, sorted;
    initializePlaylist(&playlist);
    createList(&sorted);
    int choice;

    do {
        choice = showMainMenu();
        system("clear");
	
	switch (choice) {
            case 1: {
		addSong(&playlist);
		break;
	    }
            case 2: {
                unsigned int pos;
                promptForPosition(&pos);
                removeSong(&playlist, pos);
                break;
            }
            case 3: {
                char query[256];
                promptForSearchQuery(query);
                searchSong(&playlist, query);
                break;
            }
            case 4: displayPlaylist(&playlist); break;
            case 5: {
                toSort sort;
                promptForSortChoice(&sort);
                sortAndDisplay(&playlist, sort);
                break;
            }
            case 6: inverseList(&playlist); break;
            case 7: showExitMessage(); break;
            default: showErrorMessage("Invalid choice!");
        }
    } while (choice != 7);

    deleteList(&playlist);
    deleteList(&sorted);

    return 0;
}
