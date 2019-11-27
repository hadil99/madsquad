#include "crud_materiel.h"
#include "ui_crud_materiel.h"
#include "QMessageBox"
#include "connexion.h"
#include "login.h"

crud_materiel::crud_materiel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crud_materiel)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
    ui->label_5->setPixmap(pix);
    ui->label_6->setPixmap(pix);
    ui->label_8->setPixmap(pix);
    ui->tabetudiant->setModel(tmpmateriel.afficher());
    Connexion conn;
    QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery *qry=new QSqlQuery(conn.mydb);
    qry->prepare("select nom from materiel");

    qry->exec();
    model->setQuery(*qry);
    //ui->tabetudiant_2->setModel(model);
    ui->comboBox->setModel(model);

}

crud_materiel::~crud_materiel()
{
    delete ui;
}


void crud_materiel::on_pb_ajouter_clicked()
{

    int ref = ui->lineEdit_id->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    int nbr= ui->lineEdit_prenom->text().toInt();
    Materiel e(ref,nom,nbr);
     bool test=e.ajouter();
    if(test)
    {
        ui->tabetudiant->setModel(tmpmateriel.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un Materiel"),
        QObject::tr("Materiel ajouté"), QMessageBox::Ok);
        Connexion conn;
        QSqlQueryModel * model= new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery(conn.mydb);
        qry->prepare("select nom from materiel");

        qry->exec();
        model->setQuery(*qry);
        //ui->tabetudiant_2->setModel(model);
        ui->comboBox->setModel(model);
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Materiel"),
                  QObject::tr("Erreur !"), QMessageBox::Cancel);
}


void crud_materiel::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString nom=ui->comboBox->currentText();
    QSqlQuery qry;

    qry.prepare("select * from materiel where nom = '"+nom+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->ref->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->nbr->setText(qry.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }

}

void crud_materiel::on_pb_supprimer_3_clicked()
{
    int ref = ui->ref->text().toInt();
    bool test=tmpmateriel.supprimer(ref);
    if(test)
    {ui->tabetudiant->setModel(tmpmateriel.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer Matériel"),
                    QObject::tr("Matériel supprimé"), QMessageBox::Ok);
        Connexion conn;
        QSqlQueryModel * model= new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery(conn.mydb);
        qry->prepare("select nom from materiel");

        qry->exec();
        model->setQuery(*qry);
        //ui->tabetudiant_2->setModel(model);
        ui->comboBox->setModel(model);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Matériel"),
                    QObject::tr("Erreur !"), QMessageBox::Cancel);

}

void crud_materiel::on_pb_supprimer_4_clicked()
{
    QString ref=ui->ref->text();
    int nbr=ui->nbr->text().toInt();
    bool test=tmpmateriel.modifier(ref,nbr);
    if (test)
    {
        ui->tabetudiant->setModel(tmpmateriel.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier Matériel"),
                    QObject::tr("Matériel modifié"), QMessageBox::Ok);
        Connexion conn;
        QSqlQueryModel * model= new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery(conn.mydb);
        qry->prepare("select nom from materiel");

        qry->exec();
        model->setQuery(*qry);
        ui->comboBox->setModel(model);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un nombre"),
                          QObject::tr("Erreur !"), QMessageBox::Cancel);
    }
}

void crud_materiel::on_lineEdit_id_5_returnPressed()
{
    int ref=ui->lineEdit_id_5->text().toInt();
    QSqlQuery qry;
    QString res= QString::number(ref);
        qry.prepare("select * from materiel where ref = '"+res+"'");
        if (qry.exec())
        {
            while(qry.next())
            {
                ui->ref->setText(qry.value(0).toString());
                ui->nom->setText(qry.value(1).toString());
                ui->nbr->setText(qry.value(2).toString());
            }
        }
        else
        {
            QMessageBox::critical(this,tr("error"),qry.lastError().text());
        }
}

void crud_materiel::on_lineEdit_id_returnPressed()
{
    QString ref = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString nbr= ui->lineEdit_prenom->text();
    if (ref==""||nom==""||nbr=="")
    {
        QMessageBox::information(this,"Erreur","Touts les champs sont obligatoires");
    }
}

void crud_materiel::on_lineEdit_prenom_returnPressed()
{
    QString ref = ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString nbr= ui->lineEdit_prenom->text();
    if (ref==""||nom==""||nbr=="")
    {
        QMessageBox::information(this,"Erreur","Touts les champs sont obligatoires");
    }
    else
    {
        int ref = ui->lineEdit_id->text().toInt();
        QString nom= ui->lineEdit_nom->text();
        int nbr= ui->lineEdit_prenom->text().toInt();
        Materiel e(ref,nom,nbr);
         bool test=e.ajouter();
        if(test)
        {
            ui->tabetudiant->setModel(tmpmateriel.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Ajouter un Materiel"),
            QObject::tr("Materiel ajouté"), QMessageBox::Ok);
            Connexion conn;
            QSqlQueryModel * model= new QSqlQueryModel();

            QSqlQuery *qry=new QSqlQuery(conn.mydb);
            qry->prepare("select nom from materiel");

            qry->exec();
            model->setQuery(*qry);
            //ui->tabetudiant_2->setModel(model);
            ui->comboBox->setModel(model);
        }
        else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un Materiel"),
                      QObject::tr("Erreur !"), QMessageBox::Cancel);
    }
}

void crud_materiel::on_lineEdit_id_6_returnPressed()
{
    QString ref=ui->lineEdit_id_6->text();
    ui->tabetudiant->setModel(tmpmateriel.afficher2(ref));//refresh
}

void crud_materiel::on_pushButton_clicked()
{
    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
     msgBox.setText("Voulez-vous vraiment vous déconnecter ?");
     msgBox.exec();

     if (msgBox.clickedButton() == connectButton)
     {
         msgBox.close();
         close();
         login c;
         c.exec();

     }
     else if (msgBox.clickedButton() == abortButton) {
         msgBox.close();
     }
}

bool crud_materiel::deconnexion()
{
    return  true;
}

void crud_materiel::on_lineEdit_id_6_textChanged(const QString &arg1)
{
    ui->tabetudiant->setModel(tmpmateriel.afficher2(arg1));//refresh
}
