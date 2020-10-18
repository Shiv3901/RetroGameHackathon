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

int random_num(int low, int high, int corr, int turn);

int check(int* x_corr, int* y_corr, int x, int y);

typedef struct {
	int x;
	int y;
	int c;

	bool mov_hor;
	bool mov_ver;
} object;

typedef struct {
	int x;
	int y;

	bool disp;
} obstacle;

int main()
{

	int trail_x[7], trail_y[7];

	object scr;
	int i = 1, count = 0;
	int n = 3;
	int end = 0;
	int intersection = 0;

	bool direc = true;

	initscr();

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	

	keypad(stdscr, true);

	noecho();

	curs_set(0);

	getmaxyx(stdscr, scr.y, scr.x);

  	object b = {2*H,H,0,false,false};

  	for(int i = 0 ; i < 7 ; i++){
  		trail_y[i] = H;
  		trail_x[i] = 2*H;
  	}

  	mvprintw(4,0, "What the heck!!\n\nPress enter to start!!\n\n");

  	getch();

  	obstacle obs = {H, H/2+1, true};      //x
  	obstacle obs1 = {3*H-5, H/2+1, true};	//u
  	obstacle obs2 = {H,3*H/2-3, true};	//y
  	obstacle obs3 = {3*H-5, 3*H/2-3, true};	//g
  	obstacle obs4 = {2*H-2, H-1, true};		//d
  	
  	int obs_corr_x[5] = {3*H/2};
  	int obs_corr_y[5] = {H};

  	while(i > 0) {


  		trail_x[0] = b.x;
  		trail_y[0] = b.y;

  		for(int i=7; i>0; i--){
  			trail_x[i] = trail_x[i-1];
  			trail_y[i] = trail_y[i-1];
  		}

  		switch(getch()){

  			case KEY_LEFT:
  				if((b.x - 1) >= H){
  					b.x--;
  				}
  				break;

  			case KEY_RIGHT:
  				if((b.x + 1) <= 3*H){
  					b.x++;
  				}
  				break;


  			case 'q': 
  				endwin(); 
  				return 0;
  				break;
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

  		intersection = check(obs_corr_x, obs_corr_y, b.x, b.y);

  		



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

  		if(i == 100){
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