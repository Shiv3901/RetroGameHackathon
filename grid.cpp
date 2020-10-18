//Snakeoids starts

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//defining the box size in which the game whill be played
#define H 30

using namespace std;

//function to generate and return a random number
//It also makes sure that the grid generated is not at
//the current player coordinates
int random_num(int low, int high, int corr, int turn);

//check function checks if the player hit the obstacles
//returning -1 confirms the hit
int check(int* x_corr, int* y_corr, int x, int y);

//function to wait to end the game
void endgame();

//print the box of the game
void box();

//display the rules of the game
void rule();

//struct object stores the x and y coordinates of the player
//also obstacles are the same types created in it
typedef struct {
	int x;
	int y;
} object;

//main function where the game runs
int main()
{
	//intiating the ncurses terminal screen	
	initscr();

	//assigning colour pairs and using them afterwards
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	
	//starting off
	keypad(stdscr, true);

	noecho();

	curs_set(0);

	//initialising the player at the very centre of the arena
  	object b = {2*H,H};

  	//two arrays that stores the trails of the player as snake
	int trail_x[7], trail_y[7];

  	//initialising the trails to the initial point of starting
  	for(int i = 0 ; i < 7 ; i++){
  		trail_y[i] = H;
  		trail_x[i] = 2*H;
  	}

  	//initialising end to 0 and game stops when end equates to -1
	int end = 0;

	//initialising direc to true suggesting that it has only has to fall
	bool direc_ver = true;

	box();
	rule();

  	//Waiting for any key to be pressed
  	getch();

  	//declaring five obstacles that are avoided to win the game
  	//the coordinated are aligned with the size of the box
  	object obs = {H, H/2+1};      	//x will be displayed
  	object obs1 = {3*H-5, H/2+1};	//u will be displayed
  	object obs2 = {H,3*H/2-3};		//y will be displayed
  	object obs3 = {3*H-5, 3*H/2-3};	//g will be displayed
  	object obs4 = {2*H-2, H-3};		//d will be displayed
  	
  	//stores the current coordinates of the obstacles
  	//will be used to check if that's a hit
  	int obs_corr_x[5] = {3*H/2};
  	int obs_corr_y[5] = {H};

  	//initialing the game at i = 1
  	int turn = 1;

  	//it just runs forver, as i++ is done inside the loop
  	//the only way you can get out if you hit or survive till 500 turns
  	while(turn > 0) {

  		//the current coordinates of the player are updated here
  		//and stores at the first iteration of trail arrays
  		trail_x[0] = b.x;
  		trail_y[0] = b.y;

  		//for loop that empties the first space for the new coordinates
  		//and the others are copies to right new iterations
  		for(int i=7; i>0; i--){
  			trail_x[i] = trail_x[i-1];
  			trail_y[i] = trail_y[i-1];
  		}

  		//initialising the condition to 0 
  		int condition = 0;

  		//while loop that runs unitl a valid arrow key is entered
  		while( condition != 1 ){

  			//switch statement for the key entered
	  		switch(getch()){

	  			//case for the left arrow key
	  			case KEY_LEFT:
	  				//statement to check if the border of the box is hit
	  				//if not, then and then the move is made
	  				if((b.x - 1) >= H){
	  					//changing the x coordinate that mimics the movement
	  					//of the player to the left
	  					b.x--;
	  				}
	  				//updating the condition to convey that it is allowed
	  				condition = 1;
	  				break;

	  			//same as the left arrow key case 
	  			case KEY_RIGHT:
	  				if((b.x + 1) <= 3*H){
	  					b.x++;
	  				}
	  				condition = 1;
	  				break;

	  			//if the key q is hit, then exit the game
	  			case 'q': 
	  				//terminate the ncurses window
	  				endwin(); 
	  				//returning 0 to convey completion of the game
	  				return 0;
	  				break;
	  		}

  		}
  		
  		//if statement to check if the boundary of the wall is hit
  		//and it changes itself
  		if( (b.y - 1) == H/2){
  			direc_ver = true;
  		} else if((b.y + 1) == H + H/2){
  			direc_ver = false;
  		}

  		//if its going downwards than it allows it go downwards
  		if(direc_ver == true){
  			//increasing y by 1 micmicing going downwards
  			b.y++;
  		} 
  		//else it starts going upwards
  		else {
  			//decreasing y by 1 mimicing going upwards
  			b.y--;
  		}

 		
  		//refreshing the screen at each iteration of the loop
  		refresh();
  		//erases everything that is on the screen
  		erase();  

  		srand (time(NULL)) ;


  		//random number generater that changes the coordinates of all the obstacles
  		//it happens after every 25 turns
  		if(turn % 25 == 0){

  			//also updating the coordinates in the stored location

  			//changing obs coordinates
  			obs.x = obs_corr_x[0] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs.y = obs_corr_y[0] = random_num(H/2+1, H-4, b.y, 1) ;
 			//changing obs1 coordinates
  			obs1.x = obs_corr_x[1] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs1.y = obs_corr_y[1] = random_num(H/2+1, H-4, b.y, 1) ;
  			//changing obs2 coordinates
  			obs2.x = obs_corr_x[2] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs2.y = obs_corr_y[2] = random_num(H/2+1, H-4, b.y, 1) ;
  			//changing ob3 coordinates
  			obs3.x = obs_corr_x[3] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs3.y = obs_corr_y[3] = random_num(H/2+1, H-4, b.y, 1) ;
  			//changing obs4 coordinates
  			obs4.x = obs_corr_x[4] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs4.y = obs_corr_y[4] = random_num(H/2+1, H-4, b.y, 1) ;
  		}


  		//colour on
  		attron(COLOR_PAIR(2));
		
		//displaying the obstacles with height 3 and width 5 characters		
  		for(int h = 0 ; h < 3 ; h++) {

  			for(int g = 0 ; g < 5 ; g++) {
  				mvprintw(obs.y+h,obs.x+g,"x");     	//obs
  				mvprintw(obs1.y+h,obs1.x+g,"u");	//obs1	
	  			mvprintw(obs2.y+h,obs2.x+g,"y");	//obs2
  				mvprintw(obs3.y+h,obs3.x+g,"g");	//obs3
  				mvprintw(obs4.y+h,obs4.x+g,"d");	//obs4
  			}

  		}
  		//colour off
  		attroff(COLOR_PAIR(2));
  		
  		box();
  		
  		//check if the player hit the obstacle
  		end = check(obs_corr_x, obs_corr_y, b.x, b.y);

  		//if yes, then end the game with the lost message
  		if(end == -1){
  			erase();
  			attron(COLOR_PAIR(1));
  			mvprintw(H-1, 2*H-5, "You Lost !!");
  			mvprintw(H+3, 2*H-8, "Press E to exit!!");
  			attroff(COLOR_PAIR(1));
  			box();
  			endgame();
  			return 0 ;
  		}

  		//if the number of turns exceed 250, then displaying winning message
  		if(turn == 250){
  			erase();
  			attron(COLOR_PAIR(1));
  			mvprintw(H-1, 2*H-5, "You Won !!");
  			mvprintw(H+3, 2*H-8, "Press E to exit!!");
  			attroff(COLOR_PAIR(1));
  			box();
  			endgame();
  			return 0 ;
  		}

  		

  		//colour on
  		attron(COLOR_PAIR(1));
  			//displaying the trail
  			//with the exact words of the snakoid
  			mvprintw(trail_y[1], trail_x[1], "n");
  			mvprintw(trail_y[2], trail_x[2], "a");
  			mvprintw(trail_y[3], trail_x[3], "k");
  			mvprintw(trail_y[4], trail_x[4], "o");
  			mvprintw(trail_y[5], trail_x[5], "i");
  			mvprintw(trail_y[6], trail_x[6], "d");
  		//colour off  			
  		attroff(COLOR_PAIR(1));

  		//colour on
  		attron(COLOR_PAIR(4));
  			//displaying player head
  			mvprintw(b.y,b.x,"s");
  		//colour off
  		attroff(COLOR_PAIR(4));

  		//colour on
  		attron(COLOR_PAIR(3));
  			//displaying the turn count
  			mvprintw(H/2-2,2*H-5, "Count: %i", turn);
  		//colour off
  		attroff(COLOR_PAIR(3));

  		//turns increased by 1
      	turn++;
      
  	}

  	//close the window
  	endwin();

	return 0;
}

