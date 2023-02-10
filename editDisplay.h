#pragma once

int flashCursor(int cursorPos, int editLine[1]);

int moveCursorLeft(int cursorPos);
int moveCursorRight(int cursorPos);

int changePoint(int cursorPos, int editLine);

//For the button and joystick
int buttonReleased();
