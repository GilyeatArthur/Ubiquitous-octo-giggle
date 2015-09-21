#include "sfwdraw.h"
#include "paddle.h"
#include <iostream>
#include <cstdlib>

//I got a lot of my thought process and structure from Esme's example and cppgameprogramming.com
//Terry helped me understand certain concepts on generating windows
const float SCREEN_WIDTH = 1000;
const float SCREEN_HEIGHT = 600;

struct Player
	{
		float tempx;// = 10;
		float tempy;// = ((SCREEN_HEIGHT / 2) - 40);
		float x;// = tempx;
		float y;// = tempy;
		float w;/* = x + 20*/
		float h;/* = y + 80*/
	};
/*struct Player1
{

};*/

void main()
{
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	
	float xpos = SCREEN_WIDTH/2, ypos = SCREEN_HEIGHT/2;
	float xacc = 0, yacc = 0;
	float xvel = 300, yvel = 300;
	float speed = 100;
	float rad = 15;

	int score[2];
	score[0] = 0;
	score[1] = 0;

	//player 1
	Player p1; 
	p1.tempx = 10;
	p1.tempy = ((SCREEN_HEIGHT / 2) - 40);
	p1.x = p1.tempx;
	p1.y = p1.tempy;
	p1.w = p1.x + 20;
	p1.h = p1.y + 80;

	//player 2
	Player p2;
	p2.tempx = SCREEN_WIDTH - 30;
	p2.tempy = ((SCREEN_HEIGHT / 2) - 40);
	p2.x = p2.tempx;
	p2.y = p2.tempy;
	p2.w = p2.x + 20;
	p2.h = p2.y + 80;

	while (sfw::stepContext())
	{
		sfw::drawLine(SCREEN_WIDTH, SCREEN_HEIGHT - 5, 0, SCREEN_HEIGHT - 5);
		sfw::drawLine(0, 5, SCREEN_WIDTH, 5);
	//this creates and allows player one movement
		p1.h = p1.y + 80;
		paddle::drawPlayer(p1.x, p1.y);
		if (sfw::getKey('w') && p1.y > 10) {paddle::drawPlayer(p1.x, p1.y -= 5);}
		if (sfw::getKey('s') && p1.h < 590) {paddle::drawPlayer(p1.x, p1.y += 5);}

	//this creates and allows player two movement
		p2.h = p2.y + 80;
		paddle::drawPlayer(p2.x, p2.y);
		if (sfw::getKey('o') && p2.y > 10) {paddle::drawPlayer(p2.x, p2.y -= 5);}
		if (sfw::getKey('l') && p2.h < 590) {paddle::drawPlayer(p2.x, p2.y += 5);}
		
	//draws the ball
		sfw::drawCircle(xpos, ypos, rad);
		xpos += xvel * sfw::getDeltaTime();
		ypos += yvel * sfw::getDeltaTime();

	//Reflection on walls and paddles. Terry pointed me the the right direction
	//for this one and let me figure it out from there
		if (ypos - rad < 10)
		{ 
			ypos = ((ypos + rad)-5);
			yvel *= -1;
			xvel *= 1; 
		}
		if (ypos + rad > 590) 
		{ 
			ypos = (ypos - rad);
			yvel *= -1;
			xvel *= 1;
		}
		if (xpos - rad <= p1.w && xpos -rad >= p1.x)
			{
				if (ypos >= p1.y && ypos <= p1.h)
				{ 
					xpos = (p1.w + rad);
					xvel *= -1;
					yvel *= 1;
				}
			}
		if (xpos + rad >= p2.x && xpos + rad <= p2.w)
		{
			if (ypos >= p2.y && ypos <= p2.h)
			{
				xpos = (p2.x - rad);
				xvel *= -1;
				yvel *= 1;
			}
		}
		if (xpos - rad >= SCREEN_WIDTH)
		{
			score[0]++;
			xpos = SCREEN_WIDTH / 2, ypos = SCREEN_HEIGHT / 2;
		}
		if (xpos + rad <= 0)
		{
			score[1]++;
			xpos = SCREEN_WIDTH / 2, ypos = SCREEN_HEIGHT / 2;
		}
		if (score[0] == 5 || score[1] == 5)
		{
			sfw::termContext(); 
		}
	}
	sfw::termContext();
}