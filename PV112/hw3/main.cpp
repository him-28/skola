// PV112, template for the third project

// FreeGLUT web pages: http://freeglut.sourceforge.net
// FreeGLUT download (MSVC Package): http://www.transmissionzero.co.uk/software/freeglut-devel/
// GLEW web pages: http://glew.sourceforge.net/
// GLEW download (Binaries): http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download
// DevIL: download from Study Materials from IS
// Textures: download from Study Materials from IS

//-----------------------------------------------------------------------------------------------------------------
// This template supports three projects:
// 1) Normal mapping
//		- tangent direction is accessible in vertex shader through 'gl_MultiTexCoord1' attribute
//		- bitangent direction is accessible in vertex shader through 'gl_MultiTexCoord2' attribute
//		- texture with normals is accessible in fragment shader through 'rocks_normal_tex' sampler2D uniform variable
//		- texture with color is accessible in fragment shader through 'rocks_color_tex' sampler2D uniform variable
//		- this project uses 'Fieldstone.PNG' as color texture and 'FieldstoneBumpDOT3.PNG' as normal texture, be sure they are not missing
//		- to draw cube, DO NOT FORGET to uncomment draw_cube_for_normal_mapping() in function render
// 2) Environment mapping
//		- texture with skybox is accessible in fragment shader through 'skybox_tex' samplerCube uniform variable
//		- this project uses 'skybox0.png' to 'skybox5.png' as sides of cube texture, be sure they are not missing
//		- to draw teapot with skybox surrounding, DO NOT FORGET to uncomment draw_teapot_with_skybox() in function render
// 3) Toon shading
//		- to draw teapot, DO NOT FORGET to uncomment draw_teapot_for_toon_shading() in function render
// In all cases, vertex shader is loaded from 'vs.glsl' and fragment shader is loaded from 'fs.glsl'
//-----------------------------------------------------------------------------------------------------------------

// Controls:
// 't' ... Toggle fullscreen
// 'f' ... Polygon fill mode
// 'l' ... Polygon line mode
// 'a' ... Toggle animation (rotate the object)
// Hold left mouse button to rotate the object

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#pragma comment(lib, "glew32.lib")
#include <GL/glew.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#define IL_USE_PRAGMA_LIBS
#include <IL/devil_cpp_wrapper.hpp>

using namespace std;

int win_width = 640;
int win_height = 480;

// Rotation of main object
float rotX = 0.0f, rotY = 0.0f;

bool animate = false;
bool user_rotates = false;

float time_s = 0.0f;

const float black[]		= {0.0f, 0.0f, 0.0f, 1.0f};
const float white[]		= {1.0f, 1.0f, 1.0f, 1.0f};

GLuint tex_rocks_color;
GLuint tex_rocks_normal;
GLuint tex_skybox;

GLuint program;

static const int vertices_count = 24;
static const float vertices[vertices_count * 14] =
{
// .. TexCoord .......... Normal ............... Position .............. Tangent ............. Bitangent ....
// Front face
	0.0f, 1.0f,		 0.0f, 0.0f, 1.0f,		-1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.0f, 0.0f,		 0.0f, 0.0f, 1.0f,		-1.0f,-1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 0.0f,		 0.0f, 0.0f, 1.0f,		 1.0f,-1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 1.0f,		 0.0f, 0.0f, 1.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
// Right face
	0.0f, 1.0f,		 1.0f, 0.0f, 0.0f,		 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,
	0.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		 1.0f,-1.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 0.0f,		 1.0f, 0.0f, 0.0f,		 1.0f,-1.0f,-1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 1.0f,		 1.0f, 0.0f, 0.0f,		 1.0f, 1.0f,-1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,
// Back face
	0.0f, 1.0f,		 0.0f, 0.0f,-1.0f,		 1.0f, 1.0f,-1.0f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	0.0f, 0.0f,		 0.0f, 0.0f,-1.0f,		 1.0f,-1.0f,-1.0f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 0.0f,		 0.0f, 0.0f,-1.0f,		-1.0f,-1.0f,-1.0f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 1.0f,		 0.0f, 0.0f,-1.0f,		-1.0f, 1.0f,-1.0f,		-1.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
// Left face
	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,		-1.0f, 1.0f,-1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		-1.0f,-1.0f,-1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,		-1.0f,-1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
// Top face
	0.0f, 1.0f,		 0.0f, 1.0f, 0.0f,		-1.0f, 1.0f,-1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	0.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		-1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	1.0f, 0.0f,		 0.0f, 1.0f, 0.0f,		 1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	1.0f, 1.0f,		 0.0f, 1.0f, 0.0f,		 1.0f, 1.0f,-1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
// Bottom face
	0.0f, 1.0f,		 0.0f,-1.0f, 0.0f,		-1.0f,-1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	0.0f, 0.0f,		 0.0f,-1.0f, 0.0f,		-1.0f,-1.0f,-1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	1.0f, 0.0f,		 0.0f,-1.0f, 0.0f,		 1.0f,-1.0f,-1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	1.0f, 1.0f,		 0.0f,-1.0f, 0.0f,		 1.0f,-1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
};

