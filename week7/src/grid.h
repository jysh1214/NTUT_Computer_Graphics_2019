#ifndef GRID_H
#define GRID_H

#include <GL/glut.h>    
#include <iostream>
#include <vector>
#include <math.h>
#include <map>

#include "sqr.h"

using namespace std;

class Grid
{
public:
    Grid(float w, float h, int size): _w(w), _h(h), _size(size)
    {
        _step = w/size;
    }

    virtual ~Grid(){}

    void draw()
    {
        // 畫X軸Y軸
        if (_size%2)
        {
            glColor3f( 0, 1, 0);
            glBegin(GL_LINES);

                for (float i= 0.0 - _step/100; i<=500; i += _step/50)
                {
                    glVertex3f( i, 500, 0); glVertex3f( i,-500, 0);
                    glVertex3f( -i, 500, 0); glVertex3f( -i,-500, 0);
                }

                for (float j=0.0 - _step/100; j<= 500; j += _step/50)
                {
                    glVertex3f( -500, j, 0); glVertex3f( 500,j, 0);
                    glVertex3f( -500, -j, 0); glVertex3f( 500,-j, 0);
                }
            glEnd();
        }
        else
        {
            glColor3f( 0, 1, 0);
            glBegin(GL_LINES);

                for (float i= 0.0; i<=500; i += _step/50)
                {
                    glVertex3f( i, 500, 0); glVertex3f( i,-500, 0);
                    glVertex3f( -i, 500, 0); glVertex3f( -i,-500, 0);
                }

                for (float j=0.0; j<= 500; j += _step/50)
                {
                    glVertex3f( -500, j, 0); glVertex3f( 500,j, 0);
                    glVertex3f( -500, -j, 0); glVertex3f( 500,-j, 0);
                }
            glEnd(); 
        }

        for (unsigned int i=0; i<_sqrVector.size(); i++)
        {
            _sqrVector[i].draw();
        }
    }

    void addSqr(float x, float y, float alpha)
    {
        // 找中心座標
        x /= _step;
        y /= _step;

        int m_x = (int(x) - _size/2) * _step;
        int m_y = (int(y) - _size/2) * _step;

        Sqr s = Sqr(m_x, m_y, _step); // 給中心座標和寬度
        s.alpha = alpha;
        _sqrVector.push_back(s);
    }

    void showPos(float x, float y)
    {
        x /= _step;
        y /= _step;

        cout<<"pos: "<<int(x) - _size/2<<", "<<int(y) - _size/2<<endl;
    }

