#include <iostream>

#include "quadtree.h"
#include "sector.h"

cQuadTree::cQuadTree(double x, double y, double hw) {
	cVertex *n = new cVertex[4];
	n[0].PlaceAt(x - hw, y - hw);
	n[1].PlaceAt(x + hw, y - hw);
	n[2].PlaceAt(x + hw, y + hw);
	n[3].PlaceAt(x - hw, y + hw);
	this->halfWidth = hw;
	this->center.position.x = x;
	this->center.position.y = y;
	this->quad.BuildFromVertexArray(n, 4);
	for(int i = 0; i < 4; i++) {
		this->leafs[i] = NULL;
	}
}

void cQuadTree::BuildLeafs() {
	this->leafs[0] = new cQuadTree(this->center.position.x - this->halfWidth / 2,
	                               this->center.position.y - this->halfWidth / 2,
	                               this->halfWidth / 2);
	this->leafs[1] = new cQuadTree(this->center.position.x + this->halfWidth / 2,
	                               this->center.position.y - this->halfWidth / 2,
	                               this->halfWidth / 2);
	this->leafs[2] = new cQuadTree(this->center.position.x + this->halfWidth / 2,
	                               this->center.position.y + this->halfWidth / 2,
	                               this->halfWidth / 2);
	this->leafs[3] = new cQuadTree(this->center.position.x - this->halfWidth / 2,
	                               this->center.position.y + this->halfWidth / 2,
	                               this->halfWidth / 2);
}

cQuadTree *cQuadTree::FindCollidingQuad(double x, double y) {
	cVertex *t = new cVertex;
	t->PlaceAt(x, y);
	bool check[4];
	if(t->InPolygonQuad(&(this->quad))) {
		for(int i = 0; i < 4; i++) {
			if(this->leafs[i] != NULL) {
				if(t->InPolygonQuad(&(this->leafs[i]->quad))) {
					return this->leafs[i]->FindCollidingQuad(x, y); 
				}
			}
		}
	} else {
		return NULL;
	}
	
	return this;
}
