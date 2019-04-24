#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

#include "object.h"

using namespace std;

bool is_number(string s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && (isdigit(*it) || (*it)=='-' || (*it)=='.')) ++it;
    return !s.empty() && it==s.end();
}

Object::Object(string filepath, string renderMode, string colorMode, bool boundingBox)
{
    _vertexNumber = 0;
    _faceNumber = 0;

    _renderMode = renderMode;
    _colorMode = colorMode;
    _boundingBox = boundingBox;

    parseFile(filepath);

    for (int i=0; i<_vertexNumber; i++)
    {
        _vertexMatrix[0][i] = _vertex[i].x;
        _vertexMatrix[1][i] = _vertex[i].y;
        _vertexMatrix[2][i] = _vertex[i].z;
        _vertex[i].w = 1;
        _vertexMatrix[3][i] = _vertex[i].w;
    }

    float max_x = _vertexMatrix[0][0]; float min_x = _vertexMatrix[0][0];
    float max_y = _vertexMatrix[1][0]; float min_y = _vertexMatrix[1][0];
    float max_z = _vertexMatrix[2][0]; float min_z = _vertexMatrix[2][0];

    for (int i=0; i<_vertexNumber; i ++)
    {
        // max
        if (_vertexMatrix[0][i]>max_x) max_x=_vertexMatrix[0][i];
        if (_vertexMatrix[1][i]>max_y) max_y=_vertexMatrix[1][i];
        if (_vertexMatrix[2][i]>max_z) max_z=_vertexMatrix[2][i];

        // min
        if (_vertexMatrix[0][i]<min_x) min_x=_vertexMatrix[0][i];
        if (_vertexMatrix[1][i]<min_y) min_y=_vertexMatrix[1][i];
        if (_vertexMatrix[2][i]<min_z) min_z=_vertexMatrix[2][i];
    }

    // 添加bounding box所需訊息至_vertexMatrix最後面
    // A min_x, min_y, min_z
    _vertexMatrix[0][_vertexNumber+0] = min_x;
    _vertexMatrix[1][_vertexNumber+0] = min_y;
    _vertexMatrix[2][_vertexNumber+0] = min_z;

    // B max_x, min_y, min_z
    _vertexMatrix[0][_vertexNumber+1] = max_x;
    _vertexMatrix[1][_vertexNumber+1] = min_y;
    _vertexMatrix[2][_vertexNumber+1] = min_z;

    // C max_x, max_y, min_z
    _vertexMatrix[0][_vertexNumber+2] = max_x;
    _vertexMatrix[1][_vertexNumber+2] = max_y;
    _vertexMatrix[2][_vertexNumber+2] = min_z;

    // D min_x, max_y, min_z
    _vertexMatrix[0][_vertexNumber+3] = min_x;
    _vertexMatrix[1][_vertexNumber+3] = max_y;
    _vertexMatrix[2][_vertexNumber+3] = min_z;

    // E min_x, min_y, max_z
    _vertexMatrix[0][_vertexNumber+4] = min_x;
    _vertexMatrix[1][_vertexNumber+4] = min_y;
    _vertexMatrix[2][_vertexNumber+4] = max_z;

    // F max_x, min_y, max_z
    _vertexMatrix[0][_vertexNumber+5] = max_x;
    _vertexMatrix[1][_vertexNumber+5] = min_y;
    _vertexMatrix[2][_vertexNumber+5] = max_z;

    // G max_x, max_y, max_z
    _vertexMatrix[0][_vertexNumber+6] = max_x;
    _vertexMatrix[1][_vertexNumber+6] = max_y;
    _vertexMatrix[2][_vertexNumber+6] = max_z;

    // H min_x, max_y, max_z
    _vertexMatrix[0][_vertexNumber+7] = min_x;
    _vertexMatrix[1][_vertexNumber+7] = max_y;
    _vertexMatrix[2][_vertexNumber+7] = max_z;

    // 利用bounding box做正規化
    for (int i=0; i<_vertexNumber + 8; i++)
    {
        _vertexMatrix[0][i] = ((_vertexMatrix[0][i]-min_x)/(max_x-min_x) * 2) - 1;
        _vertexMatrix[1][i] = ((_vertexMatrix[1][i]-min_y)/(max_y-min_y) * 2) - 1;
        _vertexMatrix[2][i] = ((_vertexMatrix[2][i]-min_z)/(max_z-min_z) * 2) - 1;
    }
}

