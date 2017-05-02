#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<gl\glut.h>
#include<gl\GL.h>
#include<gl\GLU.h>


#pragma warning(disable:4996)


static GLint game_state = 2;   // 0 = 게임오버, 1 = 게임시작, 2 = 메인, 3 = 난이도선택
static GLint level = 0;		   // 0 = 이지, 1 = 노멀, 2 = 하드, 3 = 헬
static GLint draw = 1;
static GLint rotate1 = 0, rotate2 = 0, rotate3 = 0;
static GLfloat coming[5] = { 2.5, 3.7, 4.9, 6.1, 7.3 };
static GLint meteo[5] = { 1, 2, 3, 2, 1 };
static GLfloat moving = 0.0;
static GLfloat speed = 0.00001;
static GLfloat shipmoving = 0.0;

static GLfloat ship_left = 0;
static GLfloat ship_right = 0;
static GLfloat ship_top = 0;
static GLfloat ship_topleft = 0;
static GLfloat ship_topright = 0;

static GLfloat meteo_pos1[5] = { 0 };
static GLfloat meteo_pos2[5] = { 0 };
static GLfloat meteo_pos3[5] = { 0 };

static GLint score = 0;
static float starX[300], starY[300], starSize[300];
unsigned int MyTextureObject[1];

void drawMeteoshape()
{
	glPushMatrix();
	glTranslatef(0.1, -0.05, 0.18);
	glutSolidSphere(0.05, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.18, -0.05, 0.03);
	glutSolidSphere(0.1, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15, -0.05, -0.2);
	glutSolidSphere(0.03, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.05, 0.18, -0.1);
	glutSolidSphere(0.06, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.03, -0.2);
	glutSolidSphere(0.08, 20, 10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.05, -0.18, -0.1);
	glutSolidSphere(0.05, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.18, -0.0, 0.0);
	glutSolidSphere(0.1, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.1, 0.15);
	glutSolidSphere(0.08, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.07, -0.1, 0.18);
	glutSolidSphere(0.06, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.12, 0.13, 0.1);
	glutSolidSphere(0.07, 20, 10);
	glPopMatrix();
}

//한 레인에 두 개의 운석이 떨어지도록 하는 함수
void getMeteo1(int row)
{
	glPushMatrix();
	glTranslatef(0.0, coming[row], 0.0);
	glRotatef(-(GLfloat)rotate1, 0.0, 1.0, 0.0);				//떨어지면서 회전하도록 설정
	glColor3f((float)76 / 255, (float)49 / 255, (float)40/255);	//연한갈색
	glutSolidSphere(0.25, 20, 10);								//타원 모양의 운석 틀 그리기
	glColor3f((float)55 / 255, (float)35 / 255, (float)29/255);	//갈색
	drawMeteoshape();											//크레이터 그리기 함수 호출
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, coming[row], 0.0);
	glRotatef((GLfloat)rotate2, 0.0, 1.0, 0.0);					//떨어지면서 회전하도록 설정
	glColor3f((float)80 / 255, (float)46 / 255, (float)0/255);	//진한 갈색
	glutSolidSphere(0.25, 20, 10);								//타원 모양의 운석 틀 그리기
	glColor3f((float)58 / 255, (float)33 / 255, (float)0/255);	//밤색
	drawMeteoshape();											//크레이터 그리기 함수 호출
	glPopMatrix();

	shipmoving = 0.005;											//우주선의 위치 값(x 좌표) 변경
}

void getMeteo2(int row)
{
	glPushMatrix();
	glTranslatef(-0.7, coming[row], 0.0);
	glRotatef(-(GLfloat)rotate3, 0.0, 1.0, 0.0);
	glColor3f((float)78 / 255, (float)53 / 255, (float)2 / 255);		//진한 갈색
	glutSolidSphere(0.25, 20, 10);
	glColor3f((float)68 / 255, (float)46 / 255, (float)2 / 255);		//밤색
	drawMeteoshape();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, coming[row], 0.0);
	glRotatef((GLfloat)rotate1, 0.0, 1.0, 0.0);
	glColor3f((float)91 / 255, (float)68 / 255, (float)35 / 255);		//진한 갈색
	glutSolidSphere(0.25, 20, 10);
	glColor3f((float)74 / 255, (float)55 / 255, (float)28 / 255);		//밤색
	drawMeteoshape();
	glPopMatrix();

	shipmoving = 0.0;

}

