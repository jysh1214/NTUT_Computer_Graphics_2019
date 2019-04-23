#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

#include "vertex.h"
#include "face.h"

using namespace std;

class Object
{
public:
    Object(string filepath, string renderMode, string colorMode, bool boundingBox);
    virtual ~Object(){}
    void draw();
    void translate(float x, float y, float z);
    void rotation(float x, float y, float z, float angle);
    void scale(float sizex, float sizey, float sizez);

    void setRenderMode(string renderMode);
    void setColorMode(string colorMode);
    void setBoundingBox(bool boundingBox);

private:
    void parseFile(string filepath);
    void matrixMultiplication(float (& a)[4][4]);
    void assignAnswer();

    int _vertexNumber; int _faceNumber;

    float * _vertexMatrix;
    float * _answerMatrix;

    vector<Vertex> _vertex;
    vector<Face> _face;

    string _renderMode; 
    string _colorMode;
    bool _boundingBox;
};

#endif
