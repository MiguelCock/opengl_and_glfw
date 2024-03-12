struct Matrix4x4
{
    double matrix[4][4];
};

struct Matrix4x4 *m4CreateIdent();

struct Matrix4x4 *m4CreateProyection();

struct Matrix4x4 *m4CreateRX();

struct Matrix4x4 *m4CreateRY();

struct Matrix4x4 *m4CreateRZ();

struct Matrix4x4 *m4Translation();

struct Matrix4x4 *m4Scaling();

struct Point4
{
    double x;
    double y;
    double z;
    double w;
};

struct Point4 *p4Create(double x, double y, double z);