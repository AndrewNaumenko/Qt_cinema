#include "addschedule.h"
#include "ui_addschedule.h"
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
#include <QDialog>

void query_3 (QString question,QSqlQueryModel *setquery)
{
     setquery->setQuery(question);
}

addschedule::addschedule(QWidget *parent): QDialog(parent), ui(new Ui::addschedule)
{
    ui->setupUi(this);
    question = "SELECT Название FROM Фильм";
    query_3 ( question,setquery);
    ui->tableView->setModel(setquery);
    for (int i=0; i<ui->tableView->model()->rowCount();i++)
    ui->comboBox_6->addItem ( ui->tableView->model()->data((ui->tableView->model()->index(i,0))).toString());
}

addschedule::~addschedule()
{
    delete ui;
}

void addschedule::on_pushButton_4_clicked()
{
    if (ui->textEdit->toPlainText()=="")
    {
        QMessageBox::about(this,"Сообщение","Не все поля заполнены !");
    }
    else
    {
        QString strings = ui->comboBox_6->currentText();
        question = "SELECT Код FROM Фильм where Название = '" +  strings + "'";
        query_3 ( question,setquery);
        ui->tableView->setModel(setquery);
        QString key_film = ui->tableView->model()->data((ui->tableView->model()->index(0,0))).toString();
         QString date = ui->comboBox_2->currentText()+"."+ui->comboBox->currentText()+"."+ui->comboBox_3->currentText();
         QString time = ui->comboBox_5->currentText()+":"+ui->comboBox_4->currentText();
         QString text = ui->textEdit->toPlainText();
         QRegExp rx( "([a-zA-ZА-Яа-я#_.]+)" );
         QString check="";
         int pos =0;
         while ((pos = rx.indexIn(text, pos)) != -1)
         {
           check += rx.cap(1);
           pos += rx.matchedLength();
         }
         if (check == "" || check == " " )
         {
             question = "insert into Сеансы(Дата,Время,Код_фильма,Цена) values('" + date +  "','" + time +   "','" + key_film +  "','" + ui->textEdit->toPlainText() +  "')";
             query_3 ( question,setquery);
             QMessageBox::about(this,"Сообщение","Операция прошла успешно");
         }
        else
        {
            QMessageBox::critical(this,"Error","Введите цену в формате :'2,3'");
        }

    }
}