void getMeteo3(int row)
{
	glPushMatrix();
	glTranslatef(-0.7, coming[row], 0.0);
	glRotatef(-(GLfloat)rotate2, 0.0, 1.0, 0.0);
	glColor3f((float)120 / 255, (float)76 / 255, (float)35 / 255);		//진한 갈색
	glutSolidSphere(0.25, 20, 10);
	glColor3f((float)107 / 255, (float)67 / 255, (float)31 / 255);		//밤색
	drawMeteoshape();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, coming[row], 0.0);
	glRotatef((GLfloat)rotate3, 0.0, 1.0, 0.0);
	glColor3f((float)134 / 255, (float)89 / 255, (float)0 / 255);		//진한 갈색
	glutSolidSphere(0.25, 20, 10);
	glColor3f((float)118 / 255, (float)79 / 255, (float)0 / 255);		//밤색
	drawMeteoshape();
	glPopMatrix();

	shipmoving = 0.005;
}

void drawship()
{
	if (game_state == 1)
	{
		glColor3f(1.0, 0.0, 0.0);		//빨강
		glBegin(GL_POLYGON); {
			glVertex3f(-0.05 + moving, -2.25, 0.0);
			glVertex3f(-0.05 + moving - shipmoving, -2.32 + shipmoving, 0.0);
			glVertex3f(-0.03 + moving, -2.3 + shipmoving, 0.0);
			glVertex3f(0.0 + moving, -2.36 + shipmoving, 0.0);
			glVertex3f(0.03 + moving, -2.3 + shipmoving, 0.0);
			glVertex3f(0.05 + moving + shipmoving, -2.32 + shipmoving, 0.0);
			glVertex3f(0.05 + moving, -2.25, 0.0);
		}
		glEnd();

		glColor3f(1.0, 1.0, 0.0);		//노랑
		glBegin(GL_POLYGON); {
			glVertex3f(-0.035 + moving, -2.25, 0.0);
			glVertex3f(-0.035 + moving - shipmoving, -2.3 + shipmoving, 0.0);
			glVertex3f(-0.015 + moving, -2.28 + shipmoving, 0.0);
			glVertex3f(0.0 + moving, -2.34 + shipmoving, 0.0);
			glVertex3f(0.015 + moving, -2.28 + shipmoving, 0.0);
			glVertex3f(0.035 + moving + shipmoving, -2.3 + shipmoving, 0.0);
			glVertex3f(0.035 + moving, -2.25, 0.0);
		}
		glEnd();
	}

	if (level == 0)
	{
		glColor3f((float)255 / 255, (float)153 / 255, (float)102/255);
	}
	else if (level == 1)
	{
		glColor3f(1, 0.6, 0.8);			//분홍
	}
	else if (level == 2)
	{
		glColor3f((float)51 / 255, (float)153 / 255, (float)255 / 255);
	}
	else if (level == 3)
	{
		glColor3f((float)51 / 255, (float)204 / 255, (float)255 / 255);
	}


	glBegin(GL_POLYGON); {
		glVertex3f(-0.08 + moving, -2, 0.0);
		glVertex3f(-0.25 + moving, -2.23, 0.0);

		glVertex3f(0.25 + moving, -2.23, 0.0);
		glVertex3f(0.08 + moving, -2, 0.0);
	}
	glEnd();

	if (level == 0)
	{
		glColor3f((float)1 / 255, (float)146 / 255, (float)1.0);
	}
	else if (level == 1)
	{
		glColor3f((float)124 / 255, (float)191 / 255, (float)51 / 255);
	}
	else if (level == 2)
	{
		glColor3f((float)253 / 255, (float)182 / 255, (float)77 / 255);
	}
	else if (level == 3)
	{
		glColor3f((float)255 / 255, (float)71 / 255, (float)71 / 255);
	}

	glBegin(GL_POLYGON); {
		//머리
		glVertex3f(0.0 + moving, -1.75, 0.0);

		glVertex3f(-0.08 + moving, -1.85, 0.0);
		glVertex3f(-0.08 + moving, -2.2, 0.0);
		glVertex3f(-0.08 + moving, -2.23, 0.0);

		//꼬리
		glVertex3f(-0.05 + moving, -2.26, 0.0);
		glVertex3f(0.05 + moving, -2.26, 0.0);

		//꼬리
		glVertex3f(0.08 + moving, -2.23, 0.0);
		glVertex3f(0.08 + moving, -2.2, 0.0);
		glVertex3f(0.08 + moving, -1.85, 0.0);

	}
	glEnd();

	glColor3f(0.741, 0.862, 0.874);		//창문
	glBegin(GL_POLYGON); {
		//머리
		glVertex3f(0.0 + moving, -1.8, 0.0);
		glVertex3f(-0.05 + moving, -1.86, 0.0);
		glVertex3f(-0.05 + moving, -2, 0.0);
		glVertex3f(0.05 + moving, -2, 0.0);
		glVertex3f(0.05 + moving, -1.86, 0.0);
	}
	glEnd();

	ship_left = -0.25 + moving;
	ship_right = 0.25 + moving;
	ship_top = 0.0 + moving;
	ship_topleft = -0.08 + moving;
	ship_topright = 0.08 + moving;

}

