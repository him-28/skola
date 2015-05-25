/**
 * @author Pavel Ondračka
 * @version 1.0
 *
 * First homework for PV112
 */

#include <math.h>
#include <time.h>
#include <GL/freeglut.h>

#define IL_USE_PRAGMA_LIBS
#include "IL/devil_cpp_wrapper.hpp"

#include "ObjLoader.h"

#define SIZE_X 1024
#define SIZE_Y 768

#define PI 3.14159265359

#define LIGHT0a 1
#define LIGHT0d 2
#define LIGHT1 4
#define LIGHT2 8

unsigned char lights;

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
int textures[20];

float red_color[] = {1.0, 0.0, 0.0, 1.0};
float green_color[] = {0.0, 1.0, 0.0, 1.0};
float blue_color[] = {0.0, 0.0, 1.0, 1.0};
float white_color[] = {1.0, 1.0, 1.0, 1.0};
float gray_color[] = {0.15, 0.15, 0.15, 1.0};
float black_color[] = {0.0, 0.0, 0.0, 0.0};
float brown_color[] = {0.66, 0.3, 0.0, 1.0};

void resize(int width, int height)
{
   window_width = width;
   window_height = height;

   glMatrixMode(GL_PROJECTION); //chceme pracovat s projekční maticí
   glLoadIdentity(); //načteme jednotkovou matici
   gluPerspective(60.0f, ((float)width) / height, 1.0f, 1000.0f); //vynásobíme projekční matici tímto
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

   case 'u' :
      lights ^= LIGHT0a;
      break;
   case 'i' :
      lights ^= LIGHT0d;
      break;
   case 'o' :
      lights ^= LIGHT1;
      break;
   case 'p' :
      lights ^= LIGHT2;
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
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
   gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());


   glBindTexture(GL_TEXTURE_2D, 0);

   return texId;
}

void set_lights(){

   float lightPos0[] = { 0.0f, 0.0f, 200.0, 1.0f };
   float lightPos1[] = { 200.0f, 0.0f, 200.0, 1.0f };
   float lightPos2[] = { -200.0f, 0.0f, 200.0, 1.0f };

   float lightDir1[] = { -0.5f, -0.0f, -0.5f};
   float lightDir2[] = { 0.5f, -0.0f, -0.5f};
   float lightAtten[] = { 0.005f, 0.005f, 0.005f};

   float cutoff = 15.0f;
   float spot_exponent = 50.0f;

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black_color);
   
   if(lights & LIGHT0d)
      glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color);
   else
      glLightfv(GL_LIGHT0, GL_DIFFUSE, black_color);
   if(lights & LIGHT0a)
      glLightfv(GL_LIGHT0, GL_AMBIENT, gray_color);
   else
      glLightfv(GL_LIGHT0, GL_AMBIENT, black_color);
   glLightfv(GL_LIGHT0, GL_SPECULAR, black_color);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
   glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, lightAtten);


   if(lights & LIGHT1)
      glLightfv(GL_LIGHT1, GL_SPECULAR, red_color);
   else
      glLightfv(GL_LIGHT1, GL_SPECULAR, black_color);

      glLightfv(GL_LIGHT1, GL_AMBIENT, black_color);
   glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir1);
   glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &cutoff);
   glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, &spot_exponent);

   if(lights & LIGHT2)
      glLightfv(GL_LIGHT2, GL_SPECULAR, blue_color);
   else
      glLightfv(GL_LIGHT2, GL_SPECULAR, black_color);

      glLightfv(GL_LIGHT2, GL_AMBIENT, black_color);
   glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
   glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir2);
   glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, &cutoff);
   glLightfv(GL_LIGHT2, GL_SPOT_EXPONENT, &spot_exponent);
}

