#include <GL/glut.h>
#include <iostream>
#include <stdlib.h> 

#include "object.h"
#include "dot.h"

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

string FilePath = "";
string RenderMode = "Face";
string ColorMode = "Red";
bool BoundingBox = false;
bool Axis = true;

Object *objectPointer = nullptr;

void RenderScence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 4.0f, 0, 0, 0, 0, 1, 0);

    if (Axis)
    {
        //畫X軸Y軸
        glBegin(GL_LINES);
            glColor3f( 0, 1, 0);glVertex3f(-8, 0, 0);
            glColor3f( 0, 1, 0);glVertex3f( 8, 0, 0);
            glColor3f( 0, 1, 0);glVertex3f( 0, 8, 0);
            glColor3f( 0, 1, 0);glVertex3f( 0,-8, 0);

            for (int i=0; i<=500; i += 1)
            {
                glVertex3f( i, 500, 0); glVertex3f( i,-500, 0);
                glVertex3f( -i, 500, 0); glVertex3f( -i,-500, 0);
            }

            for (int j=0; j<= 500; j += 1)
            {
                glVertex3f( -500, j, 0); glVertex3f( 500,j, 0);
                glVertex3f( -500, -j, 0); glVertex3f( 500,-j, 0);
            }
           
        glEnd();       
    }

    if (objectPointer!=nullptr) objectPointer->draw();
    
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
        BoundingBox? BoundingBox = false : BoundingBox = true;
        if (objectPointer!=nullptr) objectPointer->setBoundingBox(BoundingBox);
        break;
    case 1:
        Axis? Axis = false : Axis = true;
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
            free(objectPointer);
            Object * o;
            try
            {
                o = new Object("gourd.obj", RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
            objectPointer = o;
            FilePath = "gourd.obj";
            break;
        }
        case 1:
        {
            free(objectPointer);
            Object * o;
            try
            {
                o = new Object("lamp.obj", RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
            objectPointer = o;
            FilePath = "lamp.obj";
            break;
        }
        case 2:
        {
            free(objectPointer);
            Object * o;
            try
            {
                o = new Object("octahedron.obj", RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
            objectPointer = o;
            FilePath = "octahedron.obj";
            break;
        }
        case 3:
        {           
            free(objectPointer); 
            Object * o;
            try
            {
                o = new Object("teapot.obj", RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
            objectPointer = o;
            FilePath = "teapot.obj";
            break;
        }
        case 4:
        {
            free(objectPointer);
            Object * o;
            try
            {
                o = new Object("teddy.obj", RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
            objectPointer = o;
            FilePath = "teddy.obj";
            break;
        }
        case 5:
        {
            free(objectPointer);
            cout << "Enter file path: ";
            cin >> FilePath;
            Object * o;
            try
            {
                o = new Object(FilePath, RenderMode, ColorMode, BoundingBox);
            }
            catch (const exception& e)
            {
                cerr << "exception caught: " << e.what() << '\n';
            }
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

void renderModeSubMenuSelect(int option)
{
    if (objectPointer!=nullptr)
    {
    switch(option)
    {
    case 0:
        RenderMode = "Point";
        objectPointer->setRenderMode("Point");
        break;
    case 1:
        RenderMode = "Line";
        objectPointer->setRenderMode("Line");
        break;
    case 2:
        RenderMode = "Face";
        objectPointer->setRenderMode("Face");
        break;
    default:
        break;
    }
    glutPostRedisplay();
    }
}

void colorModeSubMenuSelect(int option)
{
    if (objectPointer!=nullptr)
    {
    switch(option)
    {
    case 0:
        ColorMode = "Red";
        objectPointer->setColorMode("Red");
        break;
    case 1:
        ColorMode = "Green";
        objectPointer->setColorMode("Green");
        break;
    case 2:
        ColorMode = "Blue";
        objectPointer->setColorMode("Blue");
        break;
    case 3:
    {
        int randomColor = rand() % 3;
        switch(randomColor)
        {
        case 0:
            ColorMode = "Red";
            objectPointer->setColorMode("Red");
            break;
        case 1:
            ColorMode = "Green";
            objectPointer->setColorMode("Green");
            break;
        case 2:
            ColorMode = "Blue";
            objectPointer->setColorMode("Blue");
            break;
        }
    }
    default:
        break;
    }
    glutPostRedisplay();
    }
}

void buildPopupMenu()
{
    // File
    int fileSubMenu;
    fileSubMenu = glutCreateMenu(fileSubMenuSelect);
    glutAddMenuEntry("gourd", 0);
    glutAddMenuEntry("lamp", 1);
    glutAddMenuEntry("octahedron", 2);
    glutAddMenuEntry("teapot", 3);
    glutAddMenuEntry("teddy", 4);
    glutAddMenuEntry("others...", 5);

    // Render Mode
    int renderModeSubMenu;
    renderModeSubMenu = glutCreateMenu(renderModeSubMenuSelect);
    glutAddMenuEntry("Point", 0);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Face", 2);

    // Color Mode
    int colorModeSubMenu;
    colorModeSubMenu = glutCreateMenu(colorModeSubMenuSelect);
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Random", 3);

    // main menu
    glutCreateMenu(menuSelect);
    glutAddSubMenu("File", fileSubMenu);
    glutAddSubMenu("Render Mode", renderModeSubMenu);
    glutAddSubMenu("Color Mode", colorModeSubMenu);
    glutAddMenuEntry("Bounding Box", 0);
    glutAddMenuEntry("Axis", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Skeyboard(int key, int x, int y)
{
    //按鍵操作
    if (objectPointer!=nullptr)
    {
    switch(key)
    {
        case GLUT_KEY_LEFT:
            objectPointer->translate(-0.1f, 0, 0);
            break;

        case GLUT_KEY_RIGHT:
            objectPointer->translate(0.1f, 0, 0);
            break;

        case GLUT_KEY_UP:
            objectPointer->translate(0, 0.1f, 0);
            break;

        case GLUT_KEY_DOWN:
            objectPointer->translate(0,-0.1f, 0);
            break;

        default:
            break;
    }
    glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    // 按鍵操作
    if (objectPointer!=nullptr)
    {
    switch(key)
    {
        case 'z':
            objectPointer->rotation(1.0f, 0.0f, 0.0f, 0.1f);
            break;

        case 'x':
            objectPointer->rotation(0.0f, 1.0f, 0.0f, 0.1f);
            break;

        case 'c':
            objectPointer->rotation(0.0f, 0.0f, 1.0f, 0.1f);
            break;

        case 'p':
            objectPointer->scale(1.1f, 1.0f, 1.0f);
            break;

        case 'o':
            objectPointer->scale(1.0f, 1.1f, 1.0f);
            break;

        case 'i':
            objectPointer->scale(1.0f, 1.0f, 1.1f);
            break;

        case 'r': // reset
        {
            // objectPointer->translate(0, 0, -1.0f);
            Object *o = new Object(FilePath, RenderMode, ColorMode, BoundingBox);
            objectPointer = o;
            break;
        }

        case 'n':
            objectPointer->rotation(M_X-(WINDOW_SIZE_WIDTH/2), (WINDOW_SIZE_HIGH/2)-M_Y, 0.0f, 0.1f);
            break;

        default:
            break;
    }
    glutPostRedisplay();
    }
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
    glutCreateWindow("Obj Parser");
    buildPopupMenu();
    init();
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMouseFunc(Mouse);
    glutMainLoop();

    return 0;
}