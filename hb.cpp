#include "hb.h"

HB::HB(){
    this->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    this->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
}

void HB::_load(QUrl url){
    nam = new NAM();
    this->setNetworkAccessManager(nam);
    QObject::connect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    this->mainFrame()->load(url);

}

bool HB::shouldInterruptJavaScript(){
    return false;
}

void HB::javaScriptConsoleMessage(const QString &message, int lineNumber,const QString &sourceID){
    if (!sourceID.isEmpty()){
        QString error = sourceID + ":" + QString::number(lineNumber) + " " + message + "\n";
        std::cout << error.toUtf8().data();
    }
}

void HB::_loadFinished(bool ok){
    QObject::disconnect(this, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    timer = new QTimer();

    timer->setInterval(1000); //FIXME: this is ugly. Find a better way to know when a page really finished loading.
    //NOTE: This has nothing to do with the "loadFinished" event, which is called as soon as everything is downloaded.
    //The difficult part is detecting if there are any JavaScript calls remaining (in queue), for example, AJAX requests,
    //setTimeout calls, maybe even a JavaScript MVC library, etc...

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start();
}

void HB::timeout(){
    QString current_content = this->mainFrame()->toHtml();
    if(dom_content == current_content){
        QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

        QWebElement document = this->mainFrame()->documentElement();

        //Comment to strip scripts
        foreach(QWebElement data, document.findAll("script")){
            data.removeFromDocument();
        }

        //Uncomment to strip styles (does styles matter for SEO?)
        //foreach(QWebElement data, document.findAll("style")){
        //    data.removeFromDocument();
        //}

        std::cout << this->mainFrame()->toHtml().toUtf8().data();
        QApplication::quit();
    }else{
        dom_content = current_content;
    }
}
