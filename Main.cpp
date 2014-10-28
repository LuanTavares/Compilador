#include <QApplication>
#include "TelaPrincipal.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TelaPrincipal * telaPrincipal = new TelaPrincipal();
    telaPrincipal->show();

    return app.exec();
}





