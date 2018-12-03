#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct pos {
	float x, y, z;
};
int move_x=1, move_y=1;
int set_mode = 4;
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
float arpha[9] = { 0 };
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
		if (move_y < 2) {
			move_y++;
			set_mode--;
		}
		
		break;
	case 's':
		if (move_y > 0) {
			move_y--;
			set_mode++;
		}
		break;
	case 'a':
		if (move_x > 0) {
			move_x--;
			set_mode -= 3;
			
		}
		break;
	case 'd':
		if (move_x < 2){
			move_x++;
			set_mode += 3;
			
		}
		break;
	case '+':
		if(arpha[set_mode]<=1.0f)
			arpha[set_mode]+=0.1;
		break;
	case '-':
		if (arpha[set_mode] >= 0.0f)
			arpha[set_mode] -= 0.1;
		break;
	default:
		break;
	}
	std::cout << set_mode;
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
GLfloat AmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 녹색조명
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 적색조명
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // 백색조명
GLfloat lightPos[] = { 0.0, 600.0, 100.0, 1.0 }; // 위치: (10, 5, 20)

const char *string[] = {
		"0:{GL_ONE, GL_ZERO}" ,"1:{GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA}" ,"2:{GL_ONE, GL_ONE}" ,
		"3:{GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}" ,"4:{GL_SRC_ALPHA, GL_ONE}" ,"5:{GL_ZERO, GL_SRC_COLOR}" ,
		"6:{GL_ONE_MINUS_DST_COLOR, GL_ZERO}" ,"7:{GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR}" ,"8:{GL_ZERO, GL_ONE}" ,
};

void main(int argc, char *argv[])
{
	Init();
	for (int i = 0; i < 9; ++i)
	{
		arpha[i] = 0.5;
	}
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
GLvoid drawScene(GLvoid)
{
	glClearColor(0.5, 0.5, 0.5, 1);
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

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			
			if (i * 3 + j == 0)
				glBlendFunc(GL_ONE, GL_ZERO);
			else if (i * 3 + j == 1)
				glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
			else if (i * 3 + j == 2)
				glBlendFunc(GL_ONE, GL_ONE);
			else if (i * 3 + j == 3)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			else if (i * 3 + j == 4)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else if (i * 3 + j == 5)
				glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			else if (i * 3 + j == 6)
				glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
			else if (i * 3 + j == 7)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
			else if (i * 3 + j == 8)
				glBlendFunc(GL_ZERO, GL_ONE);
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
					glColor4f(0.0, 1.0, 0.0, arpha[i * 3 + j]);
					glutSolidSphere(50, 20, 20);
				}glPopMatrix();
				glPushMatrix(); {
					glBlendFunc(GL_ONE, GL_ONE);
					glColor3f(1.0, 1.0, 1.0);
					

					int len = (int)strlen(string[i * 3 + j]);
					glRasterPos3f(0, 420,100); // 문자 출력할 위치 설정
					for (int k = 0; k < len; k++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i * 3 + j][k]);
					
					
				}glPopMatrix();
			}glPopMatrix();
		}
	}
	glPushMatrix(); {
		glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_LINES);

	glVertex3f(800 / 3 * move_x+2, 600 / 3 * (move_y + 1)-2, 0);//2
	glVertex3f(800 / 3 * move_x+2, 600 / 3 * (move_y)+2, 0);//6

	glVertex3f(800 / 3 * move_x+2, 600 / 3 * (move_y)+2, 0);//6
	glVertex3f(800 / 3 * (move_x + 1)-2, 600 / 3 * (move_y)+2, 0);//7

	glVertex3f(800 / 3 * (move_x + 1)-2, 600 / 3 * (move_y)+2, 0);//7
	glVertex3f(800 / 3 * (move_x + 1)-2, 600 / 3 * (move_y + 1)-2, 0);//3

	glVertex3f(800 / 3 * (move_x + 1)-2, 600 / 3 * (move_y + 1)-2, 0);//3
	glVertex3f(800 / 3 * move_x+2, 600 / 3 * (move_y + 1)-2, 0);//2
	glEnd();
	}glPopMatrix();
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
