/* Osama Mohammed
CS 5472
2D Game in OpenGL
*/

#include <Windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <math.h>
#include "OpenGLShootingGame.h"


void myinit()
{
 
/* attributes */

      glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */

/* set up viewing */
/* 675 x 850 window with origin lower left */

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
	  //glTranslatef(0.5, 0.5, 0.0);
      gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_LENGTH);
      glMatrixMode(GL_MODELVIEW);
	  
	  printScore();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */
	keyPress();
	arrowKeys();
	create_Player(player1_x, player1_y, GREEN, RED, player1_shooting_angle);
	drawShot(PLAYER1);
	create_Player(player2_x, player2_y, GREEN, LIGHT_BLUE, player2_shooting_angle);
	drawShot(PLAYER2);
	glFlush();
}
 
void reshape(int w, int h) {

	 glMatrixMode(GL_PROJECTION);
     glLoadIdentity(); 
     gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity(); 

     glViewport(0,0,w,h);

	 WINDOW_WIDTH = w;
	 WINDOW_LENGTH = h;

}

void drawShot(int player) {

	
	if(player == PLAYER2 && draw_bullet_player2 == 1) {

		drawLine(player2_bullet_x1, player2_bullet_y1, player2_bullet_x2, player2_bullet_y2, YELLOW);
		Sleep(DELAY_VALUE);
		updateShotPosition(PLAYER2);
	}

	else if (player == PLAYER1 && draw_bullet_player1 == 1) {

		drawLine(player1_bullet_x1, player1_bullet_y1, player1_bullet_x2, player1_bullet_y2, RED);
		Sleep(DELAY_VALUE);
		updateShotPosition(PLAYER1);
	}
}

void create_Player(int x, int y, int shield_colour, int shootingSide_colour, int shootingAngle) {
	
	drawPlayer(x, y, shield_colour, shootingSide_colour, shootingAngle);
}

void drawCircle (int k, int r, int h) {
    glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
    circle.x = r * cos(i + 0.0) - h;
    circle.y = r * sin(i + 0.0) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    
    circle.x = r * cos(i + 0.1) - h;
    circle.y = r * sin(i + 0.1) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    }
    glEnd();
}

void drawPlayer(int x, int y, int shield_colour, int shootingSide_colour, int shootingAngle) {
	
	setColour(shootingSide_colour);

	glBegin(GL_POLYGON);
		
		for (int angle = shootingAngle; angle <= shootingAngle + 360; angle = angle + 5) {

			if (angle == shootingAngle + 95)
				angle = shootingAngle + 270;

			glVertex2f((CIRCLE_RADIUS * cos(angle * PI/180)) + x, (CIRCLE_RADIUS * sin(angle * PI/180)) + y);
		}

	glEnd();

	setColour(shield_colour);

	glBegin(GL_POLYGON);

		for (int angle = shootingAngle + 90; angle <= shootingAngle + 270; angle = angle + 5) {

			glVertex2f((CIRCLE_RADIUS * cos(angle * PI/180)) + x, (CIRCLE_RADIUS * sin(angle * PI/180)) + y);
		}

	glEnd();
}

void drawLine(int x1, int y1, int x2, int y2, int colour) {

	setColour(colour);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
	
}

