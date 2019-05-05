#ifndef EDITING_H
#define EDITING_H
#include <QDialog>
namespace Ui {class editing;}
class editing : public QDialog
{
    Q_OBJECT
public:
    explicit editing(QWidget *parent = nullptr);
    ~editing();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
private:
    Ui::editing *ui;
};
#endif
