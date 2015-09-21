#pragma once
#include "sfwdraw.h"
#include <iostream>

namespace ball
{
	void moveBall()
	{
		
		
		float xpos = 300, ypos = 300;
		float xacc = 0, yacc = 0;
		float xvel = 0, yvel = 0;
		float speed = 100;
		float rad = 30;

		sfw::drawCircle(xpos, ypos, rad);
		
	}
}