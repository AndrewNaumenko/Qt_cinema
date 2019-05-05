#ifndef ADDSCHEDULE_H
#define ADDSCHEDULE_H
#include <QDialog>
#include <QtSql>
namespace Ui {class addschedule;}
class addschedule : public QDialog
{
    Q_OBJECT
public:
    explicit addschedule(QWidget *parent = nullptr);
     QSqlQueryModel *setquery = new QSqlQueryModel;
       QString question;
    ~addschedule();
private slots:
    void on_pushButton_4_clicked();
private:
    Ui::addschedule *ui;
};
#endif
