// PV112, preparation for lesson 4
// Contact Jan Cejka, or use discussion forums, for additional information.

// This file should help you get prepared for the foufth lesson of PV112. It is
// intended for students that use their own developer tools and platforms
// (NetBeans, CodeBlocks, Linux etc). Students that use the same tools as the
// teacher need not to prepare anything since it will be done at the beginning
// of the lesson.

// In the fourth lesson, we will deal with textures, and so we need to load
// them. We use DevIL image library, which is available at
// http://openil.sourceforge.net/ . However, we found that newer versions are
// not fully backward compatible, and also they need to be modified a bit for
// us to use them. That's why we have prepared a zip file and placed it in
// Study Materials for PV112 / Learning Materials / C++ DevIL / DevIL.zip. In
// lessons, we use files from this zip. If you decide to download DevIL and use
// it, you may need to tackle with problems like include paths, library paths,
// linking with libraries and different names of classes and functions.
// However, the functionality should be the same.

#include <GL/glut.h>

// When we define IL_USE_PRAGMA_LIBS, DevIL setups linker to link to all
// necessary libraries. Use this, or link with those libraries manually,
// if this does not work.
#define IL_USE_PRAGMA_LIBS
// We use class 'ilImage', which is a wrapper to IL functions. That's why we
// include 'devil_cpp_wrapper.hpp' instead of 'il.h'.
#include <IL/devil_cpp_wrapper.hpp>

void key_pressed(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	};
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// OpenGL assumes all textures have their origin in lower left corner. We
	// must inform IL about this fact, or we shall get upside-down textures.
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// As mentioned, we use classes to simplify manipulation with images.
	// We use the following methods:
	//		- Load		.. loads image from file
	//		- Width		.. returns width of loaded image
	//		- Height	.. returns height of loaded image
	//		- GetData	.. returns pointer to data of image
	ilImage image;
	
	// Try several image formats, at least PNG and JPG. Try only textures with
	// power-of-two sizes (like 256x256, 512x512 etc.). Loading images with
	// other dimensions may need some additional steps to make them work, and
	// they are not necessary to deal with to get ready for the fourth lesson.
	// Also, some platforms needs 'const char *' and some 'const wchar_t *',
	// so add/remove 'L' before the path when necessary.
	image.Load(L"coordinates.png");		// We use Load method here

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// We use Width, Height and GetData methods here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.Width(), image.Height(), 0,
		GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// We render the loaded image in the center of the window. We use no
	// transformations. Make sure the image is corrently loaded and displayed,
	// without any errors like inverted colors, upside-down etc.
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);		glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);		glVertex2f( 0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);		glVertex2f( 0.5f,  0.5f);
		glTexCoord2f(0.0f, 1.0f);		glVertex2f(-0.5f,  0.5f);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	// Init window
	glutInitWindowSize(500, 500);
	glutCreateWindow("PV112 - cv4: preparation");

	// Register callbacks
	glutDisplayFunc(render);
	glutKeyboardFunc(key_pressed);

	init();

	//Main loop
	glutMainLoop();

	return 0;
}
