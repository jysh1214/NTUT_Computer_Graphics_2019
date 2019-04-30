#ifndef FUNC_H
#define FUNC_H

#include <iostream>

using namespace std;

class Func
{
public:
    Func(){} 
    Func(int x0, int y0, int x1, int y1): _x0(x0), _y0(y0), _x1(x1), _y1(y1)
    {
        a=0; b=0;
        // ax + b = y
        if (x0 == x1)
        {
            
        }
        else if (y0 == y1)
        {
            a = 0;
            b = y0;
        }
        else
        {   
            float dx = (x0-x1);
            float dy = (y0-y1);
            a = dy/dx;
            b = -x0*a + y0;
        }
    }

    virtual ~Func(){}

    void showFunc()
    {
        cout<<_x0<<", "<<_y0<<", "<<_x1<<", "<<_y1<<"; "<<a<<"*x + "<<b<<" = y"<<endl;
    }

    bool isLeftSide(float x, float y)
    {
        if (_x0 == _x1)
        {
            if (_y1 > _y0)
                return (x <= _x0);
            else
                return (x >= _x0);
        }
        else if (_y0 == _y1) 
        {
            if (_x1 > _x0)
                return (y >= _y0);
            else
                return (y <= _y0);
        }
        else
        {
            if (_x1 > _x0)
                return y >= (a*x+b);
            else
                return y <= (a*x+b);
        }
    }

    float a; float b;

private:
    int _x0; int _y0; int _x1; int _y1;
};

#endif
