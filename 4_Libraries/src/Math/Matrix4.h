struct Matrix4x4 {
    double matrix[4][4];
};

struct Matrix4x4* m4CreateIdent();

struct Matrix4x4* m4CreateProyection();

struct Matrix4x4* m4CreateRotationX();

struct Matrix4x4* m4CreateRotationY();

struct Matrix4x4* m4CreateRotationZ();

struct Matrix4x4* m4Translation();

struct Matrix4x4* m4Scaling();