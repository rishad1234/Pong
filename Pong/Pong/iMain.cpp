#include "iGraphics.h"
#include "bitmap_loader.h"
#include<stdio.h>
#include<stdlib.h>
#define SCREENWIDTH 700
#define SCREENHEIGHT 500
/////// rectangle co-ordinates//////
int recx1 = 0;
int recy1 = 0;
int recx2 = SCREENWIDTH - 20;
int recy2 = 0;
int width = 20;
int height = 90;
///////////////////////////////////

///// middle line///////////
int lx1 = SCREENWIDTH / 2;
int ly1 = 0;
int lx2 = SCREENWIDTH / 2;
int ly2 = SCREENHEIGHT;
///////////////////////////

/////// Pong ball /////////
int bx = SCREENWIDTH / 2;
int by = SCREENHEIGHT / 4;
int radius = 10;
int cx = 5;
int cy = 5;
/////////////////////////

/////////// game over ////////
bool game = true;
////////////////

/// pause and resume////
bool pr = true;
////////////////////////

////// Score ////////////
int score1 = 0;
int score2 = 0;
char buf1[1000];
char buf2[1000];
////////////////////////

///// game restart/////
int againStart = 1;
/////////////////////

void drawRectangleLeft(){
	iSetColor(255, 255, 255);
	iFilledRectangle(recx1, recy1, width, height);
}
void drawRectangleRight(){
	iSetColor(255, 255, 255);
	iFilledRectangle(recx2, recy2, width, height);
}
void drawMiddleLine(){
	iSetColor(255, 255, 255);
	iLine(lx1, ly1, lx2, ly2);
}
void drawBall(){
	iSetColor(65, 105, 225);
	iFilledCircle(bx, by, radius, 40);
}
void coOrdinateChange(){
	bx += cx;
	by += cy;
	if((by <= recy1 + height && by >= recy1 && bx == recx1 + 15) || (by <= recy2 + height && by >= recy2 && bx == recx2)){
		cx = - cx;
		if(bx == recx1 + 15) score1++;
		if(bx == recx2) score2++;
	}		
	else if(by > SCREENHEIGHT || by < 0)
		cy = -cy;

	if(bx > SCREENWIDTH || bx < 0){
		game = false;
		score1 = 0;
		score2 = 0;
		againStart = 1;
	}

}

void showScore(){
	iSetColor(255, 255, 255);
	iText(SCREENWIDTH/ 4, SCREENHEIGHT - 200 , itoa(score1,buf1, 10), GLUT_BITMAP_TIMES_ROMAN_24);
	iText((SCREENWIDTH/4) * 3, SCREENHEIGHT - 200, itoa(score2, buf2, 10), GLUT_BITMAP_TIMES_ROMAN_24);
}

void showBG(){
	drawMiddleLine();
	drawRectangleLeft();
	drawRectangleRight();
	drawBall();
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	showBG();
	showScore();
	if(!game && againStart != 2){
		iShowBMP(SCREENWIDTH / 8, SCREENHEIGHT / 8,"1.bmp");
		againStart = 1;
	}
	if(!pr){
		iShowBMP2(SCREENWIDTH / 8, SCREENHEIGHT / 8,"2.bmp", 0);
	}
}

/*
 function iMouseMove() is called when the user presses and drags the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouseMove(int mx, int my)
{
	//printf("x = %d, y= %d\n", mx, my);
	//place your codes here

	/////// right rectangle position////////
	if(my >= 0 && my <= SCREENHEIGHT && mx >= 0 && mx <= SCREENWIDTH / 2){
		if(my >= SCREENHEIGHT - height)
			recy1 = SCREENHEIGHT - height;
		else if(my <= 0)
			recy1 = 0;
		else
			recy1 = my;
	}
	///////////////////////////////////////

	/////// left rectangle position////
	if(my >= 0 && my <= SCREENHEIGHT && mx >= SCREENWIDTH / 2 && mx <= SCREENWIDTH){
		if(my >= SCREENHEIGHT - height)
			recy2 = SCREENHEIGHT - height;
		else if(my <= 0)
			recy2 = 0;
		else
			recy2 = my;
	}
	/////////////////////////////////
}

/*
 function iMouse() is called when the user presses/releases the mouse.
 (mx, my) is the position where the mouse pointer is.
 */
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
 function iKeyboard() is called whenever the user hits a key in keyboard.
 key- holds the ASCII value of the key pressed.
 */
void iKeyboard(unsigned char key)
{

	if (key == 'w'){
		if(recy1 <= SCREENHEIGHT - height - 10)
			recy1 += 20;	
	}
		
	else if (key == 's'){
		if(recy1 > 0)
			recy1 -= 20;	
	}
	else if(key == ' '){
		againStart = 2;
		score1 = 0;
		score2 = 0;
		bx = SCREENWIDTH / 2;
		by = SCREENHEIGHT / 4;
		game = true;
	}
	//place your codes for other keys here
}

/*
 function iSpecialKeyboard() is called whenver user hits special keys like-
 function keys, home, end, pg up, pg down, arraows etc. you have to use
 appropriate constants to detect them. A list is:
 GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
 GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
 GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
 GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
 */
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key == GLUT_KEY_UP){
		if(recy2 <= SCREENHEIGHT - height - 10)
			recy2 += 30;
	}
	if(key == GLUT_KEY_DOWN){
		if(recy2 > 0)
			recy2 -= 30;
	}
	if(key == GLUT_KEY_HOME){
		iPauseTimer(0);
		pr = false;
	}
	if(key == GLUT_KEY_INSERT){
		iResumeTimer(0);
		pr = true;
	}
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.
	iSetTimer(20, coOrdinateChange);
	iInitialize(SCREENWIDTH, SCREENHEIGHT, "Pong");
	return 0;
}
