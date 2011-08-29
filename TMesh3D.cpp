/*
 *  TMesh3D.cpp
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/24/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */

#include "TMesh3D.h"

// Empty constructor
TMesh3D::TMesh3D(){}

// Full constructor
TMesh3D::TMesh3D(
				 MeshType t, 
				 float *pos, 
				 float *col, 
				 int *ord, 
				 int len, 
				 int olen){
	setupWith(t, pos, col, ord, len, olen);
}

// Setup a mesh with full parammeter control
void TMesh3D::setupWith(
						MeshType t, 
						float *pos, 
						float *col, 
						int *ord, 
						int len, 
						int olen){
	type = t;
	length = len;
	vex = new Vertex[len];
	setOrder(ord, olen);
	setVexCol(col, len);
	setVexPos(pos, len);
}

// Returns the number of vertex on this Mesh
int TMesh3D::getLength(){return length;}

// Stores new vertex array
void TMesh3D::setVex(Vertex *nuvex, int size){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < 3; j++){
			vex[i].pos[j] = nuvex[i].pos[j];
			vex[i].col[j] = nuvex[i].col[j];
		}
}

// Updates vertex positions
void TMesh3D::setVexPos(float *nuvex, int size){
	if(length == size)
		for(int i = 0; i < size; i++)
			for(int j = 0; j < 3; j++)
				vex[i].pos[j] = nuvex[i*3 + j];
}

// Updates vertex colors
void TMesh3D::setVexCol(float *nuvex, int size){
	if(length == size)
		for(int i = 0; i < size; i++)
			for(int j = 0; j < 3; j++)
				vex[i].col[j] = nuvex[i*3 + j];
}

// Assign new render order
void TMesh3D::setOrder(int *nuorder, int nolen){
	order = new int[nolen];
	for(int i = 0; i < nolen; i++)
		order[i] = nuorder[i];
	orderLength = nolen;
}

// Sets the new mesh type
void TMesh3D::setMeshType(MeshType t){type = t;}

// Returns pointer to the vertex array
Vertex * TMesh3D::getVertexes(){return vex;}

// Returns pointer to the render-order array
int * TMesh3D::getOrder(){return order;}

// Returns number of render steps
int TMesh3D::getOrderLength(){return orderLength;}

// Returns pos-th Vertex on this Mesh
Vertex TMesh3D::getVex(int pos){
	if(pos >= 0 && pos < length)
		return vex[pos];
	return vex[pos];
}

// Returns quads or triangle mesh render
MeshType TMesh3D::getMeshType(){return type;}