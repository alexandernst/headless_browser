#ifndef HB_H
#define HB_H

#include <iostream>
#include <QApplication>
#include <QtWebKit/QtWebKit>
#include "nam.h"

class HB : public QWebPage {
    Q_OBJECT

    public:
        void _load(QUrl url);

    private:
        NAM *nam;
        QWebPage *wp;

    public slots:
        void _loadFinished(bool ok);

};

#endif // HB_H
