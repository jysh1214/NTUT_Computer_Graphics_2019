#include <GL/glut.h>
#include <iostream>
#include <stdlib.h> 

#include "vertex.h"
#include "object.h"

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

GLfloat light_ambient[]={0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[]={0.0, 0.0, 0.0, 1.0};

GLfloat mat_specular[]={0.0, 0.0, 0.0, 1.0};
GLfloat mat_diffuse[]={0.8, 0.6, 0.4, 1.0};
GLfloat mat_ambient[]={0.8, 0.6, 0.4, 1.0};
GLfloat mat_shininess={20.0};

float WINDOW_SIZE_WIDTH = 1500;
float WINDOW_SIZE_HIGH = 500;

float M_X = 0.0f;
float M_Y = 0.0f;

string FilePath = "";
string RenderMode = "Face";
string ColorMode = "Red";
string ShadeModel = "Flat";

// Object *objectPointer = nullptr;

/* create lcosahedron */
float X = 0.52;
float Z = 0.85;
vector<Vertex> vdata1 {
    {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
    {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
    {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
vector<Vertex> fdata1 {
    {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
    {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
    {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
    {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7},
};
Object object1(vdata1, fdata1, RenderMode, ColorMode);
Object object2(vdata1, fdata1, RenderMode, ColorMode);
Object object3(vdata1, fdata1, RenderMode, ColorMode);


void RenderScence(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glViewport(0, 0, 500, 500);
    glLoadIdentity();
    gluLookAt(0, 0, 4.0f, 0, 0, 0, 0, 1, 0);
    object1.draw();

    glViewport(500, 0, 500, 500);
    glLoadIdentity();
    gluLookAt(0, 0, 4.0f, 0, 0, 0, 0, 1, 0);
    object2.draw();

    glViewport(1000, 0, 500, 500);
    glLoadIdentity();
    gluLookAt(0, 0, 4.0f, 0, 0, 0, 0, 1, 0);
    object3.draw();
    
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-1, 1, -1, 1, 1, 100);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glEnable(GL_LIGHTING); /* enable lighting */
    glEnable(GL_LIGHT0); /* enable light 0 */
}

void menuSelect(int option) {}

void shadeModeSubMenuSelect(int option)
{
    switch(option)
    {
        case 0:
            ShadeModel = "Flat";
            object1.setShadeMode("Flat");
            object2.setShadeMode("Flat");
            object3.setShadeMode("Flat");
            glutPostRedisplay();
            break;
        case 1:
            ShadeModel = "Smooth";
            object1.setShadeMode("Smooth");
            object2.setShadeMode("Smooth");
            object3.setShadeMode("Smooth");
            glutPostRedisplay();
        default:
            break;
    }
    glutPostRedisplay();
}

void renderModeSubMenuSelect(int option)
{
    switch(option)
    {
    case 0:
        RenderMode = "Point";
        object1.setRenderMode("Point");
        object2.setRenderMode("Point");
        object3.setRenderMode("Point");
        glutPostRedisplay();
        break;
    case 1:
        RenderMode = "Line";
        object1.setRenderMode("Line");
        object2.setRenderMode("Line");
        object3.setRenderMode("Line");
        glutPostRedisplay();
        break;
    case 2:
        RenderMode = "Face";
        object1.setRenderMode("Face");
        object2.setRenderMode("Face");
        object3.setRenderMode("Face");
        glutPostRedisplay();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void colorModeSubMenuSelect(int option)
{
    switch(option)
    {
    case 0:
        ColorMode = "Red";
        object1.setColorMode("Red");
        object2.setColorMode("Red");
        object3.setColorMode("Red");
        glutPostRedisplay();
        break;
    case 1:
        ColorMode = "Green";
        object1.setColorMode("Green");
        object2.setColorMode("Green");
        object3.setColorMode("Green");
        glutPostRedisplay();
        break;
    case 2:
        ColorMode = "Blue";
        object1.setColorMode("Blue");
        object2.setColorMode("Blue");
        object3.setColorMode("Blue");
        glutPostRedisplay();
        break;
    default:
        break;

    glutPostRedisplay();
    }
}

void buildPopupMenu()
{
    // Shade Mode
    int ShadeModeSubMenu;
    ShadeModeSubMenu = glutCreateMenu(shadeModeSubMenuSelect);
    glutAddMenuEntry("Flat", 0);
    glutAddMenuEntry("Smooth", 1);

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

    // main menu
    glutCreateMenu(menuSelect);
    glutAddSubMenu("Shade Mode", ShadeModeSubMenu);
    glutAddSubMenu("Render Mode", renderModeSubMenu);
    glutAddSubMenu("Color Mode", colorModeSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Skeyboard(int key, int x, int y)
{
    //按鍵操作
    switch(key)
    {
        case GLUT_KEY_LEFT:
            object1.rotation(0.0f, 1.0f, 0.0f, -0.1f);
            object2.rotation(0.0f, 1.0f, 0.0f, -0.1f);
            object3.rotation(0.0f, 1.0f, 0.0f, -0.1f);
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            object1.rotation(0.0f, 1.0f, 0.0f, 0.1f);
            object2.rotation(0.0f, 1.0f, 0.0f, 0.1f);
            object3.rotation(0.0f, 1.0f, 0.0f, 0.1f);
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            // objectPointer->translate(0, 0.1f, 0);
            break;

        case GLUT_KEY_DOWN:
            // objectPointer->translate(0,-0.1f, 0);
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':
            object1._depthsize ++;
            object2._depthsize ++;
            object3._depthsize ++;
            break;

        case '-':
            object1._depthsize --; if (object1._depthsize < 0) object1._depthsize = 0;
            object2._depthsize --; if (object2._depthsize < 0) object2._depthsize = 0;
            object3._depthsize --; if (object3._depthsize < 0) object3._depthsize = 0;
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
    glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HIGH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("illumination");
    buildPopupMenu();
    init();

    object1.setShadeMode("Flat");
    object2.setShadeMode("Interpolate");
    object3.setShadeMode("Subdivision");


    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMainLoop();

    return 0;
}

