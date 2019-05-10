#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

#include "object.h"

using namespace std;

Object::Object(vector<Vertex> &vdata, vector<Vertex> &fdata, string renderMode, string colorMode): _depthsize(1)
{
    _vertexNumber = vdata.size();
    _faceNumber = fdata.size();

    _renderMode = renderMode;
    _colorMode = colorMode;

    _vertexMatrix = new matrix<float>(3, _vertexNumber);

    for (int i=0; i<_vertexNumber; i++)
    {
        _vertexMatrix->data[0][i] = vdata[i].x;
        _vertexMatrix->data[1][i] = vdata[i].y;
        _vertexMatrix->data[2][i] = vdata[i].z;
    }

    _vertex = vdata;
    _face = fdata;

    // 利用bouding box 做正規化
    float max_x = _vertexMatrix->data[0][0]; float min_x = _vertexMatrix->data[0][0];
    float max_y = _vertexMatrix->data[1][0]; float min_y = _vertexMatrix->data[1][0];
    float max_z = _vertexMatrix->data[2][0]; float min_z = _vertexMatrix->data[2][0];

    for (int i=0; i<_vertexNumber; i ++)
    {
        // max
        if (_vertexMatrix->data[0][i]>max_x) max_x=_vertexMatrix->data[0][i];
        if (_vertexMatrix->data[1][i]>max_y) max_y=_vertexMatrix->data[1][i];
        if (_vertexMatrix->data[2][i]>max_z) max_z=_vertexMatrix->data[2][i];

        // min
        if (_vertexMatrix->data[0][i]<min_x) min_x=_vertexMatrix->data[0][i];
        if (_vertexMatrix->data[1][i]<min_y) min_y=_vertexMatrix->data[1][i];
        if (_vertexMatrix->data[2][i]<min_z) min_z=_vertexMatrix->data[2][i];
    }

    // 利用bounding box做正規化
    for (int i=0; i<_vertexNumber; i++)
    {
        _vertexMatrix->data[0][i] = ((_vertexMatrix->data[0][i]-min_x)/(max_x-min_x) * 2) - 1;
        _vertexMatrix->data[1][i] = ((_vertexMatrix->data[1][i]-min_y)/(max_y-min_y) * 2) - 1;
        _vertexMatrix->data[2][i] = ((_vertexMatrix->data[2][i]-min_z)/(max_z-min_z) * 2) - 1;
    }
}

void Object::draw()
{   
    if (_shadeMode == "Flat") glShadeModel(GL_FLAT);
    else if (_shadeMode == "Interpolate") glShadeModel(GL_SMOOTH);
    // else if (_shadeMode == "Subdivision")

    if (_colorMode == "Red") glColor3f( 1, 0, 0);
    else if (_colorMode == "Green") glColor3f( 0, 1, 0);
    else if (_colorMode == "Blue") glColor3f( 0, 0, 1);
   
    for (int j=0; j<_faceNumber; j++)
    {
        Vertex v = _face[j];
        // v.x: the number of first point
        // v.y: the number of second point
        // v.z: the number of thirt point

        float d1[3], d2[3], norm[3];
        for (int i=0; i<3; i++)
        {
            d1[i] = _vertexMatrix->data[i][v.x] - _vertexMatrix->data[i][v.y];
            d2[i] = _vertexMatrix->data[i][v.y] - _vertexMatrix->data[i][v.z];
        }

        norm[0] = d1[1]*d2[2] - d1[2]*d1[1];
        norm[1] = d1[2]*d2[0] - d1[0]*d1[2];
        norm[2] = d1[0]*d2[1] - d1[1]*d1[0];

        float nd = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);
        if (nd > 0) {norm[0] /= nd; norm[1] /= nd; norm[2] /= nd;}
        
        glNormal3f(norm[0], norm[1], norm[2]);

        if (_renderMode == "Point")
        {
            glPointSize(3.0);
            glBegin(GL_POINTS);
                glVertex3f(_vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x]);
                glVertex3f(_vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y]);
                glVertex3f(_vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z]);
            glEnd();
        }
        else if (_renderMode == "Line")
        {
            glBegin(GL_LINES);
                glVertex3f(_vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x]);
                glVertex3f(_vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y]);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(_vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y]);
                glVertex3f(_vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z]);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(_vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z]);
                glVertex3f(_vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x]);
            glEnd();
        }
        else if (_renderMode == "Face" && _shadeMode != "Subdivision")
        {
            glBegin(GL_TRIANGLES);
                glNormal3f(_vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x]);
                glVertex3f(_vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x]);
                glNormal3f(_vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y]);
                glVertex3f(_vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y]);
                glNormal3f(_vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z]);
                glVertex3f(_vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z]);
            glEnd();
        }
        else if (_renderMode == "Face" && _shadeMode == "Subdivision")
        {
            // glNormal3f(norm[0], norm[1], norm[2]);
            subdivision(
            _vertexMatrix->data[0][v.x], _vertexMatrix->data[1][v.x], _vertexMatrix->data[2][v.x],
            _vertexMatrix->data[0][v.y], _vertexMatrix->data[1][v.y], _vertexMatrix->data[2][v.y],
            _vertexMatrix->data[0][v.z], _vertexMatrix->data[1][v.z], _vertexMatrix->data[2][v.z], 
            _depthsize);
        }
    }
    // glFlush();
    glutPostRedisplay();
    glPopMatrix();
}

