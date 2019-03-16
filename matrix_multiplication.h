#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <string>

template <typename T, size_t ar, size_t al, size_t br, size_t bl, size_t cr, size_t cl>
void matrixMultiplication(T (& a)[ar][al], T (& b)[br][bl], T (& c)[cr][cl]) // NXM * MXR
{
    if (al != br || ar != cr || bl != cl)
    {
        throw std::string("Error.");
    }

    int N = ar; int M = br; int R = cl;

    for (int i=0; i<N ; i++)
    {
        for (int j=0; j<R; j++)
        {
            c[i][j] = 0;
            for (int k=0; k<M; k++)
            {
                c[i][j] += a[i][k] * b[k][j]; 
            } 
        }
    }
}
#endif