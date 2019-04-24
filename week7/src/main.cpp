#include <GL/glut.h>
#include <iostream>
#include <stdlib.h> 
#include <vector>

//#include "./GL/freeglut.h"

#include "object.h"
#include "dot.h"

#include "grid.h"

/*
編譯：
make

使用說明：
滑鼠任一點取為建立自訂軸
方向健上下左右移動選取方塊
鍵盤小寫英文字母z,x,c對x,y,z軸旋轉
鍵盤小寫英文字母n對自訂軸旋轉
鍵盤小寫英文字母p,o,i做scale
*/

using namespace std;

float WINDOW_SIZE_WIDTH = 500;
float WINDOW_SIZE_HIGH = 500;

float M_X = 0.0f;
float M_Y = 0.0f;

int SIZE;

string FilePath = "";
string RenderMode = "Face";
string ColorMode = "Red";
bool BoundingBox = false;
bool Axis = false;

Grid *objectPointer = nullptr;

unsigned char pixel[4];

// struct Pixel
// {
//     int x; int y;
// };

// vector<Pixel> PixelVector;

// bool isColor(int x, int y)
// {
//     for (int i=0; i<PixelVector.size(); i++)
//     {
//         if (x == PixelVector[i].x && y == PixelVector[i].y)
//         {
//             return true;
//         }
//     }
//     return false;
// }

// void fillColor(int x, int y)
// {
//     glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//     cout << "R: " << (int)pixel[0] << endl;
//     cout << "G: " << (int)pixel[1] << endl;
//     cout << "B: " << (int)pixel[2] << endl;
//     cout << endl;

//     float step = WINDOW_SIZE_WIDTH/SIZE;

//     // 白色且尚未著色過
//     if ((int)pixel[0] == 255 && (int)pixel[1] == 255 && (int)pixel[2] == 255 &&
//        !(isColor(x, y)))
//        //GLUT_WINDOW_WIDTH
//     {
//         glColor3f(0, 1, 0);
//         glPointSize(1.0);
//         glBegin(GL_POINTS);
//                 glVertex2f((x - WINDOW_SIZE_WIDTH/2 - step/(2*WINDOW_SIZE_WIDTH/10))
//                             /(WINDOW_SIZE_WIDTH/10),
//                             -(y - WINDOW_SIZE_HIGH/2 - step/(2*WINDOW_SIZE_HIGH/10))
//                             /(WINDOW_SIZE_HIGH/10));
//                 // glVertex2f((x - GLUT_WINDOW_WIDTH/2 - step/(2*GLUT_WINDOW_WIDTH/10))
//                 //             /(GLUT_WINDOW_WIDTH/10),
//                 //             -(y - GLUT_WINDOW_HEIGHT/2 - step/(2*GLUT_WINDOW_HEIGHT/10))
//                 //             /(GLUT_WINDOW_HEIGHT/10));
//         glEnd();

//         Pixel p;
//         p.x = x;
//         p.y = y;
//         PixelVector.push_back(p);

//         fillColor(x + 1, y);
//         fillColor(x - 1, y);
//         fillColor(x, y + 1);
//         fillColor(x, y - 1);
//     }
// }

void RenderScence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5.0f, 0, 0, 0, 0, 1, 0);

    if (objectPointer!=nullptr)
    {
        objectPointer->draw();
        // objectPointer->fillColor(M_X, M_Y);
        // PixelVector.clear();
        // fillColor(M_X, M_Y);
        objectPointer->addSqr(M_X, M_Y);
        objectPointer->showPos(M_X, M_Y);
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

void menuSelect(int option)
{
    switch(option)
    {
    case 0:
        // BoundingBox? BoundingBox = false : BoundingBox = true;
        // if (objectPointer!=nullptr) objectPointer->setBoundingBox(BoundingBox);
        break;
    case 1:
        // Axis? Axis = false : Axis = true;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void fileSubMenuSelect(int option)
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

void buildPopupMenu()
{
    // File
    int fileSubMenu;
    fileSubMenu = glutCreateMenu(fileSubMenuSelect);
    glutAddMenuEntry("9*9", 0);
    glutAddMenuEntry("25*25", 1);
    glutAddMenuEntry("85*85", 2);
    glutAddMenuEntry("Custom", 3);

    // main menu
    int menu_id;
    menu_id = glutCreateMenu(menuSelect);
    glutAddSubMenu("Size", fileSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// void Skeyboard(int key, int x, int y)
// {
//     //按鍵操作
//     if (objectPointer!=nullptr)
//     {
//     switch(key)
//     {
//         case GLUT_KEY_LEFT:
//             // objectPointer->translate(-0.1f, 0, 0);
//             break;

//         case GLUT_KEY_RIGHT:
//             // objectPointer->translate(0.1f, 0, 0);
//             break;

//         case GLUT_KEY_UP:
//             // objectPointer->translate(0, 0.1f, 0);
//             break;

//         case GLUT_KEY_DOWN:
//             // objectPointer->translate(0,-0.1f, 0);
//             break;

//         default:
//             break;
//     }
//     glutPostRedisplay();
//     }
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     // 按鍵操作
//     if (objectPointer!=nullptr)
//     {
//     switch(key)
//     {
//         case 'z':
//             // objectPointer->rotation(1.0f, 0.0f, 0.0f, 0.1f);
//             break;

//         case 'x':
//             // objectPointer->rotation(0.0f, 1.0f, 0.0f, 0.1f);
//             break;

//         case 'c':
//             // objectPointer->rotation(0.0f, 0.0f, 1.0f, 0.1f);
//             break;

//         case 'p':
//             // objectPointer->scale(1.1f, 1.0f, 1.0f);
//             break;

//         case 'o':
//             // objectPointer->scale(1.0f, 1.1f, 1.0f);
//             break;

//         case 'i':
//             // objectPointer->scale(1.0f, 1.0f, 1.1f);
//             break;

//         case 'r': // reset
//         {
//             // objectPointer->translate(0, 0, -1.0f);
//             // Object *o = new Object(FilePath, RenderMode, ColorMode, BoundingBox);
//             // objectPointer = o;
//             break;
//         }

//         case 'n':
//             // objectPointer->rotation(M_X-(WINDOW_SIZE_WIDTH/2), (WINDOW_SIZE_HIGH/2)-M_Y, 0.0f, 0.1f);
//             break;

//         default:
//             break;
//     }
//     glutPostRedisplay();
//     }
// }

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
    glutCreateWindow("Grid");
    buildPopupMenu();
    init();
    
    // glutKeyboardFunc(keyboard);
    // glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMouseFunc(Mouse);
    glutMainLoop();

    return 0;
}

