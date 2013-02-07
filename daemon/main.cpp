//
// @author Alexander Nestorov <alexandernst@gmail.com>
// 
// @licensed under the WTFPL
//

#include <QtWidgets/QApplication>
#include "daemon.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    Daemon *webPage = new Daemon();

#ifdef QT_NO_DEBUG
    QWebView *wv = new QWebView();
    wv->setPage(webPage);
    wv->show();

    QWebInspector *webInspector = new QWebInspector();
    webInspector->setPage(wv->page());
    webInspector->setGeometry(2000, 600, 1300, 400);
    webInspector->show();
#endif

    webPage->_load(QUrl(argv[1]));

    return a.exec();
}
