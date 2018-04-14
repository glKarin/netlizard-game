#include "glk/glk.h"

void update();
int main(void)
{
	karinInitGLctxObject();
	karinSetWindowPosiotionAndSize(0, 0, width, height);
	karinCreateGLRenderWindow("TEST");
	karinFullscreen(False);
	Bool init_glk = karinHasInitGLctx();
	printf("%d\n", init_glk);
	//karinRegisterInitFunc(Main3D_InitGLFunc);
	karinRegisterDrawFunc(update);
	//karinRegisterReshapeFunc(Main3D_ReshapeGLFunc);
	karinMainLoop();
}

void update()
{
#ifdef _HARMATTAN_OPENGLES2
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1,1,1,1);
	GLfloat v[] = {
		0, 0, 5,
		1, 0, 5,
		0, 0.8, 5,
		1, 0.8, 5
	};

	gl2MatrixMode(GL2_PROJECTION);
	gl2LoadIdentity();
	//gl2Ortho(-2, 2, -2, 2, -1, 1);
	gluPerspective(45, width / height, 0.1, 100);
	gl2MatrixMode(GL2_MODELVIEW);
	gl2LoadIdentity();
	gl2Translate(0,0,-25);
	gl2PushMatrix();
	gl2LoadIdentity();
	gl2Translate(-1,-1,0);
	gl2PushMatrix();
	gl2Color4(0, 0, 1, 1);
	gl2Translate(0.5,0,0);
	oglDrawArrays(GL_TRIANGLES, 0, 3);
	gl2Rotate(90, 0, 0, 1);
	gl2EnableClientState(GL2_VERTEX_ARRAY);
	gl2VertexPointer(3, GL_FLOAT, 0, v);
	/*
	GLuint p = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(p);
	glVertexAttribPointer(p, 3, GL_FLOAT, GL_FALSE, 0, v);
	*/
	gl2Color4(1, 1, 0, 1);
	oglDrawArrays(GL_TRIANGLES, 0, 3);
	gl2Color4(1, 0, 0, 1);
	gl2Scale(0.5,0.5,0.5);
	oglDrawArrays(GL_TRIANGLES, 0, 3);

	gl2PopMatrix();
	gl2PopMatrix();

	gl2Color4(0, 1, 0, 1);
	oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	gl2Color4(1, 0, 1, 1);
	oglDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
	printf("%d, %x\n", program, glGetError());
#endif
}
