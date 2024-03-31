typedef struct
{
    double matrix[3][3];
} Matrix3x3;

Matrix3x3 m3Rotate(double angulo);

Matrix3x3 m3Trasnlate(double x, double y);

Matrix3x3 m3Scale(double scale);

Matrix3x3 m3Multiply(Matrix3x3 *m31, Matrix3x3 *m32);

typedef struct
{
    double x;
    double y;
    double w;
} Point3;

Point3 p3Create(double x, double y);

void p3Dot(Point3 *p3, Matrix3x3 *m3);
