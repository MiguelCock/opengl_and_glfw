typedef struct Matrix4x4 {
    double matrix[4][4];
};

Matrix4x4* m4CreateIdent();

Matrix4x4* m4CreateProyection();

Matrix4x4* m4CreateRotationX();

Matrix4x4* m4CreateRotationY();

Matrix4x4* m4CreateRotationZ();

Matrix4x4* m4Translation();

Matrix4x4* m4Scaling();