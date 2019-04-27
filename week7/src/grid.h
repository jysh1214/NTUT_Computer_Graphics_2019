#ifndef GRID_H
#define GRID_H

#include <GL/glut.h>    
#include <iostream>
#include <vector>
#include <math.h>
#include <map>

#include "sqr.h"
#include "point.h"

using namespace std;

class Grid
{
public:
    Grid(float w, float h, int size): _w(w), _h(h), _size(size)
    {
        _step = int(w/size);
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

    void midPoint(int x0, int y0, int x1, int y1, bool anti_aliasing)
    {
        // 座標中心化
        x0 /= _step; x0 = x0 * _step + _step/2;
        y0 /= _step; y0 = y0 * _step + _step/2;
        x1 /= _step; x1 = x1 * _step + _step/2;
        y1 /= _step; y1 = y1 * _step + _step/2;

        float dx = abs(x1 - x0);
        float dy = abs(y1 - y0);
        float slope;
        (dx == 0)? slope = _size : slope = dy/dx;

        float iter_x = x0; float iter_y = y0;
        float x_iter_step; float y_iter_step;
        float aa_x_iter_step; float aa_y_iter_step;
        float line_pos;

        if (x0 < x1 && y0 <= y1) // 右上 & x
        {
            x_iter_step = _step; y_iter_step = _step;
            if (slope <= 1) {aa_y_iter_step = _step * slope;}
            if (slope > 1) {aa_x_iter_step = _step * dx/dy;}
        }
        else if (x1 <= x0 && y0 < y1) // 左上 & y
        {
            x_iter_step = -_step; y_iter_step = _step;
            if (slope < 1) {aa_y_iter_step = _step * slope;}
            if (slope >= 1) {aa_x_iter_step = -_step * dx/dy;}
        }
        else if (x0 <= x1 && y1 < y0) // 右下 & -y
        {
            x_iter_step = _step; y_iter_step = -_step;
            if (slope <= 1) {aa_y_iter_step = -_step * slope;}
            if (slope > 1) {aa_x_iter_step = _step * dx/dy;}

        }
        else if (x1 < x0 && y1 <= y0) // 左下 & -x
        {
            x_iter_step = -_step; y_iter_step = -_step;
            if (slope < 1) {aa_y_iter_step = -_step * slope;}
            if (slope >= 1) {aa_x_iter_step = -_step * dx/dy;}
        }

        if (slope <= 1)
        {
            line_pos = y0;
            int d = 2*dy-dx; int delE = 2*dy; int delNE = 2*(dy-dx);
            while (abs(iter_x-x1) >= _step)
            {
                if (d <= 0)
                {
                    d += delE; iter_x += x_iter_step;
                }
                else
                {
                    d += delNE; iter_x += x_iter_step; iter_y += y_iter_step;
                }
                line_pos += aa_y_iter_step;

                if (anti_aliasing)
                {
                    /* 判斷線穿過格子上半部或下半部 */
                    if (line_pos >= iter_y) // 上半部
                    {
                        float a = line_pos - iter_y; a /= _step;
                        this->addSqr(iter_x, iter_y, 1 - a);
                        if (iter_x != x1) 
                            this->addSqr(iter_x, iter_y + _step, a);
                    }
                    else // 下半部
                    {
                        float a = _step - (iter_y-line_pos); a /= _step;
                        this->addSqr(iter_x, iter_y - _step, 1 - a);
                        if (iter_x != x1) 
                            this->addSqr(iter_x, iter_y, a);
                    }
                }

                if (abs(iter_x-x1) < _step) break;
                if (!anti_aliasing) this->addSqr(iter_x, iter_y, 1);
            }
        }
        else
        {
            line_pos = x0;
            int d = 2*dx-dy; int delE = 2*dx; int delNE = 2*(dx-dy);
            while (abs(iter_y-y1) >= _step)
            {
                if (d <= 0)
                {
                    d += delE; iter_y += y_iter_step;
                }
                else
                {
                    d += delNE; iter_x += x_iter_step; iter_y += y_iter_step;
                }
                line_pos += aa_x_iter_step;

                if (anti_aliasing)
                {
                    /* 判斷線穿過格子右半部或左半部 */
                    if (line_pos >= iter_x) // 右半部
                    {
                        float a = line_pos - iter_x; a /= _step;
                        this->addSqr(iter_x, iter_y, 1 - a);
                        if (iter_y != y1) 
                            this->addSqr(iter_x + _step, iter_y, a);
                    }
                    else // 左半部
                    {
                        float a = _step - (iter_x-line_pos); a /= _step;
                        this->addSqr(iter_x - _step, iter_y, 1 - a);
                        if (iter_y != y1) 
                            this->addSqr(iter_x, iter_y, a);
                    }
                }

                if (abs(iter_y-y1) < _step) break;
                this->addSqr(iter_x, iter_y, 1);
            }
        }
    }

    void antiAliasing(int x0, int y0, int x1, int y1)
    {
        // 座標中心化
        x0 /= _step; x0 = x0 * _step + _step/2;
        y0 /= _step; y0 = y0 * _step + _step/2;
        x1 /= _step; x1 = x1 * _step + _step/2;
        y1 /= _step; y1 = y1 * _step + _step/2;

        float dx = abs(x1 - x0);
        float dy = abs(y1 - y0);
        float slope;
        (dx == 0)? slope = _size : slope = dy/dx;

        float iter_x = x0; float iter_y = y0;

        float x_iter_step; float y_iter_step;

        if (x0 < x1 && y0 <= y1) // 右上 & x
        {
            if (slope <= 1) {x_iter_step = _step; y_iter_step = _step * slope;}
            if (slope > 1) {x_iter_step = _step * dx/dy; y_iter_step = _step;}
        }
        else if (x1 <= x0 && y0 < y1) // 左上 & y
        {
            if (slope < 1) {x_iter_step = -_step; y_iter_step = _step * slope;}
            if (slope >= 1) {x_iter_step = -_step * dx/dy; y_iter_step = _step;}
        }
        else if (x0 <= x1 && y1 < y0) // 右下 & -y
        {
            if (slope <= 1) {x_iter_step = _step; y_iter_step = -_step * slope;}
            if (slope > 1) {x_iter_step = _step * dx/dy; y_iter_step = -_step;}
        }
        else if (x1 < x0 && y1 <= y0) // 左下 & -x
        {
            if (slope < 1) {x_iter_step = -_step; y_iter_step = -_step * slope;}
            if (slope >= 1) {x_iter_step = -_step * dx/dy; y_iter_step = -_step;}
        }

        if (slope == 0)
        {
            while (abs(iter_x-x1) >= _step)
            {
                this->addSqr(iter_x, iter_y, 1);
                iter_x += x_iter_step;
            }
        }
        else if (slope == _size)
        {
            while (abs(iter_y-y1) >= _step)
            {
                this->addSqr(iter_x, iter_y, 1);
                iter_y += y_iter_step;
            }
        }
        else
        {
            if (slope <= 1)
            {
                while (abs(iter_x-x1) >= _step)
                {
                    /*  判斷線在格子上半部或下半部：
                        上半部 取 本身 和 上面那格
                        下半部 取 下方那格 和 本身
                    */
                    unsigned int sqr_number = (iter_y-_step/2)/_step;
                    float center = _step*sqr_number + _step/2;
                    float a = iter_y - center; a /= _step;

                    this->addSqr(iter_x, iter_y - _step/2, 1 - a);
                    if (iter_x != x1) 
                        this->addSqr(iter_x, iter_y + _step/2, a);
                    iter_x += x_iter_step; iter_y += y_iter_step; 
                }
            }
            else
            {
                while (abs(iter_y-y1) >= _step)
                {
                    /*  判斷線在格子右半部或左半部：
                        右半部 取 本身 和 右邊那格
                        左半部 取 左邊那格 和 本身
                    */
                    unsigned int sqr_number = (iter_x-_step/2)/_step;
                    float center = _step*sqr_number + _step/2;
                    float a = iter_x - center; a /= _step;

                    this->addSqr(iter_x - _step/2, iter_y, 1 - a);
                    if (iter_y != y1) 
                        this->addSqr(iter_x + _step/2, iter_y, a);
                    iter_x += x_iter_step; iter_y += y_iter_step; 
                }
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