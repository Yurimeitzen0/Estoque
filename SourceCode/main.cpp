#include "fm_main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString css = "QPushButton{background:#248;color:#fff;font-size: 16pt;border: none;border-radius: 10px;}";
    a.setStyleSheet(css);

    Fm_main w;
    w.show();
    return a.exec();
}
