#ifndef ADDFILM_H
#define ADDFILM_H
#include <QDialog>
#include <QtSql>
namespace Ui {class addfilm;}
class addfilm : public QDialog
{
    Q_OBJECT
public:
    explicit addfilm(QWidget *parent = nullptr);
      QString question;
      QSqlQueryModel *setquery = new QSqlQueryModel;
    ~addfilm();
private slots:
    void on_pushButton_clicked();
private:
    Ui::addfilm *ui;
};
#endif
