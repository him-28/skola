/************************************************************************/
/* Title:   PV112 - cv3                                                 */
/* Version: C++                                                         */
/* Author:  Martin Bezdeka, Adam Jurcik                                 */
/************************************************************************/

/*
 * 1. Vykresleni podlahy
 * 2. Display list
 * 3. Otaceni podlahy (specialFunc)
 * 4. Pridat kulicku jako svetlo
 * 5. Materialy
 * 6. Spotlight
 * 7. Odlesk
 * 8. GL_COLOR_MATERIAL
 */

#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

#define SIZE_X 640
#define SIZE_Y 480

/**
 * Documentation:
 * http://www.opengl.org/resources/libraries/glut/spec3/spec3.html
 * http://freeglut.sourceforge.net/docs/api.php
 */

typedef enum {forward, backward, left, right} directions;
float cam_x = 5.0;
float cam_y = 0.0;
float cam_z = 2.0;

bool animate;

float angle_x = 0.0;
float target_z = 0.0;

int floorId;

void move(directions dir){
   switch(dir){
      case forward:
         cam_x += cos(angle_x);
         cam_y += sin(angle_x);
         break;
      case backward:
         cam_x -= cos(angle_x);
         cam_y -= sin(angle_x);
         break;
      case left:
         cam_x += sin(-angle_x);
         cam_y += cos(-angle_x);
         break;
      case right:
         cam_x -= sin(-angle_x);
         cam_y -= cos(-angle_x);
         break;
   }
}

void resize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, (float)width/height, 0.1f, 1000.0f);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
}

void togglePolygonMode()
{
	static int mode = 3;
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT + (mode++ % 3));
}

void keyPressed(unsigned char key, int mouseX, int mouseY)
{
    switch(key) 
    {
    case 27://VK_ESCAPE:
        exit(0);
        break;
		
	case 'y':
		animate = !animate;
		break;

	case 'f':
		glutFullScreenToggle();
		break;

	case 'm' :
		togglePolygonMode();
		break;
  	case 'w' :
		move(forward);
		break;
	case 's' :
		move(backward);
		break;
	case 'a' :
		move(left);
		break;
	case 'd' :
		move(right);
		break;
   }
}

void specialPressed(int key, int mouseX, int mouseY)
{
    switch(key) 
    {
  	case GLUT_KEY_UP :
		move(forward);
		break;
	case GLUT_KEY_DOWN :
		move(backward);
		break;
	case GLUT_KEY_LEFT :
		move(left);
		break;
	case GLUT_KEY_RIGHT :
		move(right);
		break;
   }
}

void drawAxes(float size)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glLineWidth(3.0f);
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);
    //x
    glColor3f(1,0,0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    //y
    glColor3f(0,1,0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    //z
    glColor3f(0,0,1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);

    glEnd();

	glPopAttrib();
}

void drawFloor(float size, float tiles)
{
   float step = size / tiles;

   glBegin(GL_QUADS);

   for(float x_cord = - size / 2.0; x_cord < (size / 2.0 - step / 2); x_cord += step){
      for(float z_cord = - size / 2.0; z_cord < (size / 2.0  - step / 2); z_cord += step){
          glVertex3f(x_cord, -0.1, z_cord);
          glVertex3f(x_cord + step, -0.1, z_cord);
          glVertex3f(x_cord + step, -0.1, z_cord + step);
          glVertex3f(x_cord, -0.1, z_cord + step);
      }
   }
   glEnd();
}

void createFloor(float size, float tiles)
{
   floorId = glGenLists(1);
   glNewList(floorId, GL_COMPILE);   
   
   float step = size / tiles;

   glNormal3f(0.0, 1.0, 0.0);   
   glBegin(GL_QUADS);

   for(float x_cord = - size / 2.0; x_cord < (size / 2.0 - step / 2); x_cord += step){
      for(float z_cord = - size / 2.0; z_cord < (size / 2.0  - step / 2); z_cord += step){
          glVertex3f(x_cord, -0.1, z_cord);
          glVertex3f(x_cord + step, -0.1, z_cord);
          glVertex3f(x_cord + step, -0.1, z_cord + step);
          glVertex3f(x_cord, -0.1, z_cord + step);
      }
   }
   glEnd();

   glEndList();
}

void render(void)
{
	static float x = 0.0f;
	static float y = 0.0f;
	static float posY = 0.0f;
 
	static float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (animate)
	{
		y = 0.0 + sin(x);
		x += 0.01f;
	}
	posY = exp(1 - (cos(2.5*x)+sin(1-x))) / 4.0;

   float lightPos[] = { 0.0f, 2.0f + 2.0f * y, 0.0f, 1.0f };
   float lightColor[] = { 1.0, 1.0, 0.0, 1.0 };

   float floorColor[] = { 1.0, 0.0, 0.0, 1.0 };
	
	//Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
//	gluLookAt(cam_x, cam_z, cam_y, cam_x + -cos(angle_x), cam_z + target_z, cam_y + -sin(angle_x), 0.0, 1.0, 0.0);//eye pos, center pos, normal vector

	gluLookAt(cam_x, cam_z, cam_y, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//eye pos, center pos, normal vector
	
	drawAxes(2);

   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorColor);
	glCallList(floorId);

   glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightColor);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, lightColor);
   glutSolidSphere(0.2f, 16, 16); 


    //Moves back buffer content to the front buffer.
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    
    // Init window
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SIZE_X) / 2,
	    (glutGet(GLUT_SCREEN_HEIGHT) - SIZE_Y) / 2);
    glutInitWindowSize(SIZE_X, SIZE_Y);    
    glutCreateWindow("PV112 - cv3");

    // Register callbacks
    glutDisplayFunc(render);
	glutIdleFunc(render);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialPressed);
	glutReshapeFunc(resize);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

   createFloor(10.0f, 20.0);

    // Main loop
    glutMainLoop();

    return 0;
}
