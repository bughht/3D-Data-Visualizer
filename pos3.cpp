#include "pos3.h"

Pos3::Pos3()
{
    x=0.0;
    y=0.0;
    z=0.0;
}

Pos3::Pos3(double xx,double yy,double zz){
    x=xx;
    y=yy;
    z=zz;
}

Pos3 Pos3::operator+(Pos3 &p2){
    return Pos3(x+p2.x,y+p2.y,z+p2.z);
}

Pos3 Pos3::operator-(Pos3 &p2){
    return Pos3(x-p2.x,y-p2.y,z-p2.z);
}

Pos3 Pos3::operator*(double n){
    return Pos3(x*n,y*n,z*n);
}

Pos3 operator*(double n, Pos3 &p1){
    return Pos3(p1.x*n,p1.y*n,p1.z*n);
}

Pos3 Pos3::operator+=(Pos3 &p2){
    return Pos3(x+p2.x,y+p2.y,z+p2.z);
}

Pos3 Pos3::operator-=(Pos3 &p2){
    return Pos3(x-p2.x,y-p2.y,z-p2.z);
}

Pos3 Pos3::operator*=(double n){
    return Pos3(x*n,y*n,z*n);
}

void Pos3::SwitchYZ(void){
    double t=y;
    y=z;
    z=t;
}

void Pos3::showall(void){
    qDebug()<<"x:\t"<<x<<"\ty:\t"<<y<<"\tz:\t"<<z;
}
