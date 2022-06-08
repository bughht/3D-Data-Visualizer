#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include <mesh.h>
#include <model.h>
#include <pcd.h>
#include <pos3.h>
#include <mainwindow.h>

//3D QGLViewer画布
class Viewer : public QGLViewer
{
public:
  Viewer(QWidget *parent);
  PCD *mod1;
  MESH *mod2;

protected:
  virtual void draw();
  virtual QString helpString() const;
};

#endif // VIEWER_H
