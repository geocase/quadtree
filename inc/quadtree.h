#ifndef QUADTREE_H
#define QUADTREE_H
#include "sector.h"

class cQuadTree;

class cQuadTree {
public:
	const uint8_t NODECOUNT = 4;
	cQuadTree *leafs[4];
	
	double halfWidth;
	double minimumHalfWidth;
	cVertex center;
	cPolygon quad;

	cQuadTree(double x, double y, double hw, double min);
	void BuildLeafs();
	cQuadTree *FindCollidingQuad(double x, double y);
};
#endif
