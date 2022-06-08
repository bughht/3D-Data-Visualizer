#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <pcd.h>
#include <mesh.h>
#include <QMessageBox>
#include <QLabel>
#include <QInputDialog>
#include <string>

namespace Ui {
class MainWindow;
}

//主窗口类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static PCD *m1;
    static MESH *m2;
    static short type;// 0:none, 1:pcd, 2:mesh
    static bool AABB_ON;//init false
    static bool grid_ON;//init true
    static bool center_on;//false
    static bool m_center_on;//false
    static bool surface_on;//false
    QLabel* minfo;


public Q_SLOTS:
    void load_f();
    void save_f();
    void save_t();
    void SwitchYZ_SLOT();
    void Translate_SLOT();
    void AABB_SLOT();
    void grid_SLOT();
    void Draw_Center();
    void Draw_m_Center();
    void change_statusbar();
    void change_Surface_Mesh();
    void close_file();

private:
    Ui::MainWindow *ui;
    QString filepath;
    void init_statusbar();

};

#endif // MAINWINDOW_H
