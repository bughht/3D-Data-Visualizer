#ifndef MODEL_H
#define MODEL_H
#include"pos3.h"
#include<QVector>
#include<QString>
#include<QFile>
#include<QDebug>
#define coutt qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

//模型基类
class Model
{
public:
    Model();
    Pos3 center;
    Pos3 mcenter;
    double AABB[6];
    virtual void SwitchYZ(void);
    void update(void);
    long pointnum;
    void Showpoints(void);
    void ShowAABB(void);
    void Translate(double dx,double dy,double dz);
    virtual ~Model();
    QVector<Pos3> points;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    double z_min;
    double z_max;
protected:
    double cal_max_min(int axis, int type);
    void cal_center(void);
    void cal_mcenter(void);
};

#endif // MODEL_H
