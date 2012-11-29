//
// @author Alexander Nestorov <alexandernst@gmail.com>
// 
// @licensed under the WTFPL
//

#include <QApplication>
#include "hb.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    HB *wp = new HB();

    //Uncomment to see the page in a QWebView
    //QWebView *wv = new QWebView();
    //wv->setPage(wp);
    //wv->show();

    wp->_load(QUrl(argv[1]));

    return a.exec();
}
