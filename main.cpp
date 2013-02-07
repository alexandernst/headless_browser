//
// @author Alexander Nestorov <alexandernst@gmail.com>
// 
// @licensed under the WTFPL
//

#include <QtWidgets/QApplication>
#include "headless_browser.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    HeadlessBrowser *wp = new HeadlessBrowser();

#ifdef QT_NO_DEBUG
    QWebView *wv = new QWebView();
    wv->setPage(wp);
    wv->show();

    QWebInspector *webInspector = new QWebInspector();
    webInspector->setPage(wv->page());
    webInspector->setGeometry(2000, 600, 1300, 400);
    webInspector->show();
#endif



    wp->_load(QUrl(argv[1]));

    return a.exec();
}
