#include <math.h>

typedef struct vec3 {
    double x;
    double y;
    double z;
};


void v3Cross(vec3* v1, vec3* v2, vec3* v3);

double v3Norm(vec3* v1);

void v3Normalize(vec3* v1, vec3* v2);

vec3* v3AllocNormalize(vec3* v1);

void v3Dealloc(vec3* v);

