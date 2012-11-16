#ifndef NAM_H
#define NAM_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class NAM : public QNetworkAccessManager {
    protected:
        virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData = 0){
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
};

#endif // NAM_H