//function to generate and return a random number
//It also makes sure that the grid generated is not at
//the current player coordinates
int random_num(int low, int high, int corr, int turn){

	//generate a random number using random function
	int random = low + (rand() % high);

	//increasing the field of the player
	turn += 2;

	//while loop that checkes if the number generated 
	//is beyond the protection area of the player
	//Otherwise generates another number
	while(random >= corr - turn && random <= corr + turn){
		random = low + (rand() % high);
	}

	//returns the randomly generated number
	return random;

}

//check function checks if the player hit the obstacles
//returning -1 confirms the hit
int check(int* x_corr, int* y_corr, int x, int y)
{
	//for loop that goes through each five obstacles
	for(int i = 0 ; i < 5 ; i++){

		//for loop that creates a virtual width area of the obstacle
		for(int u = 0 ; u < 5 ; u++){

			//for loop that creates a virtual height of the obstackle
			for(int h = 0 ; h < 3 ; h++){

				//if statement that checks if the player is inside 
				if( ( x_corr[i] + u ) == x && ( y_corr[i] + h ) == y){
					//returns -1 to flag that the player is hit 
					//and GAME OVER
					return -1;
				}

			}
		}

	}

	//return 0 to indicate green signal that its not a hit
	return 0;
}

//function to wait to end the game
void endgame()
{
	char input = getch();

	while(input != 'e'){
		input = getch();
	}

	endwin();
}

//print the box of the game
void box()
{
	//colour on
  	attron(COLOR_PAIR(3));

  	//for loops displying the box of the game

  	//top and bottom of the arena
  	for(int i = 0 ; i < 2*H ; i++){
  		mvprintw(H/2,H + i,"_");
  		mvprintw(H + H/2,H + i,"-");
  	}
  	//left and right of the arena
  	for(int i = 1 ; i < H ; i++){
  		mvprintw(H/2 + i,H,"|");
  		mvprintw(H/2 + i,3*H,"|");
  	}

  	//colour off
  	attroff(COLOR_PAIR(3));
}

//display the rules of the game
void rule()
{
	mvprintw(H/2+5, 2*H-14, "SNAKOIDS: SNAKE + ASTEROIDS");
	
	//colour on
	attron(COLOR_PAIR(3));
	//displaying the initial statistics of the game
  	mvprintw(H-5, 2*H-23, "1. Snakoids Welcomes you to the game");
  	mvprintw(H-3, 2*H-23, "2. Press enter and then an arrow key to start!!");
  	mvprintw(H-1, 2*H-23, "3. Game is simply, press the arrow keys super fast !!");
  	mvprintw(H+1, 2*H-23, "4. Youn win by either surviving 250 turns...");
  	mvprintw(H+3, 2*H-23, "5. Or lose by hitting one of the 5 obstacles");
  	mvprintw(H+5, 2*H-23, "6. Press Q anytime to exit the game..");

  	//offing the colour that is being used
  	attroff(COLOR_PAIR(3));
}



