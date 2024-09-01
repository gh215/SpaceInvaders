#include "SpaceInvaders_header.h"

void Screen::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Screen::drawBorders()
{
	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		put('-', { x, 0 });
	}

	for (int y = 1; y < FIELD_HEIGHT - 1; ++y)
	{
		put('|', { 0, y });
		put('|', { FIELD_WIDTH - 1, y });
	}

	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		put('-', { x, FIELD_HEIGHT - 1 });
	}
}