void Object::draw()
{
    glPushMatrix();
    
    if (_colorMode == "Red") glColor3f( 1, 0, 0);
    else if (_colorMode == "Green") glColor3f( 0, 1, 0);
    else if (_colorMode == "Blue") glColor3f( 0, 0, 1);
   
    for (int j=0; j<_faceNumber; j++)
    {
        vector<int> v = _face[j].getVertex(); // vertex編號 v[0], v[1], v[2], ...

        for (vector<int>::iterator it = v.begin() ; it != v.end(); ++it)
        {
            // Point
            if (_renderMode == "Point")
            {
                glPointSize(3.0);
                glBegin(GL_POINTS); 
                    glVertex3f(_vertexMatrix[0][(*it)], _vertexMatrix[1][(*it)], _vertexMatrix[2][(*it)]); 
                glEnd();
            }

            // Line: 窮舉前兩個點和其他所有點的組合
            else if (_renderMode == "Line")
            {
                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][v[0]], _vertexMatrix[1][v[0]], _vertexMatrix[2][v[0]]);
                    glVertex3f(_vertexMatrix[0][v[1]], _vertexMatrix[1][v[1]], _vertexMatrix[2][v[1]]);
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][v[0]], _vertexMatrix[1][v[0]], _vertexMatrix[2][v[0]]);
                    glVertex3f(_vertexMatrix[0][(*it)], _vertexMatrix[1][(*it)], _vertexMatrix[2][(*it)]);
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][v[1]], _vertexMatrix[1][v[1]], _vertexMatrix[2][v[1]]);
                    glVertex3f(_vertexMatrix[0][(*it)], _vertexMatrix[1][(*it)], _vertexMatrix[2][(*it)]);
                glEnd();
            }

            // Face: 窮舉前兩個點和其他所有點的組合
            else if (_renderMode == "Face")
            {
                glBegin(GL_TRIANGLES);
                    glVertex3f(_vertexMatrix[0][v[0]], _vertexMatrix[1][v[0]], _vertexMatrix[2][v[0]]);
                    glVertex3f(_vertexMatrix[0][v[1]], _vertexMatrix[1][v[1]], _vertexMatrix[2][v[1]]);
                    glVertex3f(_vertexMatrix[0][(*it)], _vertexMatrix[1][(*it)], _vertexMatrix[2][(*it)]);
                glEnd();
            }
            
            // Bounding Box
            if (_boundingBox == true)
            {
                // A min_x, min_y, min_z; 0
                // B max_x, min_y, min_z; 1
                // C max_x, max_y, min_z; 2
                // D min_x, max_y, min_z; 3

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+0],
                               _vertexMatrix[1][_vertexNumber+0],
                               _vertexMatrix[2][_vertexNumber+0]); // A
                    glVertex3f(_vertexMatrix[0][_vertexNumber+1],
                               _vertexMatrix[1][_vertexNumber+1],
                               _vertexMatrix[2][_vertexNumber+1]); // B
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+1], 
                               _vertexMatrix[1][_vertexNumber+1], 
                               _vertexMatrix[2][_vertexNumber+1]); // B
                    glVertex3f(_vertexMatrix[0][_vertexNumber+2],
                               _vertexMatrix[1][_vertexNumber+2], 
                               _vertexMatrix[2][_vertexNumber+2]); // C
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+2],
                               _vertexMatrix[1][_vertexNumber+2], 
                               _vertexMatrix[2][_vertexNumber+2]); // C
                    glVertex3f(_vertexMatrix[0][_vertexNumber+3],
                               _vertexMatrix[1][_vertexNumber+3], 
                               _vertexMatrix[2][_vertexNumber+3]); // D
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+3],
                               _vertexMatrix[1][_vertexNumber+3], 
                               _vertexMatrix[2][_vertexNumber+3]); // D
                    glVertex3f(_vertexMatrix[0][_vertexNumber+0], 
                               _vertexMatrix[1][_vertexNumber+0],
                               _vertexMatrix[2][_vertexNumber+0]); // A
                glEnd();

                // E min_x, min_y, max_z; 4
                // F max_x, min_y, max_z; 5
                // G max_x, max_y, max_z; 6
                // H min_x, max_y, max_z; 7

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+4], 
                               _vertexMatrix[1][_vertexNumber+4],
                               _vertexMatrix[2][_vertexNumber+4]); // E
                    glVertex3f(_vertexMatrix[0][_vertexNumber+5], 
                               _vertexMatrix[1][_vertexNumber+5],
                               _vertexMatrix[2][_vertexNumber+5]); // F
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+5], 
                               _vertexMatrix[1][_vertexNumber+5],
                               _vertexMatrix[2][_vertexNumber+5]); // F
                    glVertex3f(_vertexMatrix[0][_vertexNumber+6], 
                               _vertexMatrix[1][_vertexNumber+6],
                               _vertexMatrix[2][_vertexNumber+6]); // G
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+6], 
                               _vertexMatrix[1][_vertexNumber+6],
                               _vertexMatrix[2][_vertexNumber+6]); // G
                    glVertex3f(_vertexMatrix[0][_vertexNumber+7], 
                               _vertexMatrix[1][_vertexNumber+7],
                               _vertexMatrix[2][_vertexNumber+7]); // H
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+7], 
                               _vertexMatrix[1][_vertexNumber+7],
                               _vertexMatrix[2][_vertexNumber+7]); // H
                    glVertex3f(_vertexMatrix[0][_vertexNumber+4], 
                               _vertexMatrix[1][_vertexNumber+4],
                               _vertexMatrix[2][_vertexNumber+4]); // E
                glEnd();

                // ----------------------------------------------------

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+0], 
                               _vertexMatrix[1][_vertexNumber+0],
                               _vertexMatrix[2][_vertexNumber+0]); // A
                    glVertex3f(_vertexMatrix[0][_vertexNumber+4], 
                               _vertexMatrix[1][_vertexNumber+4],
                               _vertexMatrix[2][_vertexNumber+4]); // E
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+1], 
                               _vertexMatrix[1][_vertexNumber+1], 
                               _vertexMatrix[2][_vertexNumber+1]); // B
                    glVertex3f(_vertexMatrix[0][_vertexNumber+5], 
                               _vertexMatrix[1][_vertexNumber+5],
                               _vertexMatrix[2][_vertexNumber+5]); // F
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+2],
                               _vertexMatrix[1][_vertexNumber+2], 
                               _vertexMatrix[2][_vertexNumber+2]); // C
                    glVertex3f(_vertexMatrix[0][_vertexNumber+6], 
                               _vertexMatrix[1][_vertexNumber+6],
                               _vertexMatrix[2][_vertexNumber+6]); // G
                glEnd();

                glBegin(GL_LINES);
                    glVertex3f(_vertexMatrix[0][_vertexNumber+3],
                               _vertexMatrix[1][_vertexNumber+3], 
                               _vertexMatrix[2][_vertexNumber+3]); // D
                    glVertex3f(_vertexMatrix[0][_vertexNumber+7], 
                               _vertexMatrix[1][_vertexNumber+7],
                               _vertexMatrix[2][_vertexNumber+7]); // H
                glEnd();
            }
        }
    }
    
    glPopMatrix();
}

