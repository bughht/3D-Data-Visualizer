#include "mesh.h"

MESH::MESH()
{
    facenum=0;
    surfacearea=0;
}

void MESH::load(QString path){
    QFile f(path);
    coutt<<path;
    bool flag=f.open(QIODevice::ReadOnly);
    if(flag==false){
        coutt<<"Unable to load File";
        return;
    }
    QTextStream t(&f);
    QString Label;
    double px,py,pz;
    double fx,fy,fz;
    long pos1,pos2,pos3;
    long pf1,pf2,pf3;
    char bc;
    long bd;
    while(!t.atEnd()){
        t>>Label;
        if(Label=="v"){
            t>>px>>py>>pz;
            points.append(Pos3(px,py,pz));
        }
        else if(Label=="vn"){
            t>>fx>>fy>>fz;
            pf.append(Pos3(fx,fy,fz));
        }
        else if(Label=="f"){
            t>>pos1>>bc>>bd>>bc>>pf1>>pos2>>bc>>bd>>bc>>pf2>>pos3>>bc>>bd>>bc>>pf3;
            facenum++;
            //cout<<pf1<<pf2<<pf3;
            face.append(QVector<long>({pos1-1,pos2-1,pos3-1,pf1-1,pf2-1,pf3-1}));
            surfacearea+=TRI_S(points[pos1-1],points[pos2-1],points[pos3-1]);
        }
    }
    f.close();
    update();
}

void MESH::save(QString path){
    QFile f(path);
    bool flag=f.open(QIODevice::WriteOnly);
    if(flag==false){
        coutt<<"Unable to save File";
        return;
    }
    QTextStream t(&f);
    coutt<<path;
    t.setRealNumberPrecision(15);
    QVector<Pos3>::iterator iter;
    for(iter=points.begin();iter!=points.end();iter++)
        t<<"v "<<iter->x<<" "<<iter->y<<" "<<iter->z<<"\n";
    for(iter=pf.begin();iter!=pf.end();iter++)
        t<<"vn "<<iter->x<<" "<<iter->y<<" "<<iter->z<<"\n";
    QVector<QVector<long>>::iterator iter_o;
    for(iter_o=face.begin();iter_o!=face.end();iter_o++)
        t<<"f "<<(*iter_o)[0]+1<<"//"<<(*iter_o)[3]+1<<" "<<(*iter_o)[1]+1<<"//"<<(*iter_o)[4]+1<<" "<<(*iter_o)[2]+1<<"//"<<(*iter_o)[5]<<"\n";
    f.close();
}

void MESH::SwitchYZ(void){
    QVector<Pos3>::iterator iter;
    for(iter=points.begin();iter!=points.end();iter++){
        iter->SwitchYZ();
    }
    for(iter=pf.begin();iter!=pf.end();iter++){
        iter->SwitchYZ();
    }
    QVector<QVector<long>>::iterator iter_o;
    for(iter_o=face.begin();iter_o!=face.end();iter_o++){
        long tp,tn;
        tp=(*iter_o)[1];
        (*iter_o)[1]=(*iter_o)[2];
        (*iter_o)[2]=tp;
        tn=(*iter_o)[4];
        (*iter_o)[4]=(*iter_o)[5];
        (*iter_o)[5]=tn;
    }
    update();
}

double MESH::TRI_S(Pos3 &a,Pos3 &b,Pos3 &c){
    Pos3 v1=b-a;
    Pos3 v2=c-a;
    double s=(sqrt((v1.y*v2.z-v1.z*v2.y)*(v1.y*v2.z-v1.z*v2.y)+(v1.z*v2.x-v1.x*v2.z)*(v1.z*v2.x-v1.x*v2.z)+(v1.x*v2.y-v1.y*v2.z)*(v1.x*v2.y-v1.y*v2.z)))/2;
    return s;
}
