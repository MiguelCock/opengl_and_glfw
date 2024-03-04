struct Matrix3x3
{
    double matrix[3][3];
};

struct Matrix3x3 *m3Create();

void m3Rotate(struct Matrix3x3 *m3, double angulo);

void m3Trasnlate(struct Matrix3x3 *m3, double x, double y);

void m3Scale(struct Matrix3x3 *m3, double scale);

void m3Multiply(struct Matrix3x3 *m31, struct Matrix3x3 *m32);

void m3Free(struct Matrix3x3 *m3);

struct Point3
{
    double x;
    double y;
    double w;
};

struct Point3 *p3Create(double x, double y);

void p3Dot(struct Point3 *p3, struct Matrix3x3 *m3);

void p3Free(struct Point3 *p3);