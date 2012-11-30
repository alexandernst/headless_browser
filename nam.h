#ifndef NAM_H
#define NAM_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class NAM : public QNetworkAccessManager {
    Q_OBJECT

    private:
        int requests;

    public:
        NAM();
        int pendingRequests();

    protected:
        virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest &req, QIODevice *outgoingData);

    private slots:
        void _finished(QNetworkReply *reply);
};

#endif // NAM_H
