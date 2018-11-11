#include <GL/freeglut.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
#define PI 3.14
#define RADIAN PI/180
#define MAX 8

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
struct Pos {
	double x, y;
};
struct Rect {
	double x, y;
	int mod;
};
struct Tri {
	double x, y;
	float r;
	int dir;
	int mod;
	float r_s;
};
struct MOUSE {
	double p1X, p1Y, p2X, p2Y;
};
struct STAR {
	double x, y, s_x, s_y, r_x, r_y;
	int r;
	float cnt;
	float scale;
	float s_num;
	int mod;
	float add;
};
struct Node {
	STAR star;
	Node*next;
};
Node* Head = new Node;
Rect rec;
Tri T[MAX];
Tri surplus[40];
Pos p[40][3];
float T_c[40] = { 0 };
bool left_button;
bool drag_tri;
int drag = 0;
int meet = 0;
MOUSE m;
int cnt_Lsur = 0;
int cnt_Rsur = 20;
void Insert(double x, double y)
{
	Node*curr = Head;
	Node*New = new Node;
	New->star.x = x;
	New->star.s_x = x;
	New->star.r_x = rand() % 1100 + 50;
	New->star.y = y;
	New->star.s_y = y;
	New->star.r_y = rand() % 350 + 250;
	New->star.cnt = 0;
	New->star.r = 0;
	New->star.mod = 1;
	New->star.scale = 1;
	New->star.s_num = 0.1;
	New->star.add = 0;
	while (curr->next != nullptr)
	{
		curr = curr->next;
	}
	curr->next = New;
	New->next = nullptr;
}
void draw_Star()
{
	Node*curr = Head;
	curr = curr->next;
	while (curr != nullptr)
	{

		glPushMatrix(); {
			glTranslatef(curr->star.x, curr->star.y, 0);
			glRotatef(curr->star.r, 0.0, 0.0, 1.0);
			glColor3f(0.1*(rand() % 10), 0.1*(rand() % 10), 0.1*(rand() % 10));
			glScalef(curr->star.scale, curr->star.scale, 1);
			glBegin(GL_TRIANGLES); {
				glVertex2f(-35 - curr->star.add, 20 + curr->star.add / 2);
				glVertex2f(0, -40 - curr->star.add);
				glVertex2f(35 + curr->star.add, 20 + curr->star.add / 2); }
			glEnd();
			glBegin(GL_TRIANGLES); {
				glVertex2f(-35 - curr->star.add, -20 - curr->star.add / 2);
				glVertex2f(35 + curr->star.add, -20 - curr->star.add / 2);
				glVertex2f(0, 40 + curr->star.add); }
			glEnd();
			glColor3f(0, 0, 0); }
		glPopMatrix();
		curr = curr->next;
	}
}
void checkS_S(Node*check)
{
	Node*curr = Head;
	Node*prev = curr;
	curr = curr->next;
	while (curr != nullptr)
	{
		if (curr != check) {
			if (pow(check->star.x - curr->star.x, 2) + pow(check->star.y - curr->star.y, 2) <= 3200 + pow(check->star.add, 2) + pow(curr->star.add, 2))
			{
				prev->next = curr->next;
				check->star.add = sqrt(pow(check->star.x - curr->star.x, 2) + pow(check->star.y - curr->star.y, 2)) + curr->star.add;
				delete curr;
				checkS_S(check);
				return;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
void move_Star()
{
	Node*curr = Head;
	curr = curr->next;
	while (curr != nullptr)
	{
		if (curr->star.mod == 1)
		{
			if (curr->star.cnt <= 1)
				curr->star.cnt += 0.01;
			else
			{
				curr->star.mod = 0;
				checkS_S(curr);
			}
			curr->star.x = (1 - curr->star.cnt)*curr->star.s_x + curr->star.cnt * curr->star.r_x;
			curr->star.y = (1 - curr->star.cnt)*curr->star.s_y + curr->star.cnt * curr->star.r_y;
		}
		curr->star.r += 2;
		curr->star.scale += curr->star.s_num;
		if (curr->star.scale >= 2 || curr->star.scale < 1)
			curr->star.s_num *= -1;

		curr = curr->next;
	}
}
void init()
{
	rec.x = 600;
	rec.y = -50;
	rec.mod = rand() % 2;
	for (int i = 0; i < MAX; ++i)
	{
		T[i].x = 175 * i + 50;
		T[i].y = 725;
		T[i].r = rand() % 360;
		T[i].mod = 1;
	}
	Head->next = nullptr;
	Head->star.x = NULL;
	Head->star.r_x = NULL;
	Head->star.y = NULL;
	Head->star.r_y = NULL;
	Head->star.r = NULL;
	Head->star.cnt = NULL;
	Head->star.mod = NULL;
}
void Collision()
{
	int sensitivity = 20;
	cnt_Lsur = 0;
	cnt_Rsur = 20;
	while (surplus[cnt_Lsur].mod != 0 )
	{
		cnt_Lsur++;
		if (cnt_Rsur == cnt_Lsur)
			cnt_Lsur++;
		if (cnt_Lsur >= 40) {
			return;
		}
	}
	while (surplus[cnt_Rsur].mod != 0)
	{
		cnt_Rsur++;
		if(cnt_Rsur == cnt_Lsur)
			cnt_Rsur++;
		if (cnt_Rsur == 40)
			cnt_Rsur = 0;
		if (cnt_Rsur == 20)
			return;
	}
	cout << cnt_Lsur << "," << cnt_Rsur << endl;
	int resault = 0;
	if (rec.mod == 0) { //정사각형일 때
		
		if ((m.p1X<rec.x - 50 && m.p2X>rec.x + 50 && //왼쪽위 오른쪽아래
			m.p1Y > (-m.p1X + rec.x + rec.y - sensitivity * 2) && m.p1Y < (-m.p1X + rec.x + rec.y + sensitivity * 2) &&
			m.p2Y>(-m.p2X + rec.x + rec.y - sensitivity * 2) && m.p2Y < (-m.p2X + rec.x + rec.y + sensitivity * 2)) ||
			(m.p2X<rec.x - 50 && m.p1X>rec.x + 50 && //왼쪽아래 오른쪽위
				m.p1Y > (-m.p1X + rec.x + rec.y - sensitivity * 2) && m.p1Y < (-m.p1X + rec.x + rec.y + sensitivity * 2) &&
				m.p2Y>(-m.p2X + rec.x + rec.y - sensitivity * 2) && m.p2Y < (-m.p2X + rec.x + rec.y + sensitivity * 2)))
		{
			 resault = cnt_Lsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 0;
				surplus[resault].x = rec.x - 25;
				surplus[resault].y = rec.y - 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else
			{
				surplus[resault].mod = 1;
				surplus[resault].r = 180;
				surplus[resault].x = rec.x + 25;
				surplus[resault].y = rec.y + 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			resault = cnt_Rsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 0;
				surplus[resault].x = rec.x - 25;
				surplus[resault].y = rec.y - 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else
			{
				surplus[resault].mod = 1;
				surplus[resault].r = 180;
				surplus[resault].x = rec.x + 25;
				surplus[resault].y = rec.y + 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			rec.y = -50;
			rec.mod = rand() % 2;

		}
		else if ((m.p1X > rec.x + 50 && m.p2X<rec.x - 50 && //오른쪽아래 왼쪽위 
			m.p1Y >(m.p1X - rec.x + rec.y - sensitivity * 2) && m.p1Y < (m.p1X - rec.x + rec.y + sensitivity * 2) &&
			m.p2Y>(m.p2X - rec.x + rec.y - sensitivity * 2) && m.p2Y < (m.p2X - rec.x + rec.y + sensitivity * 2)) ||
			(m.p2X > rec.x + 50 && m.p1X<rec.x - 50 && //오른쪽위 왼쪽아래 
				m.p1Y >(m.p1X - rec.x + rec.y - sensitivity * 2) && m.p1Y < (m.p1X - rec.x + rec.y + sensitivity * 2) &&
				m.p2Y>(m.p2X - rec.x + rec.y - sensitivity * 2) && m.p2Y < (m.p2X - rec.x + rec.y + sensitivity * 2)))
		{
			resault = cnt_Lsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 270;
				surplus[resault].x = rec.x - 25;
				surplus[resault].y = rec.y + 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else {
				surplus[resault].mod = 1;
				surplus[resault].r = 90;
				surplus[resault].x = rec.x + 25;
				surplus[resault].y = rec.y - 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}

			resault = cnt_Rsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 270;
				surplus[resault].x = rec.x - 25;
				surplus[resault].y = rec.y + 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else {
				surplus[resault].mod = 1;
				surplus[resault].r = 90;
				surplus[resault].x = rec.x + 25;
				surplus[resault].y = rec.y - 25;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			rec.y = -50;
			rec.mod = rand() % 2;
		}
	}
	else if (rec.mod == 1) { //마름모일때 슬라이스
		if ((m.p1X < (rec.x - 50) && m.p2X>(rec.x + 50) && //가로 왼쪽 오른쪽
			m.p1Y > (rec.y - sensitivity) && m.p1Y<(rec.y + sensitivity) &&
			m.p2Y>(rec.y - sensitivity) && m.p2Y < (rec.y + sensitivity)) ||
			(m.p2X < (rec.x - 50) && m.p1X>(rec.x + 50) && //가로 오른쪽 왼쪽
				m.p1Y > (rec.y - sensitivity) && m.p1Y<(rec.y + sensitivity) &&
				m.p2Y>(rec.y - sensitivity) && m.p2Y < (rec.y + sensitivity)))
		{
			resault = cnt_Lsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 45;
				surplus[resault].x = rec.x;
				surplus[resault].y = rec.y - sqrt(20000) / 4;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else {
				surplus[resault].mod = 1;
				surplus[resault].r = 225;
				surplus[resault].x = rec.x;
				surplus[resault].y = rec.y + sqrt(20000) / 4;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			resault = cnt_Rsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 45;
				surplus[resault].x = rec.x;
				surplus[resault].y = rec.y - sqrt(20000) / 4;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else {
				surplus[resault].mod = 1;
				surplus[resault].r = 225;
				surplus[resault].x = rec.x;
				surplus[resault].y = rec.y + sqrt(20000) / 4;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			rec.y = -50;
			rec.mod = rand() % 2;
		}
		else if ((m.p1Y < (rec.y - 50) && m.p2Y>(rec.y + 50) && //아래 위
			m.p1X > (rec.x - sensitivity) && m.p1X<(rec.x + sensitivity) &&
			m.p2X>(rec.x - sensitivity) && m.p2X < (rec.x + sensitivity)) ||
			(m.p1Y > (rec.y + 50) && m.p2Y<(rec.y - 50) && //위 아래
				m.p1X >(rec.x - sensitivity) && m.p1X<(rec.x + sensitivity) &&
				m.p2X>(rec.x - sensitivity) && m.p2X < (rec.x + sensitivity)))
		{
			resault = cnt_Lsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 315;
				surplus[resault].x = rec.x - sqrt(20000) / 4;
				surplus[resault].y = rec.y;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else
			{
				surplus[resault].mod = 1;
				surplus[resault].r = 135;
				surplus[resault].x = rec.x + sqrt(20000) / 4;
				surplus[resault].y = rec.y;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			resault = cnt_Rsur;
			if (resault < 20) {
				surplus[resault].mod = 1;
				surplus[resault].r = 315;
				surplus[resault].x = rec.x - sqrt(20000) / 4;
				surplus[resault].y = rec.y;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 100 + 100 * (resault % 5) + 50;
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 25 + 100 * (resault % 5) + 50 * (int(resault / 5) % 2);
				p[resault][2].y = 25 + 50 * int(resault / 5);
			}
			else
			{
				surplus[resault].mod = 1;
				surplus[resault].r = 135;
				surplus[resault].x = rec.x + sqrt(20000) / 4;
				surplus[resault].y = rec.y;
				surplus[resault].r_s = surplus[resault].r;
				p[resault][0].x = surplus[resault].x;
				p[resault][0].y = surplus[resault].y;
				p[resault][1].x = 1200 - (100 + 100 * ((resault - 20) % 5) + 50);
				p[resault][1].y = surplus[resault].y - 50;
				p[resault][2].x = 1200 - (25 + 100 * ((resault - 20) % 5) + 50 * (int(resault / 5) % 2));
				p[resault][2].y = 25 + 50 * int((resault - 20) / 5);
			}
			rec.y = -50;
			rec.mod = rand() % 2;
		}
	}
}
bool CheckClick(double mx, double my, int i)
{
	if (pow(mx - surplus[i].x, 2) + pow(my - surplus[i].y, 2) <= 5000)
	{
		return 1;
	}
	else return 0;
}
bool CheckT_T()
{
	for (int i = 0; i < MAX; ++i)
	{
		if (T[i].mod) {
			if (pow(T[i].x - surplus[drag].x, 2) + pow(T[i].y - surplus[drag].y, 2) <= 5000)
			{
				meet = i;
				return 1;
			}
		}
	}
	return 0;
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'x':
		break;
	default:
		break;
	}

}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		//슬라이스 시작
		m.p1X = x;
		m.p1Y = 800 - y;
		m.p2X = x;
		m.p2Y = 800 - y;
		left_button = true;
		for (int i = 0; i < 40; ++i)
		{
			if (surplus[i].mod == 1)
			{
				if (CheckClick(x, 800 - y, i))
				{
					surplus[i].mod = 2;
					surplus[i].x = x;
					surplus[i].y = 800 - y;
					T_c[i] = 0;
					left_button = false;
					drag_tri = true;
					drag = i;
					break;
				}
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (drag_tri) {

			if (CheckT_T())
			{
				surplus[drag].mod = 0;
				T[meet].mod = 0;
				Insert(T[meet].x, T[meet].y);
				drag = 50;
				meet = 10;
			}
			else {
				drag_tri = false;
				if (surplus[drag].mod == 2)
				{
					surplus[drag].mod = 1;
					p[drag][0].x = surplus[drag].x;
					p[drag][0].y = surplus[drag].y;
				}
			}
		}
		m.p2X = x;
		m.p2Y = 800 - y;
		Collision();
		left_button = false;
	}
	glutPostRedisplay();
}
void Motion(int x, int y) {
	if (left_button == true)
	{
		m.p2X = x;
		m.p2Y = 800 - y;

		glutPostRedisplay();
	}
	else if (drag_tri)
	{
		surplus[drag].x = x;
		surplus[drag].y = 800 - y;
	}
}
void TimerFunction(int value)
{
	/*******************사각형*************************/
	rec.y += 3;
	if (rec.y >= 875)
	{
		rec.y = -50;
		rec.mod = rand() % 2;
	}
	/****************삼각형***********************/
	for (int i = 0; i < MAX; ++i)
	{
		T[i].x += 2;
		if (T[i].x > 1300) {
			T[i].x = -100;
			T[i].mod = 1;
		}
		T[i].r += 3;
	}
	/*******************잉여 삼각형*************************/

	for (int j = 0; j < 40; ++j)
	{
		if (surplus[j].mod == 1) {
			if (T_c[j] < 1) {
				T_c[j] += 0.01;
				surplus[j].x = (2 * T_c[j] * T_c[j] - 3 * T_c[j] + 1)*p[j][0].x + (-4 * T_c[j] * T_c[j] + 4 * T_c[j])*p[j][1].x + (2 * T_c[j] * T_c[j] - T_c[j])*p[j][2].x;
				surplus[j].y = (2 * T_c[j] * T_c[j] - 3 * T_c[j] + 1)*p[j][0].y + (-4 * T_c[j] * T_c[j] + 4 * T_c[j])*p[j][1].y + (2 * T_c[j] * T_c[j] - T_c[j])*p[j][2].y;

				if ((int(j / 5)) % 2 == 0) {
					if (j < 20)
					{
						surplus[j].r = (1 - T_c[j])*surplus[j].r_s;
					}
					else
					{
						surplus[j].r = (1 - T_c[j])*surplus[j].r_s + T_c[j] * 90;
					}
				}
				else
				{
					if (j < 20)
					{
						surplus[j].r = (1 - T_c[j])*surplus[j].r_s + T_c[j] * 180;
					}
					else
					{
						surplus[j].r = (1 - T_c[j])*surplus[j].r_s + T_c[j] * 270;
					}
				}
				if (T_c[j] >= 1)
				{
					surplus[j].x = p[j][2].x;
					surplus[j].y = p[j][2].y;
					if ((int(j / 5)) % 2 == 0) {
						if (j < 20)
						{
							surplus[j].r = 0;
						}
						else
						{
							surplus[j].r = 90;
						}
					}
					else
					{
						if (j < 20)
						{
							surplus[j].r = 180;
						}
						else
						{
							surplus[j].r = 270;
						}
					}
				}
			}
			else
			{
				surplus[j].mod = 2;
			}
		}
	}

	/*************************별**************************/
	move_Star();
	/*****************************************************/
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, 1);
}
void main(int argc, char *argv[])
{
	srand(time(NULL));
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(1200, 800); // 윈도우의 크기 지정
	glutCreateWindow("실습1"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	/********************바닥 네모칸********************************/
	glColor3f(0.2, 0.2, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; ++i) {
		glVertex2f(0.0f, 50 * i + 50.0f);
		glVertex2f(1200.0f, 50 * i + 50.0f);
	}
	for (int i = 0; i < 23; ++i) {
		glVertex2f(50 * i + 50, 0);
		glVertex2f(50 * i + 50, 200);
	}
	glEnd();
	glColor3f(1, 1, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; ++i) {
		glVertex2f(501.0f, 50 * i + 50.0f);
		glVertex2f(699.0f, 50 * i + 50.0f);
	}
	for (int i = 0; i < 3; ++i) {
		glVertex2f(550 + 50 * i, 0);
		glVertex2f(550 + 50 * i, 200);
	}
	glEnd();
	/****************************별***************************************/
	draw_Star();

	/**************************사각형*************************************/
	glPushMatrix(); {
		glTranslatef(rec.x, rec.y, 0);
		if (rec.mod == 1)
			glRotatef(45, 0.0, 0.0, 1.0);
		glColor3f(0, 0.0, 1.0);
		glRectf(-50, -50, +50, +50);
		glColor3f(0, 0, 0); }
	glPopMatrix();
	/****************************윗라인*********************************/
	glColor3f(0.2, 0.2, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 650);
	glVertex2f(1200.0f, 650);
	glVertex2f(0.0f, 800);
	glVertex2f(1200.0f, 800);
	glEnd();
	/***********************삼각형****************************************/

	for (int i = 0; i < MAX; ++i) {
		if (T[i].mod == 1) {
			glPushMatrix();
			glColor3f(1, 1, 0);
			glTranslatef(T[i].x, T[i].y, 0);
			glRotatef(T[i].r, 0.0, 0.0, 1.0);
			glBegin(GL_TRIANGLES);
			glVertex2f(-50, -50);
			glVertex2f(+50, -50);
			glVertex2f(0, +50);
			glEnd();
			glColor3f(0, 0, 1);
			glBegin(GL_LINES);
			glVertex2f(-50, -50);
			glVertex2f(50, -50);

			glVertex2f(+50, -50);
			glVertex2f(0, +50);

			glVertex2f(0, +50);
			glVertex2f(-50, -50);
			glEnd();
			glPopMatrix();
		}
	}
	/*********************************슬라이스*****************************/
	if (left_button) {
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(m.p1X, m.p1Y);
		glVertex2f(m.p2X, m.p2Y);
		glEnd();
	}
	/********************************잉여 삼각형***************************/
	for (int i = 0; i < 40; ++i) {
		if (surplus[i].mod >= 1)
		{
			glPushMatrix(); {
				glColor3f(0, 0, 1);
				glTranslatef(surplus[i].x, surplus[i].y, 0);
				glRotatef(surplus[i].r, 0.0, 0.0, 1.0);

				glBegin(GL_TRIANGLES); {
					glVertex2f(-25, 75);
					glVertex2f(-25, -25);
					glVertex2f(75, -25); }
				glEnd(); }
			glPopMatrix();
		}
	}
	/*********************************************************************/
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0.0, 1200.0, 0.0, 800.0, -1.0, 1.0);
}