void drawScore()
{
	int i = 0;
	char score_title[8] = "Score:";
	char mode[5] = "MODE";
	char easy[5] = "EASY";
	char normal[7] = "NORMAL";
	char hard[5] = "HARD";
	char hell[5] = "HELL";
	char *score_print;
	char tbuffer[100];

	score_print = itoa(score, tbuffer, 10);

	glLineWidth(3);
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-1.3, 2, 0.0);
	glVertex3f(-1.3, 2.5, 0.0);
	glVertex3f(1.3, 2.5, 0.0);
	glVertex3f(1.3, 2, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.1, 2.1, 0.0);
	glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
	for (i = 0; i < 7; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score_title[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 2.1, 0.0);
	glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
	for (i = 0; i < 100; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score_print[i]);
	}
	glPopMatrix();

	if (level == 0)
	{
		glPushMatrix();
		glTranslatef(0.15, 2.1, 0.0);
		glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
		for (i = 0; i < 5; i++)
		{
			glColor3f((float)1 / 255, (float)146 / 255, (float)1.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, easy[i]);
		}
		glPopMatrix();

	}
	else if (level == 1)
	{
		glPushMatrix();
		glTranslatef(-0.15, 2.1, 0.0);
		glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
		for (i = 0; i < 7; i++)
		{
			glColor3f((float)124 / 255, (float)191 / 255, (float)51 / 255);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, normal[i]);
		}
		glPopMatrix();
	}
	else if (level == 2)
	{
		glPushMatrix();
		glTranslatef(0.15, 2.1, 0.0);
		glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
		for (i = 0; i < 5; i++)
		{
			glColor3f((float)253 / 255, (float)182 / 255, (float)77 / 255);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, hard[i]);
		}
		glPopMatrix();
	}
	else if (level == 3)
	{
		glPushMatrix();
		glTranslatef(0.15, 2.1, 0.0);
		glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
		for (i = 0; i < 5; i++)
		{
			glColor3f((float)255 / 255, (float)71 / 255, (float)71 / 255);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, hell[i]);
		}
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0.65, 2.1, 0.0);
	glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
	for (i = 0; i < 5; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, mode[i]);
	}
	glPopMatrix();
}


