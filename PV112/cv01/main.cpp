/************************************************************************/
/* Title:   PV112 - cv1                                                 */
/* Version: C++                                                         */
/* Author:  Martin Bezdeka, Adam Jurcik                                 */
/************************************************************************/

#include <GL/freeglut.h>

#define SIZE_X 640
#define SIZE_Y 480

int mode = 0;
int modes[] = { GL_POINT, GL_LINE, GL_FILL };

/**
 * 1. Stahnout FreeGLUT, vytvorit aplikaci
 * 2. Reakce na klavesy ESC a F
 * 3. Osy ve 2D, vykreslit trojuhelnik, glColor
 * 4. glPolygonMode na M
 * 5. Fullscreen na F
 * 6. glBegin - GL_QUADS, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP
 * 7. Nakreslit domecek
 * 8. Rotace - placate
 */

/**
 * Documentation:
 * http://www.opengl.org/resources/libraries/glut/spec3/spec3.html
 * http://freeglut.sourceforge.net/docs/api.php
 */

void keyPressed(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
    case 27://VK_ESCAPE:
        exit(0);
        break;
		
	case 'f':
		glutFullScreenToggle();
		break;

	case 'm':
		mode = ++mode % 3;
		glPolygonMode(GL_FRONT_AND_BACK, modes[mode]);
		break;
    }

    // Flag indicating that current window needs to be redisplayed
	glutPostRedisplay();
}

float rotation = 0.0f;

void render(void)
{
    // Clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate polygon
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotation, 0.0f, 1.0f, 1.0f);

	//rotation += 0.5f;

    // Draw triangle
    glBegin(GL_TRIANGLE_STRIP);

    glColor3f(1.0f, 0.0f, 0.0f);
  
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, 0.1f, 0.0f);
    glVertex3f(-0.5f, 0.1f, 0.0f);
    
    glVertex3f(0.5f, -0.7f, 0.0f);
    glVertex3f(-0.5f, -0.7f, 0.0f);

    glEnd();

    /*
    glColor3f(0.9, 0.5, 0.1);
    glVertex3f(0.1f, -0.7f, 0.0f);
    glVertex3f(0.3f, -0.7f, 0.0f);
    glVertex3f(0.3f, -0.2f, 0.0f);
    glVertex3f(0.1f, -0.2f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.3f, -0.2f);
    glVertex2f(-0.3f, -0.5f);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(-0.1f, -0.2f);
    glEnd();*/

    //glutSolidCube(1.0f);

    // Moves back buffer content to the front buffer.
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
    glutCreateWindow("PV112 - cv1");

    // Register callbacks
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutKeyboardFunc(keyPressed);
	
    // Main loop
    glutMainLoop();

    return 0;
}
