#ifndef PYRAMID_H
#define PYRAMID_H

#include <GL/glut.h>
#include <iostream>

#include "point.h"
#include "matrix_add.h"
#include "matrix_multiplication.h"

using namespace std;
/*
A
BCDE
*/
class Pyramid
{
public:
    Pyramid(float x, float y, float z, float w, float length, float width, float height):
    _length(length), _width(width), _height(height)
    {
        _verticeC.x = x;
        _verticeC.y = y;
        _verticeC.z = z;
        _verticeC.w = w;

        _verticeB.x = x;
        _verticeB.y = y + length;
        _verticeB.z = z;
        _verticeB.w = w;

        _verticeD.x = x + width;
        _verticeD.y = y;
        _verticeD.z = z;
        _verticeD.w = w;

        _verticeE.x = x + width;
        _verticeE.y = y + length;
        _verticeE.z = z;
        _verticeE.w = w;

        _verticeA.x = x + float(width/2);
        _verticeA.y = y + float(length/2);
        _verticeA.z = z + height;
        _verticeA.w = w;

        updateVerticeMatrix();
        saveOriginVertice();
    }

    virtual ~Pyramid(){}

    void draw()
    {
        glPushMatrix();

        /* A面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        /* A面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        /* B面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        /* B面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        /* C面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        /* C面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        /* D面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        /* D面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeA.x, _verticeA.y, _verticeA.z); // A
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        /* E面 */
        glColor3f( 1, 0, 0);
        glBegin(GL_QUAD_STRIP);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
        glEnd();

        /* E面邊線 */
        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeC.x, _verticeC.y, _verticeC.z); // C
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
        glEnd();

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeD.x, _verticeD.y, _verticeD.z); // D
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E

        glColor3f( 1, 1, 0);
        glBegin(GL_LINES);
            glVertex3f( _verticeE.x, _verticeE.y, _verticeE.z); // E
            glVertex3f( _verticeB.x, _verticeB.y, _verticeB.z); // B
        glEnd();

        glPopMatrix();
    }

    void move(float x, float y, float z)
    {
        float translate[4][5];

        for (int j=0; j<5; j++)
        {
            translate[0][j] = x;
            translate[1][j] = y;
            translate[2][j] = z;
            
            translate[3][j] = 0;
        }

        try
        {
            matrixAdd(_verticeMatrix, translate, _answerMatrix);
        }
        catch (string e)
        {
            cout<<"Caught exception: "<<e<<endl;
        }

        assignAnswerMatrix();
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

        float rm[4][4] = {{    cosc+(1-cosc)*x*x,   (1-cosc)*x*y-sinc*z, (1-cosc)*x*z+sinc*y, 0.0f},
                          {  (1-cosc)*x*y+sinc*z,     cosc+(1-cosc)*y*y, (1-cosc)*y*z-sinc*x, 0.0f},
                          {(1-cosc)*x*z-(sinc*y), (1-cosc)*z*y+(sinc)*x,   cosc+(1-cosc)*z*z, 0.0f},
                          {                 0.0f,                  0.0f,                0.0f, 1.0f}};

        try
        {
            matrixMultiplication(rm, _verticeMatrix, _answerMatrix); 
        }
        catch (string e)
        {
            cout<<"Caught exception: "<<e<<endl;
        }

        assignAnswerMatrix();
        updateVerticeMatrix();
    }

    void scale(float sizex, float sizey, float sizez)
    {
        float scaleMatrix[4][4] = {{sizex,  0.0f,  0.0f, 0.0f}, 
                                   { 0.0f, sizey,  0.0f, 0.0f}, 
                                   { 0.0f,  0.0f, sizez, 0.0f},
                                   { 0.0f,  0.0f,  0.0f, 1.0f}};

        try
        {
            matrixMultiplication(scaleMatrix, _verticeMatrix, _answerMatrix); 
        }
        catch (string e)
        {
            cout<<"Caught exception: "<<e<<endl;
        }

        assignAnswerMatrix();
        updateVerticeMatrix();
    }

    void reset()
    {
        assignOringin();
    }