void stardraw()
{
	srand(unsigned(time(NULL)));
	float size;
	int dice = (rand() % 300);
	for (int i = 0; i < 300; i++){
		glPushMatrix();
		dice = (rand() % 100);
		if (dice<15)
			glColor3f(1.0, 1.0, 0.0);
		else if (dice<16)
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(1.0, 1.0, 1.0);
		glScalef(starSize[i], starSize[i], 0.0);
		glTranslatef(starX[i], starY[i], 0.0);
		glutSolidSphere(0.008, 20, 20);
		glPopMatrix();
	}
	float replace = ((rand() % 3000) / 1000.0) - 1.5;
	for (int i = 0; i < 300; i++) {
		replace = ((rand() % 9000) / 1000.0) - 4.5;
		starY[i] -= (0.01 + speed);
		if (starY[i] < -9) {
			starY[i] = 3;
			starX[i] = replace;
		}
	}
}


void starInit()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 300; i++)
	{
		starX[i] = ((rand() % 9000) / 1000.0) - 4.5;
		starY[i] = ((rand() % 18000) / 1000.0) - 9;
		starSize[i] = (rand() % 1000) / 1000.0;
	}
}


void In_game()
{
	int i;

	if (draw == 1)
	{
		if (draw == 1)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		stardraw();

		glEnable(GL_DEPTH_TEST);
		glClearDepth(1.f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);

		for (i = 0; i < 5; i++)
		{
			if (meteo[i] == 1)
			{
				getMeteo1(i);
				meteo_pos2[i] = coming[i];
				meteo_pos3[i] = coming[i];
			}
			else if (meteo[i] == 2)
			{
				getMeteo2(i);
				meteo_pos1[i] = coming[i];
				meteo_pos3[i] = coming[i];
			}
			else if (meteo[i] == 3)
			{
				getMeteo3(i);
				meteo_pos1[i] = coming[i];
				meteo_pos2[i] = coming[i];
			}
		}

		glDisable(GL_DEPTH_TEST);

		drawScore();

		if (game_state == 0)
			draw = 0;
		drawship();
		glutSwapBuffers();

	}
	else
	{
	}
}

