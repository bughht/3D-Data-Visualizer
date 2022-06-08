#ifndef MESH_H
#define MESH_H

#include "model.h"
#include<QDataStream>
#include<QFile>
#include<math.h>

//MESH类
class MESH : public Model
{
public:
    MESH();
    void load(QString path);
    void save(QString path);
    long facenum;
    double surfacearea;
    QVector<QVector<long>> face;
    void SwitchYZ(void);
    QVector<Pos3> pf;
private:
    double TRI_S(Pos3 &a,Pos3 &b,Pos3 &c);
};

#endif // MESH_H
