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
	bool direc = true;

	//changing colour pattern to 3  		
  	attron(COLOR_PAIR(3));
  	//displaying the initial statistics of the game
  	mvprintw(H-3,2*H-2, "Snackoids Welcomes you to the game");
  	mvprintw(H-1,2*H-2, "Press enter and then an arrow key to start!!");
  	//offing the colour that is being used
  	attroff(COLOR_PAIR(3));

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
  	int i = 1;

  	//it just runs forver, as i++ is done inside the loop
  	//the only way you can get out if you hit or survive till 500 turns
  	while(i > 0) {

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

  		

  		if( (b.y - 1) == H/2){
  			direc = true;
  		} else if((b.y + 1) == H + H/2){
  			direc = false;
  		}


  		if(direc == true){
  			b.y++;
  		} else {
  			b.y--;
  		}
 		

  		refresh();
  		erase();  

  		srand (time(NULL)) ;



  		if(i % 25 == 0){
  			obs.x = obs_corr_x[0] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs.y = obs_corr_y[0] = random_num(H/2+1, H-4, b.y, 1) ;
 		// }else if(i % 17 == 0){
  			obs1.x = obs_corr_x[1] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs1.y = obs_corr_y[1] = random_num(H/2+1, H-4, b.y, 1) ;
  		// }else if(i % 12 == 0) {
  			obs2.x = obs_corr_x[2] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs2.y = obs_corr_y[2] = random_num(H/2+1, H-4, b.y, 1) ;
  		// }else if(i % 9 == 0) {
  			obs3.x = obs_corr_x[3] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs3.y = obs_corr_y[3] = random_num(H/2+1, H-4, b.y, 1) ;
  		// }else {
  			obs4.x = obs_corr_x[4] = random_num(H+1, 2*H-6, b.x, 2) ;
  			obs4.y = obs_corr_y[4] = random_num(H/2+1, H-4, b.y, 1) ;
  		}



  		attron(COLOR_PAIR(2));
		
  		for(int h = 0 ; h < 3 ; h++) {

  			for(int g = 0 ; g < 5 ; g++) {
  				mvprintw(obs.y+h,obs.x+g,"x");
  				mvprintw(obs1.y+h,obs1.x+g,"u");
	  			mvprintw(obs2.y+h,obs2.x+g,"y");
  				mvprintw(obs3.y+h,obs3.x+g,"g");
  				mvprintw(obs4.y+h,obs4.x+g,"d");
  			}

  		}
  		attroff(COLOR_PAIR(2));
  		
  		attron(COLOR_PAIR(3));

  		for(int i = 0 ; i < 2*H ; i++){
  			mvprintw(H/2,H + i,"_");
  			mvprintw(H + H/2,H + i,"-");
  		}

  		for(int i = 1 ; i < H ; i++){
  			mvprintw(H/2 + i,H,"|");
  			mvprintw(H/2 + i,3*H,"|");
  		}

  		mvprintw(5, 10, "Count: %i", i);

  		attroff(COLOR_PAIR(3));
  		

  		end = check(obs_corr_x, obs_corr_y, b.x, b.y);

  		if(end == -1){
  			erase();
  			mvprintw(H-1, 2*H-2, "You Lost !!");

  			getch();
  			endwin();
  			return 0 ;
  		}

  		if(i == 500){
  			erase();
  			mvprintw(H-1, 2*H-2, "You Won !!");
  			getch();
  			endwin();
  			return 0 ;
  		}

  		attron(COLOR_PAIR(4));
  			mvprintw(b.y,b.x,"o");
  		attroff(COLOR_PAIR(4));

  		attron(COLOR_PAIR(1));
  			for(int i = 0; i < 7; i++){
  				mvprintw(trail_y[i], trail_x[i], "r");
  			}  			
  		attroff(COLOR_PAIR(1));

      	i++;
      
  	}


  	endwin();

	return 0;
}

int random_num(int low, int high, int corr, int turn){

	int random = low + (rand() % high);

	turn += 2;

	while(random >= corr - turn && random <= corr + turn){
		random = low + (rand() % high);
	}

	return random;

}

int check(int* x_corr, int* y_corr, int x, int y)
{
	for(int i = 0 ; i < 5 ; i++){

		for(int u = 0 ; u < 5 ; u++){
			for(int h = 0 ; h < 3 ; h++){

				if( ( x_corr[i] + u ) == x && ( y_corr[i] + h ) == y){
					return -1;
				}

			}
		}

	}

	return 0;
}