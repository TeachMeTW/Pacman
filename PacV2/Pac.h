#pragma once

#ifndef Item
#define Item

// includes functions

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <Windows.h>
#include <conio.h>

using std::string;
using std::vector;

//clear screen, color, pause methods

void cls();
void color(int color);
void pause();
void ln();
void ln(int);
int random(int min, int max);

class Pac{ // pacman class
//has pacman data 
private: 
	vector<vector<char>>map;
	string chosen, line;
	int choice = -1;
	int position[2];

public:
	Pac(); // constructor
	~Pac(); // destructor
	string mapchoice();
	void game();
	void printmap();
	void intro();
	void initmap();
	int getPosY();
	int getPosX();
	int ghostnum();
	void movechar();
	void movePac(char x);

};
#endif 
