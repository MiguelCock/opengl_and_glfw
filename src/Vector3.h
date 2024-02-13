#include <math.h>

struct vec3 {
    double x,
    double y,
    double z
};

void v3Cross(vec3* v1, vec3* v2, vec3* v3) {
    
}

void v3Cross(vec3* v1, vec3* v2) {

}

double v3Norm(vec3* v1){
    return sqrt((v1->x * v1->x) + (v1->y * v1->y) (v1->z * v1->z));
}

void v3Normalize(vec3* v1, vec3* v2) {
    v2->x = v1->x/v3Norm(v1);
    v2->y = v1->y/v3Norm(v1);
    v2->z = v1->z/v3Norm(v1);
}

vec3* v3AllocNormalize(vec3* v1) {
    vec3* v2 = malloc(sizeof(vec3));
    
    v2->x = v1->x/v3Norm(v1);
    v2->y = v1->y/v3Norm(v1);
    v2->z = v1->z/v3Norm(v1);

    return v2;
}
