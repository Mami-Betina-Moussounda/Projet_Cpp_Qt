//#include "client/ClientOrdi.h"
#include "client/Client.h"
#include "graph/Graph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetrePrincipale fenetre;

    ClientOrdi client1(fenetre);

//    fenetre.show();
    client1.show();

    return a.exec();
}
