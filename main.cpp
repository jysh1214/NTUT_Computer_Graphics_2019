#include <math.h>
#include <GL/glut.h>
#include<stdio.h>
#include <string>

#include "cube.h"

using namespace std;

float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

float angX = 0.0f;
float angY = 0.0f;
float angZ = 0.0f;

string choose = "a";

/* all object */
Cube a = Cube(0, 0, 0, 1);
Cube b = Cube(-2, -2, 0, 1);

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
            if (choose == "a") a.move(-0.1f, 0, 0);
            if (choose == "b") b.move(-0.1f, 0, 0);
            break;

        case GLUT_KEY_RIGHT:
            if (choose == "a") a.move( 0.1f, 0, 0);
            if (choose == "b") b.move( 0.1f, 0, 0);
            break;

        case GLUT_KEY_UP:
            if (choose == "a") a.move( 0, 0.1f, 0);
            if (choose == "b") b.move( 0, 0.1f, 0);
            break;

        case GLUT_KEY_DOWN:
            if (choose == "a") a.move( 0,-0.1f, 0);
            if (choose == "b") b.move( 0,-0.1f, 0);
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
            choose = "a";
            break;

        case 'b':
            choose = "b";
            break;

        case 'z':
            if (choose == "a") a.rotation(0.1f, 0.0f, 0.0f);
            if (choose == "b") b.rotation(0.1f, 0.0f, 0.0f);
            break;

        case 'x':
            if (choose == "a") a.rotation(0.0f, 0.1f, 0.0f);
            if (choose == "b") b.rotation(0.0f, 0.1f, 0.0f);
            break;

        case 'c':
            if (choose == "a") a.rotation(0.0f, 0.0f, 0.1f);
            if (choose == "b") b.rotation(0.0f, 0.0f, 0.1f);
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A B Cube");
    init();
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMainLoop();

    return 0;
}
