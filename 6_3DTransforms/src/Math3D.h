typedef struct
{
    double matrix[4][4];
} Matrix4x4;

Matrix4x4 m4CreateProyection();

Matrix4x4 m4CreateRX();

Matrix4x4 m4CreateRY();

Matrix4x4 m4CreateRZ();

Matrix4x4 m4Translation();

Matrix4x4 m4Scaling();

typedef struct
{
    double x;
    double y;
    double z;
    double w;
} Point4;

Point4 p4Create(double x, double y, double z);