#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>
#include <cmath>

#include "point.h"
#include "matrix_multiplication.h"

using namespace std;

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

        updateVerticeMatrix();
        saveOriginVertice();
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
        // _center.x += x;
        // _center.y += y;
        // _center.z += z;
        
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

        updateVerticeMatrix();
    }

    void rotation(float x, float y, float z, float angle)
    {
        float l = sqrt((x*x) + (y*y) + (z*z));
        l = sqrt((l*l) + (z*z));

        x /= l;
        y /= l;
        z /= l;

        float cosc = cos(angle);
        float sinc = sin(angle);

        float rm[3][3] = {{    cosc+(1-cosc)*x*x,   (1-cosc)*x*y-sinc*z, (1-cosc)*x*z+sinc*y},
                          {  (1-cosc)*x*y+sinc*z,     cosc+(1-cosc)*y*y, (1-cosc)*y*z-sinc*x},
                          {(1-cosc)*x*z-(sinc*y), (1-cosc)*z*y+(sinc)*x,   cosc+(1-cosc)*z*z}};

        matrixMultiplication(rm, _verticeMatrix, _answerMatrix); 

        assignAnswerMatrix();
        updateVerticeMatrix();
    }

    // void rotation(float anglex, float angley, float anglez)
    // {
    //     if (anglex != 0.0f)
    //     {
    //         // 單獨對 X 軸旋轉
    //         float rx[3][3] = {{1,                  0,                   0},
    //                           {0, float(cos(anglex)), -float(sin(anglex))},
    //                           {0, float(sin(anglex)), float(cos(anglex))}};

    //         matrixMultiplication(rx, _verticeMatrix, _answerMatrix);          
    //     }

    //     if (angley != 0.0f)
    //     {
    //         // 單獨對 Y 軸旋轉
    //         float ry[3][3] = {{float(cos(angley)), 0, -float(sin(angley))},
    //                           {                 0, 1,                   0},
    //                           {float(sin(angley)), 0, float(cos(angley))}};

    //         matrixMultiplication(ry, _verticeMatrix, _answerMatrix);
    //     }

    //     if (anglez != 0.0f)
    //     {
    //         // 單獨對 Z 軸旋轉
    //         float rz[3][3] = {{float(cos(anglez)) , float(sin(anglez)), 0},
    //                           {-float(sin(anglez)), float(cos(anglez)), 0},
    //                           {                  0,                  0, 1}};

    //         matrixMultiplication(rz, _verticeMatrix, _answerMatrix); 
    //     }

    //     assignAnswerMatrix();
    //     updateVerticeMatrix();
    // }

    void scale(float sizex, float sizey, float sizez)
    {
        float scaleMatrix[3][3] = {{sizex, 0.0f, 0.0f}, {0.0f, sizey, 0.0f}, {0.0f, 0.0f, sizez}};

        matrixMultiplication(scaleMatrix, _verticeMatrix, _answerMatrix); 

        assignAnswerMatrix();
        updateVerticeMatrix();
    }

    void reset()
    {
        assignOringin();
    }

