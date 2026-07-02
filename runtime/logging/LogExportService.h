#ifndef LOGEXPORTSERVICE_H
#define LOGEXPORTSERVICE_H

#include <QObject>
#include <QString>

class LogExportService : public QObject {
    Q_OBJECT

public:
    explicit LogExportService(QObject *parent = nullptr);
    ~LogExportService() override;

    Q_INVOKABLE void exportLogs(const QString &filePath, const QString &format);
};

#endif