void Main_game()
{
	int i = 0;
	char title1[15] = "Escape";
	char title2[15] = "Meteorites";
	char start[10] = "START";
	char how1[20] = "Mouse Left Button";
	char how2[20] = "Move to the LEFT!";
	char how3[20] = "Mouse Right Button";
	char how4[20] = "Move to the RIGHT!";

	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(4);

	stardraw();

	glPushMatrix();
	glTranslatef(-1.1, 0.8, 0.0);
	glScalef(1 / 400.0, 1 / 400.0, 1 / 400.0);
	for (i = 0; i < 15; i++)
	{
		glColor3f(1.0, 0.32, 0.32);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, title1[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.95, 0.3, 0.0);
	glScalef(1 / 300.0, 1 / 300.0, 1 / 300.0);
	for (i = 0; i < 15; i++)
	{
		glColor3f(0.74, 0.58, 0.14);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, title2[i]);
	}
	glPopMatrix();

	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38, -0.85, 0.0);
	glScalef(1 / 500.0, 1 / 500.0, 1 / 500.0);
	for (i = 0; i < 19; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, start[i]);
	}
	glPopMatrix();

	drawship();

	glLineWidth(1);

	glPushMatrix();
	glTranslatef(-1.07, -1.5, 0.0);
	glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
	for (i = 0; i < 20; i++)
	{
		glColor3f(0.68, 0.92, 0.95);   //연하
		glutStrokeCharacter(GLUT_STROKE_ROMAN, how1[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.17, -1.7, 0.0);
	glScalef(1 / 1200.0, 1 / 1200.0, 1 / 1200.0);
	for (i = 0; i < 20; i++)
	{
		glColor3f(0.36, 0.81, 0.98);   //하늘
		glutStrokeCharacter(GLUT_STROKE_ROMAN, how2[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.23, -1.5, 0.0);
	glScalef(1 / 1500.0, 1 / 1500.0, 1 / 1500.0);
	for (i = 0; i < 20; i++)
	{
		glColor3f(0.81, 0.69, 1.0);      //연보
		glutStrokeCharacter(GLUT_STROKE_ROMAN, how3[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.11, -1.7, 0.0);
	glScalef(1 / 1200.0, 1 / 1200.0, 1 / 1200.0);
	for (i = 0; i < 20; i++)
	{
		glColor3f(0.64, 0.4, 1.0);      //보라
		glutStrokeCharacter(GLUT_STROKE_ROMAN, how4[i]);
	}
	glPopMatrix();


	glutSwapBuffers();

}

void End_game()
{
	int i = 0;
	char gameover[20] = "GAME OVER";
	char restart[19] = "RESTART";
	char end[10] = "END";
	char score_title[8] = "Score:";
	char *score_print;
	char tbuffer[100];

	score_print = itoa(score, tbuffer, 10);

	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(3);

	stardraw();

	glPushMatrix();
	glTranslatef(-0.8, 0.85, 0.0);
	glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
	for (i = 0; i < 7; i++)
	{
		glColor3f(0.94, 0.79, 0.38);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score_title[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 0.85, 0.0);
	glScalef(1 / 700.0, 1 / 700.0, 1 / 700.0);
	for (i = 0; i < 100; i++)
	{
		glColor3f(0.94, 0.79, 0.38);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, score_print[i]);
	}
	glPopMatrix();

	glLineWidth(4);

	glPushMatrix();
	glTranslatef(-0.8, 0.5, 0.0);
	glScalef(1 / 500.0, 1 / 500.0, 1 / 500.0);
	for (i = 0; i < 19; i++)
	{
		glColor3f(1.0, 1.0, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, gameover[i]);
	}
	glPopMatrix();

	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.45, -0.34, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 19; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, restart[i]);
	}
	glPopMatrix();

	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.8, 0.0);
	glVertex3f(-0.5, -1.3, 0.0);
	glVertex3f(0.5, -1.3, 0.0);
	glVertex3f(0.5, -0.8, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -1.15, 0.0);
	glScalef(1 / 500.0, 1 / 500.0, 1 / 500.0);
	for (i = 0; i < 19; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, end[i]);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void Select_level()
{
	int i = 0;
	char select[15] = "SELECT";
	char level[6] = "LEVEL";
	char easy[5] = "EASY";
	char normal[7] = "NORMAL";
	char hard[5] = "HARD";
	char hell[5] = "HELL";

	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(4);

	stardraw();

	glPushMatrix();
	glTranslatef(-0.79, 1.4, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 15; i++)
	{
		glColor3f(1.0, 1.0, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, select[i]);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.11, 1.4, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 7; i++)
	{
		glColor3f(1.0, 1.0, 1.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, level[i]);
	}
	glPopMatrix();

	//이지
	glColor3f((float)1 / 255, (float)146 / 255, (float)1.0);	//파랑
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.29, 0.66, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 5; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, easy[i]);
	}
	glPopMatrix();
	
	//노멀
	glColor3f((float)158 / 255, (float)213 / 255, (float)97 / 255);	//초록
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.3, 0.0);
	glVertex3f(-0.5, -0.2, 0.0);
	glVertex3f(0.5, -0.2, 0.0);
	glVertex3f(0.5, 0.3, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.43, -0.04, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 7; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, normal[i]);
	}
	glPopMatrix();

	//하드
	glColor3f((float)253 / 255, (float)182 / 255, (float)77 / 255);	//주황
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.4, 0.0);
	glVertex3f(-0.5, -0.9, 0.0);
	glVertex3f(0.5, -0.9, 0.0);
	glVertex3f(0.5, -0.4, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.28, -0.74, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 5; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, hard[i]);
	}
	glPopMatrix();
	
	//헬
	glColor3f((float)255 / 255, (float)71 / 255, (float)71 / 255); //빨강
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -1.1, 0.0);
	glVertex3f(-0.5, -1.6, 0.0);
	glVertex3f(0.5, -1.6, 0.0);
	glVertex3f(0.5, -1.1, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -1.44, 0.0);
	glScalef(1 / 600.0, 1 / 600.0, 1 / 600.0);
	for (i = 0; i < 5; i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, hell[i]);
	}
	glPopMatrix();

	glutSwapBuffers();
}


