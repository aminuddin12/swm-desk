#ifndef APPBOOTSTRAP_H
#define APPBOOTSTRAP_H

#include <QObject>
#include <QQmlApplicationEngine>

class LogExportService;

class AppBootstrap : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString appDir READ getAppDir CONSTANT)

public:
    explicit AppBootstrap(QObject *parent = nullptr);
    ~AppBootstrap();

    void bootstrap();
    QString getAppDir() const;

private:
    QQmlApplicationEngine qmlEngine;
    LogExportService *logExport = nullptr;
};

#endif
