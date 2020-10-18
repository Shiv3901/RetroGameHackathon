#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define WIDTH 10
#define H 30

using namespace std;

int random_num(int low, int high);

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

	object scr;
	int i = 1, count = 0;
	int n = 3;
	bool end = false;

	bool direc = true;

	initscr();

	start_color();

	init_pair(1, COLOR_BLUE, COLOR_BLACK);

	keypad(stdscr, true);

	noecho();

	curs_set(0);

	getmaxyx(stdscr, scr.y, scr.x);

  	object b = {2*H,H,0,false,false};

  	mvprintw(4,0, "What the heck!!\n\nPress enter to start!!\n\n");

  	getch();

  	obstacle obs = {3*H/2, H, true};
  	obstacle obs1 = {3*H/2, H, true};
  	obstacle obs2 = {3*H/2, H, true};
  	obstacle obs3 = {3*H/2, H, true};
  	obstacle obs4 = {3*H/2, H, true};
  	
  	int obs_corr_x[5] = {3*H/2};
  	int obs_corr_y[5] = {H};

  	while(i > 0) {

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



  		if(i % 25 == 0){
  			obs.x = obs_corr_x[0] = random_num(H, 2*H) ;
  			obs.y = obs_corr_y[0] = random_num(H/2, H) ;
  		}else if(i % 17 == 0){
  			obs1.x = obs_corr_x[1] = random_num(H, 2*H) ;
  			obs1.y = obs_corr_y[1] = random_num(H/2, H) ;
  		}else if(i % 12 == 0) {
  			obs2.x = obs_corr_x[2] = random_num(H, 2*H) ;
  			obs2.y = obs_corr_y[2] = random_num(H/2, H) ;
  		}else if(i % 9 == 0) {
  			obs3.x = obs_corr_x[3] = random_num(H, 2*H) ;
  			obs3.y = obs_corr_y[3] = random_num(H/2, H) ;
  		}else {
  			obs4.x = obs_corr_x[4] = random_num(H, 2*H) ;
  			obs4.y = obs_corr_y[4] = random_num(H/2, H) ;
  		}
  		
  		mvprintw(obs.y,obs.x,"x");
  		mvprintw(obs1.y,obs1.x,"u");
  		mvprintw(obs2.y,obs2.x,"y");
  		mvprintw(obs3.y,obs3.x,"g");
  		mvprintw(obs4.y,obs4.x,"d");
  		

  		for(int i = 0 ; i < 2*H ; i++){
  			mvprintw(H/2,H + i,"_");
  			mvprintw(H + H/2,H + i,"-");
  		}

  		for(int i = 1 ; i < H ; i++){
  			mvprintw(H/2 + i,H,"|");
  			mvprintw(H/2 + i,3*H,"|");
  		}


  		



  		// mvvline(0,2*WIDTH,ACS_VLINE,scr.y);
  		// mvvline(0,6*WIDTH,ACS_VLINE,scr.y);

  		mvprintw(b.y,b.x,"o");

  		// for(i=-1;i<4;i++){
    //   		mvprintw(b1.y,b1.x+i,"_");
    //   	}

      	i++;
      
  	}


  	endwin();

	return 0;
}

int random_num(int low, int high){
	return low + (rand() % high);
}