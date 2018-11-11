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
	int dir;
	int mode;
	int speed;
};
struct Rotate {
	double Rx, Ry, Rz;
};
struct Running {
	int r_run;
	int r_leg;
	int r_vel;
};
pos plane;
pos smoke[3];
pos O;
pos circle;
pos camera;
Running R;
int count;
double tree_scale = 1;
float tree_velocity = 0.1;
int pull_up_R = 0;
int Bench_r = 0;
int Bench_vel = 2;
int plane_r = 0;
GLdouble rotate[16]
= { 1,0,0,0,
0,1,0,0,
0,0,1,0,
0,0,0,1 };
GLdouble rotateC[16]
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
void Collosion()
{
	if (O.x - 100 <= circle.x + 50
		&& O.x + 100 >= circle.x - 50
		&& O.z - 50 <= circle.z + 50
		&& O.z + 50 >= circle.z - 50)
	{
		O.dir *= -1;
		circle.dir *= -1;
		circle.speed *= -1;
	}
	/*********************************나무****/
	if (O.x - 100 <= -400 + 25
		&& O.x + 100 >= -400 - 25
		&& O.z - 50 <= -400 + 25
		&& O.z + 50 >= -400 - 25)
	{
		O.dir *= -1;
	}

	if (circle.x - 50 <= -400 + 25
		&& circle.x + 50 >= -400 - 25
		&& circle.z - 50 <= -400 + 25
		&& circle.z + 50 >= -400 - 25)
	{
		circle.dir *= -1;
		circle.speed *= -1;
	}
	/***********************pull*****************/
	if (O.x - 100 <= -400 + 100
		&& O.x + 100 >= -400 - 100
		&& O.z - 50 <= 400 + 100
		&& O.z + 50 >= 400 - 100)
	{
		O.dir *= -1;
	}

	if (circle.x - 50 <= -400 + 100
		&& circle.x + 50 >= -400 - 100
		&& circle.z - 50 <= 400 + 100
		&& circle.z + 50 >= 400 - 100)
	{
		circle.dir *= -1;
		circle.speed *= -1;
	}
	/*********************running**********************/
	if (O.x - 100 <= 400 + 100
		&& O.x + 100 >= 400 - 100
		&& O.z - 50 <= -400 + 100
		&& O.z + 50 >= -400 - 100)
	{
		O.dir *= -1;
	}

	if (circle.x - 50 <= 400 + 100
		&& circle.x + 50 >= 400 - 100
		&& circle.z - 50 <= -400 + 100
		&& circle.z + 50 >= -400 - 100)
	{
		circle.dir *= -1;
		circle.speed *= -1;
	}
	/*********************bench**********************/
	if (O.x - 100 <= 400 + 100
		&& O.x + 100 >= 400 - 100
		&& O.z - 50 <= 400 + 100
		&& O.z + 50 >= 400 - 100)
	{
		O.dir *= -1;
	}

	if (circle.x - 50 <= 400 + 100
		&& circle.x + 50 >= 400 - 100
		&& circle.z - 50 <= 400 + 100
		&& circle.z + 50 >= 400 - 100)
	{
		circle.dir *= -1;
		circle.speed *= -1;
	}
}
void Keyboard(unsigned char key, int x, int y)
{

	switch (key) {
		{
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
		}
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
	case '1':
		O.mode *= -1;
		break;
	case '2':
		circle.mode *= -1;
		break;
	case 'r':
		plane_r += 2;
		break;
	case 'i':
		O.x = 0;
		Init_array(rotate);
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
	plane.dir += 30;
	plane.speed += 5;
	count=(count+1)%16;
	for (int i = 0; i < 3; ++i)
	{
		smoke[i].mode= (smoke[i].mode+1)%30;
	}
	if (count == 5)
	{
		smoke[0].x = plane.x;
		smoke[0].y = plane.y;
		smoke[0].mode = 0;
	}
	else if (count  == 10)
	{
		smoke[1].x = plane.x;
		smoke[1].y = plane.y;
		smoke[1].mode = 0;
	}
	else if (count == 15)
	{
		smoke[2].x = plane.x;
		smoke[2].y= plane.y;
		smoke[2].mode = 0;
	}
	/**************************************/
	if (O.mode == 1) {
		O.x += O.dir;
		if (O.x >= 400 || O.x <= -400)
			O.dir *= -1;
	}
	else {
		O.z += O.dir;
		if (O.z >= 450 || O.z <= -450)
			O.dir *= -1;
	}
	/***************************************/
	if (circle.mode == 1) {
		circle.x += circle.dir;
		if ((circle.x + 50) >= 500 || (circle.x - 50) <= -500)
		{
			circle.dir *= -1;
			circle.speed *= -1;
		}
		glPushMatrix();
		glRotatef(-circle.speed, 0.0, 0.0, 1.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
	}
	else {
		circle.z += circle.dir;
		if ((circle.z - 50) <= -500 || (circle.z + 50) >= 500)
		{
			circle.dir *= -1;
			circle.speed *= -1;
		}
		glPushMatrix();
		glRotatef(circle.speed, 1.0, 0.0, 0.0);
		glMultMatrixd(rotateC);
		glGetDoublev(GL_MODELVIEW_MATRIX, rotateC);
		glPopMatrix();
	}
	Collosion();
	/***************************************/
	tree_scale += tree_velocity;
	if (tree_scale >= 1.5 || tree_scale <= 1)
		tree_velocity *= -1;
	pull_up_R = (pull_up_R + 5) % 360;
	if (pull_up_R > 90 && pull_up_R < 270)
		pull_up_R = (pull_up_R) % 360;
	else if (pull_up_R >= 0 || pull_up_R <= 360)
		pull_up_R = (pull_up_R + 5) % 360;
	R.r_run += 5;
	R.r_leg += R.r_vel;
	if (R.r_leg > 45 || R.r_leg < -45)
		R.r_vel *= -1;

	Bench_r += Bench_vel;
	if (Bench_r > 60 || Bench_r < 0)
		Bench_vel *= -1;
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	O.dir = 5;
	O.z = -200;
	O.mode = 1;
	circle.mode = 1;
	circle.speed = 4;
	circle.dir = 50 * PI * 2 * circle.speed / 360;
	R.r_vel = 4;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습22"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수
void drawCoordinate()
{
	glPushMatrix();       //좌표축
	glTranslatef(50, 0, 0);
	glScalef(50, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(1, 50, 1);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 50);
	glScalef(1, 1, 50);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(2);
	glPopMatrix();
}
void drawFloor()
{
	glPushMatrix(); // 바닥
	glScalef(1000, 1, 1000);
	glTranslatef(0, -150, 0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-500, -149, -500);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500, -149, 500);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500, -149, -500);
	glRotatef(180, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-500, -149, 500);
	glRotatef(270, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();
	glPopMatrix();
}

void drawCrane()
{
	glPushMatrix();//맨아래

	glTranslatef(O.x, -100, O.z);

	glPushMatrix(); {
		glColor3f(1.0, 0.0, 0.0);
		glScalef(2, 1, 1);
		glutSolidCube(100);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(100);
		glPopMatrix(); }
	glPushMatrix();//중간

	glTranslatef(0, 50, 0);

	glTranslatef(0, 50, 0);

	glPushMatrix(); {
		glColor3f(0.0, 1.0, 0.0);
		glScalef(0.5, 1, 0.5);
		glutSolidCube(100);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(100);
		glPopMatrix(); }
	glPushMatrix();//맨위
	glTranslatef(0, 50, 0);


	glTranslatef(0, 50, 0);

	glColor3f(0.0, 0.0, 1.0);
	glScalef(0.25, 1, 0.25);
	glutSolidCube(100);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(100);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void drawCircle()
{
	glColor3f(0.0, 0.0, 0.0);

	glPushMatrix();

	glTranslatef(circle.x, -100, circle.z);
	glMultMatrixd(rotateC);
	glutWireSphere(50, 10, 10);
	glPopMatrix();
}

void drawTree()
{
	glPushMatrix();

	glTranslatef(-400, -50, -400);
	glPushMatrix();
	glScalef(50, 200, 50);
	glColor3f(0.6, 0.4, 0.0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 150, 0);
	glScalef(tree_scale, tree_scale, tree_scale);
	glColor3f(0, 1, 0.0);
	glutWireSphere(100, 20, 20);
	glPopMatrix();
	glPopMatrix();
}
void drawPull_up()
{
	glPushMatrix();
	{
		glTranslatef(-400, -50, 400);
		glPushMatrix(); {
			glTranslatef(0 - 50, 0, 0 - 100);
			glScalef(1, 150, 1);
			glRotatef(90, 1.0, 0.0, 0.0);

			glColor3f(0.5, 0.5, 0.5);
			glutSolidTorus(1, 10, 5, 5); }
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0 + 100, 0, +50);
			glScalef(1, 150, 1);
			glRotatef(90, 1.0, 0.0, 0.0);

			glColor3f(0.5, 0.5, 0.5);
			glutSolidTorus(1, 10, 5, 5); }
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(25, 125, -25);

			glRotatef(45, 0.0, 1.0, 0.0);
			glPushMatrix(); {
				glScalef(1, 1, 120);
				glColor3f(0.6, 0.6, 0.6);
				glutSolidTorus(1, 5, 5, 5);
			}glPopMatrix();

			glPushMatrix(); {
				glRotatef(pull_up_R, 0.0, 0.0, 1.0);
				glTranslatef(0, -100, 0);
				glPushMatrix(); {
					glRotatef(-45, 0.0, 1.0, 0.0);
					glTranslatef(0 + 25, 50, 0 + 25);

					glScalef(15, 100, 15);
					glColor3f(1, 0.8, 0.4);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glRotatef(-45, 0.0, 1.0, 0.0);
					glTranslatef(0 - 25, 50, 0 - 25);

					glScalef(15, 100, 15);
					glColor3f(1, 0.8, 0.4);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, -30, 0);

					glScalef(30, 100, 50);
					glColor3f(0.6, 0.4, 0.0);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 30, 0);

					glScalef(2, 2, 2);
					glColor3f(1, 0.4, 0.5);
					glutWireSphere(10, 20, 20);
				}glPopMatrix();
			}glPopMatrix();
		}glPopMatrix();
	}
	glPopMatrix();
}
void drawRunning()
{
	glPushMatrix();
	{
		glTranslatef(400, -50, -400);
		glPushMatrix(); {
			glTranslatef(0, -90, 0);
			glRotatef(45, 0.0, 1.0, 0.0);
			glPushMatrix(); {

				glScalef(5, 1, 10);
				glRotatef(R.r_run, 0.0, 0.0, 1.0);
				glColor3f(0.5, 0.5, 0.5);
				glutWireTorus(5, 10, 20, 20);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 10, 50);
				glScalef(130, 30, 10);
				//glRotatef(R.r_run, 0.0, 0.0, 1.0);
				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 10, -50);
				glScalef(130, 30, 10);

				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 130, 50);
				glScalef(130, 10, 10);
				//glRotatef(R.r_run, 0.0, 0.0, 1.0);
				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 130, -50);
				glScalef(130, 10, 10);

				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(50, 80, -50);
				glScalef(10, 120, 10);

				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(50, 80, 50);
				glScalef(10, 120, 10);

				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(50, 30, 0);
				glScalef(10, 10, 100);

				glColor3f(0.1, 0.1, 0.1);
				glutSolidCube(1);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(50, 150, 0);
				glRotatef(45, 0, 0.0, 1.0);
				glScalef(50, 10, 100);

				glColor3f(0.5, 0.5, 0.5);
				glutSolidCube(1);
			}glPopMatrix();

			glPushMatrix(); {
				//glRotatef(pull_up_R, 0.0, 0.0, 1.0);
				glTranslatef(0, 200, 0);
				glPushMatrix(); {
					glTranslatef(0 + 10, -65, 0 + 10);
					glRotatef(-R.r_leg, 0.0, 0.0, 1.0);
					glRotatef(-45, 0.0, 1.0, 0.0);
					glTranslatef(0, -65, 0);

					glScalef(15, 100, 15);
					glColor3f(1, 0.8, 0.4);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0 - 10, -65, 0 - 10);
					glRotatef(R.r_leg, 0.0, 0.0, 1.0);
					glRotatef(-45, 0.0, 1.0, 0.0);
					glTranslatef(0, -65, 0);

					glScalef(15, 100, 15);
					glColor3f(1, 0.8, 0.4);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, -30, 0);

					glScalef(30, 100, 50);
					glColor3f(0.6, 0.4, 0.0);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0, 30, 0);

					glScalef(2, 2, 2);
					glColor3f(1, 0.4, 0.5);
					glutWireSphere(10, 20, 20);
				}glPopMatrix();
			}glPopMatrix();
		}glPopMatrix();
	}
	glPopMatrix();
}
void drawBenchPress()
{
	glPushMatrix();
	{
		glTranslatef(400, -50, 400);
		glRotatef(-45, 0.0, 1.0, 0.0);
		glPushMatrix(); {
			glTranslatef(0, 0, 70);
			glScalef(1, 100, 1);
			glRotatef(90, 1.0, 0.0, 0.0);

			glColor3f(0.5, 0.5, 0.5);
			glutSolidTorus(1, 10, 5, 5); }
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, -70);
			glScalef(1, 100, 1);
			glRotatef(90, 1.0, 0.0, 0.0);

			glColor3f(0.5, 0.5, 0.5);
			glutSolidTorus(1, 10, 5, 5); }
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, 0);
			glScalef(1, 1, 80);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidTorus(1, 5, 5, 5);
		}glPopMatrix();

		glPushMatrix(); {
			glTranslatef(-50, 0, 0);
			glScalef(150, 20, 50);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidCube(1); }
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(-120, -50, 0);
			glScalef(10, 100, 50);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidCube(1); }
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(-30, 125 - Bench_r * 3 / 4, 0);
			glPushMatrix(); {
				glScalef(1, 1, 120);
				glColor3f(0.6, 0.6, 0.6);
				glutSolidTorus(1, 5, 5, 5);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 0, -100);
				glScalef(1, 1, 0.5);
				glColor3f(0.1, 0.1, 0.1);
				glutWireTorus(15, 20, 20, 20);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 0, 100);
				glScalef(1, 1, 0.5);
				glColor3f(0.1, 0.1, 0.1);
				glutWireTorus(15, 20, 20, 20);
			}glPopMatrix();

			glPushMatrix(); {
				glTranslatef(0, 0, -85);
				glScalef(1, 1, 0.25);
				glColor3f(0.1, 0.1, 0.1);
				glutWireTorus(35, 40, 40, 40);
			}glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0, 0, 85);
				glScalef(1, 1, 0.25);
				glColor3f(0.1, 0.1, 0.1);
				glutWireTorus(35, 40, 40, 40);
			}glPopMatrix();
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 125, 0);
			glPushMatrix(); {
				//glRotatef(pull_up_R, 0.0, 0.0, 1.0);
				glTranslatef(0, -100, 0);

				glPushMatrix(); {
					glTranslatef(-50, 0, 0);

					glScalef(100, 30, 50);
					glColor3f(0.6, 0.4, 0.0);
					glutSolidCube(1);
				}glPopMatrix();
				glPushMatrix(); {
					glTranslatef(20, 0, 0);

					glScalef(2, 2, 2);
					glColor3f(1, 0.4, 0.5);
					glutWireSphere(10, 20, 20);
				}glPopMatrix();
				/********************************************/
				glTranslatef(-25, 0, 0);

				glPushMatrix(); {
					glTranslatef(0, 0, 0 + 25);
					glRotatef(Bench_r, 1.0, 0.0, 0.0);

					glTranslatef(0, 25, 0);

					glPushMatrix(); {
						glRotatef(-45, 0.0, 1.0, 0.0);
						glScalef(15, 50, 15);
						glColor3f(1, 0.8, 0.4);
						glutSolidCube(1);
					}glPopMatrix();
					glPushMatrix(); {
						glTranslatef(0, 25, 0);
						glRotatef(-Bench_r * 2, 1.0, 0.0, 0.0);
						glTranslatef(0, 25, 0);

						glPushMatrix(); {
							glRotatef(-45, 0.0, 1.0, 0.0);
							glScalef(15, 50, 15);
							glColor3f(1, 0.8, 0.4);
							glutSolidCube(1);
						}glPopMatrix();
					}glPopMatrix();
				}glPopMatrix();
				/***********************************************/
				glPushMatrix(); {
					glTranslatef(0, 0, 0 - 25);
					glRotatef(-Bench_r, 1.0, 0.0, 0.0);
					glTranslatef(0, 25, 0);
					glPushMatrix(); {
						glRotatef(-45, 0.0, 1.0, 0.0);
						glScalef(15, 50, 15);
						glColor3f(1, 0.8, 0.4);
						glutSolidCube(1);
					}glPopMatrix();
					glPushMatrix(); {
						glTranslatef(0, 25, 0);
						glRotatef(Bench_r * 2, 1.0, 0.0, 0.0);
						glTranslatef(0, 25, 0);
						glPushMatrix(); {
							glRotatef(-45, 0.0, 1.0, 0.0);
							glScalef(15, 50, 15);
							glColor3f(1, 0.8, 0.4);
							glutSolidCube(1);
						}glPopMatrix();
					}glPopMatrix();
				}glPopMatrix();
			}glPopMatrix();
		}glPopMatrix();
	}
	glPopMatrix();
}

