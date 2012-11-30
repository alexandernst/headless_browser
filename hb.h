#ifndef HB_H
#define HB_H

#include <iostream>
#include <QApplication>
#include <QtWebKit/QtWebKit>
#include "nam.h"

class HB : public QWebPage {
    Q_OBJECT

    public:
        HB();
        void _load(QUrl url);

    private:
        NAM *nam;
        QWebPage *wp;
        QTimer *timer;
        QString dom_content;
        void genSnapshot();

    public slots:
        void _loadFinished(bool ok);
        bool shouldInterruptJavaScript();

    private slots:
        void timeout();

    protected:
        void javaScriptConsoleMessage(const QString &message, int lineNumber,const QString &sourceID);

};

#endif // HB_H
