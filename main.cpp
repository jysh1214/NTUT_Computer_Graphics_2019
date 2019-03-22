#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>

#include "cube.h"
#include "pyramid.h"
#include "dot.h"

/*
編譯：
g++ -std=c++11 main.cpp -o myOpenGlApp -lglut -lGLU -lGL

使用說明：
滑鼠熱一點取為建立自訂軸
鍵盤小寫英文字母a,b選擇操作方塊
方向健上下左右移動選取方塊
鍵盤小寫英文字母z,x,c對x,y,z軸旋轉
鍵盤小寫英文字母n對自訂軸旋轉
鍵盤小寫英文字母p,o,i做scale
鍵盤小寫英文字母r做reset
*/

using namespace std;

float WINDOW_SIZE_WIDTH = 500;
float WINDOW_SIZE_HIGH = 500;

string CHOOSE = "a";

float M_X = 0.0f;
float M_Y = 0.0f;

/* all object */
Cube a = Cube(-0.5, -0.5, 0, 1, 1);
Pyramid b = Pyramid(-2, -2, 0, 1, 1, 1, 1);

dot p = dot(M_X, M_Y);

void RenderScence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5.0f, 0, 0, 0, 0, 1, 0);

    //畫X軸Y軸
    glBegin(GL_LINES);
        glColor3f( 0, 1, 0);glVertex3f(-8, 0, 0);
        glColor3f( 0, 1, 0);glVertex3f( 8, 0, 0); 
        glColor3f( 0, 1, 0);glVertex3f( 0, 8, 0);
        glColor3f( 0, 1, 0);glVertex3f( 0,-8, 0);       
    glEnd();

    a.draw();
    b.draw();

    p.draw(M_X, M_Y);

    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1, 1, -1, 1, 1, 1000);
    glEnable(GL_DEPTH_TEST);
}

void Skeyboard(int key, int x, int y)
{
    //按鍵操作
    switch(key)
    {
        case GLUT_KEY_LEFT:
            if (CHOOSE == "a") a.move(-0.1f, 0, 0);
            if (CHOOSE == "b") b.move(-0.1f, 0, 0);
            break;

        case GLUT_KEY_RIGHT:
            if (CHOOSE == "a") a.move( 0.1f, 0, 0);
            if (CHOOSE == "b") b.move( 0.1f, 0, 0);
            break;

        case GLUT_KEY_UP:
            if (CHOOSE == "a") a.move( 0, 0.1f, 0);
            if (CHOOSE == "b") b.move( 0, 0.1f, 0);
            break;

        case GLUT_KEY_DOWN:
            if (CHOOSE == "a") a.move( 0,-0.1f, 0);
            if (CHOOSE == "b") b.move( 0,-0.1f, 0);
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    // 按鍵操作
    switch(key)
    {
        case 'a':
            CHOOSE = "a";
            break;

        case 'b':
            CHOOSE = "b";
            break;

        case 'z':
            if (CHOOSE == "a") a.rotation(1.0f, 0.0f, 0.0f, 0.1f);
            if (CHOOSE == "b") b.rotation(1.0f, 0.0f, 0.0f, 0.1f);
            break;

        case 'x':
            if (CHOOSE == "a") a.rotation(0.0f, 1.0f, 0.0f, 0.1f);
            if (CHOOSE == "b") b.rotation(0.0f, 1.0f, 0.0f, 0.1f);
            break;

        case 'c':
            if (CHOOSE == "a") a.rotation(0.0f, 0.0f, 1.0f, 0.1f);
            if (CHOOSE == "b") b.rotation(0.0f, 0.0f, 1.0f, 0.1f);
            break;

        case 'p':
            if (CHOOSE == "a") a.scale(1.1f, 1.0f, 1.0f);
            if (CHOOSE == "b") b.scale(1.1f, 1.0f, 1.0f);
            break;

        case 'o':
            if (CHOOSE == "a") a.scale(1.0f, 1.1f, 1.0f);
            if (CHOOSE == "b") b.scale(1.0f, 1.1f, 1.0f);
            break;

        case 'i':
            if (CHOOSE == "a") a.scale(1.0f, 1.0f, 1.1f);
            if (CHOOSE == "b") b.scale(1.0f, 1.0f, 1.1f);
            break;

        case 'r':
            if (CHOOSE == "a") a.reset();
            if (CHOOSE == "b") b.reset();
            break;

        case 'n':
            if (CHOOSE == "a") a.rotation(M_X-(WINDOW_SIZE_WIDTH/2), (WINDOW_SIZE_HIGH/2)-M_Y, 0.0f, 0.1f);
            if (CHOOSE == "b") b.rotation(M_X-(WINDOW_SIZE_WIDTH/2), (WINDOW_SIZE_HIGH/2)-M_Y, 0.0f, 0.1f);
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        M_X = float(x); 
        M_Y = float(y);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A B Cube");
    init();
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMouseFunc(Mouse);
    glutMainLoop();

    return 0;
}