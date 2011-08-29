/*
 *  TMesh3D.h
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/24/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */
#include "Utilities.h"

class TMesh3D{
	int length, orderLength;
	Vertex *vex;
	int *order;
	MeshType type;
public:
	// Construction stage
	TMesh3D();
	TMesh3D(MeshType t, float *, float *, int *, int, int);
	void setupWith(MeshType t, float *, float *, int *, int, int);
	
	// Setters
	void setLength(int);
	void setVex(Vertex *, int);
	void setVexPos(float *, int);
	void setVexCol(float *, int);
	void setOrder(int *, int);
	void setMeshType(MeshType);
	
	// Accessors
	int getLength();
	Vertex * getVertexes();
	int * getOrder();
	int getOrderLength();
	Vertex getVex(int);
	MeshType getMeshType();
};