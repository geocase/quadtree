#ifndef MISC_H
#define MISC_H

namespace Misc {
	typedef struct {
		double x, y;
	} Vector2_t;
	
	typedef struct {
		double x, y, z;
	} Vector3_t;

	inline Vector3_t AddVector3(const Vector3_t a, const Vector3_t b) {
		Vector3_t c; 
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.y + b.z;
		return c;
	}

	inline double Determinant(double a, double b, double c, double d) {
		return (a * d) - (b * c);
	}
}
#endif
