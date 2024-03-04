struct vec3
{
    double x;
    double y;
    double z;
};

void v3Cross(struct vec3 *v1, struct vec3 *v2, struct vec3 *v3);

double v3Norm(struct vec3 *v1);

void v3Normalize(struct vec3 *v1, struct vec3 *v2);

struct vec3 *v3AllocNormalize(struct vec3 *v1);

void v3Dealloc(struct vec3 *v);
