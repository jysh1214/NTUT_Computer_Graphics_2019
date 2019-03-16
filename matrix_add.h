#ifndef MATRIX_ADD_H
#define MATRIX_ADD_H

#include <string>

template <typename T, size_t ar, size_t al, size_t br, size_t bl, size_t cr, size_t cl>
void matrixAdd(T (& a)[ar][al], T (& b)[br][bl], T (& c)[cr][cl]) // NXM + NXM
{
    if (ar != br || al != bl || ar != cr || al != cl)
    {
        throw std::string("Error.");
    }

    int N = ar; int M = al;

    for (int i=0; i<N ; i++)
    {
        for (int j=0; j<M; j++)
        {
            c[i][j] = a[i][j] + b[i][j]; 
        }
    }
}
#endif