void updateShotPosition(int player) {

	switch (player) {

	case PLAYER2:

		player2_bullet_x1 = player2_bullet_x2;
		player2_bullet_y1 = player2_bullet_y2;
	    player2_bullet_x2 = player2_bullet_x1 +  cos(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;
	    player2_bullet_y2 = player2_bullet_y1 +  sin(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;
		
		if (player2_bullet_x1 < 0 || player2_bullet_x1 > WINDOW_WIDTH || player2_bullet_y1 < 0 || player2_bullet_y1 > WINDOW_LENGTH || (sqrt(pow(player2_bullet_x2 - player1_x + 0.0, 2) + pow(player2_bullet_y2 - player1_y + 0.0, 2)) <= CIRCLE_RADIUS)) {
			draw_bullet_player2 = 0;
			repeat_fire_player2 = 1;

			/*if(player1_decreased_displacement == 0) {
				displacement = displacement - 4;
				angle_change = angle_change - 1.5;
				player2_increased_displacement = 0;
				player2_decreased_displacement = 1;
			}*/

			if((sqrt(pow(player2_bullet_x2 - player1_x + 0.0, 2) + pow(player2_bullet_y2 - player1_y + 0.0, 2)) <= CIRCLE_RADIUS)) {

 				double no_shield_angle = player1_shooting_angle;
				double shot_angle = player2_bullet_angle;

				if(shot_angle < 0)
					shot_angle = shot_angle + 360;
				if(no_shield_angle < 0)
					no_shield_angle = no_shield_angle + 360;

				if((no_shield_angle >= 0 && no_shield_angle <= 90) || (no_shield_angle > 270 && no_shield_angle <= 360)) {

					if(shot_angle > 90 && shot_angle < 270) {

						player2_score++;
						printScore();
					}
				}

				else if(no_shield_angle > 90 && no_shield_angle <= 270) {

					if((shot_angle >= 0 && shot_angle <= 90) || (shot_angle > 270 && shot_angle <= 360)) {

						player2_score++;
						printScore();
					}
				}
			}
		}
		
		else
			glutPostRedisplay();

		break;

	case PLAYER1:

		player1_bullet_x1 = player1_bullet_x2;
		player1_bullet_y1 = player1_bullet_y2;
	    player1_bullet_x2 = player1_bullet_x1 +  cos(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;
	    player1_bullet_y2 = player1_bullet_y1 +  sin(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;
	
		if (player1_bullet_x1 < 0 || player1_bullet_x1 > WINDOW_WIDTH || player1_bullet_y1 < 0 || player1_bullet_y1 > WINDOW_LENGTH || (sqrt(pow(player1_bullet_x2 - player2_x + 0.0, 2) + pow(player1_bullet_y2 - player2_y + 0.0, 2)) <= CIRCLE_RADIUS)) {
			draw_bullet_player1 = 0;
			repeat_fire_player1 = 1;

			if((sqrt(pow(player1_bullet_x2 - player2_x + 0.0, 2) + pow(player1_bullet_y2 - player2_y + 0.0, 2)) <= CIRCLE_RADIUS)) {

				double no_shield_angle = player2_shooting_angle;
				double shot_angle = player1_bullet_angle;

				if(shot_angle < 0)
					shot_angle = shot_angle + 360;
				if(no_shield_angle < 0)
					no_shield_angle = no_shield_angle + 360;

				if((no_shield_angle >= 0 && no_shield_angle <= 90) || (no_shield_angle > 270 && no_shield_angle <= 360)) {

					if(shot_angle > 90 && shot_angle < 270) {

						player1_score++;
						printScore();
					}
				}

				else if(no_shield_angle > 90 && no_shield_angle <= 270) {

					if((shot_angle >= 0 && shot_angle <= 90) || (shot_angle > 270 && shot_angle <= 360)) {

						player1_score++;
						printScore();
					}
				}
			}
			/*if(player2_decreased_displacement == 0) {
				displacement = displacement - 4;
				angle_change = angle_change - 1.5;
				player1_increased_displacement = 0;
				player1_decreased_displacement = 1;
			}*/
		}
		
		else
			glutPostRedisplay();

		break;
	}
	
	//glutPostRedisplay();	
}

void setColour(int colour) {

	switch(colour) {

	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;

	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;

	case LIGHT_BLUE:
		glColor3f(0.078, 0.102, 0.922);
		break;

	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;

	case BLACK:
		glColor3f(0.0, 0.0, 0.0);
		break;
	}
}

void arrowKeys() {

	if(sqrt(pow(abs(player1_x - player2_x + 0.0), 2) + pow(abs(player1_y - player2_y + 0.0), 2)) >= 2.23*CIRCLE_RADIUS && player1_x - CIRCLE_RADIUS >= 0 && player1_x + CIRCLE_RADIUS <= WINDOW_WIDTH && player1_y - CIRCLE_RADIUS >= 0 && player1_y + CIRCLE_RADIUS <= WINDOW_LENGTH ) {
		
		if(specialKeys[GLUT_KEY_UP] == 1) {
			player1_y = player1_y + displacement;
		}
	
		if (specialKeys[GLUT_KEY_DOWN] == 1) {
			player1_y = player1_y - displacement;
		}

		if(specialKeys[GLUT_KEY_LEFT] == 1) {
			player1_x = player1_x - displacement;
		}

		if(specialKeys[GLUT_KEY_RIGHT] == 1) {
			player1_x = player1_x + displacement;
		}
	}

	else if(sqrt(pow(abs(player1_x - player2_x + 0.0), 2) + pow(abs(player1_y - player2_y + 0.0), 2)) < 2.23*CIRCLE_RADIUS) {
		
		seperatePlayers();
	}
	
	else if (player1_x - CIRCLE_RADIUS < 0) {

		player1_x = player1_x + CIRCLE_RADIUS;
	}

	else if (player1_x + CIRCLE_RADIUS > WINDOW_WIDTH) {

		player1_x = player1_x - CIRCLE_RADIUS;
	}

	else if (player1_y - CIRCLE_RADIUS < 0) {

		player1_y = player1_y + CIRCLE_RADIUS;
	}

	else if (player1_y + CIRCLE_RADIUS > WINDOW_LENGTH) {

		player1_y = player1_y - CIRCLE_RADIUS;
	}
}

void seperatePlayers() {

	if(player1_x > player2_x)
		player1_x = player1_x + 1.5*CIRCLE_RADIUS;
	else
		player2_x = player2_x + 1.5*CIRCLE_RADIUS;
}

void arrowKeyDown(int key, int x, int y) {	
										
	specialKeys[key] = 1;
	glutPostRedisplay();
}

void arrowKeyUp(int key, int x, int y) {

	specialKeys[key] = 0;
	glutPostRedisplay();
}

void keyPress() {

	if(sqrt(pow(abs(player1_x - player2_x + 0.0), 2) + pow(abs(player1_y - player2_y + 0.0), 2)) >= 2.23*CIRCLE_RADIUS && player2_x + CIRCLE_RADIUS <= WINDOW_WIDTH && player2_y - CIRCLE_RADIUS >= 0 && player2_y + CIRCLE_RADIUS <= WINDOW_LENGTH ) {

		if (keys[KEY_CODE_A] || keys[KEY_CODE_a]) {

			player2_x = player2_x - displacement;
		}
	
		else if(keys[KEY_CODE_W] || keys[KEY_CODE_w]) {		
		
			player2_y = player2_y + displacement;
		}

		else if(keys[KEY_CODE_s] || keys[KEY_CODE_S]) {
		
			player2_y = player2_y - displacement;
		}

		else if(keys[KEY_CODE_d] || keys[KEY_CODE_D]) {
		
			player2_x = player2_x + displacement;
		}
	}

	else if(sqrt(pow(abs(player1_x - player2_x + 0.0), 2) + pow(abs(player1_y - player2_y + 0.0), 2)) < 2.23*CIRCLE_RADIUS) {

		seperatePlayers();
	}
	
	if (player2_x - CIRCLE_RADIUS < 0) {

		player2_x = player2_x + CIRCLE_RADIUS;
	}

	else if (player2_x + CIRCLE_RADIUS > WINDOW_WIDTH) {

		player2_x = player2_x - CIRCLE_RADIUS;
	}

	else if (player2_y - CIRCLE_RADIUS < 0) {

		player2_y = player2_y + CIRCLE_RADIUS;
	}

	else if (player2_y + CIRCLE_RADIUS > WINDOW_LENGTH) {

		player2_y = player2_y - CIRCLE_RADIUS;
	}

		if(keys[KEY_CODE_x] || keys[KEY_CODE_X]) {
		
			player2_shooting_angle = player2_shooting_angle - angle_change;
			if (player2_shooting_angle < 0)
				player2_shooting_angle = 360 + player2_shooting_angle; 
		}

		else if (keys[KEY_CODE_p] || keys[KEY_CODE_p]) {

			player1_shooting_angle = player1_shooting_angle - angle_change;
			if (player1_shooting_angle < 0)
				player1_shooting_angle = 360 + player1_shooting_angle; 
		}

		else if(keys[KEY_CODE_SPACE] && repeat_fire_player2 == 1) {
			
			draw_bullet_player2 = 1;
			player2_bullet_angle = player2_shooting_angle;
			repeat_fire_player2 = 0;

			/*if(player1_increased_displacement == 0) {
				displacement = displacement + 4;
				angle_change = angle_change + 1.5;
				player2_increased_displacement = 1;
				player2_decreased_displacement = 0;
			}*/

			player2_bullet_x1 = player2_x + cos(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;
			player2_bullet_y1 = player2_y + sin(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;

			player2_bullet_x2 = player2_bullet_x1 +  cos(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;
			player2_bullet_y2 = player2_bullet_y1 +  sin(player2_bullet_angle * PI/180) * CIRCLE_RADIUS;
		}

		else if(keys[KEY_CODE_ENTER] && repeat_fire_player1 == 1) {

			draw_bullet_player1 = 1;
			player1_bullet_angle = player1_shooting_angle;
			repeat_fire_player1 = 0;
			
			/*if(player2_increased_displacement == 0) {
				displacement = displacement + 4;
				angle_change = angle_change + 1.5;
				player1_increased_displacement = 1;
				player1_decreased_displacement = 0;
			}*/
			
			player1_bullet_x1 = player1_x + cos(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;
			player1_bullet_y1 = player1_y + sin(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;

			player1_bullet_x2 = player1_bullet_x1 +  cos(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;
			player1_bullet_y2 = player1_bullet_y1 +  sin(player1_bullet_angle * PI/180) * CIRCLE_RADIUS;
		}

}

void printScore() {

	printf("Player 1 Score: %d\n", player1_score);
	printf("Player 2 Score: %d\n\n", player2_score);
}

void keyPressDown(unsigned char key, int x, int y) {

	keys[key]=1;
	glutPostRedisplay();
}

void keyPressUp(unsigned char key, int x, int y) {

	keys[key]=0;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

/* Standard GLUT initialization */

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_LENGTH); /* 675 x 850 pixel window */
    glutInitWindowPosition(0,0); /* place window top left on display */
    glutCreateWindow("OpenGL 2D Shooter"); /* window title */

    myinit(); /* set attributes */

	glutDisplayFunc(display); /* display callback invoked when window opened */
	//glutIdleFunc (displayShooting);
	glutSpecialFunc(arrowKeyDown);
	glutSpecialUpFunc(arrowKeyUp);
	glutKeyboardFunc(keyPressDown);
	glutKeyboardUpFunc(keyPressUp);
	glutReshapeFunc(reshape);
    glutMainLoop(); /* enter event loop */
}
