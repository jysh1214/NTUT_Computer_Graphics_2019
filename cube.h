#include <GL/glut.h>

using namespace std;

struct Point
{
    float x; float y; float z;
};

Point vecAdd(Point a, Point b)
{
    a.x += b.x; a.y += b.y; a.z += b.z;
    return a;
}

class Cube
{
public:
    Cube(float x, float y, float z, float length): _length(length)
    {
        _center.x = x; _center.y = y; _center.z = z;
        
        _verticeA.x = _center.x;
        _verticeA.y = _center.y;
        _verticeA.z = _center.z;

        _verticeB.x = _center.x + _length;
        _verticeB.y = _center.y;
        _verticeB.z = _center.z;

        _verticeC.x = _center.x;
        _verticeC.y = _center.y + _length;
        _verticeC.z = _center.z;

        _verticeD.x = _center.x + _length;  
        _verticeD.y = _center.y + _length;
        _verticeD.z = _center.z ;

        _verticeE.x = _center.x;
        _verticeE.y = _center.y;
        _verticeE.z = _center.z + _length;

        _verticeF.x = _center.x + _length;
        _verticeF.y = _center.y;
        _verticeF.z = _center.z + _length;

        _verticeG.x = _center.x;
        _verticeG.y = _center.y + _length;
        _verticeG.z = _center.z + _length;

        _verticeH.x = _center.x + _length;
        _verticeH.y = _center.y + _length;
        _verticeH.z = _center.z + _length; 
    }

    virtual ~Cube(){}

