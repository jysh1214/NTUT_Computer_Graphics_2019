#include <GL/glut.h>
#include <iostream>
#include <stdlib.h> 
#include <vector>

//#include "./GL/freeglut.h"

#include "grid.h"

/*
編譯：
make

使用說明：
右鍵選單選取size，algo
*/

using namespace std;

float WINDOW_SIZE_WIDTH = 500;
float WINDOW_SIZE_HIGH = 500;

float M_X = 0.0f;
float M_Y = 0.0f;

float Z_DIS = 5.0;

int SIZE;

string ALGO = "mid_point";

Grid *objectPointer = nullptr;

struct point
{
    float x; float y;
};

point * Start = nullptr; point * End = nullptr;

void RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, Z_DIS, 0, 0, 0, 0, 1, 0);

    if (objectPointer != nullptr)
    {
        objectPointer->draw();
        // 改變滑鼠座標係： 左上 改到 左下
        objectPointer->addSqr(M_X, 500-M_Y, 1);
    }

    if (End != nullptr)
    {
        if (ALGO == "mid_point")
            objectPointer->midPoint(Start->x, 500-Start->y, End->x, 500-End->y);
        if (ALGO == "anti_aliasing")
            objectPointer->antiAliasing(Start->x, 500-Start->y, End->x, 500-End->y);

        Start = nullptr; End = nullptr;
    }
    
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1, 1, -1, 1, 1, 1000);
    gluPerspective(10.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void menuSelect(int option) {}

void sizeSubMenuSelect(int option)
{
    switch(option)
    {
        case 0:
        {
            Grid * o = new Grid(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH, 9);
            SIZE = 9;
            objectPointer = o;
            break;
        }
        case 1:
        {
            Grid * o = new Grid(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH, 25);
            SIZE = 25;
            objectPointer = o;
            break;
        }
        case 2:
        {
            Grid * o = new Grid(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH, 85);
            SIZE = 85;
            objectPointer = o;
            break;
        }
        case 3:
        {
            int temp;
            cout << "Input size: ";
            cin >> temp;
            SIZE = temp;
            Grid * o = new Grid(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH, temp);
            objectPointer = o;
            break;
        }
        default:
        {
            break;
        }
    }
    glutPostRedisplay();
}

void algoSubMenuSelect(int option)
{
    switch(option)
    {
        case 0:
            ALGO = "mid_point";
            break;

        case 1:
            ALGO = "anti_aliasing";
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void buildPopupMenu()
{
    // Size
    int sizeSubMenu;
    sizeSubMenu = glutCreateMenu(sizeSubMenuSelect);
    glutAddMenuEntry("9*9", 0);
    glutAddMenuEntry("25*25", 1);
    glutAddMenuEntry("85*85", 2);
    glutAddMenuEntry("Custom", 3);

    // Algo
    int algoSubMenu;
    algoSubMenu = glutCreateMenu(algoSubMenuSelect);
    glutAddMenuEntry("mid_point", 0);
    glutAddMenuEntry("anti_aliasing", 1);

    // main menu
    glutCreateMenu(menuSelect);
    glutAddSubMenu("Size", sizeSubMenu);
    glutAddSubMenu("Algo", algoSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        M_X = float(x);
        M_Y = float(y);

        point * p = new point; p->x = M_X; p->y = M_Y;
        if (Start == nullptr) Start = p;
        else End = p;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Grid");
    buildPopupMenu();
    init();
    
    glutDisplayFunc(RenderScence);
    glutMouseFunc(Mouse);
    glutMainLoop();

    return 0;
}

