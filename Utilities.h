/*
 *  Vertex.h
 *  House Demo
 *
 *  Created by Samuel Chavez on 8/24/11.
 *  Copyright 2011 Nozzmo. All rights reserved.
 *
 */

struct Vertex{
	float pos[3];
	float col[3];
};

enum MeshType { MESH_SQUARE, MESH_TRIANGLE };