    void midPoint(int x0, int y0, int x1, int y1)
    {
        float dx = abs(x1 - x0);
        float dy = abs(y1 - y0);
        float slope;
        (dx == 0)? slope = _size : slope = dy/dx;

        float iter_x = x0; float iter_y = y0;
        float iter_step = _step;

        if (slope <= 1)
        {
            int d = 2*dy-dx; int delE = 2*dy; int delNE = 2*(dy-dx);

            while (iter_x < x1 && y1 > y0)
            {
                if (d <= 0)
                {
                    d += delE; iter_x += iter_step;
                }
                else
                {
                    d += delNE; iter_x += iter_step; iter_y += iter_step;
                }
                if (iter_x > x1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_x < x1 && y1 < y0)
            {
                if (d <= 0)
                {
                    d += delE; iter_x += iter_step;
                }
                else
                {
                    d += delNE; iter_x += iter_step; iter_y -= iter_step;
                }
                if (iter_x > x1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_x > x1 && y1 > y0)
            {
                if (d <= 0)
                {
                    d += delE; iter_x -= iter_step;
                }
                else
                {
                    d += delNE; iter_x -= iter_step; iter_y += iter_step;
                }
                if (iter_x < x1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_x > x1 && y1 < y0)
            {
                if (d <= 0)
                {
                    d += delE; iter_x -= iter_step;
                }
                else
                {
                    d += delNE; iter_x -= iter_step; iter_y -= iter_step;
                }
                if (iter_x < x1) break;
                this->addSqr(iter_x, iter_y, 1);
            }
        }

        else if (slope > 1)
        {
            int d = 2*dx-dy; int delE = 2*dx; int delNE = 2*(dx-dy);

            while (iter_y < y1 && x1 > x0)
            {
                if (d <= 0)
                {
                    d += delE; iter_y += iter_step;
                }
                else
                {
                    d += delNE; iter_x += iter_step; iter_y += iter_step;
                }
                if (iter_y > y1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_y < y1 && x1 < x0)
            {
                if (d <= 0)
                {
                    d += delE; iter_y += iter_step;
                }
                else
                {
                    d += delNE; iter_x -= iter_step; iter_y += iter_step;
                }
                if (iter_y > y1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_y > y1 && x1 < x0)
            {
                if (d <= 0)
                {
                    d += delE; iter_y -= iter_step;
                }
                else
                {
                    d += delNE; iter_x -= iter_step; iter_y -= iter_step;
                }
                if (iter_y < y1) break;
                this->addSqr(iter_x, iter_y, 1);
            }

            while (iter_y > y1 && x1 > x0)
            {
                if (d <= 0)
                {
                    d += delE; iter_y -= iter_step;
                }
                else
                {
                    d += delNE; iter_x += iter_step; iter_y -= iter_step;
                }
                if (iter_y < y1) break;
                this->addSqr(iter_x, iter_y, 1);
            }
        }
    }

    void antiAliasing(int x0, int y0, int x1, int y1)
    {
        float dx = abs(x1 - x0);
        float dy = abs(y1 - y0);
        float slope;
        (dx == 0)? slope = _size : slope = dy/dx;

        float iter_x = x0; float iter_y = y0;

        if (slope <= 1)
        {
            while (iter_x < x1 && y1 > y0)
            {
                float a = iter_y - floor(iter_y);
                this->addSqr(iter_x, floor(iter_y), 1 - a);
                this->addSqr(iter_x, floor(iter_y) + 1, a);
                iter_x ++; iter_y += slope;
            }

            while (iter_x < x1 && y1 < y0)
            {
                float a = -(iter_y - floor(iter_y));
                this->addSqr(iter_x, floor(iter_y), 1 - a);
                this->addSqr(iter_x, floor(iter_y) + 1, a);
                iter_x ++; iter_y -= slope;
            }

            while (iter_x > x1 && y1 > y0)
            {
                float a = iter_y - floor(iter_y);
                this->addSqr(iter_x, floor(iter_y), 1 - a);
                this->addSqr(iter_x, floor(iter_y) + 1, a);
                iter_x --; iter_y += slope;
            }

            while (iter_x > x1 && y1 < y0)
            {
                float a = -(iter_y - floor(iter_y));
                this->addSqr(iter_x, floor(iter_y), 1 - a);
                this->addSqr(iter_x, floor(iter_y) + 1, a);
                iter_x --; iter_y -= slope;
            }
        }

        else if (slope > 1)
        {
            while (iter_y < y1 && x1 > x0)
            {
                float a = iter_x - floor(iter_x);
                this->addSqr(floor(iter_x), iter_y, 1 - a);
                this->addSqr(floor(iter_x) + 1, iter_y, a);
                iter_x += dx/dy; iter_y ++;
            }

            while (iter_y < y1 && x1 < x0)
            {
                float a = -(iter_x - floor(iter_x));
                this->addSqr(floor(iter_x), iter_y, 1 - a);
                this->addSqr(floor(iter_x) + 1, iter_y, a);
                iter_x -= dx/dy; iter_y ++;
            }

            while (iter_y > y1 && x1 < x0)
            {
                float a = -(iter_x - floor(iter_x));
                this->addSqr(floor(iter_x), iter_y, 1 - a);
                this->addSqr(floor(iter_x) + 1, iter_y, a);
                iter_x -= dx/dy; iter_y --;
            }

            while (iter_y > y1 && x1 > x0)
            {
                float a = iter_x - floor(iter_x);
                this->addSqr(floor(iter_x), iter_y, 1 - a);
                this->addSqr(floor(iter_x) + 1, iter_y, a);
                iter_x += dx/dy; iter_y --;
            }
        }
    }

private:
    float _w; float _h;
    int _size;
    float _step;

    vector<Sqr> _sqrVector;
};

#endif