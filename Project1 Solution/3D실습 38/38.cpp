#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct pos {
	float x, y, z;
};
pos camera;
GLdouble rotate[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
void Init_array(GLdouble arr[])
{
	arr[0] = 1; arr[1] = 0; arr[2] = 0; arr[3] = 0;
	arr[4] = 0; arr[5] = 1; arr[6] = 0; arr[7] = 0;
	arr[8] = 0; arr[9] = 0; arr[10] = 1; arr[11] = 0;
	arr[12] = 0; arr[13] = 0; arr[14] = 0; arr[15] = 1;
}
void Init()
{
	camera.x = 0;
	camera.y = 100;
	camera.z = 100;
	Init_array(rotate);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		glPushMatrix();
		glRotatef(5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'X':
		glPushMatrix();
		glRotatef(-5, 1.0, 0.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'y':
		glPushMatrix();
		glRotatef(5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Y':
		glPushMatrix();
		glRotatef(-5, 0.0, 1.0, 0.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'z':
		glPushMatrix();
		glRotatef(5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'Z':
		glPushMatrix();
		glRotatef(-5, 0.0, 0.0, 1.0);
		glMultMatrixd(rotate);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotate);
		glPopMatrix();
		break;
	case 'w':
		camera.y += 2;
		break;
	case 's':
		camera.y -= 2;
		break;
	case 'a':
		camera.x -= 2;
		break;
	case 'd':
		camera.x += 2;
		break;
	case '+':
		camera.z -= 2;
		break;
	case '-':
		camera.z += 2;
		break;
	default:
		break;
	}

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	Init();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
void drawRec(float size)
{
	glBegin(GL_QUADS);
	//윗면
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
											  //앞면		 
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, size / 2, size / 2);//3
											 //오른쪽옆면
	glVertex3f(size / 2, size / 2, size / 2);//3
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, size / 2, -size / 2);//4
											  //왼쪽옆면
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, size / 2, size / 2);//2
											  //뒷면
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, size / 2, -size / 2);//1

											   //바닥면
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glEnd();
}

GLfloat AmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 녹색조명
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 적색조명
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명
GLfloat lightPos[] = { 0.0, 600.0, 100.0, 1.0 }; // 위치: (10, 5, 20)
GLvoid drawScene(GLvoid)
{
	//glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	//gluLookAt(0 + camera.x, 200 + camera.y, 500, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/****************************************************/



												   // 조명을 사용하도록 설정
	glEnable(GL_LIGHTING);
	// 조명 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 조명 효과를 설정한다.
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	// 재질 컬러 트래킹을 설정한다.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
				glEnable(GL_BLEND); 
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			glPushMatrix(); {
				glTranslatef(i * 800 / 3, -j * 600 / 3, 0);
				glEnable(GL_LIGHT0);

				glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
				glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
				glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

				//glEnable(GL_CULL_FACE);

				

				glPushMatrix(); {
					glTranslatef(100, 500, 0);
					glColor4f(1.0, 0.0, 0.0, 0.6);
					glutSolidTeapot(50);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(190, 500, -50);
					glColor4f(0.0, 0.0, 1.0, 0.6);
					glRotated(-90, 1, 0, 0);
					glutSolidCone(50, 50, 20, 20);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(150, 480, 50);
					glColor4f(0.0, 1.0, 0.0, 0.6);
					glutSolidSphere(50, 20, 20);
				}glPopMatrix();
			}glPopMatrix();
		}
	}
	/****************************************************/
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}
