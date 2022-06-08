#include "model.h"

Model::Model()
{
    x_min=0;
    x_max=0;
    y_min=0;
    y_max=0;
    z_min=0;
    z_max=0;
    pointnum=0;
}

void Model::SwitchYZ(void){
    QVector<Pos3>::iterator iter;
    for(iter=points.begin();iter!=points.end();iter++){
        iter->SwitchYZ();
    }
    update();
}

double Model::cal_max_min(int axis, int type){
    QVector<Pos3>::iterator iter;
    double out;
    switch (type) {
    case 0:
        out=1000000.0;
        break;
    case 1:
        out=-1000000.0;
        break;
    }
    for(iter=points.begin();iter!=points.end();iter++){
        switch (axis) {
        case 0:
            if(type==0){
                double xx=iter->x;
                out=xx<out?xx:out;
            }
            else{
                double xx=iter->x;
                out=xx>out?xx:out;
            }
            break;

        case 1:
            if(type==0){
                double xx=iter->y;
                out=xx<out?xx:out;
            }
            else{
                double xx=iter->y;
                out=xx>out?xx:out;
            }
            break;

        case 2:
            if(type==0){
                double xx=iter->z;
                out=xx<out?xx:out;
            }
            else{
                double xx=iter->z;
                out=xx>out?xx:out;
            }
            break;
        }
    }
    return out;
}

void Model::update(void){
    pointnum=points.size();
    AABB[0]=x_min=cal_max_min(0,0);
    AABB[1]=x_max=cal_max_min(0,1);
    AABB[2]=y_min=cal_max_min(1,0);
    AABB[3]=y_max=cal_max_min(1,1);
    AABB[4]=z_min=cal_max_min(2,0);
    AABB[5]=z_max=cal_max_min(2,1);
    cal_center();
    cal_mcenter();
}

void Model::cal_center(void){
    center=Pos3((x_max+x_min)/2,(y_max+y_min)/2,(z_max+z_min)/2);
}

void Model::cal_mcenter(void){
    double xs,ys,zs;
    xs=ys=zs=0;
    QVector<Pos3>::iterator iter;
    for(iter=points.begin();iter!=points.end();iter++){
        xs+=iter->x;
        ys+=iter->y;
        zs+=iter->z;
    }
    mcenter=Pos3(xs/pointnum,ys/pointnum,zs/pointnum);
}

void Model::Showpoints(void){
    int i;
    coutt<<"PointNum: "<<pointnum;
    if(pointnum<10){
        for(i=0;i<pointnum;i++)
            points[i].showall();
        return;
    }
    for(i=0;i<4;i++)
        points[i].showall();
    qDebug()<<"...";
    for(i=points.size()-3;i<points.size();i++)
        points[i].showall();
}

void Model::ShowAABB(void){
    int i;
    for(i=0;i<6;i++)
        qDebug()<<AABB[i];
}

void Model::Translate(double dx, double dy, double dz){
    QVector<Pos3>::iterator iter;
    for(iter=points.begin();iter!=points.end();iter++){
        iter->x+=dx;
        iter->y+=dy;
        iter->z+=dz;
    }
    update();
}

//void Model::load(QString path){}
//void Model::save(QString path){}

Model::~Model(){

}
