#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorization.h"
#include "movie.h"
#include "editing.h"
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
#define ACCESS "DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=DB.mdb"

void query (QString question,QSqlQueryModel *setquery)
{
     setquery->setQuery(question);
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    moive = new Movie();
    connect(ui->pushButton_4, SIGNAL(clicked()),  moive, SLOT(show()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(this, SIGNAL(sendData(QString)),moive, SLOT(recieveData(QString)));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9);
    shadowEffect->setOffset(0);
    mDatabase = QSqlDatabase::addDatabase("QODBC");
    mDatabase.setDatabaseName(ACCESS);
    if (!mDatabase.open())
    {
        QMessageBox::critical(this,"Error",mDatabase.lastError().text());
        return;
    }
    question  = "SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код";
    query (question,setquery);
    ui->tableView->setModel(setquery);
}

void MainWindow::onButtonSend()
{
    QStringList list;
    QModelIndex currentDiscount  = ui->tableView->currentIndex();
    QString temp = (ui->tableView->model()->data(ui->tableView->model()->index(currentDiscount.row(),0),0)).toString();
    if (temp==""){QMessageBox::warning(this, tr("Database Error"),"Выберите фильм");  moive ->close();}
    else {emit sendData(temp);}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
     Authorization enter;
     enter.setModal(true);
     enter.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->label_2->text()=="user")
    {
         QMessageBox::about(this,"Сообщение","Необходимо зайти в систему");
    }
    else
    {
     editing enter;
     enter.setModal(true);
     enter.exec();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    qApp->closeAllWindows();
    qApp->quit();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
}

void MainWindow::on_pushButton_6_clicked()
{
    question  = ("SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код");
    query (question,setquery);
    ui->tableView->setModel(setquery);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString date =ui->comboBox_2->currentText()+'.'+ui->comboBox->currentText()+'.'+ui->comboBox_3->currentText();
    question  = ("SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна,Сеансы  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код and Фильм.Код=Сеансы.Код_фильма and Сеансы.Дата = '" + date + "'");
    query (question,setquery);
    ui->tableView->setModel(setquery);
}

void MainWindow::on_pushButton_7_clicked()
{
        QFile file("who.txt");
        QString strings;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                strings += in.readLine();
            }
        }
        ui->label_2->setText(strings);
        question  = "SELECT Название,Длительность,Возраст,Страна FROM Фильм,Возраст,Страна  where Фильм.Код_возраст=Возраст.Код and Фильм.Код_страна=Страна.Код";
        query (question,setquery);
        ui->tableView->setModel(setquery);
}
