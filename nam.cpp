#include "nam.h"

NAM::NAM(){
    requests = 0;
    QObject::connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(_finished(QNetworkReply*)));
}

QNetworkReply* NAM::createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData = 0){
    requests++;
    if(
            req.url().path().endsWith("jpg") ||
            req.url().path().endsWith("png") ||
            req.url().path().endsWith("gif") ||
            req.url().path().endsWith("ttf") ||
            req.url().path().endsWith("svg") ||
            req.url().path().endsWith("eot") ||
            req.url().path().endsWith("jpeg") ||
            req.url().path().endsWith("woff")
      ){
        return QNetworkAccessManager::createRequest(QNetworkAccessManager::GetOperation, QNetworkRequest(QUrl()));
    }else{
        return QNetworkAccessManager::createRequest(op, req, outgoingData);
    }
}

int NAM::pendingRequests(){
    return requests;
}

void NAM::_finished(QNetworkReply *reply){
    requests--;
}
