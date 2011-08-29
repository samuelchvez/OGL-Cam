//
//  main.cpp
//  OpenGL Template
//
//  Created by Samuel Chavez on 8/24/11.
//  Copyright Nozzmo 2011. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
	#include <OpenAl/al.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "Camera.h"

// Mesh models
TMesh3D house;
TMesh3D floo;

// Camera managment object
Camera cam;

// Funny animation parammeter
float rot = 0.0;

// Fog
GLfloat density = 0.0019;
GLfloat fogColor[4] = {0.0, 0.0, 0.0, 1.0};

// Method signatures
void init();
static void redraw(void);
void setupView();
void updateCamera();
void renderMesh(TMesh3D);

// Debug method signatures
void print(TMesh3D);
void printVector(Vector3D);

// Main
int main(int argc, char **argv) {
	
	// Setup environment management object
	init();
	
	// Setup GLUT (environment display manager)
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("House Demo");
	glEnable(GL_DEPTH_TEST);
	
	// Fog
	glEnable (GL_FOG);
	glFogi (GL_FOG_MODE, GL_EXP2);
	glFogfv (GL_FOG_COLOR, fogColor);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST);
	
	// Repaint function
	glutDisplayFunc(redraw);
	
	// Setup default world view
	setupView();
	glutMainLoop();
	
	return 0;
	
}

// Initiates mesh and camera objects
void init(){
	
	// Create mesh models
	
	// House Vertex positions
	float vexesp[22][3] = {
		// Front
		{	0.0,	7.0,	5.0		},
		{	-5.0,	3.0,	5.0		},
		{	-5.0,	-3.0,	5.0		},
		{	-5.0,	-7.0,	5.0		},
		{	-2.0,	-7.0,	5.0		},
		{	-2.0,	-3.0,	5.0		},
		{	2.0,	-3.0,	5.0		},
		{	2.0,	-7.0,	5.0		},
		{	5.0,	-7.0,	5.0		},
		{	5.0,	-3.0,	5.0		},
		{	5.0,	3.0,	5.0		},
		// Back
		{	0.0,	7.0,	-5.0	},
		{	-5.0,	3.0,	-5.0	},
		{	-5.0,	-3.0,	-5.0	},
		{	-5.0,	-7.0,	-5.0	},
		{	-2.0,	-7.0,	-5.0	},
		{	-2.0,	-3.0,	-5.0	},
		{	2.0,	-3.0,	-5.0	},
		{	2.0,	-7.0,	-5.0	},
		{	5.0,	-7.0,	-5.0	},
		{	5.0,	-3.0,	-5.0	},
		{	5.0,	3.0,	-5.0	}
	};
	
	// House Vertex colors
	float vexesc[22][3] = {
		// Front
		{0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 1.0, 0.0},
		{1.0, 1.0, 0.0},
		{1.0, 1.0, 0.0},
		// Back
		{0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 1.0, 0.0},
		{1.0, 1.0, 0.0},
		{1.0, 1.0, 0.0}
	};
	
	// House Vertex rendering order
	int vorder[66] = {
		// Front
		0,1,10,
		1,2,10,
		5,2,3,
		5,3,4,
		6,7,8,
		9,6,8,
		10,2,9,
		// Back
		11,12,21,
		12,13,21,
		16,13,14,
		16,14,15,
		17,18,19,
		20,17,19,
		21,13,20,
		// Left seil
		0,12,1,
		0,11,12,
		// Right Seil
		0,10,21,
		0,21,11,
		// Left wall
		1,14,3,
		1,12,14,
		// Right wall
		10,8,19,
		10,19,21
	};
	house.setupWith(MESH_TRIANGLE, 
					&vexesp[0][0], 
					&vexesc[0][0],
					&vorder[0], 
					22, 
					66);
	
	// Floor Vertex positions
	float fvexesp[4][3] = {
		// Front
		{	-500.0,	-7.0,	500.0		},
		{	500.0,	-7.0,	500.0		},
		{	500.0,	-7.0,	-500.0		},
		{	-500.0,	-7.0,	-500.0	}
	};
	
	// Floor Vertex colors
	float fvexesc[4][3] = {
		{0.0, 0.7, 0.0},
		{0.0, 0.7, 0.0},
		{0.0, 0.7, 0.0},
		{0.0, 0.7, 0.0}
	};
	
	// Floor Vertex rendering order
	int fvorder[4] = {
		0,1,2,3
	};
	floo.setupWith(MESH_SQUARE, 
					&fvexesp[0][0], 
					&fvexesc[0][0],
					&fvorder[0], 
					4, 
					4);
	
	// Create camera
	Vector3D focus(0.0, 0.0, 0.0);
	cam.setUpWith(focus,   // Focus point
				  2,     // Distance from focus
				  0.-3,    // X-rotation
				  0.0,    // Y-rotation
				  PI,     // Z-rotation
				  45,      // Field of view Y angle
				  1.0,     // Aspect Ratio
				  1.0,     // Near clipping plane
				  1000.0); // Far clipping plane
}

