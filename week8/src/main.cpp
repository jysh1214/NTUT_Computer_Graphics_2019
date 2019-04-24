#include <GL/glut.h>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <math.h>

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

struct point
{
    float x; float y;
};

point * Start = nullptr; point * End = nullptr;

void showPos()
{
    if (Start != nullptr && End != nullptr)
    {
        cout<<"start: "<< Start->x <<", "<< Start->y << "; ";
        cout<<"end: "<< End->x <<", "<< End->y <<endl;

        Start = nullptr; End = nullptr;
    }
}

void midPoint_algo(int x0, int y0, int x1, int y1, int type)
{
    int dx = x1 - x0; int dy = y1 - y0;
    int d = 2*dy-dx;
    int delE = 2*dy;
    int delNE = 2*(dy-dx);

    int x = x0; int y = y0;
    objectPointer->addSqr(x, 500-y);

    float step = 500/SIZE;
    float slope;
    (dx == 0)? slope = SIZE : slope = dy/dx;

    float it_step = sqrt(step*step + (slope*step)*(slope*step));

    while (x < x1)
    {
        if (d <= 0)
        {
                d += delE; x += it_step;
        }
        else
        {
                d += delNE; x += it_step; y += it_step;
        }
        if (x > x1) break;

        if (type == 1)
        {
            objectPointer->addSqr(x, 500 - y); cout<<"type 1"<<endl;
        }
        // else if (type == 2)
        // {
        //     objectPointer->addSqr(y, 500-x);
        // }
        else if (type == 3)
        {
            objectPointer->addSqr(x, 500 - ((-y+y0)+y0)); cout<<"type 3"<<endl;
        }
    }
}

void midPoint_main(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0; int dy = y1 - y0;
    float slope;
    (dx == 0)? slope = SIZE : slope = dy/dx;

    cout<<"dx: "<<dx<<", "<<"dy: "<<dy<<endl;

    // int event;
    if (dx > 0 && dy > 0 && 0 <= slope && slope <= 1) // 第一象限: 0~45度
    {
        midPoint_algo(x0, y0, x1, y1, 1);
    }
    // else if (dx > 0 && dy > 0 && slope > 1) // 第一象限: 46~90度
    // {
    //     midPoint_algo(x0, y0, y1, x1, 2);
    // }
    else if (dx > 0 && dy < 0 && 0 <= -slope && -slope <= 1) // 第四象限: 0~-45度
    {
        midPoint_algo(x0, y0, x1, y0-y1+y0, 3);
    }

    


    // int dx = x1 - x0; int dy = y1 - y0;
    // int d = 2*dy-dx;
    // int delE = 2*dy;
    // int delNE = 2*(dy-dx);

    // int x = x0; int y = y0;
    // objectPointer->addSqr(x, 500-y);

    // float step = 500/SIZE;
    // float slope;
    // (dx == 0)? slope = SIZE : slope = dy/dx;

    // bool positive_slope = (dx > 0 && dx > 0);

    // float it_step = sqrt(step*step + (slope*step)*(slope*step));

    // while (x < x1)
    // {
    //     if (d <= 0)
    //     {
    //             d += delE; x += it_step;
    //     }
    //     else
    //     {
    //             d += delNE; x += it_step; y += it_step;
    //     }
    //     if (x > x1) break;
    //     objectPointer->addSqr(x, 500-y);
    // }
}

void RenderScence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5.0f, 0, 0, 0, 0, 1, 0);

    if (objectPointer!=nullptr)
    {
        objectPointer->draw();
        objectPointer->addSqr(M_X, M_Y);
        
        if (Start != nullptr && End != nullptr)
        {
            // float t_x = Start->x; float t_y = Start->y;
            // Start->y = 500 - Start->y;
            // End->y = 500 - End->y;
            // int i = 0;
            float slope;
            if (End->x - Start->x != 0)
            {
                cout<<"pre: "<<(End->y - Start->y)<<", "<<(End->x - Start->x)<<endl;
                slope = (End->y - Start->y)/(End->x - Start->x);
            }
            cout<<"slope: "<<slope<<endl;

            midPoint_main(Start->x, Start->y, End->x, End->y);

            // do
            // {
            //     if (End->x - Start->x > 0) t_x += 1;
            //     else t_x -= 1;

            //     // cout<<"vector: "<<vector<<endl;

            //     if (End->y - Start->y > 0 && End->x - Start->x > 0) t_y += slope;
            //     else if (End->y - Start->y > 0 && End->x - Start->x < 0) t_y -= slope;
            //     else if (End->y - Start->y < 0 && End->x - Start->x > 0) t_y += slope;
            //     else t_y -= slope;
            //     // i ++;
            //     objectPointer->addSqr(t_x, 500-t_y);

            // } while (t_x != End->x);
        }
        showPos();
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

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state != GLUT_UP)
    {
        M_X = float(x);
        M_Y = float(y);

        if (Start == nullptr)
        {
            point * p = new point; p->x = M_X; p->y = 500-M_Y; 
            Start = p;
        }
        else
        {
            point * p = new point; p->x = M_X; p->y = 500-M_Y; 
            End = p;
        }
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

