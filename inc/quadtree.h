#ifndef QUADTREE_H
#define QUADTREE_H
#include "sector.h"

class cQuadTree;

class cQuadTree {
public:
	const uint8_t NODECOUNT = 4;
	cQuadTree *leafs[4];
	
	double halfWidth;
	cVertex center;
	cPolygon quad;

	cQuadTree(double x, double y, double hw);
	void BuildLeafs();
	cQuadTree *FindCollidingQuad(double x, double y);
};
#endif
