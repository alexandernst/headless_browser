#include <../socket-ipc/server/server.h>
#include "daemon.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    Server *server = new Server("ipc");

    QObject::connect(server, &Server::newMessageFromClient, [server](int clientID, QString message){
        Daemon *webPage = new Daemon();
        webPage->_load(QUrl(message));

        QObject::connect(webPage, &Daemon::newSnapshot, [server, clientID](QString html_snapshot){
            server->sendMessageToClient(clientID, html_snapshot);
            server->disconnectClient(clientID);
        });
    });

    return a.exec();
}
