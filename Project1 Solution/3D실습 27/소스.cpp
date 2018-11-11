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
	int jump;
};
struct Rotate {
	double Rx, Ry, Rz;
};
struct Running {
	int r_run;
	int r_leg;
	int r_vel;
};
pos O;
pos camera;
Running R;
double tree_scale = 1;
float tree_velocity = 0.1;
int pull_up_R = 0;
int Bench_r = 0;
int Bench_vel = 2;
bool stage_open;
double door_y = 0;
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
int Collosion()
{
	/***********************************************/
	if (O.x - 50 <= -400 + 25
		&& O.x + 50 >= -400 - 25
		&& O.z - 50 <= -400 + 25
		&& O.z + 50 >= -400 - 25)
	{
		return 1;
	}
	
	/***********************pull*****************/
	if (O.x - 50 <= -400 + 100
		&& O.x + 50 >= -400 - 100
		&& O.z - 50 <= 400 + 100
		&& O.z + 50 >= 400 - 100)
	{
		return 1;
	}


	/*********************running**********************/
	if (O.x - 50 <= 400 + 100
		&& O.x + 50 >= 400 - 100
		&& O.z - 50 <= -400 + 100
		&& O.z + 50 >= -400 - 100)
	{
		return 1;
	}

	
	/*********************bench**********************/
	if (O.x - 100 <= 400 + 100
		&& O.x + 100 >= 400 - 100
		&& O.z - 50 <= 400 + 100
		&& O.z + 50 >= 400 - 100)
	{
		return 1;
	}

	return 0;
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
		O.mode = 180;
		
		
		break;
	case 's':
		O.mode = 0;
		
		break;
	case 'a':
		O.mode = 270;
		
		break;
	case 'd':
		O.mode = 90;
		
		break;
	case 'o':
		if(stage_open)
			stage_open = 0;
		else
			stage_open = 1;
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
	if (O.mode == 0)
	{
		O.z += O.dir;
		if (O.z >= 450 || O.z <= -450|| Collosion()) {
			O.z -= O.dir;
			if (O.jump == 0)
				O.jump = 1;
		}
	}
	else if (O.mode == 90)
	{
		O.x += O.dir;
		if (O.x >= 450 || O.x <= -450 || Collosion()) {
			O.x -= O.dir;
			if (O.jump == 0)
				O.jump = 1;
		}
	}
	else if (O.mode == 180)
	{
		O.z -= O.dir;
		if (O.z >= 450 || O.z <= -450 || Collosion()) {
			O.z += O.dir;
			if (O.jump == 0)
				O.jump = 1;
		}
	}
	else if (O.mode == 270)
	{
		O.x -= O.dir;
		if (O.x >= 450 || O.x <= -450 || Collosion()) {
			O.x += O.dir;
			if (O.jump == 0)
				O.jump = 1;
		}
	}
	
	if (O.jump == 1)
	{
			O.y += 5;
			if (O.y >= 50)
				O.jump = 2;
	}
	else if (O.jump == 2)
	{
		O.y -= 5;
		if (O.y <= 0)
			O.jump = 0;
	}
	/***************************************/
	if (stage_open) {
		if (door_y < 1000)
			door_y += 50;
	}
	else
	{
		if (door_y > 0)
			door_y -= 50;
	}
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
	O.mode = 0;
	R.r_vel = 5;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("실습21"); // 윈도우 생성 (윈도우 이름)
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
void drawRecSTAGE(float size)
{
	
	glPushMatrix();
	glFrontFace(GL_CCW);
	glPushMatrix();
	glTranslatef(0.0, door_y, 0);
	glBegin(GL_QUADS);
	//앞면		 
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-size / 2, size / 2, size / 2);//2
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, size / 2, size / 2);//3

	glEnd();
	glPopMatrix();
	glBegin(GL_QUADS);
	//윗면
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-size / 2, size / 2, -size / 2); //1
	glVertex3f(-size / 2, size / 2, size / 2);// 2
	glVertex3f(size / 2, size / 2, size / 2);// 3
	glVertex3f(size / 2, size / 2, -size / 2);//4
	
	//오른쪽옆면
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(size / 2, size / 2, size / 2);//3
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, size / 2, -size / 2);//4
	//왼쪽옆면
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(-size / 2, size / 2, -size / 2);//1
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, size / 2, size / 2);//2
	//뒷면
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(size / 2, size / 2, -size / 2);//4
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, size / 2, -size / 2);//1

	//바닥면
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	glVertex3f(size / 2, -size / 2, size / 2);//7

	glColor3f(1, 1, 0);
	glVertex3f(-size / 2, -size / 2, -size / 2);//5
	glVertex3f(-size / 2, -size / 2, size / 2);//6
	glVertex3f(size / 2, -size / 2, size / 2);//7
	glVertex3f(size / 2, -size / 2, -size / 2);//8
	
	glEnd();
	
	/*****************************************************************/
	glPushMatrix();
	glFrontFace(GL_CW);
	glTranslatef(-500, -499, -500);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(500, -499, 500);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glFrontFace(GL_CCW);
	glTranslatef(500, -499, -500);
	glRotatef(180, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glFrontFace(GL_CW);
	glTranslatef(-500, -499, 500);
	glRotatef(270, 0.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void drawCrane()
{
	glPushMatrix();//맨아래

	glTranslatef(O.x, -100+O.y, O.z);
	glRotatef(O.mode, 0.0, 1.0, 0.0);
	/**************************************************/
	glPushMatrix(); {
		glTranslatef(0, 100, 0);
		glPushMatrix(); {
			glTranslatef(0 + 15, -50, 0);
			glRotatef(-R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(1, 0, 0);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0 -15, -50, 0);
			glRotatef(R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(1, 0, 0);
			glutSolidCube(1);
		}glPopMatrix();
		/*****************************************************/
		glPushMatrix(); {
			glTranslatef(0 + 50, 50, 0);
			glRotatef(R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(0, 1, 0);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0 - 50, 50, 0);
			glRotatef(-R.r_leg, 1.0, 0.0, 0.0);
			glTranslatef(0, -50, 0);

			glScalef(30, 100, 30);
			glColor3f(0, 1, 0);
			glutSolidCube(1);
		}glPopMatrix();
		/*******************************************************/
		glPushMatrix(); {
			glTranslatef(0, 0, 0);

			glScalef(70, 100, 50);
			glColor3f(0, 0, 1);
			glutSolidCube(1);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 70, 0);

			glScalef(2, 2, 2);
			glColor3f(1, 0.4, 0.5);
			glutSolidCube(20);
			glPushMatrix(); {
				glTranslatef(0, 0, 13);

				glScalef(1, 2, 1);
				glColor3f(0.9,0.9, 0.9);
				glutSolidCube(5);
			}glPopMatrix();
		}glPopMatrix();
	}glPopMatrix();
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
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	/**************************************************/
	gluLookAt(0 + camera.x, 200 + camera.y, 500 + camera.z, 0.0 + camera.x, 0.0 + camera.y, 0.0 , 0.0, 1, 0.0);
	glMultMatrixd(rotate);
	/**************************************************/
	drawCoordinate();
	glPushMatrix(); {
		glTranslatef(0.0, 350.0,0 );
		drawRecSTAGE(1000);
	}glPopMatrix();
	/*****************************************************/
	drawCrane();
	drawTree();
	drawPull_up();
	drawRunning();
	drawBenchPress();
	/****************************************************/
	glPopMatrix();
	glEnable(GL_CULL_FACE);
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
	glTranslatef(0.0, 0.0, -700.0);
	glMatrixMode(GL_MODELVIEW);
}
