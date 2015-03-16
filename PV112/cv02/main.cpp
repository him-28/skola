/************************************************************************/
/* Title:   PV112 - cv2                                                 */
/* Version: C++                                                         */
/* Author:  Martin Bezdeka, Adam Jurcik                                 */
/************************************************************************/

/*
 * 1. Osy (ukol)
 * 2. Kamera + resize
 * 3. Krychle (ukol)
 * 4. Transformace
 * 5. Animace
 * 6. Skladani
 * 7. Ukladani matice
 */

#include <math.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#define SIZE_X 640
#define SIZE_Y 480

/**
 * Documentation:
 * http://www.opengl.org/resources/libraries/glut/spec3/spec3.html
 * http://freeglut.sourceforge.net/docs/api.php
 */

/**
 * Links:
 * http://www.fooplot.com
 */

bool animate;

void resize(int width, int height)
{
	glMatrixMode(GL_PROJECTION); //chceme pracovat s projekční maticí
	glLoadIdentity(); //načteme jednotkovou matici
	gluPerspective(60.0f, ((float)width) / height, 1.0f, 1000.0f); //vynásobíme projekční matici tímto
	//(úhel pohledu, poměr stran, vzdálenost přední a zadní pohledové roviny)
	
	glViewport(0, 0, width, height); //ve viewport začínají souřadice v levém horním rohu.
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
		
	case 'a':
		animate = !animate;
		break;

	case 'f':
		glutFullScreenToggle();
		break;

	case 'm' :
		togglePolygonMode();
		break;
    }

    // Flag indicating that current window needs to be redisplayed
    glutPostRedisplay();
}

void drawAxes(float size)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);//uloží všechny GL atributy
	glDisable(GL_LIGHTING);
	glLineWidth(2.0f);
	
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, size, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, size);

	glEnd();

	glPopAttrib();
}

void drawCube(){

	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);

	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);

	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	
	glEnd();
}

float angle = 0.0;

void render(void)
{
	static float x = 0.0f;
	static float y = 0.0f;
	static float rotX = 0.0f;
	static float rotY = 0.0f;

	x += 0.1f;
	rotY += 1.0f;
	rotX -= 1.0f;


    // Clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//eye pos, center pos, normal vector

	//glPushMatrix(); //uloží aktuální matici
	//glPopMatrix(); //načte aktuální matici

	drawAxes(3.0);

	glTranslatef(2.0, 0.0, 0.0);//posune 
	glRotatef(rotX, 0.0, 1.0, 0.0);

	drawAxes(1.0);
	glutSolidCube(1.0);

	glLoadIdentity();//reset all transforms
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//eye pos, center pos, normal vector

	glTranslatef(0.0, sin(x), cos(x));//posune 
	glRotatef(rotY, 0.0, 1.0, 0.0);

	glutSolidTeapot(1.0);

    // Moves back buffer content to the front buffer
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    
    // Init window
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SIZE_X) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - SIZE_Y) / 2);
    glutInitWindowSize(SIZE_X, SIZE_Y);    
    glutCreateWindow("PV112 - cv2");

    // Register callbacks
    glutDisplayFunc(render);
	glutIdleFunc(render);
    glutKeyboardFunc(keyPressed);
	glutReshapeFunc(resize);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    // Main loop
    glutMainLoop();

    return 0;
}
