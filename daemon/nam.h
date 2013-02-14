#ifndef NAM_H
#define NAM_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class NAM : public QNetworkAccessManager {
    Q_OBJECT

    protected:
        virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData);
};

#endif // NAM_H
