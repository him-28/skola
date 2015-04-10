/************************************************************************/
/* Title:   PV112 - cv4                                                 */
/* Version: C++                                                         */
/* Author:  Martin Bezdeka, Adam Jurcik                                 */
/************************************************************************/

/*
 * 1. Pridani texturove souradnice do podlahy
 * 2. Nacteni textury - loadTexture
 * 3a. Filtrovani - GL_NEAREST, GL_LINEAR
 * 3b. Co kdyz je textura velmi daleko?
 * 4. Mipmapy
 * 5. Chovani na okraji (2x2 dilky) + GL_CLAMP_TO_EDGE
 * 6. Otaceni mysi + zoom
 */

#include "GL/freeglut.h"
#include "GL/glext.h"

#define IL_USE_PRAGMA_LIBS
#include "IL/devil_cpp_wrapper.hpp"

#include <cmath>
#include <iostream>

using namespace std;

unsigned int sizeX = 800;
unsigned int sizeY = 600;

bool animate = false;

float x = 0.0f;
float a = 1.0f;

float zoom = 10.0f;
float cameraX = 0.0f;
float cameraY = 0.0f;

int modelId;
int textureId;

void resize(int x, int y) 
{
    sizeX = x;
    sizeY = (y == 0) ?  1 : y;
    GLfloat aspect = (GLfloat) sizeX / sizeY;

    glViewport(0, 0, sizeX, sizeY);    

    // Switch to Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the correct perspective.
    gluPerspective(60, aspect, 0.1, 1000);        

    // Get Back to the ModelView
    glMatrixMode(GL_MODELVIEW);
}

void polygonModeToggle() 
{
    static unsigned int mode = 3;
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT + (mode++ % 3));
}

void specialPressed(int key, int mouseX, int mouseY) 
{
    switch(key) 
    {
    case GLUT_KEY_UP:
        cameraY++;
        break;

    case GLUT_KEY_DOWN:
        cameraY--;
        break;

    case GLUT_KEY_LEFT:
        cameraX++;
        break;

    case GLUT_KEY_RIGHT:
        cameraX--;
        break;
	}
}

void mouse_func(int x, int y){
   int diffX = sizeX / 2 - x;
   int diffY = sizeY / 2 - y;

   cameraX += diffY / 10.0f;
   cameraY -= diffX / 10.0f;

   if(diffX != 0 || diffY != 0){
      glutWarpPointer(sizeX / 2, sizeY / 2);
   }

}

void keyPressed(unsigned char key, int mouseX, int mouseY)
{
    switch(key) 
    {
    case 27:
        exit(0);
        break;

    case 'f':
        glutFullScreenToggle();
        break;

    case 'm':
        polygonModeToggle();
        break;

    case 'a':
        animate = !animate;
        break;
    }
}

int loadTexture(const char * filename)
{
	unsigned int texId = 0;

	ilImage image;

	bool loaded = image.Load(filename);

	if(!loaded)
		fprintf(stderr, "unable to load %s\n", filename);

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());


	glBindTexture(GL_TEXTURE_2D, 0);

	return texId;
}

void drawAxes(float size)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    // Set line width
    glLineWidth(2);
    // Disable lighting
    glDisable(GL_LIGHTING);
    // Draw axes
    glBegin(GL_LINES);
    // X
    glColor3f(1,0,0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    // Y
    glColor3f(0,1,0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    // Z
    glColor3f(0,0,1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);

    glEnd();
    // Restore to the previous state
    glPopAttrib();    
}

int createFloor(float size, int tiles, int repetition)
{
	int floorId = glGenLists(1);

	float step = size / tiles;
	float xstart = -0.5f * size;
	float zstart = 0.5f * size;
	float rep = 4.0;

	glNewList(floorId, GL_COMPILE);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int z = 0; z < tiles; z++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int x = 0; x <= tiles; x++)
		{
			glTexCoord2f( (float)x / tiles * rep, (float)(z + 1) / tiles * rep);
			glVertex3f(xstart + x * step, -0.01f, zstart - (z + 1) * step);
			glTexCoord2f( (float)x / tiles * rep, (float)z / tiles * rep);
			glVertex3f(xstart + x * step, -0.01f, zstart - z * step);
		}
		glEnd();
	}
	glEndList();

	return floorId;
}

void render(void)
{
    // Computation of animation
    if (animate) {
        a = sin(x) + 1;
        x += 0.02f;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

	// Set the light to be point light
	float lightPos[] = { 0.0, 0.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	gluLookAt(0, 5, zoom,  // Camera position [x,y,z]
        0,0,0,   // Look at position
        0,1,0);  // Camera tilting

    glRotatef(cameraY, 1,0,0);
    glRotatef(cameraX, 0,1,0);
    drawAxes(2);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glCallList(modelId);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

	
    // Moves back buffer content to the front buffer.
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

    // Init window
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - sizeX) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - sizeY) / 2);
    glutInitWindowSize(sizeX, sizeY);    
    glutCreateWindow("PV112 - cv4");

    // Register callbacks
    glutDisplayFunc(render);
    glutKeyboardFunc(keyPressed);    
    glutSpecialFunc(specialPressed);
    glutReshapeFunc(resize);
    glutIdleFunc(render);
    glutMotionFunc(mouse_func);

    // Enable important features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);

	// Configure ResIL
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// Load data
	modelId = createFloor(8.0f, 12, 1);
	textureId = loadTexture("texture/wood.jpg");

    // Main loop
    glutMainLoop();

    return 0;
}
