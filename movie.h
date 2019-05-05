#ifndef MOVIE_H
#define MOVIE_H
#include <QDialog>
#include <QtSql>

namespace Ui {class Movie;}
class Movie : public QDialog
{
    Q_OBJECT
public slots:
    void recieveData(QString str);
public:
    explicit Movie(QWidget *parent = nullptr);
    ~Movie();
    QSqlQueryModel *setquery = new QSqlQueryModel;
    QString question;
private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
private:
    Ui::Movie *ui;

};
#endif
