#include <iostream>
#include <fstream>
#include <QtCore/QCoreApplication>
#include <../socket-ipc/client/client.h>

using namespace std;

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    Client *client = new Client("ipc");

    QObject::connect(client, &Client::newMessageFromServer, [](QString message){
        std::cout << message.toUtf8().data();
        qDebug() << "new message:" << message;

        ofstream file;
        file.open("snapshot.html");
        file << message.toUtf8().data();
        file.close();
    });

    client->sendMessage(argv[1]);

    return a.exec();
}
