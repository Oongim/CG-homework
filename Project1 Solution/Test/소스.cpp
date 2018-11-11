#include <GL/freeglut.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14
#define RADIAN PI/180

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
                    /////////////////////////////////////  'c'  회전 이동 변환 ,    'r'  사각형 삼각형 변환
int move_x = 0;
int Size = 15;
int Size_mode = 0;
int Rotate = 0;
int Shape_mode = 1;
int Move_mode = 1;
int Move_stat = 0;

int left_button = 0;
double mouse_x = 0,mouse_y=0;
int mouse_arr[6][2] = { 0 };
int mouse_count = 0;
int mouse_move = false;
int Mmove_mode = 0;

double dx = 0, dy = 0, d = 0; //기울기 계산 을 위한 변수
double cx, cy = 0; //x,y절편
int dold, dnew; //결정 변수;
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'y':
		move_x += 4;
		break;
	case'Y':
		move_x -= 4;
		break;

	case'r':
		Shape_mode *= -1;
		break;
	case'c':
		Move_mode *= -1;
		break;

	case'0':
		Move_stat = 0;
		break;
	case'1':
		Move_stat = 1;
		break;
	case'2':
		Move_stat = 2;
		break;
	case'3':
		Move_stat = 3;
		break;
	case'4':
		Move_stat = 4;
		break;
	default:
		break;
	}
	
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&&mouse_move==false)
	{
		left_button = true;

		mouse_arr[mouse_count][0] = x-400;
		mouse_arr[mouse_count][1] = 300-y;
		mouse_count++;
		if (mouse_count == 6)
		{
			mouse_move = true;
			mouse_x = mouse_arr[0][0];
			mouse_y = mouse_arr[0][1];
			//기울기
			dx = mouse_arr[Mmove_mode + 1][0] - mouse_arr[Mmove_mode][0];
			dy = mouse_arr[Mmove_mode + 1][1] - mouse_arr[Mmove_mode][1];
			d = (double)dy / (double)dx;

			//y절편
			cy = mouse_arr[Mmove_mode][1] - (d*mouse_arr[Mmove_mode][0]);
			//x절편
			cx = -(cy / d);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouse_move = true;
		mouse_x = mouse_arr[0][0];
		mouse_y = mouse_arr[0][1];
		//기울기
		dx = mouse_arr[Mmove_mode + 1][0] - mouse_arr[Mmove_mode][0];
		dy = mouse_arr[Mmove_mode + 1][1] - mouse_arr[Mmove_mode][1];
		d = (double)dy / (double)dx;

		//y절편
		cy = mouse_arr[Mmove_mode][1] - (d*mouse_arr[Mmove_mode][0]);
		//x절편
		cx = -(cy / d);
	}
	glutPostRedisplay();

}
void Motion(int x, int y) {
	if (left_button == true&&true!=mouse_move)
	{
		mouse_x = x - 400;
		mouse_y = 300 - y;

		glutPostRedisplay();
	}
}
void TimerFunction(int value)
{
	
	if (Move_stat == 1)
	{
		if (move_x >= 1200)
			move_x = 0;
	}
	else if (Move_stat == 2)
	{
		if (move_x >= 1160)
			move_x = 0;
	}
	else if (Move_stat == 3)
	{
		if (move_x >= 600)
			move_x = 0;
	}

	if (Size_mode == 0) {
		Size += 1;
		if (Size == 20)
			Size_mode = 1;
	}
	else if (Size_mode == 1)
	{
		Size -= 1;
		if (Size == 15)
			Size_mode = 0;
	}

	if (mouse_move == true)
	{
		if (d < 1.0)
		{
			if (mouse_arr[Mmove_mode + 1][0] > mouse_arr[Mmove_mode][0])
			{
				mouse_x += 4;
				mouse_y = d * mouse_x + cy;
			}
			else
			{
				mouse_x -=4;
				mouse_y = d * mouse_x + cy;
			}
			if (mouse_arr[Mmove_mode + 1][0] + 4 >= mouse_x && mouse_arr[Mmove_mode + 1][0] - 4 <= mouse_x)
			{
				mouse_x = mouse_arr[Mmove_mode + 1][0];
				mouse_y = mouse_arr[Mmove_mode + 1][1];

				Mmove_mode++;
				if (Mmove_mode + 1 == mouse_count)
				{
					left_button = false;
					mouse_count = 0;
					mouse_x = 0, mouse_y = 0;
					mouse_move = false;
					Mmove_mode = 0;
				}
				//기울기
				dx = mouse_arr[Mmove_mode + 1][0] - mouse_arr[Mmove_mode][0];
				dy = mouse_arr[Mmove_mode + 1][1] - mouse_arr[Mmove_mode][1];
				d = (double)dy / (double)dx;

				//y절편
				cy = mouse_arr[Mmove_mode][1] - (d*mouse_arr[Mmove_mode][0]);
				//x절편
				cx = -(cy / d);
			}
		}
		else
		{
			if (mouse_arr[Mmove_mode + 1][1] > mouse_arr[Mmove_mode][1])
			{
				mouse_y += 4;
				mouse_x =  (mouse_y - cy)/d;
			}
			else
			{
				mouse_y -= 4;
				mouse_x = (mouse_y - cy) / d;
			}
			if (mouse_arr[Mmove_mode + 1][1] + 4 >= mouse_y && mouse_arr[Mmove_mode + 1][1] - 4 <= mouse_y)
			{
				mouse_x = mouse_arr[Mmove_mode + 1][0];
				mouse_y = mouse_arr[Mmove_mode + 1][1];

				Mmove_mode++;
				if (Mmove_mode + 1 == mouse_count)
				{
					left_button = false;
					mouse_count = 0;
					mouse_x = 0, mouse_y = 0;
					mouse_move = false;
					Mmove_mode = 0;
				}
				//기울기
				dx = mouse_arr[Mmove_mode + 1][0] - mouse_arr[Mmove_mode][0];
				dy = mouse_arr[Mmove_mode + 1][1] - mouse_arr[Mmove_mode][1];
				d = (double)dy / (double)dx;

				//y절편
				cy = mouse_arr[Mmove_mode][1] - (d*mouse_arr[Mmove_mode][0]);
				//x절편
				cx = -(cy / d);
			}
		}
		
			
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치지정
	glutInitWindowSize(800, 600) ; // 윈도우의 크기 지정
	glutCreateWindow("저 별은 내 별이다"); // 윈도우 생성 (윈도우 이름)

	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	///////////////////////////////  좌표축
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-400.0, 0.0);
	glVertex2f(400.0, 0.0);
	glVertex2f(0.0, -300.0);
	glVertex2f(0.0, 300.0);
	glEnd();
	///////////////////////////////
	glPushMatrix();
	glRotatef(Rotate, 0.0, 1.0, 0.0);
		if (Move_stat == 0) {
			///////////////////////////////////////////////
			glColor3f(0.0, 0.0, 0.0);
			for (int i = 0; i < 1440; ++i)
			{
				glBegin(GL_LINES);
				glVertex2d(150 * sin(RADIAN*(i)*0.25), 150 * cos(RADIAN*(i)*0.25));
				glVertex2d(150 * sin(RADIAN*(i + 1)*0.25), 150 * cos(RADIAN*(i + 1)*0.25));
				glEnd();
			}
			///////////////////////////////////////////////////////////
			glColor3f(0.0, 0.0, 1.0);
			if (Move_mode == 1) {
				
				glRotatef((move_x), 0.0, 0.0, 1.0);
				if (Shape_mode == 1)
				{
					glTranslatef(0, 150, 0);
					glScalef(0.2, 1, 0.2);
					glutSolidCube(300);
				}
				else
				{
					glScalef(0.2, 1, 0.2);
					glutSolidCube(150);
				}
			}
			else
			{
				if (Shape_mode == 1)
				{
					glRectd(150 * sin(RADIAN*(move_x)) - Size, 150 * cos(RADIAN*(move_x)) - Size, 150 * sin(RADIAN*(move_x)) + Size, 150 * cos(RADIAN*(move_x)) + Size);
				}
				else
				{
					glBegin(GL_TRIANGLES);
					glVertex2d(150 * sin(RADIAN*(move_x)), 150 * cos(RADIAN*(move_x)) + Size);
					glVertex2d(150 * sin(RADIAN*(move_x)) - Size, 150 * cos(RADIAN*(move_x)) - Size);
					glVertex2d(150 * sin(RADIAN*(move_x)) + Size, 150 * cos(RADIAN*(move_x)) - Size);
					glEnd();

					glColor3f(0.0, 0.0, 0.0);
					glBegin(GL_LINES);
					glVertex2d(150 * sin(RADIAN*(move_x)), 150 * cos(RADIAN*(move_x)) + Size);
					glVertex2d(150 * sin(RADIAN*(move_x)) - Size, 150 * cos(RADIAN*(move_x)) - Size);

					glVertex2d(150 * sin(RADIAN*(move_x)) - Size, 150 * cos(RADIAN*(move_x)) - Size);
					glVertex2d(150 * sin(RADIAN*(move_x)) + Size, 150 * cos(RADIAN*(move_x)) - Size);

					glVertex2d(150 * sin(RADIAN*(move_x)) + Size, 150 * cos(RADIAN*(move_x)) - Size);
					glVertex2d(150 * sin(RADIAN*(move_x)), 150 * cos(RADIAN*(move_x)) + Size);
					glEnd();
				}
			}
		}
		else if (Move_stat == 1)
		{
			glColor3f(0.0, 0.0, 0.0);
			for (int i = 0; i < 1200; ++i)
			{
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex2d((i - 600)*0.5, 150 * sin(RADIAN*(i - 600)));
				glVertex2d((i + 1 - 600)*0.5, 150 * sin(RADIAN*(i + 1 - 600)));
				glEnd();

				glColor3f(0.0, 0.0, 1.0);

					//glRotatef((-move_x), 0.0, 0.0, 1.0);
					if (Shape_mode == 1)
					{
						glRectd((move_x - 600)*0.5 - Size, 150 * sin(RADIAN*(move_x - 600)) - Size,
							(move_x - 600)*0.5 + Size, 150 * sin(RADIAN*(move_x - 600)) + Size);
					}
					else
					{
						glBegin(GL_TRIANGLES);
						glVertex2d((move_x - 600)*0.5, 150 * sin(RADIAN*(move_x - 600)) + Size);
						glVertex2d((move_x - 600)*0.5 - Size, 150 * sin(RADIAN*(move_x - 600)) - Size);
						glVertex2d((move_x - 600)*0.5 + Size, 150 * sin(RADIAN*(move_x - 600)) - Size);
						glEnd();

					}
			}
		}
		else if (Move_stat == 2)
		{
			glColor3f(0.0, 0.0, 0.0);
			for (int i = 0; i < 1160; ++i)
			{
				glBegin(GL_LINES);
				glVertex2d(50 * sin(RADIAN*(70 - i + 600) * 2) + (i - 600)*0.5,100 * cos(RADIAN*(70 - i + 600) * 2) );
				glVertex2d(50 * sin(RADIAN*(70 - (i + 1) + 600) * 2) + ((i + 1) - 600)*0.5, 100 * cos(RADIAN*(70 - (i + 1) + 600) * 2) );
				glEnd();
			}
			glColor3f(0.0, 0.0, 1.0);

			//glRotatef((-move_x), 0.0, 0.0, 1.0);
			if (Shape_mode == 1)
			{
				glRectd(50 * sin(RADIAN*(70 - move_x + 600) * 2) + (move_x - 600)*0.5 - Size, 100 * cos(RADIAN*(70 - move_x + 600) * 2) - Size,
					50 * sin(RADIAN*(70 - move_x + 600) * 2) + (move_x - 600)*0.5 + Size, 100 * cos(RADIAN*(70 - move_x + 600) * 2) + Size);
			}
			else
			{
				glBegin(GL_TRIANGLES);
				glVertex2d(50 * sin(RADIAN*(70 - move_x + 600) * 2) + (move_x - 600)*0.5, 100 * cos(RADIAN*(70 - move_x + 600) * 2) + Size);
				glVertex2d(50 * sin(RADIAN*(70 - move_x + 600) * 2) + (move_x - 600)*0.5 - Size, 100 * cos(RADIAN*(70 - move_x + 600) * 2) - Size);
				glVertex2d(50 * sin(RADIAN*(70 - move_x + 600) * 2) + (move_x - 600)*0.5 + Size, 100 * cos(RADIAN*(70 - move_x + 600) * 2) - Size);
				glEnd();

			}
		}
		else if (Move_stat == 3)
		{
			glColor3f(0.0, 0.0, 0.0);
			for (int i = 0; i < 12; i+=2)
			{
				glBegin(GL_LINES);
				glVertex2i(-300+50*i, 100);
				glVertex2i(-300+50*(i+1), -100);

				glVertex2i(-300 + 50 * (i + 1), -100);
				glVertex2i(-300 + 50 * (i + 2), 100);
				glEnd();
			}
			glColor3f(0.0, 0.0, 1.0);

			//glRotatef((-move_x), 0.0, 0.0, 1.0);
			if (Shape_mode == 1)
			{
				if((move_x/50)%2==0)
					glRectd(move_x-300-Size,100-(move_x%50)*4-Size, move_x - 300 + Size, 100 - (move_x % 50) * 4 + Size);
				else
					glRectd(move_x - 300 - Size, -100 + (move_x % 50) * 4 - Size, move_x - 300 + Size, -100 + (move_x % 50) * 4 + Size);
			}
			else
			{
				if ((move_x / 50) % 2 == 0) {
					glBegin(GL_TRIANGLES);
					glVertex2d(move_x - 300, 100 - (move_x % 50) * 4 + Size);
					glVertex2d(move_x - 300 - Size, 100 - (move_x % 50) * 4 - Size);
					glVertex2d(move_x - 300 + Size, 100 - (move_x % 50) * 4 - Size);
					glEnd();
				}
				else {
					glBegin(GL_TRIANGLES);
					glVertex2d(move_x - 300, -100 + (move_x % 50) * 4 + Size);
					glVertex2d(move_x - 300 - Size, -100 + (move_x % 50) * 4 - Size);
					glVertex2d(move_x - 300 + Size, -100 + (move_x % 50) * 4 - Size);
					glEnd();
				}
			}
		}
		else if (Move_stat == 4)
		{
				glColor3f(0.0, 0.0, 0.0);
				for (int i = 0; i < mouse_count; ++i)
				{
					if (i >= 1) {
						glBegin(GL_LINES);
						glVertex2i(mouse_arr[i-1][0], mouse_arr[i-1][1]);
						glVertex2i(mouse_arr[i][0], mouse_arr[i][1]);

						glEnd();
					}
				}
				if (  mouse_count >= 1&&mouse_x!=0&&mouse_y!=0&&mouse_move!=true )
				{
					glBegin(GL_LINES);
					glVertex2i(mouse_arr[mouse_count-1][0], mouse_arr[mouse_count - 1][1]);
					glVertex2i(mouse_x, mouse_y);
					glEnd();
				}
			glColor3f(0.0, 0.0, 1.0);

			if (Shape_mode == 1)
			{
				if(mouse_move==true)
					glRectd(mouse_x - Size, mouse_y - Size, mouse_x+Size, mouse_y + Size);
				
			}
			else
			{
				if (mouse_move == true) {
					glBegin(GL_TRIANGLES);
					glVertex2d(mouse_x, mouse_y + Size);
					glVertex2d(mouse_x - Size, mouse_y - Size);
					glVertex2d(mouse_x + Size, mouse_y - Size);
					glEnd();
				}
			}
		}
	glPopMatrix();
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
}
