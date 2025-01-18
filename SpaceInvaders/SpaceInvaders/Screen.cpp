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
	string status = "Score: " + to_string(score) + "                                  " 
		+ "Lives: " + to_string(lives);
	for (int i = 0; i < status.size(); ++i)
	{
		put(status[i], { i, 0 });  
	}

	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		put('-', { x, 1 });
	}

	for (int y = 2; y < FIELD_HEIGHT - 1; ++y)
	{
		put('|', { 0, y });
		put('|', { FIELD_WIDTH - 1, y });
	}

	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		put('-', { x, FIELD_HEIGHT - 1 });
	}
}

void Screen::clearPauseMessage()
{
    const int messageWidth = 14;
    const int messageHeight = 5;
    int centerX = FIELD_WIDTH / 2;  
    int centerY = FIELD_HEIGHT / 2; 
    int startX = centerX - messageWidth / 2;
    int startY = centerY - messageHeight / 2;

    for (int y = startY; y < startY + messageHeight; y++)
    {
        for (int x = startX; x < startX + messageWidth; x++)
        {
            drawSymb(' ', x, y);
        }
    }
}

void Screen::boardMessage(string message)
{
	const int messageWidth = 14;
	const int messageHeight = 5;

	int centerX = FIELD_WIDTH / 2;  
	int centerY = FIELD_HEIGHT / 2; 

	int startX = centerX - messageWidth / 2;
	int startY = centerY - messageHeight / 2;

	for (int y = startY; y < startY + messageHeight; y++)
	{
		for (int x = startX; x < startX + messageWidth; x++)
		{
			drawSymb(' ', x, y);
		}
	}

	for (int y = startY; y < startY + messageHeight; y++)
	{
		for (int x = startX; x < startX + messageWidth; x++)
		{
			if (y == startY || y == startY + messageHeight - 1)
			{
				drawSymb('-', x, y);
			}
			else if (x == startX || x == startX + messageWidth - 1)
			{
				drawSymb('|', x, y);
			}
		}
	}

	int messageX = startX + (messageWidth - message.length()) / 2;
	int messageY = startY + messageHeight / 2;
	for (size_t i = 0; i < message.size(); i++)
	{
		drawSymb(message[i], messageX + static_cast<int>(i), messageY);
	}
}

void Screen::showPauseMessage()
{
    string message = "PAUSE";
    boardMessage(message);
}

void Screen::showGameOverMessage()
{
    string message = "GAME OVER";
    boardMessage(message);
}

void Screen::showWonMessage()
{
	string message = "YOU WON!!!";
	boardMessage(message);
}

void Screen::moveCursorToBottom()
{
	COORD endPosition = { 4, (SHORT)(FIELD_WIDTH / 3) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), endPosition);
}