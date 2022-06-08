#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mesh.h"
#include "pcd.h"

PCD *MainWindow::m1=NULL;
MESH *MainWindow::m2=NULL;
short MainWindow::type=0;
bool MainWindow::AABB_ON=false;
bool MainWindow::grid_ON=true;
bool MainWindow::center_on=false;
bool MainWindow::m_center_on=false;
bool MainWindow::surface_on=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->setSizeGripEnabled(false);
    init_statusbar();

    type=0;
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(load_f()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(change_statusbar()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save_f()));
    connect(ui->actionsaveto,SIGNAL(triggered()),this,SLOT(save_t()));
    connect(ui->actionSwitchYZ,SIGNAL(triggered()),this,SLOT(SwitchYZ_SLOT()));
    connect(ui->actionSwitchYZ,SIGNAL(triggered()),this,SLOT(change_statusbar()));
    connect(ui->actionTranslate,SIGNAL(triggered()),this,SLOT(Translate_SLOT()));
    connect(ui->actionTranslate,SIGNAL(triggered()),this,SLOT(change_statusbar()));
    connect(ui->actionAABB,SIGNAL(triggered()),this,SLOT(AABB_SLOT()));
    connect(ui->actionGrid,SIGNAL(triggered()),this,SLOT(grid_SLOT()));
    connect(ui->actionCenter,SIGNAL(triggered()),this,SLOT(Draw_Center()));
    connect(ui->actionm_Center,SIGNAL(triggered()),this,SLOT(Draw_m_Center()));
    connect(ui->actionsurface_mesh,SIGNAL(triggered()),this,SLOT(change_Surface_Mesh()));
    connect(ui->actionclosefile,SIGNAL(triggered()),this,SLOT(close_file()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开文件
void MainWindow::load_f(){
    QString OpenFile;
    OpenFile=QFileDialog::getOpenFileName(this,"打开点云/网格模型文件","","Model Files(*.PCD *.obj)");
    QFileInfo fileinfo(OpenFile);
    if( fileinfo.suffix()=="PCD" ){
        filepath=fileinfo.absoluteFilePath();
        type=1;
        if(m1!=NULL){
            delete m1;
            m1=NULL;
        }
        if(m2!=NULL){
            delete m2;
            m2=NULL;
        }
        m1=new PCD;
        m1->load(filepath);
    }
    else if(fileinfo.suffix()=="obj"){
        filepath=fileinfo.absoluteFilePath();
        type=2;
        if(m1!=NULL){
            delete m1;
            m1=NULL;
        }
        if(m2!=NULL){
            delete m2;
            m2=NULL;
        }
        m2=new MESH;
        m2->load(filepath);
    }
    else{
        QMessageBox::warning(NULL, QStringLiteral("Error"), QStringLiteral("Please input supported file!"));
    }
}
//保存文件
void MainWindow::save_f(){
    if(type==1){
        m1->save(filepath);
    }
    else if(type==2){
        coutt<<'?';
        m2->save(filepath);
    }
}
//另存为文件
void MainWindow::save_t(){
    QString SaveFile;
    if(type==1){
        SaveFile=QFileDialog::getSaveFileName(this,"保存点云文件","","Model Files(*.PCD)",Q_NULLPTR, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(!SaveFile.isEmpty()){
            m1->save(SaveFile);
        }
    }
    if(type==2){
        SaveFile=QFileDialog::getSaveFileName(this,"保存网格模型文件","","Model Files(*.obj)",Q_NULLPTR, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(!SaveFile.isEmpty()){
            m2->save(SaveFile);
        }
    }
}
//交换YZ轴
void MainWindow::SwitchYZ_SLOT(){
    if(type==1){
        m1->SwitchYZ();
    }
    else if(type==2){
        m2->SwitchYZ();
    }
}
//位移
void MainWindow::Translate_SLOT(){
    bool dxok;
    double dx = QInputDialog::getDouble(this, tr("输入Δx"),
                                       tr("Δx:"), 0.0, -10000, 10000, 2, &dxok);
    bool dyok;
    double dy = QInputDialog::getDouble(this, tr("输入Δy"),
                                       tr("Δy:"), 0.0, -10000, 10000, 2, &dyok);
    bool dzok;
    double dz = QInputDialog::getDouble(this, tr("输入Δz"),
                                       tr("Δz:"), 0.0, -10000, 10000, 2, &dzok);
    if(dxok && dyok && dzok){
        if(type==1){
            //m1->Showpoints();
            m1->Translate(dx,dy,dz);
            //m1->Showpoints();
        }
        else if(type==2){
            m2->Translate(dx,dy,dz);
        }
    }
}
//显示AABB包围盒
void MainWindow::AABB_SLOT(){
    AABB_ON=!AABB_ON;
}
//显示地面网格
void MainWindow::grid_SLOT(){
    grid_ON=!grid_ON;
}
//绘制中心
void MainWindow::Draw_Center(){
    center_on=!center_on;
}
//绘制重心
void MainWindow::Draw_m_Center(){
    m_center_on=!m_center_on;
}
//状态栏启动
void MainWindow::init_statusbar(){
    QStatusBar* bar = ui->statusbar; //获取状态栏
    minfo = new QLabel; //新建标签
    minfo->setMinimumSize(150,20);
    //minfo->setFrameShape(QFrame::WinPanel); //设置标签形状
    //minfo->setFrameShadow(QFrame::Sunken); //设置标签阴影
    minfo->setText("模型信息: ");
    bar->addWidget(minfo);
}
//状态栏修改
void MainWindow::change_statusbar(){
    QString text;
    text.append("模型信息:\t");
    if(type==1){
        text.append("类型: 点云\t\t");
        text.append("点数: "+QString::number(m1->pointnum)+"\t\t");
        text.append("中心: ["+QString::number(m1->center.x)+", "+QString::number(m1->center.y)+", "+QString::number(m1->center.z)+"] \t\t");
        text.append("重心: ["+QString::number(m1->mcenter.x)+", "+QString::number(m1->mcenter.y)+", "+QString::number(m1->mcenter.z)+"]\t\t");
    }
    else if(type==2){
        text.append("类型: 网格模型\t\t");
        text.append("点数: "+QString::number(m2->pointnum)+"\t");
        text.append("面数: "+QString::number(m2->facenum)+"\t");
        text.append("面积: "+QString::number(m2->surfacearea)+"\t\t");
        text.append("中心: ["+QString::number(m2->center.x)+", "+QString::number(m2->center.y)+", "+QString::number(m2->center.z)+"] \t\t");
        text.append("重心: ["+QString::number(m2->mcenter.x)+", "+QString::number(m2->mcenter.y)+", "+QString::number(m2->mcenter.z)+"]\t\t");
    }
    minfo->setText(text);
}
//显示表面/网格
void MainWindow::change_Surface_Mesh(){
    surface_on=!surface_on;
}
//关闭当前文件
void MainWindow::close_file(){
    if(type==1){
        type=0;
        delete m1;
        m1=NULL;
    }
    else if(type==2){
        type=0;
        delete m2;
        m2=NULL;
    }
}
