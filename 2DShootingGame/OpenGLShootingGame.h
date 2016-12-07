/* Osama Mohammed
CS 5472
2D Game in OpenGL
*/

#define CIRCLE_RADIUS 30
#define PLAYER1 1
#define PLAYER2 2
#define START_PLAYER1_X 150
#define START_PLAYER1_Y 150
#define START_PLAYER2_X 400
#define START_PLAYER2_Y 400
#define PI 3.14159265
#define CIRCLE_EDGES 100
#define DELAY_VALUE 45
#define RED 1
#define GREEN 2
#define YELLOW 3
#define LIGHT_BLUE 4
#define BLACK 5
#define KEY_CODE_a 97
#define KEY_CODE_A 65
#define KEY_CODE_s 115
#define KEY_CODE_S 83
#define KEY_CODE_w 119
#define KEY_CODE_W 87
#define KEY_CODE_D 68
#define KEY_CODE_d 100
#define KEY_CODE_R 82
#define KEY_CODE_r 114
#define KEY_CODE_SPACE 32
#define KEY_CODE_ENTER 13
#define KEY_CODE_P 80
#define KEY_CODE_p 112
#define KEY_CODE_X 88
#define KEY_CODE_x 120

int WINDOW_WIDTH = 850;
int WINDOW_LENGTH = 675;

double angle_change = 3.0;
int displacement = 5;
/*int player1_increased_displacement = 0;
int player2_increased_displacement = 0;
int player2_decreased_displacement = 0;
int player1_decreased_displacement = 0;*/
int player1_x = START_PLAYER1_X;
int player1_y = START_PLAYER1_Y;
int player2_x = START_PLAYER2_X;
int player2_y = START_PLAYER2_Y;
double player1_shooting_angle = 0;
double player2_shooting_angle = 0;
int draw_bullet_player1 = 0;
int draw_bullet_player2 = 0;
int repeat_fire_player1 = 1;
int repeat_fire_player2 = 1;
int player2_bullet_x1 = 0;
int player2_bullet_x2 = 0; 
int player2_bullet_y1 = 0; 
int player2_bullet_y2 = 0;
double player2_bullet_angle = 0;
double player1_bullet_angle = 0;
int player1_bullet_x1 = 0;
int player1_bullet_x2 = 0; 
int player1_bullet_y1 = 0; 
int player1_bullet_y2 = 0;
int player2_score = 0;
int player1_score = 0;
int keys[256];
int specialKeys[256];

typedef struct
{
float x;
float y;
}CIRCLE;

CIRCLE circle;
float rot = 0;

void transform();
void myinit();
void display();
void reshape();
void create_Player(int x, int y, int shield_colour, int shootingSide_colour, int shootingAngle);
void drawCircle (int k, int r, int h);
void drawPlayer(int x, int y, int shield_colour, int shootingSide_colour, int shootingAngle);
void drawLine(int x1, int y1, int x2, int y2, int colour);
void drawShot(int player);
void updateShotPosition(int player);
void seperatePlayers();
void setColour(int colour);
void arrowKeys();
void arrowKeyDown(int key, int x, int y);
void arrowKeyUp(int key, int x, int y);
void keyPress();
void keyPressDown(unsigned char key, int x, int y);
void keyPressUp(unsigned char key, int x, int y);
void printScore();