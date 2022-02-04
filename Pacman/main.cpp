#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
#include <algorithm> 
using namespace std;

// This whole code needs streamlining

// function prototypes
string mapchoice();
void game(); // runs game
void printmap(); // prints map
void initmap(); // creates map
void intro(); // intro menu
int ghostnum();  // tracks ghost
void movechar(); // moves char
void movePac(char); 
int getPosX();
int getPosY();

vector<vector<char>>map; //vector init

string chosen, line;
int choice;
int position [2]; 

int main(){ // main
  intro();
  return 0;
}

void game(){ // game function
  mapchoice();
  initmap();
  printmap();
  ghostnum();
  movechar();
}

string mapchoice() // map choosing
{
  do // I could've done yet another switch statement here
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

void printmap()
{
  for (int i=0; i<map.size();i++)
  {
    for (int j=0; j<map[i].size();j++)
    cout << map[i][j] << "";
    cout << endl;
  }
}

void intro() // introfunction which prints menu
{
  char menu;
  cout << "\nWelcome to the Pacman Game" << endl<< endl;
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

void initmap(){ // initializes map
  ifstream infile(chosen);
  while (!infile.eof()){ // end of file
    getline(infile, line);
    vector<char>row; 
    row.assign(line.begin(),line.end()); // assign row to 2d vector
    map.push_back(row);
  }
}


int getPosY(){ // gets position of pacman
  int y;
  for (int i=0; i<map.size();i++){
    for (int j=0; j<map[i].size();j++)
    if (map[i][j]== '@'){
      y = j;
      return y; 
    } 
  }
  return 0;
}

int getPosX(){ // gets position of pacman
  int x;
  for (int i=0; i<map.size();i++){
    for (int j=0; j<map[i].size();j++)
    if (map[i][j]== '@'){
      x = i;
      return x; 
    } 
  }
  return 0;
}

int ghostnum(){ // finds number of ghosts
  int counter = 0;
  for (int i=0; i<map.size();i++){
    for (int j=0; j<map[i].size();j++)
    if (map[i][j]== '$'){
      counter++;
      
    } 
  }

  return counter;
}

void movechar() // moves pacman
{
  char replay {'Y'};
  int posy = getPosY();
  int posx = getPosX();
  char move;
  int x = ghostnum();
  cout << "\nTotal Ghosts remaining: " << x << endl << endl;
  while (replay == 'Y' || 'y'){
    while (x > 0){
      cout << "\nWhat move would you like to make? W for forward, A for left, S for down, D for right, E to end game " << endl<< endl;
      cin >> move;
      while (move != 'W' && move != 'A' && move != 'S' && move != 'D' && move != 'E'){
        cout << "\nPlease enter valid input" << endl;
        cin >> move;
      }
    
      movePac(move);
      x = ghostnum();
      cout << "\nTotal Ghosts remaining: " << x << endl << endl;
    }
    if (x==0){
      cout << "\nCongrats! You've beaten pacman! Play again? Y/N" << endl;
      cin >> replay;
      switch (replay){
        case 'Y':
        map.clear();
        intro();
        movechar();
        case 'N':
        cout << "Thanks for playing" << endl;
        terminate();
      }      
  
    }
  }
}

void movePac(char x) // moves pacman behind the scenes
{
int YPos = getPosY();
int XPos = getPosX();
    switch (x)
      {
        case 'W':

        if(map[XPos-1][YPos] != '*'){ 
          cout << "\nPosition is: " << XPos << " " << YPos << endl;
          if (map[XPos-1][YPos] == '$'){
            map[XPos][YPos] = '#';  
            map[XPos-1][YPos] = '@'; 
          }
          else{
            map[XPos][YPos] = ' ';  
            map[XPos-1][YPos] = '@'; 
          }
          cout << endl;
          printmap();
        }
        else { cout << "Invalid movement" << endl<< endl;}
        break;

        case 'S':

        if(map[XPos+1][YPos] != '*'){ 
          cout << "\nPosition is: " << XPos << " " << YPos << endl;
          if (map[XPos+1][YPos] == '$'){
            map[XPos][YPos] = '#';  
            map[XPos+1][YPos] = '@'; 
          }
          else{
            map[XPos][YPos] = ' ';  
            map[XPos+1][YPos] = '@'; 
          }
          cout << endl;
          printmap();
        }
        else { cout << "Invalid" << endl<< endl;}
        break;

        case 'A':
        if(map[XPos][YPos-1] != '*'){ 
          cout << "\nPosition is: " << XPos << " " << YPos << endl;
          if (map[XPos][YPos-1] == '$'){
            map[XPos][YPos] = '#';  
            map[XPos][YPos-1] = '@'; 
          }
          else{
            map[XPos][YPos] = ' ';  
            map[XPos][YPos-1] = '@'; 
          } 
          cout << endl;
          printmap();
        }
        else { cout << "Invalid" << endl<< endl;}
        break;

        case 'D':

        if(map[XPos][YPos+1] != '*'){ 
          cout << "\nPosition is: " << XPos << " " << YPos << endl;
          if (map[XPos][YPos+1] == '$'){
            map[XPos][YPos] = '#';  
            map[XPos][YPos+1] = '@'; 
          }
          else{
            map[XPos][YPos] = ' ';  
            map[XPos][YPos+1] = '@'; 
          }
          cout << endl;
          printmap();
        }
        else { cout << "Invalid" << endl<< endl;}
        break;

        case 'E':
          cout << "\n Ending program" << endl;
          terminate();
          break;

        default:
          cout << "\nEnter valid input" << endl;
          break;

      }
  
}


