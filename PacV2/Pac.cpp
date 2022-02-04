#include "Pac.h"

using namespace std;
using std::cin; // use correct cin

void cls() // clear screen
{
	system("cls");
}
void color(int color) // color function
{
	switch (color)
	{
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		break;

	case 1:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		break;

	case 2:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		break;

	case 3:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		break;

	case 4:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	case 5:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;

	case 6:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;

	case 7:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;

	case 8:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
		break;

	case 9:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
		break;

	case 10:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;

	case 11:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		break;

	case 12:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		break;

	case 13:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;

	case 14:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		break;

	case 15:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;

	default:
		cout << "\nCOLOR NOT CHANGED! PLEASE RE-EVALUATE COLOR METHOD!\n";
		break;
	}

	/*
		COLOR KEY


		BLACK		   = 0
	   /--------------------/
		DARK RED       = 1
		DARK GREEN     = 2
		DARK BLUE      = 3
	   /--------------------/
		RED            = 4
		GREEN          = 5
		BLUE		   = 6
	   /--------------------/
		DARK CYAN	   = 7
		DARK MAGENTA   = 8
		DARK YELLOW    = 9
	   /--------------------/
		CYAN		  = 10
		MAGENTA		  = 11
		YELLOW		  = 12
	   /--------------------/
		WHITE		  = 13
		GRAY		  = 14
		DARK GRAY	  = 15
	*/
}
void pause()
{
	system("pause");
}
int random(int min, int max) 
{
	std::random_device device;
	std::mt19937 random_engine(device());
	std::uniform_int_distribution<int> dt(min, max);

	int a = dt(random_engine);

	return a;
}
void ln() // creates endlines;
{
	cout << endl;
}
void ln(int x)
{
	for (int i = 0; i < x; i++)
		cout << endl;
}

Pac::Pac() // constructs the game
{
	intro();
	game();
	
}

Pac::~Pac(){} // destruct the game


//Functions

string Pac::mapchoice()
{
	do
	{
		cout << "\nWhat map would you like? Please enter 1 or 2 " << endl << endl;
		cin >> choice;
		cout << "\nYou have chosen map " << choice << endl << endl;
		if (choice == 1) chosen = "map1.txt";
		else if (choice == 2) chosen = "map2.txt";
		else cout << "Invalid input" << endl << endl;
	} while (choice > 3 || choice < 1);
	return chosen;
}

void Pac::game()
{
	mapchoice();
	initmap();
	printmap();
	ghostnum();
	movechar();
}

void Pac::printmap()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++) 
		{
			

			if (map[i][j] == '@')  // checks if pacman, changes color
			{
				color(12);
				cout << map[i][j] << "";
			}
			else if (map[i][j] == '$')  // checks if ghost, changes color
			{
				color(6);
				cout << map[i][j] << ""; 
			}
			else 
			{
				color(11); // if wall it stays white
				cout << map[i][j] << "";
			}
			
		}
		
		cout << endl;
	}
	color(13);
}

void Pac::intro()
{
	char menu;
	cout << "\nWelcome to the Pacman Game" << endl << endl;
	cout << "\nS to start game, P to print map, E to end game, I for instructions" << endl << endl;
	cin >> menu;

	while (menu != 'S' && menu != 'I' && menu != 'P' && menu != 'E')
	{
		cout << "\nPlease enter valid input" << endl << endl;
		cin >> menu;
	}

	if (menu == 'S' || menu == 'I' || menu == 'P' || menu == 'E')
	{
		switch (menu)
		{
		case 'S':
			game();
			break;
		case 'I':
			cout << "@ is pacman, * is the wall, $ are the ghosts" << endl;
			cout << "W to move up, A to move left, S to move down, D to move right" << endl;
			cout << "Collect all the ghosts to win!" << endl << endl;
			intro();
			break;
		case 'P':
			mapchoice();
			initmap();
			printmap();
			break;
		case 'E':
			cout << "Program Stopped" << endl;
			terminate();
		}
	}

}

void Pac::initmap()
{
	ifstream infile(chosen);
	while (!infile.eof()) {
		getline(infile, line);
		vector<char>row;
		row.assign(line.begin(), line.end());
		map.push_back(row);
	}
	cls();
}

int Pac::getPosY()
{
	int y;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			if (map[i][j] == '@') {
				y = j;
				return y;
			}
	}
	return 0;
}

int Pac::getPosX()
{
	int x;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			if (map[i][j] == '@') {
				x = i;
				return x;
			}
	}
	return 0;
}

int Pac::ghostnum()
{
	int counter = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			if (map[i][j] == '$') {
				counter++;

			}
	}

	return counter;
}

void Pac::movechar()
{
	char replay{ 'Y' };
	int posy = getPosY();
	int posx = getPosX();
	char move;
	int x = ghostnum();
	cout << "\nTotal Ghosts remaining: " << x << endl << endl;
	while (replay == 'Y' || 'y') {
		while (x > 0) {
			cout << "\nWhat move would you like to make?" << endl << endl;
			cin >> move;
			while (move != 'W' && move != 'A' && move != 'S' && move != 'D') {
				cout << "\nPlease enter valid input" << endl;
				cin >> move;
			}

			movePac(move);
			x = ghostnum();
			cout << "\nTotal Ghosts remaining: " << x << endl << endl;
		}
		if (x == 0) {
			cout << "\nCongrats! You've beaten pacman! Play again? Y/N" << endl;
			cin >> replay;
			if (replay == 'N' || 'n') {
				cout << "Thanks for playing" << endl;
				terminate();
				if (replay == 'Y' || 'y') {
					map.clear();
					intro();
					movechar();
				}
			}
		}
	}
}

void Pac::movePac(char x)
{
	int YPos = getPosY();
	int XPos = getPosX();
	cls();
	ln(5);
	switch (x)
	{
	case 'W':

		if (map[XPos - 1][YPos] != '*') {
			cout << "\nPosition is: " << XPos << " " << YPos << endl;

			map[XPos][YPos] = ' ';
			map[XPos - 1][YPos] = '@';
			cout << endl;
			
		}
		else
		{
			cout << "Invalid" << endl << endl;
		}
		printmap();
		break;

	case 'S':

		if (map[XPos + 1][YPos] != '*') {
			cout << "\nPosition is: " << XPos << " " << YPos << endl;

			map[XPos][YPos] = ' ';
			map[XPos + 1][YPos] = '@';
			cout << endl;
		}
		else { cout << "Invalid" << endl << endl; }
		printmap();
		break;

	case 'A':
		if (map[XPos][YPos - 1] != '*') {
			cout << "\nPosition is: " << XPos << " " << YPos << endl;

			map[XPos][YPos] = ' ';
			map[XPos][YPos - 1] = '@';
			cout << endl;
		}
		else { cout << "Invalid" << endl << endl; }
		printmap();
		break;

	case 'D':

		if (map[XPos][YPos + 1] != '*') {
			cout << "\nPosition is: " << XPos << " " << YPos << endl;

			map[XPos][YPos] = ' ';
			map[XPos][YPos + 1] = '@';
			cout << endl;
		}
		else { cout << "Invalid" << endl << endl; }
		printmap();
		break;

	default:
		cout << "\nEnter valid input" << endl;
		break;

	}

}

