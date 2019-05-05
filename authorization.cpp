#include "authorization.h"
#include "ui_authorization.h"
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
Authorization::Authorization(QWidget *parent): QDialog(parent),ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

QStringList fun_file_enter ( QString filename)
{
    QFile file(filename);
    QStringList strings;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
        strings += in.readLine().split(";");
        }
    }
    return strings;
}

void fun_file_in_out (QString filename, bool check)
{
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
       QTextStream stream( &file );
       if (check == false )
       stream << "user" << endl;
       else
       stream << "admin" << endl;
    }
}

void Authorization::on_pushButton_clicked()
{
    QString filename = "enter.txt";
    QStringList strings =  fun_file_enter(filename);
    filename="who.txt";
    bool check = false;
    if (strings[0]==ui->textEdit->toPlainText()&&strings[1]==ui->textEdit_2->toPlainText())
    {
       check=true;
       fun_file_in_out( filename,check);
       QMessageBox::about(this,"Сообщение","Вы вошли");
    }
    else
    {
        QMessageBox::about(this,"Сообщение","Неверный логин или пароль");
    }
}

void Authorization::on_pushButton_2_clicked()
{
    QString filename = "who.txt";
    bool check = false;
    fun_file_in_out( filename,check);
    QMessageBox::about(this,"Сообщение","Вы вошли как пользователь");
}
