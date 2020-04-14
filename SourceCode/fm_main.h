#ifndef FM_MAIN_H
#define FM_MAIN_H

#include <QMainWindow>
#include <QtSql>



QT_BEGIN_NAMESPACE
namespace Ui { class Fm_main; }
QT_END_NAMESPACE

class Fm_main : public QMainWindow
{
    Q_OBJECT

public:
    Fm_main(QWidget *parent = nullptr);
    ~Fm_main();
    QIcon keylock_open;
    QIcon *keylock_locked = new QIcon();




private slots:
    void on_Bt_block_clicked();

    void on_Bt_Sale_clicked();

    void on_actionEstoque_triggered();

    void on_actionColaboradores_triggered();

    void on_actionVendas_triggered();

private:
    Ui::Fm_main *ui;
};
#endif // FM_MAIN_H
