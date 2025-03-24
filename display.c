#include "display.h"
#include "input.h"

int showMainMenu() {
    system("clear");
    printf("\n=== Playlist Manager ===\n");
    printf("1. Add Song\n2. Remove Song\n3. Search\n");
    printf("4. Display Playlist\n5. Display Sorted Playlist\n6. Reverse Playlist\n7. Exit\n");
    printf("Choice: ");
    
    int choice;
    getIntegerInput(&choice);
    return choice;
}

void showExitMessage() {
    printf("\nExiting...\n");
    sleep(3);
    system("clear");
}

void waitForEnter() {
    printf("\nPress enter to continue...");
    while(getchar() != '\n');
    getchar();
}

void showErrorMessage(const char* message) {
    printf("\nERROR: %s\n", message);
}

void showSuccessMessage(const char* message) {
    printf("\nSUCCESS: %s\n", message);
}

void displayPlaylistHeader() {
    printf("\n--- Current Playlist ---\n");
}

void displaySongDetails(elmtAddress node) {
    printf("\nTitle\t: %s\n", node->title);
    printf("Length\t: %u:%u:%u\n", 
        node->len.hours, node->len.minutes, node->len.seconds);
    printf("Album\t: %s\n", node->album);
    printf("Artist\t: %s\n", node->artist);
}

void displayEmptyPlaylist() {
    printf("\nPlaylist is empty.\n");
}

void promptForLength(Length* len) {
    do {
        printf("Hours (0-10): ");
        getUnsignedInput(&len->hours);
    } while (!limit(*len));

    do {
        printf("Minutes (0-59): ");
        getUnsignedInput(&len->minutes);
    } while (!maxMinutes(*len));

    do {
        printf("Seconds (0-59): ");
        getUnsignedInput(&len->seconds);
    } while (!maxSeconds(*len));
}

void promptForTrackDetails(char* title, char* album, char* artist, Length* len) {
    printf("\n--- New Track ---\n");
    printf("Title: ");
    getStringInput(title, 256);
    
    printf("Album: ");
    getStringInput(album, 256);
    
    printf("Artist: ");
    getStringInput(artist, 256);
    
    printf("\n-- Track Length --\n");
    promptForLength(len);
}

void promptForPosition(unsigned int* pos) {
    printf("Position: ");
    getUnsignedInput(pos);
}

void promptForSearchQuery(char* query) {
    printf("Search: ");
    getStringInput(query, 256);
}

void promptForSortChoice(toSort* sort) {
    printf("\nSort by:\n1. Title\n2. Length\n3. Album\n4. Artist\nChoice: ");
    int choice;
    getIntegerInput(&choice);
    *sort = choice - 1;
}
