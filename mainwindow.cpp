#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QMessageBox>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tabpatient->setModel(tmppatient.afficher());
QPixmap pix("C:/Users/foura/OneDrive/Bureau/New folder (3)/Atelier_Crud_Vf/pic/aa.jpg");
int w=ui->label_pic->width();
int h=ui->label_pic->height();

ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id = ui->nump->text().toInt();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QString drdv= ui->drdv->text();
    QString maladie= ui->maladie->text();
    QString obs= ui->obs->text();


  patient e(id,nom,prenom,drdv,maladie,obs);
  bool test=e.ajouter();
  if(test)
{ui->tabpatient->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("patient ajouté"),
                  QObject::tr("Dossier ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_id_2->text().toInt();
bool test=tmppatient.supprimer(id);
if(test)
{ui->tabpatient->setModel(tmppatient.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                QObject::tr("Etudiant supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_modif_clicked()
{
    int id = ui->m1->text().toInt();
    QString nom= ui->m2->text();
    QString prenom= ui->m3->text();
    QString drdv= ui->m4->text();
    QString maladie= ui->m5->text();
    QString obs= ui->m6->text();


  patient e(0,nom,prenom,drdv,maladie,obs);
  e.set_nump(id);
  bool test=e.modifier();
  if(test)
{ui->tabpatient->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Dossier modifié"),
                  QObject::tr("Dossier modifié !!.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}




void MainWindow::on_rechercher_clicked()
{
    QString rech;
    rech=ui->rech->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from patient where nump like '"+rech+"'");
     qry->bindValue("rech",rech);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr->setModel(model);
}