    void draw()
    {
        glPushMatrix();

        /* A面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        /* A面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
        glEnd();

        /* B面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
        glEnd();

        /* B面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
        glEnd();

        /* C面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
        glEnd();

        /* C面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
        glEnd();

        /* D面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        /* D面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd(); 

        /* E面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        /* E面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeF.x, _verticeF.y, _verticeF.z); // F
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        /* F面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        /* F面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeG.x, _verticeG.y, _verticeG.z); // G
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeH.x, _verticeH.y, _verticeH.z); // H
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glBegin(GL_LINES);
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();        

        glPopMatrix();
    }

    void move(float x, float y, float z)
    {
        _center.x += x;
        _center.y += y;
        _center.z += z;
        
        _verticeA.x += x;
        _verticeA.y += y;
        _verticeA.z += z;

        _verticeB.x += x;
        _verticeB.y += y;
        _verticeB.z += z;

        _verticeC.x += x;
        _verticeC.y += y;
        _verticeC.z += z;

        _verticeD.x += x;
        _verticeD.y += y;
        _verticeD.z += z;

        _verticeE.x += x;
        _verticeE.y += y;
        _verticeE.z += z;

        _verticeF.x += x;
        _verticeF.y += y;
        _verticeF.z += z;


        _verticeG.x += x;
        _verticeG.y += y;
        _verticeG.z += z;

        _verticeH.x += x;
        _verticeH.y += y;
        _verticeH.z += z;
    }

    void rotation(float anglex, float angley, float anglez)
    {
        // 單獨對 X 軸旋轉
        float rx[3][3] = {{1, 0, 0}, 
        {0, float(cos(anglex)), float(sin(anglex))}, 
        {0, -float(sin(anglex)), float(cos(anglex))}};

        // 單獨對 Y 軸旋轉
        float ry[3][3] = {{float(cos(angley)), 0, -float(sin(angley))}, 
        {0, 1, 0}, 
        {float(sin(angley)), 0, float(cos(angley))}};

        // 單獨對 Z 軸旋轉
        float rz[3][3] = {{float(cos(anglez)), float(sin(anglez)), 0}, 
        {-float(sin(anglez)), float(cos(anglez)), 0}, 
        {0, 0, 1}};

        float newPoint[3];

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _center.x) + (rx[i][1] * _center.y) + (rx[i][2] * _center.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _center.x) + (ry[i][1] * _center.y) + (ry[i][2] * _center.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _center.x) + (rz[i][1] * _center.y) + (rz[i][2] * _center.z);
            }
        }

        _center.x = newPoint[0];
        _center.y = newPoint[1];
        _center.z = newPoint[2];

        // A
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeA.x) + (rx[i][1] * _verticeA.y) + (rx[i][2] * _verticeA.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeA.x) + (ry[i][1] * _verticeA.y) + (ry[i][2] * _verticeA.z);
            }
        }

        if (anglez != 0)
        { 
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeA.x) + (rz[i][1] * _verticeA.y) + (rz[i][2] * _verticeA.z);
            }
        }

        _verticeA.x = newPoint[0];
        _verticeA.y = newPoint[1];
        _verticeA.z = newPoint[2];


        // B
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeB.x) + (rx[i][1] * _verticeB.y) + (rx[i][2] * _verticeB.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeB.x) + (ry[i][1] * _verticeB.y) + (ry[i][2] * _verticeB.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeB.x) + (rz[i][1] * _verticeB.y) + (rz[i][2] * _verticeB.z);
            }
        }

        _verticeB.x = newPoint[0];
        _verticeB.y = newPoint[1];
        _verticeB.z = newPoint[2];


        // C
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeC.x) + (rx[i][1] * _verticeC.y) + (rx[i][2] * _verticeC.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeC.x) + (ry[i][1] * _verticeC.y) + (ry[i][2] * _verticeC.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeC.x) + (rz[i][1] * _verticeC.y) + (rz[i][2] * _verticeC.z);
            }
        }

        _verticeC.x = newPoint[0];
        _verticeC.y = newPoint[1];
        _verticeC.z = newPoint[2];


        // D
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeD.x) + (rx[i][1] * _verticeD.y) + (rx[i][2] * _verticeD.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeD.x) + (ry[i][1] * _verticeD.y) + (ry[i][2] * _verticeD.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeD.x) + (rz[i][1] * _verticeD.y) + (rz[i][2] * _verticeD.z);
            }
        }

        _verticeD.x = newPoint[0];
        _verticeD.y = newPoint[1];
        _verticeD.z = newPoint[2];


        // E
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeE.x) + (rx[i][1] * _verticeE.y) + (rx[i][2] * _verticeE.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeE.x) + (ry[i][1] * _verticeE.y) + (ry[i][2] * _verticeE.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeE.x) + (rz[i][1] * _verticeE.y) + (rz[i][2] * _verticeE.z);
            }
        }

        _verticeE.x = newPoint[0];
        _verticeE.y = newPoint[1];
        _verticeE.z = newPoint[2];


        // F
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeF.x) + (rx[i][1] * _verticeF.y) + (rx[i][2] * _verticeF.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeF.x) + (ry[i][1] * _verticeF.y) + (ry[i][2] * _verticeF.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeF.x) + (rz[i][1] * _verticeF.y) + (rz[i][2] * _verticeF.z);
            }
        }

        _verticeF.x = newPoint[0];
        _verticeF.y = newPoint[1];
        _verticeF.z = newPoint[2];


        // G
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeG.x) + (rx[i][1] * _verticeG.y) + (rx[i][2] * _verticeG.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeG.x) + (ry[i][1] * _verticeG.y) + (ry[i][2] * _verticeG.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeG.x) + (rz[i][1] * _verticeG.y) + (rz[i][2] * _verticeG.z);
            }
        }

        _verticeG.x = newPoint[0];
        _verticeG.y = newPoint[1];
        _verticeG.z = newPoint[2];


        // H
        for (int i=0; i<2; i++) newPoint[i] = 0.0f;

        if (anglex != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rx[i][0] * _verticeH.x) + (rx[i][1] * _verticeH.y) + (rx[i][2] * _verticeH.z);
            }            
        }

        if (angley != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (ry[i][0] * _verticeH.x) + (ry[i][1] * _verticeH.y) + (ry[i][2] * _verticeH.z);
            }
        }

        if (anglez != 0)
        {
            for (int i=0; i<=2; i++)
            {
               newPoint[i] = (rz[i][0] * _verticeH.x) + (rz[i][1] * _verticeH.y) + (rz[i][2] * _verticeH.z);
            }
        }

        _verticeH.x = newPoint[0];
        _verticeH.y = newPoint[1];
        _verticeH.z = newPoint[2];
    }

    void scale()
    {
        
    }

private:
    Point _center; float _length;
    // Point _org; 
    Point _vectorA; Point _vectorB; Point _vectorC;
    Point _verticeA; Point _verticeB; Point _verticeC; Point _verticeD;
    Point _verticeE; Point _verticeF; Point _verticeG; Point _verticeH;
};