void Object::translate(float x, float y, float z)
{
    float translateMatrix[4][_vertexNumber + 8];

    for (int j=0; j<_vertexNumber + 8; j++)
    {
        translateMatrix[0][j] = x;
        translateMatrix[1][j] = y;
        translateMatrix[2][j] = z;
        
        translateMatrix[3][j] = 0;
    }

    int N = 4; int M = _vertexNumber + 8;

    for (int i=0; i<N ; i++)
    {
        for (int j=0; j<M; j++)
        {
            _answerMatrix[i][j] = _vertexMatrix[i][j] + translateMatrix[i][j]; 
        }
    }

    assignAnswer();
}

void Object::rotation(float x, float y, float z, float angle)
{
    float l = sqrt((x*x) + (y*y));
    l = sqrt((l*l) + (z*z));

    x /= l;
    y /= l;
    z /= l;

    float cosc = cos(angle);
    float sinc = sin(angle);

    float rotationMatrix[4][4] = 
    {{    cosc+(1-cosc)*x*x,   (1-cosc)*x*y-sinc*z, (1-cosc)*x*z+sinc*y, 0.0f},
     {  (1-cosc)*x*y+sinc*z,     cosc+(1-cosc)*y*y, (1-cosc)*y*z-sinc*x, 0.0f},
     {(1-cosc)*x*z-(sinc*y), (1-cosc)*z*y+(sinc)*x,   cosc+(1-cosc)*z*z, 0.0f},
     {                 0.0f,                  0.0f,                0.0f, 1.0f}};

    matrixMultiplication(rotationMatrix); 
    assignAnswer();
}

