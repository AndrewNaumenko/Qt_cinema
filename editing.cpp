#include "editing.h"
#include "ui_editing.h"
#include "mainwindow.h"
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
#include "addfilm.h"
#include "addschedule.h"
int choose = 1;
editing::editing(QWidget *parent):QDialog(parent), ui(new Ui::editing)
{
    ui->setupUi(this);
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код");
    ui->tableView->setModel(setquery1);
}

editing::~editing()
{
    delete ui;
}

QString find_key (QString question)
{   
     QSqlQuery query;
     query.exec(question);
     if ( ! query.isActive() )
     {}
     QString  key="";
     while (query.next())
     key =  query.value(0).toString();
     return key;
}

void editing::on_pushButton_clicked()
{
    choose = 1;
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код");
    ui->tableView->setModel(setquery1);
}

void editing::on_pushButton_2_clicked()
{
    choose = 2;
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("SELECT DISTINCT Название, Дата, Время,Сеансы.Код FROM Фильм,Сеансы,Билеты where Фильм.Код = Сеансы.Код_фильма");
    ui->tableView->setModel(setquery1);
}

void editing::on_pushButton_3_clicked()
{
    choose = 3;
    QSqlQueryModel *setquery1 = new QSqlQueryModel;
    setquery1->setQuery("SELECT DISTINCT  Название, Дата, Время,Ряд,Место FROM Место,Ряд,Билеты,Сеансы,Фильм where Фильм.Код = Сеансы.Код_фильма and Сеансы.Код = Билеты.Код_сеанс and Билеты.Код_место = Место.Код and Билеты.Код_ряд=Ряд.Код");
    ui->tableView->setModel(setquery1);
}

void editing::on_pushButton_4_clicked()
{
    switch (choose)
    {
    case 1:
    {
        addfilm enter;
        enter.setModal(true);
        enter.exec();
    }
    break;
    case 2:
    {
        addschedule enter;
        enter.setModal(true);
        enter.exec();
    }
    break;
    case 3:
    QMessageBox::about(this,"Сообщение","Для выполнения этой операции перейдите на соответствующую форму");
    break;
    }
}

void editing::on_pushButton_5_clicked()
{
    QModelIndex currentDiscount  = ui->tableView->currentIndex();
    QString question;
    QSqlQueryModel *setquery4 = new QSqlQueryModel;
    switch (choose)
    {
    case 1:
    {
        question = "SELECT Код FROM Фильм where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "'";
        QString key_film = find_key(question);
        question = "SELECT Сеансы.Код FROM Фильм,Сеансы where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "' and Фильм.Код = Сеансы.Код_фильма";
        QString key_seans = find_key(question);
        setquery4->setQuery("delete from Билеты where Билеты.Код_сеанс = " + key_seans  +"");
        setquery4->setQuery("delete from Сеансы where Сеансы.Код = " + key_seans  +"");
        setquery4->setQuery("delete from Актеры where Актеры.Код_фильма = " +key_film  +"");
        setquery4->setQuery("delete from Жанры where Жанры.Код_фильма =" + key_film  +"");
        setquery4->setQuery("delete from Режиссеры where Режиссеры.Код_фильма = " + key_film  +"");
        setquery4->setQuery("delete from Фильм where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() +"'");
    }
    break;
    case 2:
       {
         question = "SELECT Код FROM Фильм where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "'";
         QString key_film = find_key(question);
         question = "SELECT Сеансы.Код FROM Фильм,Сеансы where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "' and Фильм.Код = Сеансы.Код_фильма";
         QString key_seans = find_key(question);
         setquery4->setQuery("delete from Билеты where Билеты.Код_сеанс = " + key_seans  +"");
         setquery4->setQuery("delete from Сеансы where Сеансы.Код = " + key_seans  +"");
    }
    break;
    case 3:
    {
        question = "SELECT Код FROM Фильм where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "'";
        QString key_film = find_key(question);
        question = "SELECT Сеансы.Код FROM Фильм,Сеансы where Название = '" +  (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString() + "' and Фильм.Код = Сеансы.Код_фильма";
        QString key_seans = find_key(question);
        QString col = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),4),0)).toString();
        QString row = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),3),0)).toString();
        question = "SELECT Билеты.Код FROM Билеты where Билеты.Код_сеанс = " + key_seans  + " and Билеты.Код_место " + (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),4)).toString()   +"and Билеты.Код_ряд = " + (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),3),0)).toString()   +" ";
        QString key_tic = find_key(question);
        setquery4->setQuery("delete from Билеты where Билеты.Код_сеанс = " + key_seans  + " and Билеты.Код_место " + (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),4)).toString()   +"and Билеты.Код_ряд = " + (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),3),0)).toString()   +"");
    }
    break;
    }
}
