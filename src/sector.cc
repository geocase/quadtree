#include <iostream>
#include <cmath>
#include "sector.h"
#include "misc.h"

#include "window.h"

void cVertex::Rotate(const double ax, const double ay, const double r) {
	double nx = (this->position.x - ax) * std::cos(r) - (this->position.y - ay) * std::sin(r);
	double ny = (this->position.y - ay) * std::cos(r) + (this->position.x - ax) * std::sin(r);

	this->PlaceAt(nx + ax, ny + ay);
}

void cVertex::PlaceAt(const double nx, const double ny) {
	this->position.x = nx;
	this->position.y = ny;
}

bool cVertex::InPolygon(cPolygon *p) {
	// Get quad of shape
	double yMin = p->faces.at(0).a->position.y, yMax = p->faces.at(0).a->position.y;
	double xMin = p->faces.at(0).a->position.x, xMax = p->faces.at(0).a->position.x;
	for(uint32_t i = 0; i < p->faceCount; i++) {
		if(p->faces.at(i).a->position.x < xMin) { xMin = p->faces.at(i).a->position.x;}
		if(p->faces.at(i).a->position.x > xMax) { xMax = p->faces.at(i).a->position.x;}
		if(p->faces.at(i).a->position.y < yMin) { yMin = p->faces.at(i).a->position.y;}
		if(p->faces.at(i).a->position.y > yMax) { yMax = p->faces.at(i).a->position.y;}
	}

	// If point isn't even in the quad then throw it out
	if(this->position.x < xMin || this->position.x > xMax || this->position.y < yMin || this->position.y > yMax) {
		return false;
	}

	// Otherwise move to "raycast" collision detection
	/* Basically:
	 * Find intersection of testLine (a segment extending from the testing
	 * point coords all the way to the xMax value of the polygon)
	 * Then, if point is within the checked line vertical bounaries and it is 
	 * to the right of the point, count it as a proper "collision."
	 */

	cVertex *endPoint = new cVertex;
	endPoint->PlaceAt(xMax, this->position.y);
	cSegment *testLine = new cSegment(this, endPoint);
	uint32_t colliderCount = 0;
	cVertex collisionPoint;

	for(uint32_t i = 0; i < p->faceCount; i++) {
		collisionPoint = testLine->GetIntersection(&(p->faces.at(i))); 
		// This is the y boundary check
		if(((p->faces.at(i).a->position.y >= p->faces.at(i).b->position.y) &&
		    (collisionPoint.position.y >= p->faces.at(i).b->position.y) &&
			(collisionPoint.position.y <= p->faces.at(i).a->position.y)) ||
		   ((p->faces.at(i).a->position.y <= p->faces.at(i).b->position.y) &&
			(collisionPoint.position.y <= p->faces.at(i).b->position.y) &&
		    (collisionPoint.position.y >= p->faces.at(i).a->position.y))) {
			// This is the "to the right" check
	   		if(this->position.x <= collisionPoint.position.x) {
				colliderCount++;
			}
		}
	}
	
	/* If collisions are even, then it's outside of the polygon, otherwise
	 * it resides inside
	 */
	
	return !(colliderCount % 2 == 0);
}

cSegment::cSegment(double ax, double ay, double bx, double by) {
	this->a = new cVertex;
	this->b = new cVertex;
	this->a->position.x = ax;
	this->a->position.y = ay;
	this->b->position.x = bx;
	this->b->position.y = by;
}

cSegment::cSegment(cVertex *na, cVertex *nb) {
	this->a = na;
	this->b = nb;
}

cVertex cSegment::GetPointAt(double ratio) {
	cVertex temp;
	temp.position.x = (this->a->position.x - this->b->position.x) * ratio + this->b->position.x;
	temp.position.y = (this->a->position.y - this->b->position.y) * ratio + this->b->position.y;

	return temp;
}

cVertex cSegment::GetIntersection(cSegment *s) {
	cVertex t;
	double x1 = this->a->position.x, y1 = this->a->position.y;
	double x2 = this->b->position.x, y2 = this->b->position.y;
	double x3 = s->a->position.x, y3 = s->a->position.y;
	double x4 = s->b->position.x, y4 = s->b->position.y;
	t.position.x = Misc::Determinant(Misc::Determinant(x1, y1, x2, y2), Misc::Determinant(x1, 1, x2, 1), 
	                                 Misc::Determinant(x3, y3, x4, y4), Misc::Determinant(x3, 1, x4, 1)) / 
	               Misc::Determinant(Misc::Determinant(x1, 1, x2, 1), Misc::Determinant(y1, 1, y2, 1),
	                                 Misc::Determinant(x3, 1, x4, 1), Misc::Determinant(y3, 1, y4, 1));

	t.position.y = Misc::Determinant(Misc::Determinant(x1, y1, x2, y2), Misc::Determinant(y1, 1, y2, 1),
	                                 Misc::Determinant(x3, y3, x4, y4), Misc::Determinant(y3, 1, y4, 1)) /
	               Misc::Determinant(Misc::Determinant(x1, 1, x2, 1), Misc::Determinant(y1, 1, y2, 1),
	                                 Misc::Determinant(x3, 1, x4, 1), Misc::Determinant(y3, 1, y4, 1));
	return t;
}

void cSegment::Rotate(const double ax, const double ay, const double r) {
	a->Rotate(ax, ay, r);
	b->Rotate(ax, ay, r);
}

void cPolygon::AddFace(const cSegment *l) {
	this->faces.push_back(*l);	
	this->faceCount++;
}

void cPolygon::BuildFromVertexArray(cVertex *p, uint32_t nc) {
	for(uint32_t i = 0; i < nc; i++) {
		if(i + 1 > nc - 1) {
			this->AddFace(new cSegment(&p[i], &p[0]));
		} else {
			this->AddFace(new cSegment(&p[i], &p[i+1]));
		}
	}
}

bool cPolygon::CompletelyInPolygon(cPolygon *p) {
	for(uint32_t i = 0; i < this->faceCount; i++) {
		if(!(this->faces.at(i).a->InPolygon(p)) || !(this->faces.at(i).b->InPolygon(p))) {
			return false;
		}
	}

	return true;
}

bool cPolygon::PartiallyInPolygon(cPolygon *p) {
	for(uint32_t i = 0; i < this->faceCount; i++) {
		if((this->faces.at(i).a->InPolygon(p)) || (this->faces.at(i).b->InPolygon(p))) {
			return true;
		}
	}

	return false;
}
void cPolygon::Rotate(const double ax, const double ay, const double r) {
	for(uint32_t i = 0; i < this->faceCount; i++) {
		this->faces.at(i).Rotate(ax, ay, r);
	}
}

void cPath::AddSegment(const cSegment *l) {
	this->lineDefs.push_back(*l);
	this->lineDefCount++;
}

void cPath::BuildFromVertexArray(cVertex *p, uint32_t nc) {
	for(uint32_t i = 0; i < nc - 1; i++) {
		this->AddSegment(new cSegment(&p[i], &p[i+1]));
	}
}
