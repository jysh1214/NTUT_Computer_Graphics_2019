#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "vertex.h"
#include "face.h"
#include "matrix.h"

using namespace std;

class Object
{
public:
    Object(vector<Vertex> &vdata, vector<Vertex> &fdata, string renderMode, string colorMode);
    virtual ~Object(){}
    void draw();
    void rotation(float x, float y, float z, float angle);

    void setShadeMode(string shadeMode);
    void setRenderMode(string renderMode);
    void setColorMode(string colorMode);

    int _depthsize;

private:
    void subdivision(float v1_x, float v1_y, float v1_z , 
        float v2_x, float v2_y, float v2_z , float v3_x, float v3_y, float v3_z, int d);

    int _vertexNumber;
    int _faceNumber;

    struct matrix<float> * _vertexMatrix;

    vector<Vertex> _vertex;
    vector<Vertex> _face;

    string _shadeMode;
    string _renderMode; 
    string _colorMode;
};

#endif