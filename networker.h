#ifndef NETWORKER_H
#define NETWORKER_H

#include <QObject>



/*****************************************************
**Copyright(C), 2017-2025, zl software.
**Version: 0.1
**Author: zl
**Date: 20170811
**Description:对于QNetWorkAccessManager的简单封装
** 仅仅是将其改为了使用单例模式
** PS：
** 已经经过简单测试
*****************************************************/
class QNetworkReply;
class NetWorker : public QObject
{
    Q_OBJECT
public:
    //该类使用单例模式，这是获取该类实例的一般唯一方法
    static NetWorker *instance();
    ~NetWorker();
    //向目标地址发送get请求
    void get (const QString& url);
signals:
    void finished (QNetworkReply* reply );

private:
    class NetWorker_p;
    friend class NetWorker_p;
    NetWorker_p* d;

    //单例模式下，类的构造函数，复制构造函数和赋值运算符声明为 私有的
    explicit NetWorker(QObject *parent = 0);
    NetWorker (const NetWorker &) = delete;
    NetWorker &operator =(NetWorker rhs) Q_DECL_EQ_DELETE;
};

#endif // NETWORKER_H
