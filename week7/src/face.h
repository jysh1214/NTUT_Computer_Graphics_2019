#ifndef FACE_H
#define FACE_H

#include <vector>

#include "vertex.h"

using namespace std;

class Face
{
public:
    Face()
    {
        // 紀錄vertex編號
    }

    virtual ~Face(){}

    void append(int i)
    {
        _vertexList.push_back(i);
    }

    vector<int> getVertex()
    {
    	return _vertexList;
    }

private:
    vector<int> _vertexList;
};

#endif