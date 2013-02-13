#include <../socket-ipc/server/server.h>
#include "daemon.h"

int main(int argc, char *argv[]){
#ifdef QT_NO_DEBUG
    QCoreApplication a(argc, argv);
#else
    QApplication a(argc, argv);
#endif

    Server *server = new Server("ipc");

#ifdef QT_NO_DEBUG
    QWebView *wv = new QWebView();
    wv->setPage(webPage);
    wv->show();

    QWebInspector *webInspector = new QWebInspector();
    webInspector->setPage(wv->page());
    webInspector->setGeometry(2000, 600, 1300, 400);
    webInspector->show();
#endif

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