void drawAirPlane()
{
	plane.x = 300 * cos(plane.speed*RADIAN);
	plane.y = 300 * sin(plane.speed*RADIAN);
	glPushMatrix(); {

		for (int i = 0; i < 3; ++i) {
			if (smoke[i].mode >= 3) {
				glPushMatrix(); {
					glTranslatef(smoke[i].x, 200, smoke[i].y);
					glScalef(30 - smoke[i].mode, 30 - smoke[i].mode, 30 - smoke[i].mode);
					glColor3f(0.1, 0.1, 0.1);
					glutSolidSphere(1, 20, 20);
				}glPopMatrix();
			}
		}
		glTranslatef(plane.x, 200, plane.y);
		
		glRotatef(180-plane.speed, 0.0, 1.0, 0.0);
		glRotatef(plane_r, 0.0, 0.0, 1.0);
		glPushMatrix(); {
			glScalef(20, 30, 100);
			glColor3f(1.0, 0.0,1.0);
			glutSolidSphere(1,20,20);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 20, -20);
			glScalef(10, 20, 30);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidSphere(1, 20, 20);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, -30);
			glScalef(250, 10, 80);
			glColor3f(1.0, 1.0, 1.0);
			glutSolidCube(1);
		}glPopMatrix();

		glPushMatrix(); {
			glTranslatef(0, 0, 90);
			glScalef(100, 10, 20);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 25, 90);
			glScalef(10, 50, 20);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1);
		}glPopMatrix();


		glRotatef(plane.dir, 0.0, 0.0, 1.0);
		glPushMatrix(); {
			glTranslatef(0, 0, -100);
			glScalef(10, 80, 10);
			glColor3f(0.5, 0.7, 0.3);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, -100);
			glScalef(80, 10, 10);
			glColor3f(0.5, 0.7, 0.3);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0, -100);
			glRotatef(180, 0.0, 1.0, 0.0);
			glScalef(10, 10, 20);
			glColor3f(0.1, 0.2, 0.8);
			glutSolidCone(1, 1, 20, 20);
		}glPopMatrix();
	}glPopMatrix();
}
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/**************************************************/
	gluLookAt(0 + camera.x, 200 + camera.y, 500, 0.0 + camera.x, 0.0 + camera.y, 0.0 + camera.z, 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/**************************************************/
	drawCoordinate();

	drawFloor();
	/*****************************************************/
	drawCircle();
	drawCrane();
	drawTree();
	drawPull_up();
	drawRunning();
	drawBenchPress();
	drawAirPlane();
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
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -500.0);
	glMatrixMode(GL_MODELVIEW);
}
