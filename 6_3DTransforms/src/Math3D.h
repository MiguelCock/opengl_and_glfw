typedef struct
{
    double m[4][4];
} mat4;

mat4 m4CreateProyection(double fov, double aspect, double near, double far);

mat4 m4CreateRX(double angle);

mat4 m4CreateRY(double angle);

mat4 m4CreateRZ(double angle);

mat4 m4Translation(double x, double y, double z);

mat4 m4Scaling(double scale);

typedef struct
{
    double x;
    double y;
    double z;
    double w;
} vec4;

vec4 vec4Create(double x, double y, double z);
vec4 vec4Dot(vec4 *p4, mat4 *m4);
vec4 vec4Sum(vec4 *p41, vec4 *p42);