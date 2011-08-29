/*
 *  Vector3D.cpp
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/25/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */

#include "Vector3D.h"

// true if in range, false if out of bounds
bool Vector3D::testIndex(int i){return i >= 0 && i < 3;}

// Single Axis vector rotation (CCW)
Vector3D Vector3D::rotateX(float angle){
	Vector3D result(
					coords[0], 
					coords[1]*cos(angle) - coords[2]*sin(angle), 
					coords[1]*sin(angle) + coords[2]*cos(angle));
	return result;
}
Vector3D Vector3D::rotateY(float angle){
	Vector3D result(
					coords[0]*cos(angle) + coords[2]*sin(angle), 
					coords[1], 
					-coords[0]*sin(angle) + coords[2]*cos(angle));
	return result;
}
Vector3D Vector3D::rotateZ(float angle){
	Vector3D result(
					coords[0]*cos(angle) - coords[1]*sin(angle), 
					coords[0]*sin(angle) + coords[1]*cos(angle), 
					coords[2]);
	return result;
}

// Empty constructor
Vector3D::Vector3D(){}

// Given 3 floats ...
Vector3D::Vector3D(float nx, float ny, float nz){
	coords[0] = nx; coords[1] = ny; coords[2] = nz;
}

// Given 3D-float-array
Vector3D::Vector3D(float nuc[3]){
	setCoords(nuc);
}

// Returns pointer to the first coordinate
float* Vector3D::getCoords(){return &coords[0];}

// Returns i-th coordinate
float Vector3D::getCoord(int i){return coords[i];}

// Coordinate asignation through 3D-float-array
void Vector3D::setCoords(float nuc[3]){
	coords[0] = nuc[0]; coords[1] = nuc[1]; coords[2] = nuc[2];
}

// Asignates i-th coordinate
void Vector3D::setCoord(int i, float v){
	if(testIndex(i))
		coords[i] = v;
}

// Returns dot (.) product calcultion
float Vector3D::dotProduct(Vector3D v){
	float sum = 0.0;
	for(int i = 0; i < 3; i++)
		sum += coords[i]*v.getCoord(i);
	return sum;
}

// Returns this vector norm (scalar length)
float Vector3D::getNorm(){return sqrt(dotProduct(*this));}

// Returns 1-norm vector like this
Vector3D Vector3D::normalize(){
	float norm = getNorm();
	Vector3D result(coords[0]/norm, coords[1]/norm, coords[2]/norm);
	return result;
}

// Returns cross (x) product calculation
Vector3D Vector3D::crossProduct(Vector3D v){
	float 
	x1 = coords[0], 
	x2 = v.getCoord(0), 
	y1 = coords[1], 
	y2 = v.getCoord(1), 
	z1 = coords[2], 
	z2 = v.getCoord(2);
	Vector3D result(y1*z2 - y2*z1,x2*z1 - x1*z2, x1*y2 - x2*y1);
	return result;
}

// Returns by Scalar product
Vector3D Vector3D::byScalarProduct(float s){
	Vector3D result(coords[0]*s, coords[1]*s, coords[2]*s);
	return result;
}

// Adds this vector to v
Vector3D Vector3D::add(Vector3D v){
	Vector3D result(coords[0] + v.getCoord(0), coords[1] + v.getCoord(1), coords[2] + v.getCoord(2));
	return result;
}

// Substracts v to this vector
Vector3D Vector3D::sub(Vector3D v){
	Vector3D result(coords[0] - v.getCoord(0), coords[1] - v.getCoord(1), coords[2] - v.getCoord(2));
	return result;
}

// Rotate angle radians over the specified axis (1 or 0)
Vector3D Vector3D::rotate(float angle, int x, int y, int z){
	Vector3D result = *this;
	if(x == 1)
		result = result.rotateX(angle);
	if(y == 1)
		result = result.rotateY(angle);
	if(z == 1)
		result = result.rotateZ(angle);
	return result;
}

/*
float Vector3D::getTx(Vector3D v){
	float a1 = Vector3D::getFlatAngle(coords[2], coords[1]);
	float a2 = Vector3D::getFlatAngle(v.getCoord(2), v.getCoord(1));
	return a2 - a1;
}
float Vector3D::getTy(Vector3D v){
	float a1 = Vector3D::getFlatAngle(coords[2], coords[0]);
	float a2 = Vector3D::getFlatAngle(v.getCoord(2), v.getCoord(0));
	return a2 - a1;
}
*/