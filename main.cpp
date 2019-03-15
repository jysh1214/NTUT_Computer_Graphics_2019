#include <math.h>
#include <GL/glut.h>
#include<stdio.h>
#include <string>

#include "cube.h"
#include "dot.h"

using namespace std;

float WINDOW_SIZE_H = 500;
float WINDOW_SIZE_L = 500;

string CHOOSE = "a";

float M_X = 0.0f;
float M_Y = 0.0f;

/* all object */
Cube a = Cube(-0.5, -0.5, 0, 1);
Cube b = Cube(-2, -2, 0, 1);

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
    //按鍵操作
    switch(key)
    {
        case 'a':
            CHOOSE = "a";
            break;

        case 'b':
            CHOOSE = "b";
            break;

        case 'z':
            if (CHOOSE == "a") a.rotation(0.1f, 0.0f, 0.0f);
            if (CHOOSE == "b") b.rotation(0.1f, 0.0f, 0.0f);
            break;

        case 'x':
            if (CHOOSE == "a") a.rotation(0.0f, 0.1f, 0.0f);
            if (CHOOSE == "b") b.rotation(0.0f, 0.1f, 0.0f);
            break;

        case 'c':
            if (CHOOSE == "a") a.rotation(0.0f, 0.0f, 0.1f);
            if (CHOOSE == "b") b.rotation(0.0f, 0.0f, 0.1f);
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
            if (CHOOSE == "a") a.crotation(M_X-250.0, 250.0-M_Y, 0.0f, 0.1f);
            if (CHOOSE == "b") b.crotation(M_X-250.0, 250.0-M_Y, 0.0f, 0.1f);
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
    glutInitWindowSize(WINDOW_SIZE_H, WINDOW_SIZE_L);
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