void Object::scale(float sizex, float sizey, float sizez)
{
    float scaleMatrix[4][4] = {{sizex,  0.0f,  0.0f, 0.0f}, 
                               { 0.0f, sizey,  0.0f, 0.0f}, 
                               { 0.0f,  0.0f, sizez, 0.0f},
                               { 0.0f,  0.0f,  0.0f, 1.0f}};

    matrixMultiplication(scaleMatrix);
    assignAnswer();
}

void Object::setRenderMode(string renderMode)
{
    _renderMode = renderMode;
}

void Object::setColorMode(string colorMode)
{
    _colorMode = colorMode;
}

void Object::setBoundingBox(bool boundingBox)
{
    _boundingBox = boundingBox;
}

void Object::parseFile(string filepath)
{
    ifstream myfile;
    myfile.open(filepath);

    //read the file as pure string
    stringstream strStream;
    strStream << myfile.rdbuf();     //read the file
    string myFile = strStream.str(); //str holds the content of the file

    string function = "";
    string number;
    vector<float> arg;
    int p = 0;

    bool function_check = false;
    bool begin = false;

    for (string::size_type i = 0; i < myFile.size(); ++i)
    {
        if (myFile[i] == 'v')
        {
            function += "v";
        }
        
        else if (myFile[i] == 'f' && begin)
        {
            function += "f";
        }

        else if (myFile[i] == '#') // 遇到註解直接下一行
        {
            while(myFile[i]!='\n') i++;
        }

        else if (myFile[i] == ' ')
        {
            if (!function_check) function += " ";
            string number = myFile.substr(p, i-p);

            if (is_number(number))
            {
                arg.push_back(stof(number));
            }

            if (function == "v " && myFile[i-1] == 'v')
            {
                function = "vertex";
                function_check = true;
                begin = true; // read first v
            }
            else if (function == "f " && myFile[i-1] == 'f')
            {
                function = "face";
                function_check = true;
            }
            else if (!function_check)
            {
                function = "";
            }

            p = i + 1;
        }

        else if (myFile[i]=='\n')
        {
            string number = myFile.substr(p, i-p);

            if (is_number(number))
            {
                arg.push_back(stof(number));
            }

            if (function == "vertex")
            {
                Vertex v;
                v.x = arg[0]; v.y = arg[1]; v.z = arg[2];
                _vertex.push_back(v);
                arg.clear();
                _vertexNumber ++; // 紀錄頂點數
            } 
            else if (function == "face")
            {
                Face f;
                for (vector<float>::iterator it = arg.begin() ; it != arg.end(); ++it)
                {
                    // 面添加 點編號-1
                    f.append((*it)-1);
                }
                _face.push_back(f);
                arg.clear();
                _faceNumber ++; // 紀錄邊數
            }

            function_check = false;
            function = "";
            p = i + 1;
        }

        else
        {

        }
    }
    myfile.close();
}

void Object::matrixMultiplication(float (& a)[4][4])
{
    int N = 4; int M = 4; int R = _vertexNumber + 8;

    for (int i=0; i<N ; i++)
    {
        for (int j=0; j<R; j++)
        {
            _answerMatrix[i][j] = 0;
            for (int k=0; k<M; k++)
            {
                _answerMatrix[i][j] += a[i][k] * _vertexMatrix[k][j]; 
            } 
        }
    }
}

void Object::assignAnswer()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<_vertexNumber + 8; j++)
        {
            _vertexMatrix[i][j] = _answerMatrix[i][j];
        }
    }
}

