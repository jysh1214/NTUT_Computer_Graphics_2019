#include <math.h>
#include <GL/glut.h>
#include<stdio.h>

float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

float angX = 0.0f;
float angY = 0.0f;
float angZ = 0.0f;

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

    //畫出cube
    glColor3f(0, 0, 1);
    glTranslatef(cubeX, cubeY, cubeZ); //位移

    //旋轉
    glRotatef(angX, 1.0, 0.0, 0.0);
    glRotatef(angY, 0.0, 1.0, 0.0);
    glRotatef(angZ, 0.0, 0.0, 1.0);

    glutSolidCube(3);

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
            cubeX -= 0.1f;
            break;

        case GLUT_KEY_RIGHT:
            cubeX += 0.1f;
            break;

        case GLUT_KEY_UP:
            cubeY += 0.1f;
            break;

        case GLUT_KEY_DOWN:
            cubeY -= 0.1f;
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
            angX += 1.0f;
            break;

        case 's':
            angY += 1.0f;
            break;

        case 'd':
            angZ += 1.0f;
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    gluLookAt(0,0,-10.0f,0,0,0, 0,1,0);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cube");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Skeyboard);
    glutDisplayFunc(RenderScence);
    glutMainLoop();

    return 0;
}
