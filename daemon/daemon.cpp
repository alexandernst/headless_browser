#include "daemon.h"

Daemon::Daemon() : QWebPage(){
    results = 0;
    settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    QObject::connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(createJSMonitor()));
}

void Daemon::createJSMonitor(){
    mainFrame()->addToJavaScriptWindowObject("HeadlessBrowser", this);
}

void Daemon::_load(QUrl url){
    nam = new NAM();
    setNetworkAccessManager(nam);
    QObject::connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    mainFrame()->load(url);
}

bool Daemon::shouldInterruptJavaScript(){
    return false;
}

void Daemon::javaScriptConsoleMessage(const QString &message, int lineNumber,const QString &sourceID){
    if(!sourceID.isEmpty()){
        QString error = sourceID + ":" + QString::number(lineNumber) + " " + message;
        qDebug() << error;
    }
}

void Daemon::_loadFinished(bool ok){
    QObject::disconnect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));

    QFile ftimer(":/js/timer.js");
    ftimer.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray dtimer = ftimer.readAll();
    ftimer.close();
    mainFrame()->evaluateJavaScript(QString(dtimer));

    QFile fprogress(":/js/progress.js");
    fprogress.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray dprogress = fprogress.readAll();
    fprogress.close();
    mainFrame()->evaluateJavaScript(QString(dprogress));

    mainFrame()->evaluateJavaScript("timer.callibrate(function(){ timer.collect(); collector.start(); });");
}

void Daemon::genSnapshot(int result){
    int IDLE_HITS = 8;
    int IDLE_NOISE = 10;

    if(result <= IDLE_NOISE && results >= IDLE_HITS){
        QWebElement document = mainFrame()->documentElement();

        //Uncomment to strip scripts
        foreach(QWebElement data, document.findAll("script")){
            data.removeFromDocument();
        }

        //Uncomment to strip styles (does styles matter for SEO?)
        foreach(QWebElement data, document.findAll("style")){
            data.removeFromDocument();
        }

        emit newSnapshot(mainFrame()->toHtml());
        deleteLater();
    }else if(result <= IDLE_NOISE){
        results++;
    }else{
        results = 0;
    }
}