private:
    Point _center; float _length;
    Point _vectorA; Point _vectorB; Point _vectorC;
    Point _verticeA; Point _verticeB; Point _verticeC; Point _verticeD;
    Point _verticeE; Point _verticeF; Point _verticeG; Point _verticeH;
    float _verticeMatrix[3][8];
    float _answerMatrix[3][8];

    float _originVertice[3][8];

    void updateVerticeMatrix()
    {
        _verticeMatrix[0][0] = _verticeA.x; _verticeMatrix[1][0] = _verticeA.y; _verticeMatrix[2][0] = _verticeA.z; // A
        _verticeMatrix[0][1] = _verticeB.x; _verticeMatrix[1][1] = _verticeB.y; _verticeMatrix[2][1] = _verticeB.z; // B
        _verticeMatrix[0][2] = _verticeC.x; _verticeMatrix[1][2] = _verticeC.y; _verticeMatrix[2][2] = _verticeC.z; // C
        _verticeMatrix[0][3] = _verticeD.x; _verticeMatrix[1][3] = _verticeD.y; _verticeMatrix[2][3] = _verticeD.z; // D
        _verticeMatrix[0][4] = _verticeE.x; _verticeMatrix[1][4] = _verticeE.y; _verticeMatrix[2][4] = _verticeE.z; // E
        _verticeMatrix[0][5] = _verticeF.x; _verticeMatrix[1][5] = _verticeF.y; _verticeMatrix[2][5] = _verticeF.z; // F
        _verticeMatrix[0][6] = _verticeG.x; _verticeMatrix[1][6] = _verticeG.y; _verticeMatrix[2][6] = _verticeG.z; // G
        _verticeMatrix[0][7] = _verticeH.x; _verticeMatrix[1][7] = _verticeH.y; _verticeMatrix[2][7] = _verticeH.z; // H
    }

    void assignAnswerMatrix()
    {
        _verticeA.x = _answerMatrix[0][0]; _verticeA.y = _answerMatrix[1][0]; _verticeA.z = _answerMatrix[2][0]; // A
        _verticeB.x = _answerMatrix[0][1]; _verticeB.y = _answerMatrix[1][1]; _verticeB.z = _answerMatrix[2][1]; // B
        _verticeC.x = _answerMatrix[0][2]; _verticeC.y = _answerMatrix[1][2]; _verticeC.z = _answerMatrix[2][2]; // C
        _verticeD.x = _answerMatrix[0][3]; _verticeD.y = _answerMatrix[1][3]; _verticeD.z = _answerMatrix[2][3]; // D
        _verticeE.x = _answerMatrix[0][4]; _verticeE.y = _answerMatrix[1][4]; _verticeE.z = _answerMatrix[2][4]; // E
        _verticeF.x = _answerMatrix[0][5]; _verticeF.y = _answerMatrix[1][5]; _verticeF.z = _answerMatrix[2][5]; // F
        _verticeG.x = _answerMatrix[0][6]; _verticeG.y = _answerMatrix[1][6]; _verticeG.z = _answerMatrix[2][6]; // G
        _verticeH.x = _answerMatrix[0][7]; _verticeH.y = _answerMatrix[1][7]; _verticeH.z = _answerMatrix[2][7]; // H
    }

    void saveOriginVertice()
    {
        _originVertice[0][0] = _verticeA.x; _originVertice[1][0] = _verticeA.y; _originVertice[2][0] = _verticeA.z; // A
        _originVertice[0][1] = _verticeB.x; _originVertice[1][1] = _verticeB.y; _originVertice[2][1] = _verticeB.z; // B
        _originVertice[0][2] = _verticeC.x; _originVertice[1][2] = _verticeC.y; _originVertice[2][2] = _verticeC.z; // C
        _originVertice[0][3] = _verticeD.x; _originVertice[1][3] = _verticeD.y; _originVertice[2][3] = _verticeD.z; // D
        _originVertice[0][4] = _verticeE.x; _originVertice[1][4] = _verticeE.y; _originVertice[2][4] = _verticeE.z; // E
        _originVertice[0][5] = _verticeF.x; _originVertice[1][5] = _verticeF.y; _originVertice[2][5] = _verticeF.z; // F
        _originVertice[0][6] = _verticeG.x; _originVertice[1][6] = _verticeG.y; _originVertice[2][6] = _verticeG.z; // G
        _originVertice[0][7] = _verticeH.x; _originVertice[1][7] = _verticeH.y; _originVertice[2][7] = _verticeH.z; // H
    }

    void assignOringin()
    {
        _verticeA.x = _originVertice[0][0]; _verticeA.y = _originVertice[1][0]; _verticeA.z = _originVertice[2][0]; // A
        _verticeB.x = _originVertice[0][1]; _verticeB.y = _originVertice[1][1]; _verticeB.z = _originVertice[2][1]; // B
        _verticeC.x = _originVertice[0][2]; _verticeC.y = _originVertice[1][2]; _verticeC.z = _originVertice[2][2]; // C
        _verticeD.x = _originVertice[0][3]; _verticeD.y = _originVertice[1][3]; _verticeD.z = _originVertice[2][3]; // D
        _verticeE.x = _originVertice[0][4]; _verticeE.y = _originVertice[1][4]; _verticeE.z = _originVertice[2][4]; // E
        _verticeF.x = _originVertice[0][5]; _verticeF.y = _originVertice[1][5]; _verticeF.z = _originVertice[2][5]; // F
        _verticeG.x = _originVertice[0][6]; _verticeG.y = _originVertice[1][6]; _verticeG.z = _originVertice[2][6]; // G
        _verticeH.x = _originVertice[0][7]; _verticeH.y = _originVertice[1][7]; _verticeH.z = _originVertice[2][7]; // H
    }
};
#endif
