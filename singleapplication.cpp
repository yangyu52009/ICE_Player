#include "singleapplication.h"

#include <QLocalSocket>


SingleApplication::SingleApplication(int &arg,
                                     char *argv[],
                                     const QString uniqueKey):
    QApplication(argc, argv, m_uniqueKey(uniqueKey))
{
    this->m_sharedMemory.setKey ( uniqueKey );
    if(m_sharedMemory.attach ())
        this->m_isRunning = true;
    else{
        this->m_isRunning = false;
        if(!m_sharedMemory.create ( 1 )){
            qDebug() << "Unable to create single instance";
            return ;
        }
        //使用共享内存标记判断是否只是启动了一个
        this->m_localServer = new QLocalServer(this);
        connect (this->m_localServer, &QLocalServer::newConnection,
                 this, &SingleApplication::receiveMessage);
        m_localServer->listen ( m_uniqueKey );
    }

}

bool SingleApplication::isRunning()
{
    return this->m_isRunning;
}

bool SingleApplication::sendMessage(const QString &message)
{

}

void SingleApplication::receiveMessage()
{
    QLocalSocket* localSocket = this->m_localServer->nextPendingConnection ();
    if(!localSocket->waitForReadyRead ( this->timeout )) { //timeout = 1000
        qDebug(localSocket->errorString ().toLatin1 ());
        return ;
    }
    QByteArray byteArray = localSocket->readAll ();
    QString message = QString::fromUtf8 ( byteArray.constData () );
    emit this->messageAvailable (message);
    localSocket->disconnectFromServer ();
}
