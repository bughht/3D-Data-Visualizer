#include "viewer.h"

#include <math.h>

// Constructor must call the base class constructor.
Viewer::Viewer(QWidget *parent) : QGLViewer(parent) {
  //restoreStateFromFile();
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH,GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH,GL_NICEST);
    setCameraIsEdited();
    //setGridIsDrawn();
    setAxisIsDrawn();
    glPointSize(2);
    glLineWidth(1);
    //glDisable(GL_LIGHTING);
}

void Viewer::draw() {
    setGridIsDrawn(MainWindow::grid_ON);
    if(MainWindow::center_on){
        if(MainWindow::type==1){
            PCD &mm1=*MainWindow::m1;
            glColor3f(1,0,0);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(mm1.center.x,mm1.center.y,mm1.center.z);
            glEnd();
        }
        if(MainWindow::type==2){
            MESH &mm2=*MainWindow::m2;
            glColor3f(1,0,0);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(mm2.center.x,mm2.center.y,mm2.center.z);
            glEnd();
        }
    }
    if(MainWindow::m_center_on){
        if(MainWindow::type==1){
            PCD &mm1=*MainWindow::m1;
            glColor3f(0,0,1);
            glPointSize(10);
            //mm1.mcenter.showall();
            glBegin(GL_POINTS);
                glVertex3f(mm1.mcenter.x,mm1.mcenter.y,mm1.mcenter.z);
            glEnd();
        }
        if(MainWindow::type==2){
            MESH &mm2=*MainWindow::m2;
            glColor3f(0,0,1);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(mm2.mcenter.x,mm2.mcenter.y,mm2.mcenter.z);
            glEnd();
        }
    }
    if(MainWindow::type==1){ //PCD
        PCD &mm1=*MainWindow::m1;
        glPointSize(2);
        glDisable(GL_LIGHTING);
        glBegin(GL_POINTS);
            for(int i=0;i<mm1.pointnum;i++){
                glColor3f(1.0-sqrt(mm1.points[i].x*mm1.points[i].x+mm1.points[i].y*mm1.points[i].y),1.0,(mm1.points[i].z-mm1.z_min)/(mm1.z_max-mm1.z_min));
                glNormal3f(mm1.points[i].x,mm1.points[i].y,mm1.points[i].z);
                glVertex3f(mm1.points[i].x,mm1.points[i].y,mm1.points[i].z);
            }
        glEnd();
        //mm1.Showpoints();
        if(MainWindow::AABB_ON==true){
            //coutt<<"???";
            glColor3f(1,1,1);
            glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
            glBegin(GL_QUADS);
                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[4]);
                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[4]);

                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[5]);
                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[5]);

                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[5]);
                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[5]);

                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[4]);
                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[4]);

                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[1],mm1.AABB[2],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[1],mm1.AABB[3],mm1.AABB[4]);

                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[4]);
                glVertex3f(mm1.AABB[0],mm1.AABB[2],mm1.AABB[5]);
                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[5]);
                glVertex3f(mm1.AABB[0],mm1.AABB[3],mm1.AABB[4]);
            glEnd();
        }
    }
    else if(MainWindow::type==2){
        MESH &mm2=*MainWindow::m2;
        if(MainWindow::surface_on){
            //coutt<<"on";
            glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHTING);
            glBegin(GL_TRIANGLES);
                for(int i=0;i<mm2.facenum;i++){
                    //glColor3f(1.0,1.0,1.0);
                    glNormal3f(mm2.pf[mm2.face[i][0]].x+mm2.pf[mm2.face[i][1]].x+mm2.pf[mm2.face[i][2]].x,mm2.pf[mm2.face[i][0]].y+mm2.pf[mm2.face[i][1]].y+mm2.pf[mm2.face[i][2]].y,mm2.pf[mm2.face[i][0]].z+mm2.pf[mm2.face[i][1]].z+mm2.pf[mm2.face[i][2]].z);
                    glColor3f(1.0-sqrt(mm2.points[mm2.face[i][0]].x*mm2.points[mm2.face[i][0]].x+mm2.points[mm2.face[i][0]].y*mm2.points[mm2.face[i][0]].y),1.0,(mm2.points[mm2.face[i][0]].z-mm2.z_min)/(mm2.z_max-mm2.z_min));
                    glVertex3f(mm2.points[mm2.face[i][0]].x,mm2.points[mm2.face[i][0]].y,mm2.points[mm2.face[i][0]].z);
                    glVertex3f(mm2.points[mm2.face[i][1]].x,mm2.points[mm2.face[i][1]].y,mm2.points[mm2.face[i][1]].z);
                    glVertex3f(mm2.points[mm2.face[i][2]].x,mm2.points[mm2.face[i][2]].y,mm2.points[mm2.face[i][2]].z);
                }
                //glNormal3f()
            glEnd();
            //mm2.Showpoints();
            if(MainWindow::AABB_ON==true){
                //coutt<<"???";
                glColor3f(1,1,1);
                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
                glBegin(GL_QUADS);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);
                glEnd();
            }
        }
        else{
            glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHTING);
            glBegin(GL_TRIANGLES);
                for(int i=0;i<mm2.facenum;i++){
                    //glColor3f(1.0,1.0,1.0);
                    glNormal3f(mm2.pf[mm2.face[i][0]].x+mm2.pf[mm2.face[i][1]].x+mm2.pf[mm2.face[i][2]].x,mm2.pf[mm2.face[i][0]].y+mm2.pf[mm2.face[i][1]].y+mm2.pf[mm2.face[i][2]].y,mm2.pf[mm2.face[i][0]].z+mm2.pf[mm2.face[i][1]].z+mm2.pf[mm2.face[i][2]].z);
                    glColor3f(1.0-sqrt(mm2.points[mm2.face[i][0]].x*mm2.points[mm2.face[i][0]].x+mm2.points[mm2.face[i][0]].y*mm2.points[mm2.face[i][0]].y),1.0,(mm2.points[mm2.face[i][0]].z-mm2.z_min)/(mm2.z_max-mm2.z_min));
                    glVertex3f(mm2.points[mm2.face[i][0]].x,mm2.points[mm2.face[i][0]].y,mm2.points[mm2.face[i][0]].z);
                    glVertex3f(mm2.points[mm2.face[i][1]].x,mm2.points[mm2.face[i][1]].y,mm2.points[mm2.face[i][1]].z);
                    glVertex3f(mm2.points[mm2.face[i][2]].x,mm2.points[mm2.face[i][2]].y,mm2.points[mm2.face[i][2]].z);
                }
                //glNormal3f()
            glEnd();
            //mm2.Showpoints();
            if(MainWindow::AABB_ON==true){
                //coutt<<"???";
                glColor3f(1,1,1);
                glDisable(GL_LIGHTING);
                glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
                glBegin(GL_QUADS);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[1],mm2.AABB[3],mm2.AABB[4]);

                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[4]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[2],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[5]);
                    glVertex3f(mm2.AABB[0],mm2.AABB[3],mm2.AABB[4]);
                glEnd();
            }
        }
    }

}

QString Viewer::helpString() const {
  QString text("<h2>3D Viewer</h2>");
  return text;
}
