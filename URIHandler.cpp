#include "URIHandler.h"
#include "WalletManager.h"

URIHandler::URIHandler(QObject *parent) : QObject(parent)
{
    connect(&mServer, SIGNAL(newConnection()),this,SLOT(newConnection()));
}

URIHandler::~URIHandler()
{
}

void URIHandler::listen(QString name)
{
    mServer.removeServer(name);
    mServer.listen(name);
}

bool URIHandler::hasURI(QString name, QStringList arg)
{
    QLocalSocket socket;
    std::string uri_scheme = "monero:";
    socket.connectToServer(name, QLocalSocket::ReadWrite);

    if(socket.waitForConnected())
    {
        QByteArray buffer;
        foreach(QString item, arg)
        {
            if(item.toStdString().substr(0, uri_scheme.size()) == uri_scheme)
            {
                buffer.append(item);
                socket.write(buffer);
                socket.waitForBytesWritten();
                return true;
            }
        }
    }
    return false;
}

void URIHandler::newConnection()
{
    emit newInstance();

    mSocket = mServer.nextPendingConnection();
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void URIHandler::readyRead()
{
    QString url = mSocket->readAll();
    WalletManager::parse_uri(url);
    mSocket->deleteLater();
}