private:
    float _length; float _height; float _width; 
    Point _verticeA; Point _verticeB; Point _verticeC; Point _verticeD; Point _verticeE;  
    float _verticeMatrix[4][5];
    float _answerMatrix[4][5];

    float _originVertice[4][5];

    void updateVerticeMatrix()
    {
        // A
        _verticeMatrix[0][0] = _verticeA.x; 
        _verticeMatrix[1][0] = _verticeA.y; 
        _verticeMatrix[2][0] = _verticeA.z;
        _verticeMatrix[3][0] = _verticeA.w;

        // B
        _verticeMatrix[0][1] = _verticeB.x; 
        _verticeMatrix[1][1] = _verticeB.y; 
        _verticeMatrix[2][1] = _verticeB.z;
        _verticeMatrix[3][1] = _verticeB.w;

        // C
        _verticeMatrix[0][2] = _verticeC.x; 
        _verticeMatrix[1][2] = _verticeC.y; 
        _verticeMatrix[2][2] = _verticeC.z;
        _verticeMatrix[3][2] = _verticeC.w;

        // D
        _verticeMatrix[0][3] = _verticeD.x; 
        _verticeMatrix[1][3] = _verticeD.y; 
        _verticeMatrix[2][3] = _verticeD.z;
        _verticeMatrix[3][3] = _verticeD.w;

        // E
        _verticeMatrix[0][4] = _verticeE.x; 
        _verticeMatrix[1][4] = _verticeE.y; 
        _verticeMatrix[2][4] = _verticeE.z;
        _verticeMatrix[3][4] = _verticeE.w;
    }

    void assignAnswerMatrix()
    {
        // A
        _verticeA.x = _answerMatrix[0][0]; 
        _verticeA.y = _answerMatrix[1][0]; 
        _verticeA.z = _answerMatrix[2][0];
        _verticeA.w = _answerMatrix[3][0];

        // B
        _verticeB.x = _answerMatrix[0][1]; 
        _verticeB.y = _answerMatrix[1][1]; 
        _verticeB.z = _answerMatrix[2][1];
        _verticeB.w = _answerMatrix[3][1];

        // C
        _verticeC.x = _answerMatrix[0][2]; 
        _verticeC.y = _answerMatrix[1][2]; 
        _verticeC.z = _answerMatrix[2][2];
        _verticeC.w = _answerMatrix[3][2];

        // D
        _verticeD.x = _answerMatrix[0][3]; 
        _verticeD.y = _answerMatrix[1][3]; 
        _verticeD.z = _answerMatrix[2][3];
        _verticeD.w = _answerMatrix[3][3];

        // E
        _verticeE.x = _answerMatrix[0][4]; 
        _verticeE.y = _answerMatrix[1][4];
        _verticeE.z = _answerMatrix[2][4];
        _verticeE.w = _answerMatrix[3][4];
    }

    void saveOriginVertice()
    {
        // A
        _originVertice[0][0] = _verticeA.x; 
        _originVertice[1][0] = _verticeA.y; 
        _originVertice[2][0] = _verticeA.z;
        _originVertice[3][0] = _verticeA.w;

        // B
        _originVertice[0][1] = _verticeB.x; 
        _originVertice[1][1] = _verticeB.y; 
        _originVertice[2][1] = _verticeB.z;
        _originVertice[3][1] = _verticeB.w;

        // C
        _originVertice[0][2] = _verticeC.x; 
        _originVertice[1][2] = _verticeC.y; 
        _originVertice[2][2] = _verticeC.z;
        _originVertice[3][2] = _verticeC.w;

        // D
        _originVertice[0][3] = _verticeD.x; 
        _originVertice[1][3] = _verticeD.y; 
        _originVertice[2][3] = _verticeD.z;
        _originVertice[3][3] = _verticeD.w;

        // E
        _originVertice[0][4] = _verticeE.x; 
        _originVertice[1][4] = _verticeE.y; 
        _originVertice[2][4] = _verticeE.z;
        _originVertice[3][4] = _verticeE.w;
    }

void assignOringin()
    {
        _verticeA.x = _originVertice[0][0]; _verticeA.y = _originVertice[1][0]; _verticeA.z = _originVertice[2][0]; // A
        _verticeB.x = _originVertice[0][1]; _verticeB.y = _originVertice[1][1]; _verticeB.z = _originVertice[2][1]; // B
        _verticeC.x = _originVertice[0][2]; _verticeC.y = _originVertice[1][2]; _verticeC.z = _originVertice[2][2]; // C
        _verticeD.x = _originVertice[0][3]; _verticeD.y = _originVertice[1][3]; _verticeD.z = _originVertice[2][3]; // D
        _verticeE.x = _originVertice[0][4]; _verticeE.y = _originVertice[1][4]; _verticeE.z = _originVertice[2][4]; // E
    }
};

#endif
