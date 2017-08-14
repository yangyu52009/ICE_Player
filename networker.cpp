#include "networker.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class NetWorker::NetWorker_p
{
public:
    NetWorker_p(NetWorker* q) : manager(new QNetworkAccessManager(q)){

    }
    QNetworkAccessManager* manager;
};


NetWorker *NetWorker::instance()
{
    static NetWorker netWorker;
    return &netWorker;
}

NetWorker::~NetWorker()
{
    delete this->d;
    d = nullptr;
}

void NetWorker::get(const QString &url)
{
    this->d->manager->get (QNetworkRequest(QUrl(url)));
}

NetWorker::NetWorker(QObject *parent) :
    QObject(parent)
{
    this->d = new NetWorker_p( this );
    this->connect (d->manager, &QNetworkAccessManager::finished,
                   this, &NetWorker::finished);
}
