/*
 *  Vector3D.h
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/25/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */
#include <math.h>
#define PI 3.14159265
class Vector3D{
	float coords[3];
	
private:
	// Local utilities
	bool testIndex(int);
	Vector3D rotateX(float);
	Vector3D rotateY(float);
	Vector3D rotateZ(float);
public:
	// Construction stage
	Vector3D();
	Vector3D(float, float, float);
	Vector3D(float[3]);
	
	// Accessors
	float* getCoords();
	float getCoord(int);
	void setCoords(float[3]);
	void setCoord(int, float);
	float dotProduct(Vector3D);
	
	// LA utilities
	float getNorm();
	Vector3D normalize();
	Vector3D crossProduct(Vector3D);
	Vector3D byScalarProduct(float);
	Vector3D add(Vector3D);
	Vector3D sub(Vector3D);
	Vector3D rotate(float, int, int, int);
	
	/*
	float getTx(Vector3D);
	float getTy(Vector3D);
	static float getFlatAngle(float x, float y){
		float xp = abs(x), yp = abs(y), sangle = 0.0;
		if(xp == 0){
			if(y == 0)
				return 0.0;
			else
				if(y > 0)
					return PI/2.0;
				else
					return 3*PI/2.0;
		}
		else{
			sangle = (float)atan(yp/xp);
			if(x > 0)
				if(y >= 0)
					return sangle;
				else
					return 2*PI - sangle;
				else
					if(y >= 0)
						return PI - sangle;
					else
						return PI + sangle;
		}
	}
	*/
};