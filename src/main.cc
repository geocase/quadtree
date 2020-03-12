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

	cQuadTree *t = new cQuadTree(320, 320, 200);
	std::cout << "OUT" << std::endl;
	t->BuildLeafs();
	t->leafs[0]->BuildLeafs();
	t->leafs[0]->leafs[0]->BuildLeafs();
	while(!primIn.windowExit) {
		primFPS.StartFrame();
		primWin.DrawPolygon(&(t->quad), col);
		for(int i = 0; i < t->NODECOUNT; i++) {
			primWin.DrawPolygon(&(t->leafs[i]->quad), col);
			primWin.DrawPolygon(&(t->leafs[0]->leafs[i]->quad), col);
			primWin.DrawPolygon(&(t->leafs[0]->leafs[0]->leafs[i]->quad), col);
		}
		primWin.Update();
		primFPS.EndFrame();
		
		primIn.Update();
		std::cout << "Frametime: " << primFPS.GetFrameTime() << std::endl;
	}

	return 0;
}
