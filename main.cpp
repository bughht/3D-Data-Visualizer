#include <QGLViewer/qglviewer.h>
#include <QApplication>
#include <pos3.h>
#include <pcd.h>
#include <mesh.h>
#include <mainwindow.h>

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow Frame3d;
    Frame3d.setWindowTitle("3D Viewer");
    Frame3d.show();
    return a.exec();
}
