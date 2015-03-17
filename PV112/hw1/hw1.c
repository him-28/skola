/**
 * @author Pavel Ondračka
 * @version 1.0
 *
 * First homework for PV112
 */

#include <math.h>
#include <GL/freeglut.h>

#define SIZE_X 640
#define SIZE_Y 480

#define PI 3.14159265359

typedef enum {forward, backward, left, right} directions;
float cam_x = -5.0;
float cam_y = 0.0;
float cam_z = 1.0;

float angle_x = 0.0;
//float target_y = 0.0;
float target_z = 0.0;

int mouse_x = -1.0;
int mouse_y = -1.0;

int window_width;
int window_height;


void resize(int width, int height)
{
   window_width = width;
   window_height = height;
   
	glMatrixMode(GL_PROJECTION); //chceme pracovat s projekční maticí
	glLoadIdentity(); //načteme jednotkovou matici
	gluPerspective(60.0f, ((float)width) / height, 1.0f, 100.0f); //vynásobíme projekční matici tímto
	//(úhel pohledu, poměr stran, vzdálenost přední a zadní pohledové roviny)
	
	glViewport(0, 0, width, height); //ve viewport začínají souřadice v levém horním rohu.
	glMatrixMode(GL_MODELVIEW);
}

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

void keyPressed(unsigned char key, int mouseX, int mouseY){
   switch(key) 
   {
   case 27:/* Esc */
      exit(0);
      break;
		
	case 'f':
		glutFullScreenToggle();
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

   // Flag indicating that current window needs to be redisplayed
   glutPostRedisplay();
}

void mouse_moved(int x, int y){
   static char is_warping = 0;

   if(is_warping == 1)
      return;

   if(mouse_x == -1 && mouse_y == -1){
      mouse_x = x;
      mouse_y = y;
   }

   angle_x += (x - mouse_x)* 60 * PI / (180 * window_width / 2);

   //is_warping = 1;
   //glutWarpPointer( window_width/2, window_height/2 );
   //is_warping = 0;

   //mouse_x = window_width/2;
   //mouse_y = window_height/2;

      mouse_x = x;
      mouse_y = y;

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
	gluLookAt(cam_x, cam_y, cam_z, cam_x + cos(angle_x), cam_y + sin(angle_x), cam_z + target_z, 0.0, 0.0, 1.0);//eye pos, center pos, normal vector

	drawAxes(3.0);




   // Moves back buffer content to the front buffer
   glutSwapBuffers();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
   glutInitContextVersion(2,1);

   // Init window
   glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SIZE_X) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - SIZE_Y) / 2);
   glutInitWindowSize(SIZE_X, SIZE_Y);    
   glutCreateWindow("PV112 - cv2");

   // Register callbacks
   glutDisplayFunc(render);
	glutIdleFunc(render);
   glutKeyboardFunc(keyPressed);
	glutReshapeFunc(resize);
   glutPassiveMotionFunc(mouse_moved);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

   // Main loop
   glutMainLoop();

   return 0;
}
