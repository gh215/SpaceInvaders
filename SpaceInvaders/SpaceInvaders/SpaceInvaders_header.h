#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <list>

using namespace std;

const char BORDER_CHAR = '|';
const char PLAYER_CHAR = '^';
const char ALIEN_CHAR = '#';
const char BULLET_CHAR = '|';
const int FIELD_WIDTH = 60;
const int FIELD_HEIGHT = 20;
const int ARROW = 224;
const int LEFT = 75;
const int RIGHT = 77;
const int STOP = 0;
const int SCORE_FOR_SHIP = 100;
const double SHOOT_COOLDOWN = 1.5;
const double ALIEN_SHOOT_COOLDOWN = 3.5;
const int ALIEN_INITIAL_POS = 1;
const int ALIEN_H_INTERVAL = 4;
const int ALIEN_V_INTERVAL = 2;
const int ALIEN_PERIOD = 10;
const int MAX_LIVES = 3;
const int ALIEN_ROWS = 3;
const int PLAYER_LIVES = 3;
const int DEFENDED_ZONE = 3;
const int ALIEN_COLUMNS = 7;
const int PLAYER_BULLET_PERIOD = 4;
const int SLEEP = 50;

struct Point
{
	int x;
	int y;
};

enum class Dir { RIGHT, LEFT, STOP };
enum class Dir_bull { UP, DOWN };

class Clock
{
private:
	long ticks;
public:
	Clock() : ticks(0) {}
	void tick() { ticks++; }
	long getTicks() { return ticks; }
};

extern Clock globalClock;

class Screen
{
private:
	char nextBuffer[FIELD_HEIGHT][FIELD_WIDTH];
	char activeBuffer[FIELD_HEIGHT][FIELD_WIDTH];
	void drawSymb(char symb, size_t x, size_t y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
		cout << symb;
	}
	void showConsoleCursor(bool showFlag);
	int score;
	int lives;
public:
	Screen() : score(0), lives(3) { clear(); showConsoleCursor(false); }
	void setScoreAndLives(int newScore, int newLives)
	{
		score = newScore;
		lives = newLives;
	}
	bool put(char symb, Point p)
	{
		if (p.x < 0 || p.x > FIELD_WIDTH - 1) return false;
		if (p.y < 0 || p.y > FIELD_HEIGHT - 1) return false;
		if (!isprint(symb)) return false;

		nextBuffer[p.y][p.x] = symb;
		return true;
	}
	void draw()
	{
		drawBorders();
		for (size_t x = 0; x < FIELD_WIDTH; x++)
		{
			for (size_t y = 0; y < FIELD_HEIGHT; y++)
			{
				if (nextBuffer[y][x] == activeBuffer[y][x]) continue;
				activeBuffer[y][x] = nextBuffer[y][x];
				drawSymb(activeBuffer[y][x], x, y);
			}
		}
		clear();
	}
	void clear()
	{
		for (size_t x = 0; x < FIELD_WIDTH; x++)
		{
			for (size_t y = 0; y < FIELD_HEIGHT; y++)
			{
				nextBuffer[y][x] = ' ';
			}
		}
	}
	void drawBorders();
};


class PlayerShip
{
private:
	Point position;
	bool isInvinsible;
	Dir direction;
	int lives;
	int invinsible_timer;
	double lastShotTime;
	bool shoot;
public:
	PlayerShip()
	{
		position = { FIELD_WIDTH / 2, FIELD_HEIGHT - DEFENDED_ZONE };
		direction = Dir::STOP;
		isInvinsible = false;
		invinsible_timer = 0;
		lives = PLAYER_LIVES;
		lastShotTime = 0;
		shoot = false;
	};
	void move();
	void setDir(Dir dir)
	{
		direction = dir;
	}
	bool canShoot(double currentTime)
	{
		return (currentTime - lastShotTime) >= SHOOT_COOLDOWN;
	}
	void updateLastShotTime(double currentTime)
	{
		lastShotTime = currentTime;
	}
	void tryShoot();
	bool hasShot()
	{
		if (shoot)
		{
			shoot = false;
			return true;
		}
		return false;
	}
	void draw(Screen& screen);
	Point getPosition() { return position; }
	void setInvinsible(bool inv)
	{
		isInvinsible = true;
		invinsible_timer = 3;
	};
};

class Alien
{
private:
	Point position;
	bool isAlive;
	Dir currentDirection;
public:
	Alien(int x, int y) : position({ x, y }), isAlive(true), currentDirection(Dir::LEFT){}
	void drop();
	void draw(Screen& screen);
	void move();
	void reverseDir()
	{
		if (currentDirection == Dir::LEFT)
		{
			currentDirection = Dir::RIGHT;
		}
		else
		{
			currentDirection = Dir::LEFT;
		}
	}
	bool isHit(const Point& bulletPosition);
	bool isOnFire(vector<Alien>& aliens);
	bool tryShoot(vector<Alien>& aliens);
	bool getIsAlive() { return isAlive; }
	bool isOnEdge()
	{
		if ((currentDirection == Dir::RIGHT && position.x >= FIELD_WIDTH - 3) ||
			(currentDirection == Dir::LEFT && position.x <= 2))
		{
			return true;
		}
		return false;
	}
	Point getPosition() { return position; }
};

class Bullet
{
private:
	Point position;
	Dir_bull direction;
	int period = PLAYER_BULLET_PERIOD;
	char symb;
	bool isEnemy;
public:
	Bullet(Point p, bool e) : position(p), isEnemy(e), symb(BULLET_CHAR)
	{
		if (isEnemy)
		{
			direction = Dir_bull::DOWN;
			return;
		}
		direction = Dir_bull::UP;
	}
	void move();
	void draw(Screen& screen);
	bool isOutOfBounds();
	Point getPosition() { return position; }
};

class Blast
{
private:
	Point position;
	int lifetime;
public:
	void draw();
	int tick() { return lifetime--; };
	Blast(Point pos);
};

class Game
{
private:
	PlayerShip playerShip;
	vector<Alien> aliens;
	vector<Bullet> playerBullets;
	vector<Bullet> alienBullets;
	vector<Blast> blasts;
	Screen screen;
public:
	void draw();
	void createAlienGrid();
	void moveBullets();
	void moveAliens();
	void run();
	void processInput();
	void update();
};

