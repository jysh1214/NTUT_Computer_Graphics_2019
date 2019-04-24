#ifndef SQR_H
#define SQR_H

#include <GL/glut.h>

class Sqr
{
public:
    Sqr(int x, int y, float width): _x(x), _y(y), _width(width)
    {
        
    }

    virtual ~Sqr(){}

    void draw()
    {
        float lux = ((_x - _width/2))/50;
        float luy = -((_y + _width/2))/50;

        float rux = ((_x + _width/2))/50;
        float ruy = -((_y + _width/2))/50;

        float ldx = ((_x - _width/2))/50;
        float ldy = -((_y - _width/2))/50;

        float rdx = ((_x + _width/2))/50;
        float rdy = -((_y - _width/2))/50;

        glColor3f( 1, 0, 0);
            glBegin(GL_QUAD_STRIP);
                glVertex2f(lux, luy); // 左上
                glVertex2f(rux, ruy); // 右上
                glVertex2f(ldx, ldy); // 左下
                glVertex2f(rdx, rdy); // 右下
        glEnd();
    }

private:
    int _x; int _y;
    float _width;

};

#endif