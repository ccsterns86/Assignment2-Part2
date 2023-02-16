/*

 */

#include "lib.h"
#include "editDisplay.h"

int main()
{
    int i; 
    int cursorPos = 0;
    char *buf;
    int editLine = 0b00000000000000000000000000000000;
    int displayedLine[1] = {editLine};
    volatile int *joystickState = (volatile int *) 0xffff1110;
    int joystickPos;
    
    printstr("Welcome to the simulation.\n"); 
    printstr("You are in editing mode. \nUse the joystick and button to \nedit the first line.\n");
    printstr("When done, press enter on the \nMMIO keyboard.\n");

    while(1) { //keep looping in edit mode until we exit
        displayedLine[0] = flashCursor(cursorPos, displayedLine);
        if (pollkbd() == 0) { //no keyboard input
            joystickPos = *joystickState;
            if (buttonReleased()) { //check if the button is being pressed and has been released.
                editLine = changePoint(cursorPos, editLine);
                displayedLine[0] = editLine;
            }
            //check if the joystick is being moved
            if (joystickPos > 8) { //moved to the right
                cursorPos = moveCursorRight(cursorPos);
                displayedLine[0] = editLine;
            }
            else if (joystickPos < 8) { //moved to the left
                cursorPos =  moveCursorLeft(cursorPos);
                displayedLine[0] = editLine;
            }
        } 
        else {
            break;
        }
    }
    displayedLine[0] = editLine;
    display_line(displayedLine, 0);
    printstr("Simulating...");
    
    int prevLine = displayedLine[0];
    int currLine = 0;
    int currentBit;
    int picture[31];
    picture[0] = prevLine;
    // array to map value to 1 or 0
    int valArr[8] = {0, 1, 1, 1, 0, 1, 1, 0};
    int idx;

    for (int j = 1; j < 32; j++) {
        // loop through each bit in the row
        for (int n = 30;n >= -1; n--) { 
            // isolate three bits above 'n' and move to three least significant bits
            if (n == -1) { idx = (prevLine << 1) & 6; } // edge case, right
            else if (n == 30) { idx = (prevLine >> n) & 3; } // edge case, left
            else { idx = (prevLine >> n) & 7; } 
            
            // properly place currentBit correctly in the new line
            currentBit = valArr[idx]; 
            currLine = currLine | (currentBit << (n+1)); 

        }

        prevLine = currLine;
        picture[j] = currLine;
        currLine = 0;
        showpic(picture);
    }    
    printstr("Done");
}
