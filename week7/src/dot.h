#ifndef DOT_H
#define DOT_H

#include <GL/glut.h>

class dot
{
public:
    dot(float x, float y): _x(x), _y(y)
    {
     
    }

    virtual ~dot(){}

    void draw(float x, float y)
    {
        _x = x; _y = y;
        glPushMatrix();
        glColor3f(0,0,1);
        glPointSize(10.0);
        glBegin(GL_POINTS); 
            glVertex2f( (_x-250)/50, -(_y-250)/50); 
        glEnd(); 

        // glBegin(GL_LINES);
        //     glVertex3f( 0.0f, 0.0f, 0.0f);
        //     glVertex3f( (_x-250)/50, -(_y-250)/50, 0.0f);
        // glEnd();

        glPopMatrix();
    }


private:
    float _x; float _y;
};

#endif 