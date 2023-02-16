/*
 Written by Cassandra Sterns
 SN: 22209739
 Team: 404 Name not Found
*/

#pragma once

int flashCursor(int cursorPos, int editLine[1]);

int moveCursorLeft(int cursorPos);
int moveCursorRight(int cursorPos);

int changePoint(int cursorPos, int editLine);

//For the button
int buttonReleased();
