#include "addfilm.h"
#include "ui_addfilm.h"
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
#include "mainwindow.h"
addfilm::addfilm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addfilm)
{
    ui->setupUi(this);
}

addfilm::~addfilm()
{
    delete ui;
}

QString find_key_3 (QString question)
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

void addfilm::on_pushButton_clicked()
{
    if ((ui->textEdit->toPlainText())=="" && (ui->textEdit_2->toPlainText())=="" && (ui->textEdit_3->toPlainText())==""&& (ui->textEdit_4->toPlainText())==""&& (ui->textEdit_5->toPlainText())==""&& (ui->textEdit_6->toPlainText())=="") QMessageBox::about(this,"Сообщение","Не все поля заполнены !");
        else
    {
        QString fkey ="";
        QString country="";
        QString age = "";
        QString film_name = ui->textEdit->toPlainText();
        question = "SELECT Код FROM Фильм where Название = '"+film_name+"'";
        fkey = find_key_3 ( question);
        if (fkey != ""){QMessageBox::warning(this, "Ошибка","Данный фильм уже есть");}
        else
        {
           question = "SELECT Страна.Код FROM Страна where Страна = '"+ui->textEdit_2->toPlainText()+"'";
           country = find_key_3 ( question);
            if ( country != "")
            {
                question = "SELECT Страна.Код FROM Страна where Страна.Страна = '"+ui->textEdit_2->toPlainText()+"'";
                country=find_key_3(question);
            }
            else
            {
                setquery->setQuery("insert into Страна(Страна) values('" + ui->textEdit_2->toPlainText() + "')");
                country = find_key_3(question);
            }
            QString temp = ui->comboBox->currentText();
            question = "SELECT Возраст.Код FROM Возраст where Возраст.Возраст = '"+temp+"'";
         age = find_key_3(question);
         QString time = ui->comboBox_3->currentText()+":"+ui->comboBox_2->currentText();
         setquery->setQuery("insert into Фильм(Название,Длительность,Код_страна,Код_возраст,Описание) values('" +  ui->textEdit->toPlainText() + "','" + time  + "','" + country + "','" + age + "','" +  ui->textEdit_6->toPlainText() + "')");
         question = "SELECT Код FROM Фильм where Название = '"+ ui->textEdit->toPlainText()+"'";
         fkey = find_key_3(question);
         QString key= ui->textEdit_3->toPlainText();
         QStringList list = key.split(',');
        for (int i=0;i<list.count();i++)
        {
            QString addkey ="";
            question = "SELECT Жанр.Код FROM Жанр where Жанр = '"+list[i]+"'";
            addkey = find_key_3(question);
            if (addkey=="")
            {
                setquery->setQuery("insert into Жанр(Жанр) values('" + list[i] + "')");
                addkey = find_key_3(question);
                setquery->setQuery("insert into Жанры(Код_фильма,Код_формата) values('" + fkey +  "','" + addkey +  "')");
            }
             else
             {
                 setquery->setQuery("insert into Жанры(Код_фильма,Код_формата) values('" + fkey +  "','" + addkey +  "')");
             }
        }
        key= ui->textEdit_4->toPlainText();
        list = key.split(',');
        for (int i=0;i<list.count();i++)
        {
        QString addkey ="";
        question = "SELECT Режиссер.Код FROM Режиссер where Имя = '"+list[i]+"'";
        addkey = find_key_3(question);
        if (addkey=="")
        {
            setquery->setQuery("insert into Режиссер(Имя) values('" + list[i] + "')");
            addkey = find_key_3(question);
            setquery->setQuery("insert into Режиссеры(Код_фильма,Код_режиссера) values('" + fkey +  "','" + addkey +  "')");
        }
        else
        {
            setquery->setQuery("insert into Режиссеры(Код_фильма,Код_режиссера) values('" + fkey +  "','" + addkey +  "')");
        }
        }
        key= ui->textEdit_5->toPlainText();
        list = key.split(',');
        for (int i=0;i<list.count();i++)
        {
        QString addkey ="";
        question = "SELECT Актер.Код FROM Актер where Имя = '"+list[i]+"'";
        addkey = find_key_3(question);
        if (addkey=="")
        {
            setquery->setQuery("insert into Актер(Имя) values('" + list[i] + "')");
            addkey = find_key_3(question);
            setquery->setQuery("insert into Актеры(Код_фильма,Код_актера) values('" + fkey +  "','" + addkey +  "')");
        }
        else
        {
            setquery->setQuery("insert into Актеры(Код_фильма,Код_актера) values('" + fkey +  "','" + addkey +  "')");
        }
        }
         QMessageBox::about(this,"Сообщение","Фильм добавлен");
    }
}
}