void render(void)
{

   // Clear buffers
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glShadeModel(GL_SMOOTH);

   glMatrixMode(GL_MODELVIEW);
   glEnable(GL_NORMALIZE);
   glLoadIdentity();
   gluLookAt( 100 * cam_x, 100 * cam_y, 100 * cam_z, 100 * (cam_x + cos(angle_x)), 100 * (cam_y + sin(angle_x)), 100 * (cam_z + sin(angle_z)), 0.0, 0.0, 1.0);//eye pos, center pos, normal vector

   set_lights();

   float shininess = 0.0f;

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white_color);

   if(lights & LIGHT0d){
      glPushMatrix();
      glTranslatef(0.0f, 0.0f, 200.0f);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white_color);
      glutSolidSphere(10.0, 20, 20);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_color);
      glPopMatrix();
   }

   /* table 1 */
   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[1]);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[0]);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   /* clock */
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glPushMatrix();
   glTranslatef(0.0, 100.0, 140.0);
   glRotatef(90, 1.0, 0.0, 0.0);
   glCallList(objects[1]);

   /* clockhand */
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_color);
   //FIXME: clock hour is a little bit off
   //glTranslatef(0.0, 0.0, 0.0);
   glRotatef(time(NULL)%360*10, 0.0, 0.0, 1.0);

   glCallList(objects[2]);
   glPopMatrix();

   /* vase 1 */
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[3]);
   glTranslatef(-150.0, -150.0, 0.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[4]);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   /* vase 2 */
   glPushMatrix();
   glTranslatef(-150.0, 150.0, 0.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[4]);
   glPopMatrix();

   /* vase 3 */
   glPushMatrix();
   glTranslatef(150.0, 150.0, 0.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[4]);
   glPopMatrix();

   /* vase 4 */
   glPushMatrix();
   glTranslatef(150.0, -150.0, 0.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glCallList(objects[4]);
   glPopMatrix();

   /* teapot 1 */
   glPushMatrix();
   glTranslatef(-30.0, 20.0, 77.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glutSolidTeapot(10.0);
   glPopMatrix();

   /* teapot 2 */
   glPushMatrix();
   glTranslatef(-30.0, -20.0, 77.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glutSolidTeapot(10.0);
   glPopMatrix();

   /* teapot 3 */
   glPushMatrix();
   glTranslatef(30.0, -20.0, 77.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glutSolidTeapot(10.0);
   glPopMatrix();

   /* teapot 4 */
   glPushMatrix();
   glTranslatef(30.0, 20.0, 77.0);
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[1]);
   glutSolidTeapot(10.0);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   /* floor */
   glPushMatrix();
   glRotatef(90.0, 1.0, 0.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white_color);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[0]);
   glCallList(objects[5]);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);

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
   vector<Vector2f> tx = obj.GetTexcords();
   vector<Vector3f> n = obj.GetNormals();

   glBegin(GL_TRIANGLES);
   for(int i = 0; i < tr.size(); i++){
      //printf("%i\n", i);
      glNormal3f(n[tr[i].n0].x, n[tr[i].n0].y, n[tr[i].n0].z);
      glTexCoord2f(tx[tr[i].t0].x, tx[tr[i].t0].y);
      glVertex3f(v[tr[i].v0].x, v[tr[i].v0].y, v[tr[i].v0].z);
      //printf("%f %f %f\n", n[tr[i].n0].x, n[tr[i].n0].y, n[tr[i].n0].z);
      //printf("%f %f %f\n", v[tr[i].v0].x, v[tr[i].v0].y, v[tr[i].v0].z);

      glNormal3f(n[tr[i].n1].x, n[tr[i].n1].y, n[tr[i].n1].z);
      glTexCoord2f(tx[tr[i].t1].x, tx[tr[i].t1].y);
      glVertex3f(v[tr[i].v1].x, v[tr[i].v1].y, v[tr[i].v1].z);
      //printf("%f %f %f\n", n[tr[i].n1].x, n[tr[i].n1].y, n[tr[i].n1].z);

      glNormal3f(n[tr[i].n2].x, n[tr[i].n2].y, n[tr[i].n2].z);
      glTexCoord2f(tx[tr[i].t2].x, tx[tr[i].t2].y);
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
   objects[5] = createFloor(500.0, 500, 10);

   textures[0] = loadTexture("texture/pavement.jpg");
   textures[1] = loadTexture("texture/wood.jpg");
   textures[2] = loadTexture("texture/dice6.png");
   textures[3] = loadTexture("texture/vase.jpg");

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
   glutInitContextVersion(2,1);

   // Init window
   glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SIZE_X) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - SIZE_Y) / 2);
   glutInitWindowSize(SIZE_X, SIZE_Y);
   glutCreateWindow("PV112 - projekt 2 - Pavel Ondračka");

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
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);

   lights = 15;

   // Configure DevIL
   ilEnable(IL_ORIGIN_SET);
   ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

   load_scene();

   // Main loop
   glutMainLoop();

   return 0;
}
