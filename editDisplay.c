#include "editDisplay.h"
#include "lib.h"

//takes the position of the cursor and flips the value
int flashCursor(int cursorPos, int editLine[1]) {
    int newEditLine[1];
    int cursorBin = 0b1 << cursorPos;
    newEditLine[0] = editLine[0] ^ cursorBin; //XOR the line to get a flashing cursor
    display_line(newEditLine);
    return newEditLine[0];
}

//takes the position of the cursor and moves it to the left if it can
int moveCursorLeft(int cursorPos) {
    if (cursorPos < 31) { return cursorPos+1; }
    else { return 31; }
}

//takes the postion of the cursor and moves it to the right if it can
int moveCursorRight(int cursorPos) {
    if (cursorPos > 0) { return cursorPos-1; }
    else { return 0; }
}

//change the value at the cursor position
int changePoint(int cursorPos, int editLine) {
    int cursorBin = 0b1 << cursorPos;
    editLine = editLine ^ cursorBin;
    return editLine;
}

int buttonReleased() {
    volatile int *curState = (volatile int *) 0xffff1010;
    int btnVal = *curState;
    if (btnVal == 1) { //if button was pressed
        while(btnVal == 1) { //wait until it is no longer pressed
            btnVal = *curState;
        }
        return 1; //button has been released
    } else { return 0; } //button isn't being pressed
}
