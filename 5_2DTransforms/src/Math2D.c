#include "Math2D.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

struct Matrix3x3 *m3Create()
{
    struct Matrix3x3 *m3 = (struct Matrix3x3 *)calloc(1, sizeof(struct Matrix3x3));

    m3->matrix[0][0] = 1;
    m3->matrix[1][1] = 1;
    m3->matrix[2][2] = 1;

    return m3;
}

struct Matrix3x3 *m3Rotate(double angulo)
{
    struct Matrix3x3 *m3 = m3Create();

    double ang = angulo * PI / 180;

    m3->matrix[0][0] = cos(ang);
    m3->matrix[0][1] = -sin(ang);

    m3->matrix[1][0] = sin(ang);
    m3->matrix[1][1] = cos(ang);

    return m3;
}

struct Matrix3x3 *m3Trasnlate(double x, double y)
{
    struct Matrix3x3 *m3 = m3Create();

    m3->matrix[0][2] = x;
    m3->matrix[1][2] = y;

    return m3;
}

struct Matrix3x3 *m3Scale(double scale)
{
    struct Matrix3x3 *m3 = m3Create();

    m3->matrix[0][0] = scale;
    m3->matrix[1][1] = scale;

    return m3;
}

struct Matrix3x3 *m3Multiply(struct Matrix3x3 *m31, struct Matrix3x3 *m32)
{
    struct Matrix3x3 *m3 = m3Create();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                m3->matrix[i][j] += m31->matrix[i][k] * m32->matrix[k][j];
            }
        }
    }

    return m3;
}

void m3Free(struct Matrix3x3 *m3)
{
    free(m3);
}

struct Point3 *p3Create(double x, double y)
{
    return (struct Point3 *)calloc(1, sizeof(struct Point3));
}

void p3Dot(struct Point3 *p3, struct Matrix3x3 *m3)
{
    p3->x = (m3->matrix[0][0] * p3->x) + (m3->matrix[0][1] * p3->y) + (m3->matrix[0][2] * p3->w);
    p3->y = (m3->matrix[1][0] * p3->x) + (m3->matrix[1][1] * p3->y) + (m3->matrix[1][2] * p3->w);
    p3->w = (m3->matrix[2][0] * p3->x) + (m3->matrix[2][1] * p3->y) + (m3->matrix[2][2] * p3->w);
}

void p3Free(struct Point3 *p3)
{
    free(p3);
}