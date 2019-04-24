#ifndef GRID_H
#define GRID_H

#include <GL/glut.h>    
#include <iostream>
#include <vector>
#include <map>

#include "dot.h"
#include "sqr.h"

using namespace std;

    
class Grid
{
public:
    Grid(float w, float h, int size): _w(w), _h(h), _size(size)
    {
        _step = w/size;
        _sqrp = nullptr;
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

        if (_sqrp!=nullptr) _sqrp->draw();

        // for (unsigned int i=0; i<_sqrVector.size(); i++)
        // {
        //     _sqrVector[i].draw();
        // }
    }

    void addSqr(float x, float y)
    {
        // 找中心座標
        x /= _step;
        y /= _step;

        int m_x = (int(x) - _size/2) * _step;// + _step/2;
        int m_y = (int(y) - _size/2) * _step;// + _step/2;

        Sqr * s = new Sqr(m_x, m_y, _step); // 給中心座標和寬度
        // _sqrVector.push_back(s);
        _sqrp = s;
    }

    void fillColor(int x, int y)
    {
         //glPushMatrix();

        // cout<<"pos: "<<x<<", "<<y<<endl;

        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, _pixel);
        cout << "R: " << (int)_pixel[0] << endl;
        cout << "G: " << (int)_pixel[1] << endl;
        cout << "B: " << (int)_pixel[2] << endl;
        cout << endl;

        if ((int)_pixel[0] == 255 && (int)_pixel[1] == 255 && (int)_pixel[2] == 255)
        {
            glColor3f(0, 1, 0);
            glPointSize(1.0);
            glBegin(GL_POINTS);
                    glVertex2f((x - 250 - _step/100)/50, 
                               -(y - 250 - _step/100)/50);
            glEnd();

            // glFlush();
            // glutSwapBuffers();

            //glPopMatrix();

            // glutPostRedisplay();

            fillColor(x + 1, y);
            // fillColor(x  -1, y);
        }
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
    unsigned char _pixel[4];

    // vector<Sqr> _sqrVector;
    Sqr * _sqrp;
};

#endif