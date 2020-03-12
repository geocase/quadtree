#ifndef QUADTREE_H
#define QUADTREE_H
#include "sector.h"

class cQuadTree;

class cQuadTree {
public:
	const uint8_t NODECOUNT = 4;
	cQuadTree **leafs;
	
	double halfWidth;
	cVertex center;
	cPolygon quad;

	cQuadTree(double x, double y, double hw);
	void BuildLeafs();
};
#endif
