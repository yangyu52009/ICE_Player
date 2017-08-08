#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H
#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>
/*!class!
*
* PS:
*   bool sendMessage 函数作用未知，暂时没有实现
*/
class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    SingleApplication(int &arg, char* argv[], const QString uniqueKey);
    bool isRunning();
    bool sendMessage(const QString& message);
public slots:
    void receiveMessage();
signals:
    void messageAvailable(QString message);
private:
    bool m_isRunning;
    QString m_uniqueKey;
    QSharedMemory m_sharedMemory;
    QLocalServer* m_localServer;
    static const int timeout = 1000;
};

#endif // SINGLEAPPLICATION_H