void MyDisplay()
{
	switch (game_state)
	{
	case 0:
		End_game();
		break;
	case 1:
		In_game();
		break;
	case 2:
		Main_game();
		break;
	case 3:
		Select_level();
		break;
	}

}



void MyMouseClick(GLint button, GLint state, GLint x, GLint y)
{
	int i = 0;

	if (game_state == 1)
	{
		//마우스 왼쪽 버튼을 클릭했을 때
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			//우주선이 왼쪽 끝에 있지 않을 때
			if (moving > -0.35)
				moving -= 0.7;	//moving(변경될 값)을 감소

			//우주선의 모든 요소들을 왼쪽으로 이동
			ship_left = -0.25 + moving;
			ship_right = 0.25 + moving;
			ship_top = 0.0 + moving;
			ship_topleft = -0.08 + moving;
			ship_topright = 0.08 + moving;
			shipmoving = 0.0;

			drawship();	//우주선 그리기 함수 호출
		}
		//마우스 오른쪽 버튼을 클릭했을 때
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			//우주선이 오른쪽 끝에 있지 않을 때
			if (moving < 0.35)
				moving += 0.7;	//moving(변경될 값)을 증가

			//우주선의 모든 요소들을 오른쪽으로 이동
			ship_left = -0.25 + moving;
			ship_right = 0.25 + moving;
			ship_top = 0.0 + moving;
			ship_topleft = -0.08 + moving;
			ship_topright = 0.08 + moving;
			shipmoving = 0.005;

			drawship();	//우주선 그리기 함수 호출
		}
	}
	else if (game_state == 2)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((x < 425 && x > 175) && (y < 677 && y > 575))
				game_state = 3;
		}
	}
	else if (game_state == 0)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((x < 424 && x > 175) && (y < 574 && y > 473))
				game_state = 2;
			else if ((x < 424 && x > 175) && (y < 733 && y > 635))
				exit(1);
		}
	}
	else if (game_state == 3)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if ((x < 424 && x > 175) && (y < 375 && y > 275))
				level = 0;
			else if ((x < 424 && x > 175) && (y < 516 && y > 416))
				level = 1;
			else if ((x < 424 && x > 175) && (y < 655 && y > 555))
				level = 2;
			else if ((x < 424 && x > 175) && (y < 794 && y > 696))
				level = 3;
			game_state = 1;
		}
	}
}

void meteo1_collision(int row)
{
	//2meteo
	//우주선 상단과 운석이 부딪히면
	if (((meteo_pos2[row] - 0.25) < -1.75) && ((ship_top > -0.25) && (ship_top < 0.25)))
		game_state = 0;		//게임 오버
	//우주선 양쪽 날개와 운석이 부딪히면
	if (((meteo_pos2[row] - 0.25) < -1.85) && ((ship_topleft > -0.25) && (ship_topright < 0.25)))
		game_state = 0;		//게임 오버

	//3meteo
	//우주선 상단과 운석이 부딪히면
	if (((meteo_pos3[row] - 0.25) < -1.75) && ((ship_top > 0.45) && (ship_top < 0.95)))
		game_state = 0;		//게임 오버
	//우주선 양쪽 날개와 운석이 부딪히면
	if (((meteo_pos3[row] - 0.25) < -1.85) && ((ship_topleft > 0.45) && (ship_topright < 0.95)))
		game_state = 0;		//게임 오버

	glutPostRedisplay();
}

void meteo2_collision(int row)
{
	//1meteo
	if (((meteo_pos1[row] - 0.25) < -1.75) && ((ship_top > -0.95) && (ship_top < -0.45)))
		game_state = 0;
	if (((meteo_pos1[row] - 0.25) < -1.85) && ((ship_topleft > -0.95) && (ship_topright < -0.45)))
		game_state = 0;
	//if (((meteo_pos1[row] - 0.25) < -2.23) && ((ship_left > -0.95) && (ship_right < -0.45)))
	//	game_state = 0;

	//3meteo
	if (((meteo_pos3[row] - 0.25) < -1.75) && ((ship_top > 0.45) && (ship_top < 0.95)))
		game_state = 0;
	if (((meteo_pos3[row] - 0.25) < -1.85) && ((ship_topleft > 0.45) && (ship_topright < 0.95)))
		game_state = 0;
	//if (((meteo_pos3[row] - 0.25) < -2.23) && ((ship_left > 0.45) && (ship_right < 0.95)))
	//	game_state = 0;
	glutPostRedisplay();
}

