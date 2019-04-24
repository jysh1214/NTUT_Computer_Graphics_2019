#ifndef GRID_H
#define GRID_H

#include <GL/glut.h>    
#include <iostream>
#include <vector>
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

        // if (_sqrp!=nullptr) _sqrp->draw();
        for (unsigned int i=0; i<_sqrVector.size(); i++)
        {
            _sqrVector[i].draw();
        }
    }

    void addSqr(float x, float y)
    {
        // 找中心座標
        x /= _step;
        y /= _step;

        int m_x = (int(x) - _size/2) * _step;
        int m_y = (int(y) - _size/2) * _step;

        Sqr s = Sqr(m_x, m_y, _step); // 給中心座標和寬度
        _sqrVector.push_back(s);
    }

    void showPos(float x, float y)
    {
        x /= _step;
        y /= _step;

        cout<<"pos: "<<int(x) - _size/2<<", "<<-(int(y) - _size/2)<<endl;
    }

private:
    float _w; float _h;
    int _size;
    float _step;

    vector<Sqr> _sqrVector;
    // Sqr * _sqrp;
};

#endif