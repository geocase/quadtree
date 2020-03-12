#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include "misc.h"

class cVertex;
class cSegment;
class cPolygon;

class cPath;

class cVertex {
public:
	Misc::Vector2_t position;
	void Rotate(const double ax, const double ay, const double r);
	void PlaceAt(const double nx, const double ny);
	bool InPolygon(cPolygon *p);
	bool InPolygonQuad(cPolygon *p);
};

class cSegment {
public:
	cVertex *a, *b;

	cSegment(double ax, double ay, double bx, double by);
	cSegment(cVertex *na, cVertex *nb);

	cVertex GetPointAt(double ratio);
	cVertex GetIntersection(cSegment *s);

	void Rotate(const double ax, const double ay, const double r);
};

class cPolygon  {
public:
	std::vector<cSegment> faces;
	uint32_t faceCount = 0;

	void AddFace(const cSegment *l);
	void BuildFromVertexArray(cVertex *p, uint32_t nc);
	bool CompletelyInPolygon(cPolygon *p);
	bool PartiallyInPolygon(cPolygon *p);
	void Rotate(const double ax, const double ay, const double r);
};

class cPath {
public:
	std::vector<cSegment> lineDefs;
	uint32_t lineDefCount = 0;
	void AddSegment( const cSegment *l);
	void BuildFromVertexArray(cVertex *p, uint32_t nc);

};
#endif