// Redraws frame
static void redraw(void){
	
	// Get ready
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Update view state
	updateCamera();
	
	// DRAW!
	
	// Scene
	glPushMatrix();
	renderMesh(house);
	renderMesh(floo);
	glPopMatrix();
	
	// Put the drawing on screen
	glutSwapBuffers();
	glutPostRedisplay();
}

// Uses camera data to update gluLookAt
void updateCamera(){
	
	// Update camera parammeters
	Vector3D eye = cam.getEye();
	Vector3D focus = cam.getFocus();
	Vector3D up = cam.getUp();
	
	// Starts fun
	//cam.rotateView(0.0006, 0.0006, 0, 1);
	cam.rotateFocussed(0.0001, 0.0005, 0, 1);
	rot += 0.007;
	cam.setDistance(rot);
	/*cam.rotateOverZAxis(0.001);
	;*/
	// End fun
	
	// Update world view
	gluLookAt(eye.getCoord(0), 
			  eye.getCoord(1), 
			  eye.getCoord(2), 
			  focus.getCoord(0), 
			  focus.getCoord(1), 
			  focus.getCoord(2), 
			  up.getCoord(0), 
			  up.getCoord(1), 
			  up.getCoord(2));
}

// Sets default environment view
void setupView(){
	glMatrixMode(GL_PROJECTION);
	gluPerspective(cam.getFovy(),
				   cam.getAspectRatio(),
				   cam.getZNear(),
				   cam.getZFar());
	glMatrixMode(GL_MODELVIEW);
}

// Given a Mesh object, renders it on screen
void renderMesh(TMesh3D mesh){
	if(mesh.getMeshType() == MESH_SQUARE)
		glBegin(GL_QUADS);
	if(mesh.getMeshType() == MESH_TRIANGLE)
		glBegin(GL_TRIANGLES);
	for (int a = 0; a < mesh.getOrderLength(); a++){
		Vertex currentVer = mesh.getVex(mesh.getOrder()[a]);
		glColor3fv(currentVer.col);
		glVertex3fv(currentVer.pos);
	}
	glEnd();
}

// DEBUG METHODS

/* -- MESH PRINT SNIPPET -- */
void print(TMesh3D t){
	Vertex *vexr = t.getVertexes();
	int len = t.getLength();
	printf("Positions:\n");
	for(int i = 0; i < len; i++)
		printf("%i(%f,%f,%f)\n", i, vexr[i].pos[0], vexr[i].pos[1], vexr[i].pos[2]);
	printf("Colors:\n");
	for(int i = 0; i < len; i++)
		printf("%i(%f,%f,%f)\n", i, vexr[i].col[0], vexr[i].col[1], vexr[i].col[2]);
	len = t.getOrderLength();
	int *ords = t.getOrder();
	printf("Order:\n");
	for(int i = 0; i < len; i++)
		printf("%i >> %i\n", i, ords[i]);
}

/* -- VECTOR PRINT SNIPPET --*/
void printVector(Vector3D v){
	printf("(%f,%f,%f)", v.getCoord(0), v.getCoord(1), v.getCoord(2));
}