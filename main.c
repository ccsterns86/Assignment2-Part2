/*
 * Example software running in Logisim RISC-V Computer System model by Pavel Gladyshev
 * licensed under Creative Commons Attribution International license 4.0
 *
 * This example shows how graphics display can be used to dsisplay pictures.
 * 
 * the showpic() function that fills graphics display with the given picture is 
 * written in assembly language (it is in the file showpic.s). 
 * It is declared at the end of lib.h
 * 
 * The picture data for two pictures is defined in pictures.c file,
 * the pictures[] array is declared in pictures.h header file.
 */

#include "lib.h"
#include "editDisplay.h"
#include "pictures.h"

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
    display_line(displayedLine);
    printstr("Simulating...");

    for( i=0 ;; i=(i+1) % PICTURES_TOTAL)   // Looping through the pictures forever
    {
        //display_line(editLine);
        showpic(pictures[i]);               // output next picture to the graphics display
    }
    
}
