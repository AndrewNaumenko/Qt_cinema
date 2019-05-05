#include "movie.h"
#include "ui_movie.h"
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QCoreApplication>
#include <QtSql>
#include <QUrl>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QStandardItem>

void query_2 (QString question,QSqlQueryModel *setquery)
{
     setquery->setQuery(question);
}

Movie::Movie(QWidget *parent):QDialog(parent),ui(new Ui::Movie)
{
    ui->setupUi(this);
}

void Movie::recieveData(QString str)
{

   ui->label->setText(str);
   question = "SELECT DISTINCT Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код and Фильм.Название='"+ui->label->text()+"' ";
   query_2 (question,setquery);
    ui->tableView->setModel(setquery);
    ui->label_11->setText( ui->tableView->model()->data((ui->tableView->model()->index(0,2))).toString());
    ui->label_14->setText( ui->tableView->model()->data((ui->tableView->model()->index(0,1))).toString());
    ui->label_8->setText( ui->tableView->model()->data((ui->tableView->model()->index(0,0))).toString());
    question = "SELECT Жанр FROM Фильм,Жанр,Жанры  where Фильм.Название='"+ui->label->text()+"' and Фильм.Код=Жанры.Код_фильма and Жанры.Код_формата = Жанр.Код";
    query_2 (question,setquery);
    ui->tableView->setModel(setquery);
    QString temp;
    for (int i=0 ; i< ui->tableView->model()->rowCount();i++)
    {
        temp+=ui->tableView->model()->data((ui->tableView->model()->index(i,0))).toString();
        temp+=' ';
    }
    ui->label_7->setText( temp );
    question = "SELECT Имя FROM Фильм,Актер,Актеры  where Фильм.Название='"+ui->label->text()+"' and Фильм.Код=Актеры.Код_фильма and Актеры.Код_актера = Актер.Код";
    query_2 (question,setquery);
    ui->tableView->setModel(setquery);
    temp="";
    for (int i=0 ; i< ui->tableView->model()->rowCount();i++)
    {
        temp+=ui->tableView->model()->data((ui->tableView->model()->index(i,0))).toString();
        temp+=' ';
    }
     ui->label_10->setText( temp );
     question = "SELECT Имя FROM Фильм,Режиссер,Режиссеры  where Фильм.Название='"+ui->label->text()+"' and Фильм.Код=Режиссеры.Код_фильма and Режиссеры.Код_режиссера = Режиссер.Код";
     query_2 (question,setquery);
     ui->tableView->setModel(setquery);
     temp="";
     for (int i=0 ; i< ui->tableView->model()->rowCount();i++)
     {
         temp+=ui->tableView->model()->data((ui->tableView->model()->index(i,0))).toString();
         temp+=' ';
     }
     ui->label_12->setText( temp );
     question = "SELECT DISTINCT Название, Дата, Время,Цена,Сеансы.Код FROM Фильм,Сеансы,Билеты  where Фильм.Название='"+ui->label->text()+"' and Фильм.Код=Сеансы.Код_фильма";
     query_2 (question,setquery);
     ui->tableView->setModel(setquery);
     QStandardItemModel *model = new QStandardItemModel;
     QStandardItem *item;
     for (int i=0; i<6;i++)
          for (int j=0; j<10;j++)
          {
              item = new  QStandardItem();
              model->setItem(i,j,item);
          }
     ui->tableView_2->setModel(model);
     ui->tableView_2->resizeRowsToContents();
     ui->tableView_2->resizeColumnsToContents();
     for (int i=0; i<5;i++)
          for (int j=0; j<10;j++)
          {
              ui->tableView_2->model()->setData(ui->tableView_2->model()->index(i,j),QColor(Qt::gray),Qt::BackgroundColorRole);
          }
     for (int temp2=3;temp2<7;temp2++)
     {
        ui->tableView_2->model()->setData(ui->tableView_2->model()->index(5,temp2),QColor(Qt::gray),Qt::BackgroundColorRole);
     }
}

Movie::~Movie()
{
    delete ui;
}

void Movie::on_tableView_clicked(const QModelIndex &index)
{
    for (int i=0; i<5;i++)
         for (int j=0; j<10;j++)
         {
             ui->tableView_2->model()->setData(ui->tableView_2->model()->index(i,j),QColor(Qt::gray),Qt::BackgroundColorRole);
         }
    for (int temp2=3;temp2<7;temp2++)
    {
       ui->tableView_2->model()->setData(ui->tableView_2->model()->index(5,temp2),QColor(Qt::gray),Qt::BackgroundColorRole);
    }
        QModelIndex currentDiscount  = ui->tableView->currentIndex();
        QString name = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString();
        QString date = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),1),0)).toString();
        QString time = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),2),0)).toString();
        QSqlQueryModel *setquery2 = new QSqlQueryModel;
        setquery2->setQuery("SELECT DISTINCT Ряд,Место FROM Место,Ряд,Билеты,Сеансы,Фильм  where Фильм.Название = '"+name+"'and Сеансы.Дата='"+date+"'and Сеансы.Время='"+time+"'and Билеты.Код_место=Место.Код and Билеты.Код_ряд=Ряд.Код and Сеансы.Код=Билеты.Код_сеанс");
        ui->tableView_3->setModel(setquery2);
        for (int i=0 ; i< ui->tableView_3->model()->rowCount();i++)
        {
            int row =ui->tableView_3->model()->data((ui->tableView_3->model()->index(i,0))).toInt()-1;
            int col =ui->tableView_3->model()->data((ui->tableView_3->model()->index(i,1))).toInt()-1;
            ui->tableView_2->model()->setData(ui->tableView_2->model()->index(row,col),QColor(Qt::red),Qt::BackgroundColorRole);
        }
}

void Movie::on_pushButton_clicked()
{
    QModelIndex currentDiscount  = ui->tableView->currentIndex();
    if (ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==1 || ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==2 || ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==3 || ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==8 || ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==9 ||ui->comboBox_2->currentText().toInt()==6 && ui->comboBox->currentText().toInt()==10)
    {
        QMessageBox::critical(this,"Error","Такого места нет");
    }
    else
    {
        QSqlQueryModel *setquery4 = new QSqlQueryModel;
        bool chek = false;
        for (int i =0 ; i<ui->tableView_3->model()->rowCount();i++)
        if ((ui->tableView_3->model()->data((ui->tableView_3->model()->index(i,0)))).toString()==ui->comboBox_2->currentText()&&(ui->tableView_3->model()->data((ui->tableView_3->model()->index(i,1)))).toString()==ui->comboBox->currentText())
        {
            chek = true;
            QMessageBox::about(this,"Сообщение","Билет уже куплен");
        }
        if (chek==false)
        {
        setquery4->setQuery("insert into Билеты(Код_сеанс,Код_место,Код_ряд) values('" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),4),0)).toString() + "','" + ui->comboBox->currentText()  + "','" + ui->comboBox_2->currentText() + "')");
        QMessageBox::about(this,"Сообщение","Билет куплен");
        }
    }
}