void meteo3_collision(int row)
{
	//1meteo
	if (((meteo_pos1[row] - 0.25) < -1.75) && ((ship_top > -0.95) && (ship_top < -0.45)))
		game_state = 0;
	if (((meteo_pos1[row] - 0.25) < -1.85) && ((ship_topleft > -0.95) && (ship_topright < -0.45)))
		game_state = 0;
	//if (((meteo_pos1[row] - 0.25) < -2.23) && ((ship_left > -0.95) && (ship_right < -0.45)))
	//	game_state = 0;

	//2meteo
	if (((meteo_pos2[row] - 0.25) < -1.75) && ((ship_top > -0.25) && (ship_top < 0.25)))
		game_state = 0;
	if (((meteo_pos2[row] - 0.25) < -1.85) && ((ship_topleft > -0.25) && (ship_topright < 0.25)))
		game_state = 0;
	//if (((meteo_pos2[row] - 0.25) < -2.23) && ((ship_left > -0.25) && (ship_right < 0.25)))
	//	game_state = 0;
	glutPostRedisplay();
}

void collision(int row, int meteo)
{
	if (meteo == 1)
	{
		meteo1_collision(row);
	}
	else if (meteo == 2)
	{
		meteo2_collision(row);
	}
	else if (meteo == 3)
	{
		meteo3_collision(row);
	}
}


void MeteoIdle()
{
	int i = 0;
	int before = 0;
	int score_plus = 1;

	if (game_state == 1)
	{
		rotate1 = (rotate1 + 2) % 360;
		rotate2 = (rotate2 + 1) % 360;
		rotate3 = (rotate3 + 3) % 360;

		for (i = 0; i < 5; i++)
		{
			collision(i, meteo[i]);

			if (i == 0)
				before = meteo[4];
			else
				before = meteo[i - 1];

			if (coming[i] < -2.3)
			{
				coming[i] = 3.7 - speed;
				meteo[i] = rand() % 3 + 1;
				score += score_plus;

				if (level == 0)
					speed += 0.00005;
				else if (level == 1)
					speed += 0.0005;
				else if (level == 2)
					speed += 0.005;
				else if (level == 3)
					speed += 0.01;

				if (before == 1)
				{
					while (meteo[i] == 3)
						meteo[i] = rand() % 3 + 1;
					shipmoving = 0.005;
				}
				else if (before == 3)
				{
					while (meteo[i] == 1)
						meteo[i] = rand() % 3 + 1;
					shipmoving = 0.0;
				}
			}
			else
			{
				coming[i] = coming[i] - (0.02 + speed);
				score_plus++;
			}

		}
	}
	else if (game_state == 2)
	{
		draw = 1;
		rotate1 = 0;
		rotate2 = 0;
		rotate3 = 0;
		moving = 0.0;
		speed = 0.00001;
		score = 0;

		level = rand() % 4;

		for (i = 0; i < 5; i++)
		{
			coming[i] = 2.5 + (1.2 * (i + 1));
			meteo_pos1[i] = 0;
			meteo_pos2[i] = 0;
			meteo_pos3[i] = 0;
		}

		ship_left = 0;
		ship_right = 0;
		ship_top = 0;
		ship_topleft = 0;
		ship_topright = 0;

	}

	glutPostRedisplay();
}

void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)400;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0*WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor, -1.0, 1.0);
}

void main(int argc, char **argv)
{
	int i = 0;
	srand(unsigned(time(NULL)));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 950);
	glutInitWindowPosition(1000, 0);
	glutCreateWindow("Escape Meteorites");
	glClearDepth(1.f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_EQUAL);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	starInit();
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MeteoIdle);
	glutMouseFunc(MyMouseClick);
	glutReshapeFunc(MyReshape);


	glutMainLoop();

}