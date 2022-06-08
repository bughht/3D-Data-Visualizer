#include "pcd.h"

PCD::PCD()
{

}

void PCD::load(QString path){
    QFile f(path);
    bool flag=f.open(QIODevice::ReadOnly);
    if(flag==false){
        coutt<<"Unable to load File";
        return;
    }
    double x,y,z;
    QTextStream t(&f);
    while(!t.atEnd()){
        t>>x>>y>>z;
        points.append(Pos3(x,y,z));
    }
    f.close();
    update();
}

void PCD::save(QString path){
    QFile f(path);
    //coutt<<path;
    bool flag=f.open(QIODevice::WriteOnly);
    if(flag==false){
        coutt<<"Unable to save File";
        return;
    }
    QTextStream t(&f);
    //t.setRealNumberNotation(QTextStream::FixedNotation);
    t.setRealNumberPrecision(15);
    QVector<Pos3>::iterator iter;

    for(iter=points.begin();iter!=points.end();iter++){
        t<<iter->x<<" "<<iter->y<<" "<<iter->z<<"\n";
    }
    f.close();
}