void key_pressed(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 't':
		glutFullScreenToggle();
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'l':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'a':
		animate = !animate;
		break;
	};
}

void mouse_moved(int mouse_x, int mouse_y)
{
	// Rotate the object if user moves with mouse
	if (user_rotates)
	{
		int diff_x = (mouse_x - (win_width / 2));
		int diff_y = (mouse_y - (win_height / 2));

		if (diff_x != 0 || diff_y != 0)
		{
			float sensitivity = 0.2f;
			rotX += float(diff_x) * sensitivity;
			rotY += float(diff_y) * sensitivity;

			glutWarpPointer(win_width / 2, win_height / 2);
		}
	}
}

void mouse_fnc(int button, int state, int x, int y)
{
	// Start/stop rotating the object when user presses/releases left mouse button
	if (button == GLUT_LEFT_BUTTON)
	{
		if (user_rotates != (state == GLUT_DOWN))
		{
			user_rotates = (state == GLUT_DOWN);

			glutSetCursor(user_rotates ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
			if (user_rotates)
				glutWarpPointer(win_width / 2, win_height / 2);
		}
	}
}

void reshape(int width, int height)
{
	win_width = width;
	win_height = height;

	glViewport(0, 0, win_width, win_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, double(win_width) / double(win_height), 0.1, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

string load_file_to_string(const char *file_name)
{
	ifstream file(file_name);
	stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

void init()
{
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	int compile_status;
	const char *source;

	// Load and compile vertex shader
	string vs_source = load_file_to_string("vs.glsl");
	GLuint vs_shader = glCreateShader(GL_VERTEX_SHADER);
	source = vs_source.c_str();
	glShaderSource(vs_shader, 1, &source, nullptr);
	glCompileShader(vs_shader);
	glGetShaderiv(vs_shader, GL_COMPILE_STATUS, &compile_status);
	if (GL_FALSE == compile_status)
	{
		int log_len = 0;
		glGetShaderiv(vs_shader, GL_INFO_LOG_LENGTH, &log_len);
		unique_ptr<char []> log(new char[log_len]);
		glGetShaderInfoLog(vs_shader, log_len, nullptr, log.get());
		
		cout << "Failed to compile vertex shader" << endl;
		cout << log.get() << endl;

		getchar();		// Wait for keypress
		exit(1);
	}

	// Load and compile fragment shader
	string fs_source = load_file_to_string("fs.glsl");
	GLuint fs_shader = glCreateShader(GL_FRAGMENT_SHADER);
	source = fs_source.c_str();
	glShaderSource(fs_shader, 1, &source, nullptr);
	glCompileShader(fs_shader);
	glGetShaderiv(fs_shader, GL_COMPILE_STATUS, &compile_status);
	if (GL_FALSE == compile_status)
	{
		int log_len = 0;
		glGetShaderiv(fs_shader, GL_INFO_LOG_LENGTH, &log_len);
		unique_ptr<char []> log(new char[log_len]);
		glGetShaderInfoLog(fs_shader, log_len, nullptr, log.get());

		cout << "Failed to compile fragment shader" << endl;
		cout << log.get() << endl;

		getchar();		// Wait for keypress
		exit(1);
	}

	// Create and link glsl program
	program = glCreateProgram();
	glAttachShader(program, vs_shader);
	glAttachShader(program, fs_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &compile_status);
	if (GL_FALSE == compile_status)
	{
		int log_len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
		unique_ptr<char []> log(new char[log_len]);
		glGetProgramInfoLog(program, log_len, nullptr, log.get());

		cout << "Failed to link program" << endl;
		cout << log.get() << endl;

		getchar();		// Wait for keypress
		exit(1);
	}

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// Load images, if used
	GLint rocks_color_tex_uniform = glGetUniformLocation(program, "rocks_color_tex");
	GLint rocks_normal_tex_uniform = glGetUniformLocation(program, "rocks_normal_tex");

	glUseProgram(program);

	if (rocks_color_tex_uniform != -1)
	{
		// 'rocks_color_tex' is used in the shader
		glUniform1i(rocks_color_tex_uniform, 0);	// Bind it to the first texture unit

		ilImage image;
		if (image.Load("Fieldstone.PNG"))
		{
			glGenTextures(1, &tex_rocks_color);
			glBindTexture(GL_TEXTURE_2D, tex_rocks_color);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
		}
		else
		{
			cout << "Warning: rocks_color_tex texture is used, but failed to load. Texture will be missing." << endl;
		}
	}

	if (rocks_normal_tex_uniform != -1)
	{
		// 'rocks_normal_tex' is used in the shader
		glUniform1i(rocks_normal_tex_uniform, 1);	// Bind it to the second texture unit

		ilImage image;
		if (image.Load("FieldstoneBumpDOT3.PNG"))
		{
			glGenTextures(1, &tex_rocks_normal);
			glBindTexture(GL_TEXTURE_2D, tex_rocks_normal);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width(), image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
		}
		else
		{
			cout << "Warning: tex_rocks_normal texture is used, but failed to load. Texture will be missing." << endl;
		}
	}

	glUseProgram(0);
}

void draw_cube_for_normal_mapping()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_rocks_color);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_rocks_normal);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * 14, &vertices[5]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(float) * 14, &vertices[2]);
	glEnableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 14, &vertices[0]);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE1);
	glTexCoordPointer(3, GL_FLOAT, sizeof(float) * 14, &vertices[8]);			// Tangents are set as the second texture unit multi-texture coordinates
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE2);
	glTexCoordPointer(3, GL_FLOAT, sizeof(float) * 14, &vertices[11]);			// Bitangents are set as the third texture unit multi-texture coordinates
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glUseProgram(program);
	glRotatef(rotY, 1.0f, 0.0f, 0.0f);
	glRotatef(rotX, 0.0f, 1.0f, 0.0f);

	glDrawArrays(GL_QUADS, 0, 24);
	glUseProgram(0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE2);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 
	float light0_position[] = {2.0f, 2.0f, 2.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0f);

	draw_cube_for_normal_mapping();

	glutSwapBuffers();
}

void timer(int)
{
	time_s += 0.05f;

	// Animate object, if animation is activated and object is not handled by the user
	if (animate && !user_rotates)
	{
		rotX += 5.0f;
		rotY += 5.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Init window
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("PV112 - Third project");
	glutHideWindow();
	init();
	glutShowWindow();

	// Register callbacks
	glutDisplayFunc(render);
	glutKeyboardFunc(key_pressed);
	glutReshapeFunc(reshape);
	glutTimerFunc(50, timer, 0);
	glutPassiveMotionFunc(mouse_moved);
	glutMotionFunc(mouse_moved);
	glutMouseFunc(mouse_fnc);

	//Main loop
	glutMainLoop();

	return 0;
}