void Object::subdivision(float v1_x, float v1_y, float v1_z ,
    float v2_x, float v2_y, float v2_z , float v3_x, float v3_y, float v3_z, int d)
{
    if (d == 0)
    {
        glShadeModel(GL_SMOOTH);
        glBegin(GL_TRIANGLES);
            glNormal3f(v1_x, v1_y, v1_z);
            glVertex3f(v1_x, v1_y, v1_z);
            glNormal3f(v2_x, v2_y, v2_z);
            glVertex3f(v2_x, v2_y, v2_z);
            glNormal3f(v3_x, v3_y, v3_z);
            glVertex3f(v3_x, v3_y, v3_z);
        glEnd();
        glutPostRedisplay();
        return;
    }

    float v12_x; float v12_y; float v12_z;
    float v23_x; float v23_y; float v23_z;
    float v31_x; float v31_y; float v31_z;

    v12_x = (v1_x + v2_x)/2; v12_y = (v1_y + v2_y)/2; v12_z = (v1_z + v2_z)/2;
    v23_x = (v2_x + v3_x)/2; v23_y = (v2_y + v3_y)/2; v23_z = (v2_z + v3_z)/2;
    v31_x = (v3_x + v1_x)/2; v31_y = (v3_y + v1_y)/2; v31_z = (v3_z + v1_z)/2;

    float dd = sqrt(v12_x*v12_x + v12_y*v12_y + v12_z*v12_z);
    if (dd >0) {v12_x/=dd; v12_y/=dd; v12_z/=dd;}

    dd = sqrt(v23_x*v23_x + v23_y*v23_y + v23_z*v23_z);
    if (dd >0) {v23_x/=dd; v23_y/=dd; v23_z/=dd;}

    dd = sqrt(v31_x*v31_x + v31_y*v31_y + v31_z*v31_z);
    if (dd >0) {v31_x/=dd; v31_y/=dd; v31_z/=dd;}

    this->subdivision(v1_x, v1_y, v1_z,
        v12_x, v12_y, v12_z, v31_x, v31_y, v31_z, d-1);

    this->subdivision(v2_x, v2_y, v2_z,
        v23_x, v23_y, v23_z, v12_x, v12_y, v12_z, d-1);

    this->subdivision(v3_x, v3_y, v3_z,
        v31_x, v31_y, v31_z, v23_x, v23_y, v23_z, d-1);

    this->subdivision(v12_x, v12_y, v12_z,
        v23_x, v23_y, v23_z, v31_x, v31_y, v31_z, d-1);
}

void Object::translate(float x, float y, float z)
{
}

void Object::rotation(float x, float y, float z, float angle)
{
    struct matrix<float> * answerMatrix = new matrix<float>(3, _vertexNumber);

    float l = sqrt((x*x) + (y*y));
    l = sqrt((l*l) + (z*z));

    x /= l;
    y /= l;
    z /= l;

    float cosc = cos(angle);
    float sinc = sin(angle);

    float rotationMatrix[3][3] = 
    {{    cosc+(1-cosc)*x*x,   (1-cosc)*x*y-sinc*z, (1-cosc)*x*z+sinc*y},
    {  (1-cosc)*x*y+sinc*z,     cosc+(1-cosc)*y*y, (1-cosc)*y*z-sinc*x},
    {(1-cosc)*x*z-(sinc*y), (1-cosc)*z*y+(sinc)*x,   cosc+(1-cosc)*z*z}};

    int N = 3; int M = 3; int R = _vertexNumber;

    for (int i=0; i<N ; i++)
    {
        for (int j=0; j<R; j++)
        {
            answerMatrix->data[i][j] = 0;
            for (int k=0; k<M; k++)
            {
                answerMatrix->data[i][j] += rotationMatrix[i][k] * _vertexMatrix->data[k][j];
            } 
        }
    }

    // assign answer
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<_vertexNumber; j++)
        {
            _vertexMatrix->data[i][j] = answerMatrix->data[i][j];
        }
    }

}

void Object::scale(float sizex, float sizey, float sizez)
{
}

void Object::setShadeMode(string shadeMode)
{
    _shadeMode = shadeMode;
}

void Object::setRenderMode(string renderMode)
{
    _renderMode = renderMode;
}

void Object::setColorMode(string colorMode)
{
    _colorMode = colorMode;
}

