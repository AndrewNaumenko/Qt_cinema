#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSqlDatabase>
#include "movie.h"
#include <QtSql>

namespace Ui {class MainWindow;}
class QSqlTableModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
     QSqlDatabase mDatabase;
     QSqlQueryModel *setquery = new QSqlQueryModel;
     QString question;
    ~MainWindow();
signals:
    void sendData(QString str);
 private slots:
    void onButtonSend();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *mModel;
    Movie *moive;
};

#endif
