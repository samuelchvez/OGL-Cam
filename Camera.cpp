/*
 *  Camera.cpp
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/25/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */
#include "Camera.h"

// Empty constructor
Camera::Camera(){}

// Full constructor
Camera::Camera(
			   Vector3D f, 
			   double d, 
			   double rx, 
			   double ry, 
			   double rz, 
			   double fo, 
			   double ar, 
			   double zn, 
			   double zf){
	setUpWith(f, d, rx, ry, rz, fo, ar, zn, zf);
}

// Setup camera with full parameter control
void Camera::setUpWith(
					   Vector3D f, 
					   double d, 
					   double rx, 
					   double ry, 
					   double rz, 
					   double fo,
					   double ar, 
					   double zn, 
					   double zf){	
	focus = f; distance = d;
	xangle = rx; yangle = ry; zangle = rz;
	fovy = fo; aspectRatio = ar;
	zNear = zn; zFar = zf;
}

// Calculates eye position
Vector3D Camera::getEye(){
	
	// Base axsis
	Vector3D defaultAxis(0.0, 0.0, 1.0);
	Vector3D resultAxis = defaultAxis.rotate(xangle, 1, 0, 0);
	
	// Rotation
	resultAxis = resultAxis.rotate(yangle, 0, 1, 0).byScalarProduct(distance);
	return focus.add(resultAxis);
}

Vector3D Camera::getFocus(){
	
	// If there are no over-own-center rotations
	if(xoangle == 0.0 && yoangle == 0.0)
		return focus;
	
	// Get new space coordinates refference
	Vector3D eye = getEye();
	Vector3D dirAxis = eye.sub(focus).normalize(); // z' (eye - focus, not focus - eye)
	// couse the z+ direction
	Vector3D up = getSingleUp(); // y'
	Vector3D right = dirAxis.crossProduct(up).normalize(); // x'
	
	// Rotate standar position focus
	Vector3D pivotalAxis(0.0, 0.0, -distance);
	pivotalAxis = pivotalAxis.rotate(xoangle, 1, 0, 0);
	pivotalAxis = pivotalAxis.rotate(yoangle, 0, 1, 0);
	
	// Translate new standar position focus to the new space coordinates refference
	Vector3D nuPivotalAxis = right.byScalarProduct(pivotalAxis.getCoord(0));
	nuPivotalAxis = nuPivotalAxis.add(up.byScalarProduct(pivotalAxis.getCoord(1)));
	nuPivotalAxis = nuPivotalAxis.add(dirAxis.byScalarProduct(pivotalAxis.getCoord(2)));
	return eye.add(nuPivotalAxis);
}

// Calculates local north vector for this Camera (without over-own-center rotations)
Vector3D Camera::getSingleUp(){
	
	// Base moving axis
	Vector3D defaultAxis(0.0, 0.0, 1.0);
	defaultAxis = defaultAxis.byScalarProduct(distance);
	Vector3D defaultUp(0.0, 1.0, 0.0);
	defaultUp = defaultUp.rotate(zangle, 0, 0, 1);
	Vector3D defaultUpAxis = defaultAxis.add(defaultUp);
	
	// Rotated up axis
	Vector3D resultUpAxis = defaultUpAxis.rotate(xangle, 1, 0, 0);
	resultUpAxis = resultUpAxis.rotate(yangle, 0, 1, 0);
	
	// Rotated base axis
	Vector3D resultAxis = defaultAxis.rotate(xangle, 1, 0, 0);
	resultAxis = resultAxis.rotate(yangle, 0, 1, 0);
	
	// Actual up
	return resultUpAxis.sub(resultAxis);
	
}

// Calculates local north vector for this Camera
Vector3D Camera::getUp(){
	
	// If there are no over-own-center rotations
	if(xoangle == 0.0 && yoangle == 0.0)
		return getSingleUp();
	
	// Get new space coordinates refference
	Vector3D eye = getEye();
			// Not using getFocus ... we need original focus, not rotated one
	Vector3D dirAxis = eye.sub(focus).normalize(); // z' (eye - focus, not focus - eye)
	                                               // couse the z+ direction
	Vector3D up = getSingleUp(); // y'
	Vector3D right = dirAxis.crossProduct(up).normalize(); // x'
	
	// Rotate standar position focus
	Vector3D pivotalAxis(0.0, 1.0, 0.0);
	pivotalAxis = pivotalAxis.rotate(xoangle, 1, 0, 0);
	pivotalAxis = pivotalAxis.rotate(yoangle, 0, 1, 0);
	
	// Translate new standar position focus to the new space coordinates refference
	Vector3D nuPivotalAxis = right.byScalarProduct(pivotalAxis.getCoord(0));
	nuPivotalAxis = nuPivotalAxis.add(up.byScalarProduct(pivotalAxis.getCoord(1)));
	nuPivotalAxis = nuPivotalAxis.add(dirAxis.byScalarProduct(pivotalAxis.getCoord(2)));
	return nuPivotalAxis;
	
}

// Boring accessors
double Camera::getFovy(){return fovy;}
double Camera::getAspectRatio(){return aspectRatio;}
double Camera::getZNear(){return zNear;}
double Camera::getZFar(){return zFar;}
double Camera::getDistance(){return distance;}

// Boring setters
void Camera::setFocus(Vector3D v){focus = v;}
void Camera::setFovy(double f){fovy = f;}
void Camera::setAspectRatio(double ar){aspectRatio = ar;}
void Camera::setZNear(double zn){zNear = zn;}
void Camera::setZFar(double zf){zFar = zf;}
void Camera::setDistance(double d){distance = d;}

// Rotate z radians over local Z-axis
void Camera::rotateOverZAxis(double z){zangle += z;}

// Given x, y (radians), rotates this Cammera over x (if ix = 1) and y (if iy = 1) axses
// without loosing focus direction
void Camera::rotateFocussed(double x, double y, int ix, int iy){
	if(ix == 1)
		xangle += x;
	if(iy == 1)
		yangle += y;
}

// Manually sets x, y and z rotation
void Camera::setRotations(double x, double y, double z, double ox, double oy, int ix, int iy, int iz, int iox, int ioy){
	if(ix == 1)
		xangle = x;
	if(iy == 1)
		yangle = y;
	if(iz == 1)
		zangle = z;
	if(iox == 1)
		xoangle = z;
	if(ioy == 1)
		yoangle = z;
}

// Rotate focus over the sphere (getEye, distance)
void Camera::rotateView(double rx, double ry, int ix, int iy){
	if(ix == 1)
		xoangle += rx;
	if(iy == 1)
		yoangle += ry;
}