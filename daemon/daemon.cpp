#include "daemon.h"

Daemon::Daemon() : QWebPage(){
    this->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    this->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    this->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    QObject::connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(createJSMonitor()));
}

void Daemon::createJSMonitor(){
    mainFrame()->addToJavaScriptWindowObject("HeadlessBrowser", this);
}

void Daemon::_load(QUrl url){
    nam = new NAM();
    this->setNetworkAccessManager(nam);
    QObject::connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    this->mainFrame()->load(url);
}

bool Daemon::shouldInterruptJavaScript(){
    return false;
}

void Daemon::javaScriptConsoleMessage(const QString &message, int lineNumber,const QString &sourceID){
    if (!sourceID.isEmpty()){
        QString error = sourceID + ":" + QString::number(lineNumber) + " " + message + "\n\n";
        //qDebug() << error;
    }
}

void Daemon::_loadFinished(bool ok){
    QObject::disconnect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));

    //QWebElement document = this->mainFrame()->documentElement();
    //QWebElement body = document.findFirst("body");
    //qDebug() << body.attribute("onload");
    //body.setAttribute("onload", "HeadlessBrowser.genSnapshot();");
    //qDebug() << body.attribute("onload");

}

void Daemon::genSnapshot(int result){
    if(result == 0 && results >= 10){
        QWebElement document = this->mainFrame()->documentElement();

        //Uncomment to strip scripts
        foreach(QWebElement data, document.findAll("script")){
            data.removeFromDocument();
        }

        //Uncomment to strip styles (does styles matter for SEO?)
        foreach(QWebElement data, document.findAll("style")){
            data.removeFromDocument();
        }

        emit newSnapshot(mainFrame()->toHtml());
    }else{
        result++;
    }
}
