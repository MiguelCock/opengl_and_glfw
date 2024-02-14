#include "Vector3.h"

void v3Cross(struct vec3* v1, struct vec3* v2, struct vec3* v3) {
    
}

double v3Norm(struct vec3* v1){
    return sqrt((v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z));
}

void v3Normalize(struct vec3* v1, struct vec3* v2) {
    v2->x = v1->x/v3Norm(v1);
    v2->y = v1->y/v3Norm(v1);
    v2->z = v1->z/v3Norm(v1);
}

struct vec3* v3AllocNormalize(struct vec3* v1) {
    struct vec3* v2 = malloc(sizeof(struct vec3));
    
    v2->x = v1->x/v3Norm(v1);
    v2->y = v1->y/v3Norm(v1);
    v2->z = v1->z/v3Norm(v1);

    return v2;
}

void v3Dealloc(struct vec3* v) {
    free(v);
}