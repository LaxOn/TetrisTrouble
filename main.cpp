#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

const int M = 20;
const int N = 100;
int currN = 10;
bool countme = false;
int currx = 180;
int permx = 720;
int curry = 360;



int field[M][N] = {0};

struct Point{int x,y;} a[4], b[4];

int figures[7][4] = {	
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
					};

bool check() {
   for (int i=0;i<4;i++) {
	  if (a[i].x<0 || a[i].x>=currN || a[i].y>=M || N <= currN) return 0;		// boundary check
      else if (field[a[i].y][a[i].x]) return 0;				// 
  }
   return 1;
};


int main() {
    srand(time(0));	 

	RenderWindow window(VideoMode(permx, curry), "The Game!");

    Texture t1,t2,t3;
	t1.loadFromFile("images/tiles.png");
	//t2.loadFromFile("images/background.png");
	//t3.loadFromFile("images/frame.png");

	Sprite s(t1);//, background(t2), frame(t3);

    int dx=0; bool rotate=0; int colorNum=1;
	float timer=0,delay=0.3; 
	Clock clock;
    while (window.isOpen()) {


		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }

			if (e.type == Event::KeyPressed) {
			  if (e.key.code==Keyboard::Up) {rotate=true;}
			  else if (e.key.code==Keyboard::Left) {dx=-1;}
			  else if (e.key.code==Keyboard::Right) {dx=1;}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

		//// <- Move -> ///
		for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }
	    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];

		//////Rotate//////
		if (rotate) {
			Point p = a[1]; //center of rotation
			for (int i=0;i<4;i++) {
				int x = a[i].y-p.y;
				int y = a[i].x-p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
		 	  }
	   	    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
		  }

		///////Tick//////
		if (timer>delay) {

		    for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

			if (!check()) {
				for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

				colorNum=1+rand()%7;
				int n=rand()%7;
				for (int i=0;i<4;i++) {
				    a[i].x = figures[n][i] % 2;
				    a[i].y = figures[n][i] / 2;
				}
			}

		  	timer=0;
		  }

		///////check lines//////////
	    int k=M-1;
		for (int i=M-1;i>0;i--) {
			int count=0;
			for (int j=0;j<currN;j++) {
			    if (field[i][j]) {
			    	count++;

					
				}
				if (k != i) countme = true;

			    field[k][j]=field[i][j]; // this makes line disappear

			}
			if (count<currN) {
				k--;
			}
		}
			//////////////
			if (countme == true) {
				currN++;			// this makes extra "space"/column 
				countme = false;
				currx += 20;
				Vector2u vec2(currx,curry);
				window.setSize(vec2);
				// int col[N] ={0};
				// field[M] = col;
				/*

				add what to remove last line when
				complete and replace below

				++currN;
				currx += 20;
				Vector2u vec2(currx,curry);
				std::cout <<"hey";
				window.setSize(vec2);
				window.setActive(false);
				window.setActive(true);
				addc = false;
				*/
			}
			//////////////

	    dx=0; rotate=0; delay=0.3;

	    /////////draw//////////
	    window.clear(Color::White);	
	    //window.draw(background);
		

	    // show when reach the bottom
		for (int i=0;i<M;i++) {
			for (int j=0;j<currN;j++) {
		         if (field[i][j]==0) {
		         	continue;
				 }
				 s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
				 s.setPosition(j*18,i*18);
				// s.move(28,31); //offset
				 window.draw(s);
			}
		}


		//generate new blocks
		for (int i=0;i<4;i++) {
			s.setTextureRect(IntRect(colorNum*18,0,18,18));
			s.setPosition(a[i].x*18,a[i].y*18);
			//s.move(28,31); //offset
			window.draw(s);
		}

		//window.draw(frame);
	 	window.display();
	}

    return 0;
}