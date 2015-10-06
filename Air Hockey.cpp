#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

float paddle1x, paddle1y;
float paddle2x, paddle2y;
float ballx, bally, balldirx, balldiry;
char msg[30];
int player1score, player2score;
char buffer[10];
bool keystates[256],gameover;

void initgame()
{
	/* starting location of ball*/
	ballx = 320;
	bally = 240;
	/* distance of paddles from boundaries */
	paddle1x = 50; 
	paddle1y = 240;
	paddle2x = 590;
	paddle2y = 240;
	/* coordinates to control the speed of ball*/
	balldirx = 3;
	balldiry = 3;
}

void KeyUpPress(unsigned char key, int x, int y )
{
    switch(key)
	{
		case 'w': keystates['w'] = false;
				  break;
		case 's': keystates['s'] = false;
				  break;
		case '8': keystates['8'] = false;
				  break;
		case '2': keystates['2'] = false;
				  break;
		case 27: exit(0);
	}
}

void KeyDownPress(unsigned char key, int x, int y )
{
    switch(key)
	{
		case 'w': keystates['w'] = true;
				  break;
		case 's': keystates['s'] = true;
				  break;
		case '8': keystates['8'] = true;
				  break;
		case '2': keystates['2'] = true;
				  break;
		case 27: exit(0);
	}   
}

void drawString (void * font, char *s, float x, float y)
{
     unsigned int i;
     glRasterPos2f(x, y);
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void drawpaddle1()
{
	glBegin(GL_POLYGON);
		glColor3f(0, 0, 1);
		glVertex2f (paddle1x - 5, paddle1y - 15);
        glVertex2f (paddle1x - 5, paddle1y + 15);
        glVertex2f (paddle1x + 5, paddle1y + 15);
        glVertex2f (paddle1x + 5, paddle1y - 15);
	glEnd();
}

void drawpaddle2()
{
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f (paddle2x - 5, paddle2y - 15);
        glVertex2f (paddle2x - 5, paddle2y + 15);
        glVertex2f (paddle2x + 5, paddle2y + 15);
        glVertex2f (paddle2x + 5, paddle2y - 15);
	glEnd();
}

void moveball()
{
	ballx = ballx + balldirx;
	//check if the ball hit the wall
	if(ballx + 5 > 640 || ballx - 5 < 0)
	{
		if((ballx + 5 > 640) && ((bally > 100 && bally < 380)))
			player1score = player1score + 1;
		if((ballx - 5 < 0) && ((bally > 100 && bally < 380)))
			player2score = player2score + 1;
		balldirx = -balldirx;
	}
	
	if(player1score==5 && player1score > player2score)
	{
		glColor3f(1, 1, 0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 1 wins!", 300, 75);
		_itoa_s(*msg,buffer, 10);
		gameover= true;
	}
	if(player2score==5 && player2score > player1score)
	{
		glColor3f(1, 1, 0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 2 wins!", 300, 75);
		_itoa_s(*msg, buffer, 10);
		gameover= true;
	}	
	//check if the ball hit the paddle
	if(balldirx >= 1)
	{
		if(ballx + 5 > paddle2x - 5 && ballx - 5 < paddle2x + 5 && bally - 5 < paddle2y + 15 && bally + 5 > paddle2y - 15)
		{
			balldirx = -balldirx;
		}
	}
	else
	{
		if(ballx + 5 > paddle1x - 5 && ballx - 5 < paddle1x + 5 && bally - 5 < paddle1y + 15 && bally + 5 > paddle1y - 15)
		{
			balldirx = -balldirx;
		}
	}

	bally = bally + balldiry;
	if(bally + 5 > 480 || bally - 5 < 0)
		balldiry = -balldiry;
}

void drawball()
{
	glBegin(GL_QUADS);
		glColor3f(0.95, 0.95, 0.95);
		glVertex2f (ballx - 5, bally - 5);
        glVertex2f (ballx - 5, bally + 5);
        glVertex2f (ballx + 5, bally + 5);
        glVertex2f (ballx + 5, bally - 5);
	glEnd();
}
void circle(int a,int b,int x,int y,int al,int ah)
{
	int i;
	float th;
	for(i=0;i<=ah;i++)
	{
		th=i*3.14/180.0;
		glVertex2f(x+a*cos(th),y+b*sin(th));
	}
}
void display()
{
	if(gameover==false)
	{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 1: ", 10, 20);
	_itoa_s(player1score, buffer, 30);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, 55, 20);
	glColor3f(1, 1, 0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 2: ", 560, 20);
	_itoa_s(player2score, buffer, 30);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, 605, 20);
	//Background Color
	glClearColor(0, 0.5, 0, 0);
	//Left Top Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (0, 0);
		glVertex2f (0, 100);
	glEnd();
	//Left Bottom Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (0, 380);
		glVertex2f (0, 480);
	glEnd();
	//Top Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (0, 0);
		glVertex2f (640,0);
	glEnd();
	//Bottom Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (0, 480);
		glVertex2f (640, 480);
	glEnd();
	//Right Top Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (640, 0);
		glVertex2f (640, 100);
	glEnd();
	//Right Bottom Line
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(0.28,0,0.04);
		glVertex2f (640, 380);
		glVertex2f (640, 480);
	glEnd();
	//Left Side Goal
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f (0, 100);
		glVertex2f (30, 100);
	glEnd();
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f (0, 380);
		glVertex2f (30, 380);
	glEnd();
	//Right Side Goal
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f (610, 100);
		glVertex2f (640, 100);
	glEnd();
	glLineWidth(9.0);
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f (609, 379);
		glVertex2f (639, 379);
	glEnd();
	//Center Circle Call
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glColor3f(1,1,1);
		circle(35,35,320,240,0,360);
	glEnd();
	//Center Line
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex2f (320, 3);
		glVertex2f (320, 477);
	glEnd();
	
	if(keystates['w'] == true)
		if(paddle1y - 30 > 0)
			paddle1y = paddle1y - 5;
	if(keystates['s'] == true)
		if(paddle1y + 30 < 480)
			paddle1y = paddle1y + 5;
	drawpaddle1();

	if(keystates['8'] == true)
		if(paddle2y - 30 > 0)
			paddle2y = paddle2y - 5;
	if(keystates['2'] == true)
		if(paddle2y + 30 < 480)
			paddle2y = paddle2y + 5;
	drawpaddle2();

	moveball();
	drawball();

	glutSwapBuffers();
	}
}

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, 640, 480, 0);
	glOrtho(0,640,480,0,0,1);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	initgame();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Air Hockey");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyDownPress);
	glutKeyboardUpFunc(KeyUpPress);
	glutIdleFunc(display);
	glutFullScreen();
    glutMainLoop();
}
