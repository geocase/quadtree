#include <iostream>

#include "fps.h"
#include "sector.h"
#include "window.h"
#include "input.h"
#include "quadtree.h"

int main() {
	srand(time(NULL));
	cWindow primWin;
	cInput primIn;
	
	sColor_t col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	sColor_t red;
	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;

	cFPS primFPS;
	primFPS.StartFPSCounter();

	cQuadTree *t = new cQuadTree(320, 320, 320, 10);
	std::cout << "OUT" << std::endl;
	t->BuildLeafs();
	cQuadTree *temp;

	while(!primIn.windowExit) {
		primFPS.StartFrame();
		primWin.DrawQuadTree(t, col);
		primWin.Update();
		primFPS.EndFrame();
		
		temp = t->FindCollidingQuad(primIn.mouseX, primIn.mouseY);
		if(temp != NULL) {
			temp->BuildLeafs();
		}
		primIn.Update();
		std::cout << "Frametime: " << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
