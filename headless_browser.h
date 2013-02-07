#ifndef HB_H
#define HB_H

#include <iostream>
#include <QtWidgets/QApplication>

#include <QtWebKit>
#include <QWebFrame>
#include <QWebView>

#include "nam.h"

class HeadlessBrowser : public QWebPage {
    Q_OBJECT

    public:
        HeadlessBrowser();
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
