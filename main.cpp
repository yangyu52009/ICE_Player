#include "mainwindow.h"

#include <QFileInfo>
#include <QStringList>
#include <QSettings>

#include "singleapplication.h"
static void associateFileTypes(const QStringList& fileTypes);

int main(int argc, char *argv[])
{
    QApplication::addLibraryPath ("./plugins");
    SingleApplication app(argc, argv, "iceplayer");

   // associateFileTypes (QStringList(".mp3"));
    const QStringList arguments = QCoreApplication::arguments ();


    return app.exec();
}

/*************************************************
**Function:    associateFileTypes    // 函数名称
**Description:  将指定的文件类型进行注册 // 函数功能描述
*************************************************/
static void associateFileTypes(const QStringList& fileTypes)
{
    QString displayName = QGuiApplication::applicationDisplayName ();
    QString filePath = QCoreApplication::applicationFilePath ();
    QString fileName = QFileInfo(filePath).fileName ();

    QSettings settings ( "HKEY_CURRENT_USER\\Software\\Classes\\Applications\\" + fileName,
                        QSettings::NativeFormat );
    settings.setValue ( "FriendlyAppName", displayName);

    settings.beginGroup ("SupportedTypes");

    foreach (const QString& fileType, fileTypes)
        settings.setValue (fileTypesm, QString());

    settings.endGroup ();

    settings.beginGroup ("shell");
        settings.beginGroup ("open");
        settings.setValue ("FriendlyAppName", displayName);
            settings.beginGroup ("Command");
            settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
            settings.endGroup ();
        settings.endGroup ();
    settings.endGroup ();

}
