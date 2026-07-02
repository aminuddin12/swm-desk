#ifndef LOGLISTMODEL_H
#define LOGLISTMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <memory>
#include "LogEntry.h"
#include "LogRepository.h"
#include "../../core/contracts/IEventBus.h"

class LogListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString levelFilter READ levelFilter WRITE setLevelFilter NOTIFY levelFilterChanged)
    Q_PROPERTY(QString categoryFilter READ categoryFilter WRITE setCategoryFilter NOTIFY categoryFilterChanged)
    Q_PROPERTY(QString searchQuery READ searchQuery WRITE setSearchQuery NOTIFY searchQueryChanged)
    Q_PROPERTY(bool caseSensitive READ caseSensitive WRITE setCaseSensitive NOTIFY caseSensitiveChanged)
    Q_PROPERTY(bool regexEnabled READ regexEnabled WRITE setRegexEnabled NOTIFY regexEnabledChanged)
    Q_PROPERTY(bool wholeWord READ wholeWord WRITE setWholeWord NOTIFY wholeWordChanged)
    Q_PROPERTY(QString sessionFilter READ sessionFilter WRITE setSessionFilter NOTIFY sessionFilterChanged)
    Q_PROPERTY(bool autoScroll READ autoScroll WRITE setAutoScroll NOTIFY autoScrollChanged)

public:
    enum LogRoles {
        TimeRole = Qt::UserRole + 1,
        LevelRole,
        CategoryRole,
        ThreadRole,
        MessageRole,
        SessionIdRole,
        ProcessIdRole,
        PlatformRole,
        AppVersionRole,
        SourceRole
    };

    explicit LogListModel(QObject *parent = nullptr);
    ~LogListModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString levelFilter() const { return m_levelFilter; }
    void setLevelFilter(const QString &val);

    QString categoryFilter() const { return m_categoryFilter; }
    void setCategoryFilter(const QString &val);

    QString searchQuery() const { return m_searchQuery; }
    void setSearchQuery(const QString &val);

    bool caseSensitive() const { return m_caseSensitive; }
    void setCaseSensitive(bool val);

    bool regexEnabled() const { return m_regexEnabled; }
    void setRegexEnabled(bool val);

    bool wholeWord() const { return m_wholeWord; }
    void setWholeWord(bool val);

    QString sessionFilter() const { return m_sessionFilter; }
    void setSessionFilter(const QString &val);

    bool autoScroll() const { return m_autoScroll; }
    void setAutoScroll(bool val);

    Q_INVOKABLE void clearFilters();
    Q_INVOKABLE QVariantMap getRow(int row) const;

signals:
    void levelFilterChanged();
    void categoryFilterChanged();
    void searchQueryChanged();
    void caseSensitiveChanged();
    void regexEnabledChanged();
    void wholeWordChanged();
    void sessionFilterChanged();
    void autoScrollChanged();

private:
    void rebuildFilteredLogs();
    bool matchesFilter(const std::shared_ptr<LogEntry> &entry) const;

    std::shared_ptr<IEventBus> bus;
    std::shared_ptr<LogRepository> repo;
    SubscriptionToken tokenAdded;
    SubscriptionToken tokenCleared;

    std::vector<std::shared_ptr<LogEntry>> filteredLogs;

    QString m_levelFilter = "All";
    QString m_categoryFilter = "All";
    QString m_searchQuery = "";
    bool m_caseSensitive = false;
    bool m_regexEnabled = false;
    bool m_wholeWord = false;
    QString m_sessionFilter = "Current";
    bool m_autoScroll = true;
};

#endif
