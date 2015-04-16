/**
 * @author Pavel Ondračka
 * @version 1.0
 *
 * First homework for PV112
 */

#include <math.h>
#include <GL/freeglut.h>

#include "ObjLoader.h"

#define SIZE_X 640
#define SIZE_Y 480

#define PI 3.14159265359

typedef enum {Forward, Backward, Left, Right} directions;
float cam_x = -5.0;
float cam_y = 0.0;
float cam_z = 1.0;

float angle_x = 0.0;
float angle_z = 0.0;

int mouse_x = -1.0;
int mouse_y = -1.0;

int window_width;
int window_height;

int objects[20];

void resize(int width, int height)
{
   window_width = width;
   window_height = height;
   
	glMatrixMode(GL_PROJECTION); //chceme pracovat s projekční maticí
	glLoadIdentity(); //načteme jednotkovou matici
	gluPerspective(60.0f, ((float)width) / height, 0.1f, 100.0f); //vynásobíme projekční matici tímto
	//(úhel pohledu, poměr stran, vzdálenost přední a zadní pohledové roviny)
	
	glViewport(0, 0, width, height); //ve viewport začínají souřadice v levém horním rohu.
	glMatrixMode(GL_MODELVIEW);

   mouse_x = -1.0;
   mouse_y = -1.0;
}

void move(directions dir){
   float speed = 0.1;
   switch(dir){
      case Forward:
         cam_x += speed * cos(angle_x);
         cam_y += speed * sin(angle_x);
         break;
      case Backward:
         cam_x -= speed * cos(angle_x);
         cam_y -= speed * sin(angle_x);
         break;
      case Left:
         cam_x += speed * sin(-angle_x);
         cam_y += speed * cos(-angle_x);
         break;
      case Right:
         cam_x -= speed * sin(-angle_x);
         cam_y -= speed * cos(-angle_x);
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
		move(Forward);
		break;
	case 's' :
		move(Backward);
		break;
	case 'a' :
		move(Left);
		break;
	case 'd' :
		move(Right);
		break;
   }

   // Flag indicating that current window needs to be redisplayed
   glutPostRedisplay();
}

char warping = 0;

void mouse_moved(int x, int y){

   /* on first load set mouse to curson position so we don't have a jump */
   if(mouse_x == -1 && mouse_y == -1){
      mouse_x = x;
      mouse_y = y;
   }

   angle_x -= (x - mouse_x)* 60 * PI / (180 * window_width / 2);
   angle_z -= (y - mouse_y)* 60 * PI / (180 * window_height / 2);

   if(warping % 2 == 1){
      glutWarpPointer( window_width/2, window_height/2 );
      warping = 0;
   }
   else
      warping++;

   mouse_x = window_width/2;
   mouse_y = window_height/2;

   glutPostRedisplay();
}

float angle = 0.0;
float y = 0.0;

void render(void)
{

   // Clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_x, cam_y, cam_z, cam_x + cos(angle_x), cam_y + sin(angle_x), cam_z + sin(angle_z), 0.0, 0.0, 1.0);//eye pos, center pos, normal vector

   float lightPos[] = { 0.0f, 0.0f, 20.0, 1.0f };
   float lightDir[] = { 0.0f, 0.0f, 1.0f};
   y += 0.01;

   float red_color[] = {1.0, 0.0, 0.0, 1.0};
   float green_color[] = {0.0, 1.0, 0.0, 1.0};
   float blue_color[] = {0.0, 0.0, 1.0, 1.0};
   float white_color[] = {1.0, 1.0, 1.0, 1.0};
   float black_color[] = {0.0, 0.0, 0.0, 1.0};


   glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color);
   //glLightfv(GL_LIGHT0, GL_SPECULAR, white_color);   
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);  
   //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);           
                

	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_color);
   //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white_color);
   glScalef(0.01, 0.01, 0.01);

   /* table 1 */
   glPushMatrix();
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[0]);
   glPopMatrix();

   /* clock */
   glPushMatrix();
   glTranslatef(0.0, 100.0, 100.0);

   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[1]);

   //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, green_color);
   glCallList(objects[2]);
   glRotatef(90.0, 0.0, 1.0, 0.0);
   glCallList(objects[3]);
   glPopMatrix();

   /* vase */
   glPushMatrix();
   //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_color);
   glTranslatef(30.0, 0.0, 70.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[4]);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-30.0, 0.0, 77.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glutSolidTeapot(10.0);
   glPopMatrix();

   glPushMatrix();
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[5]);
   glPopMatrix();   

   // Moves back buffer content to the front buffer
   glutSwapBuffers();
}

int load_object(const char *path){
   int objectId = glGenLists(1);
   glNewList(objectId, GL_COMPILE);

   ObjLoader obj;
   obj.Load(path);

   vector<Triangle> tr = obj.GetTriangles();
   vector<Vector3f> v = obj.GetVertices();
   vector<Vector3f> n = obj.GetNormals();

   glBegin(GL_TRIANGLES);
   for(int i = 0; i < tr.size(); i++){
      //printf("%i\n", i);
      glNormal3f(n[tr[i].n0].x, n[tr[i].n0].y, n[tr[i].n0].z);
      glVertex3f(v[tr[i].v0].x, v[tr[i].v0].y, v[tr[i].v0].z);
      //printf("%f %f %f\n", n[tr[i].n0].x, n[tr[i].n0].y, n[tr[i].n0].z);
      //printf("%f %f %f\n", v[tr[i].v0].x, v[tr[i].v0].y, v[tr[i].v0].z);

      glNormal3f(n[tr[i].n1].x, n[tr[i].n1].y, n[tr[i].n1].z);
      glVertex3f(v[tr[i].v1].x, v[tr[i].v1].y, v[tr[i].v1].z);
      //printf("%f %f %f\n", n[tr[i].n1].x, n[tr[i].n1].y, n[tr[i].n1].z);

      glNormal3f(n[tr[i].n2].x, n[tr[i].n2].y, n[tr[i].n2].z);
      glVertex3f(v[tr[i].v2].x, v[tr[i].v2].y, v[tr[i].v2].z);
      //printf("%f %f %f\n", n[tr[i].n2].x, n[tr[i].n2].y, n[tr[i].n2].z);
      //cout << tr[i].x << tr[i].y << tr[i].z << endl;
   }
   glEnd();
   glEndList();

   return objectId;
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

void load_scene(void){

   objects[0] = load_object("objects/table.obj");
   objects[1] = load_object("objects/clock.obj");
   objects[2] = load_object("objects/clock-minutehand.obj");
   objects[3] = load_object("objects/clock-hourhand.obj");
   objects[4] = load_object("objects/vase.obj");
   objects[5] = createFloor(50000.0, 500, 1);

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
   glutMotionFunc(mouse_moved);
   
   glutWarpPointer( glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2 );

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

   load_scene();

   // Main loop
   glutMainLoop();

   return 0;
}
