#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    fenprincipale fen;
    fen.show();
    return app.exec();
}
