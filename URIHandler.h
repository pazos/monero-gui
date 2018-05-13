#ifndef URIHANDLER_H
#define URIHANDLER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

class URIHandler : public QObject
{
    Q_OBJECT
public:
    explicit URIHandler(QObject *parent = 0);
    ~URIHandler();

    void listen(QString name);
    bool hasURI(QString name, QStringList arg);

signals:
    void newInstance();

public slots:
    void newConnection();
    void readyRead();

private:
    QLocalSocket* mSocket;
    QLocalServer mServer;
};

#endif // URIHANDLER_H
