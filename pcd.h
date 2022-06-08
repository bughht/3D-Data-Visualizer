#ifndef PCD_H
#define PCD_H

#include "model.h"
#include<QDebug>
#include<QDataStream>
#include<QFile>
#include<qobject.h>

//PCD类
class PCD : public Model,public QObject
{
public:
    PCD();
    void load(QString path);
    void save(QString path);
};

#endif // PCD_H
