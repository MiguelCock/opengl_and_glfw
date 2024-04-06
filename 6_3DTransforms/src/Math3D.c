#include "Math3D.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846

mat4 m4CreateIdent()
{
    mat4 m4;
    memset(&m4, 0, sizeof(mat4));

    m4.m[0][0] = 1;
    m4.m[1][1] = 1;
    m4.m[2][2] = 1;
    m4.m[3][3] = 1;

    return m4;
}

mat4 m4CreateProyection(double fov, double aspect, double near, double far)
{
    mat4 m4 = m4CreateIdent();

    double tanFov = tan(fov / 2);

    m4.m[0][0] = aspect / tanFov;
    m4.m[1][1] = 1 / tanFov;
    m4.m[2][2] = far / (far - near);
    m4.m[2][3] = (-far + near) / (far - near);
    m4.m[3][2] = 1.;
    m4.m[3][3] = 0;

    //m4.m[3][2] = 1/near;

    return m4;
}

mat4 m4CreateRX(double angle)
{
    mat4 m4 = m4CreateIdent();

    double ang = angle * PI / 180;

    m4.m[1][1] = cos(ang);
    m4.m[1][2] = -sin(ang);

    m4.m[2][1] = sin(ang);
    m4.m[2][2] = cos(ang);

    return m4;
}

mat4 m4CreateRY(double angle)
{
    mat4 m4 = m4CreateIdent();

    double ang = angle * PI / 180;

    m4.m[0][0] = cos(ang);
    m4.m[0][2] = sin(ang);

    m4.m[2][0] = -sin(ang);
    m4.m[2][2] = cos(ang);

    return m4;
}

mat4 m4CreateRZ(double angle)
{
    mat4 m4 = m4CreateIdent();

    double ang = angle * PI / 180;

    m4.m[0][0] = cos(ang);
    m4.m[0][1] = -sin(ang);

    m4.m[1][0] = sin(ang);
    m4.m[1][1] = cos(ang);

    return m4;
}

mat4 m4Translation(double x, double y, double z)
{
    mat4 m4 = m4CreateIdent();

    m4.m[0][3] = x;
    m4.m[1][3] = y;
    m4.m[2][3] = z;

    return m4;
}

mat4 m4Scaling(double scale)
{
    mat4 m4 = m4CreateIdent();

    m4.m[0][0] = scale;
    m4.m[1][1] = scale;
    m4.m[2][2] = scale;

    return m4;
}

vec4 vec4Create(double x, double y, double z)
{
    return (vec4){x: x, y: y, z: z, w: 1};
}

vec4 vec4Dot(vec4* p, mat4* m)
{
    vec4 result;

    result.x = (m->m[0][0] * p->x) + (m->m[0][1] * p->y) + (m->m[0][2] * p->z) + (m->m[0][3] * p->w);
    result.y = (m->m[1][0] * p->x) + (m->m[1][1] * p->y) + (m->m[1][2] * p->z) + (m->m[1][3] * p->w);
    result.z = (m->m[2][0] * p->x) + (m->m[2][1] * p->y) + (m->m[2][2] * p->z) + (m->m[2][3] * p->w);
    result.w = (m->m[3][0] * p->x) + (m->m[3][1] * p->y) + (m->m[3][2] * p->z) + (m->m[3][3] * p->w);

    return result;
}

vec4 vec4Sum(vec4 *p41, vec4 *p42)
{
    return (vec4){x: p41->x + p42->x, y: p41->y + p42->y, z: p41->z + p42->z, w: 1};;
}