/*
 *  Camera.h
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/25/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */

#include "TMesh3D.h"
#include "Vector3D.h"

class Camera{
	Vector3D focus;
	double distance, xangle, yangle, zangle, fovy, aspectRatio, zNear, zFar, xoangle, yoangle;
private:
	Vector3D getSingleUp();
public:
	// Construction stage
	Camera();
	Camera(
		   Vector3D, 
		   double, 
		   double, 
		   double, 
		   double, 
		   double, 
		   double, 
		   double, 
		   double);
	void setUpWith(
				   Vector3D, 
				   double, 
				   double, 
				   double, 
				   double, 
				   double, 
				   double,
				   double, 
				   double);
	
	// Complex accessors
	Vector3D getEye();
	Vector3D getUp();
	
	// Simple accessors
	Vector3D getFocus();
	double getFovy();
	double getAspectRatio();
	double getZNear();
	double getZFar();
	double getDistance();
	
	// Setters
	void setFocus(Vector3D);
	void setFovy(double);
	void setAspectRatio(double);
	void setZNear(double);
	void setZFar(double);
	void setDistance(double);
	
	// Rotation management
	void rotateOverZAxis(double);
	void rotateFocussed(double, double, int, int);
	void setRotations(double, double, double, double, double, int, int, int, int, int);
	void rotateView(double, double, int, int);
};