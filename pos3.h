#ifndef POS3_H
#define POS3_H
#include<QDebug>

class Pos3
{
public:
    double x;
    double y;
    double z;
    Pos3();
    Pos3(double xx,double yy,double zz);
    Pos3 operator+(Pos3 &p2);
    Pos3 operator-(Pos3 &p2);
    Pos3 operator*(double n);
    friend Pos3 operator*(double n,Pos3 &p1);
    Pos3 operator+=(Pos3 &p2);
    Pos3 operator-=(Pos3 &p2);
    Pos3 operator*=(double n);
    void showall(void);
    void SwitchYZ(void);
};

#endif // POS3_H
