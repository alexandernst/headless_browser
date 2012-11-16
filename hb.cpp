#include "hb.h"

void HB::_load(QUrl url){
    wp = new QWebPage();
    nam = new NAM();
    wp->setNetworkAccessManager(nam);
    QObject::connect(wp, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    wp->mainFrame()->load(url);
}

void HB::_loadFinished(bool ok){
    QObject::disconnect(wp, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    std::cout << wp->mainFrame()->toHtml().toUtf8().data();
    QApplication::quit();
}
