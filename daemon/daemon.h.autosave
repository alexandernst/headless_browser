#ifndef HB_H
#define HB_H

#include <iostream>
#include <fstream>
#include <QtWidgets/QApplication>

#include <QtWebKit>
#include <QWebFrame>
#include <QWebView>
#include <QWebInspector>

#include "nam.h"

class Daemon : public QWebPage {
    Q_OBJECT

    public:
        Daemon();
        void _load(QUrl url);
        Q_INVOKABLE void genSnapshot();

    private:
        NAM *nam;
        QWebPage *wp;
        QTimer *timer;
        QString dom_content;

    public slots:
        void _loadFinished(bool ok);
        bool shouldInterruptJavaScript();

    private slots:
        void timeout();
        void createJSMonitor();

    protected:
        void javaScriptConsoleMessage(const QString &message, int lineNumber,const QString &sourceID);

};

#endif // HB_H
