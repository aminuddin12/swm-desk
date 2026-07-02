#include "LogListModel.h"
#include "../../application/services/ServiceRegistry.h"
#include <QRegularExpression>

LogListModel::LogListModel(QObject *parent) : QAbstractListModel(parent) {
    auto &registry = ServiceRegistry::instance();
    bus = std::any_cast<std::shared_ptr<IEventBus>>(registry.resolve("IEventBus"));
    repo = std::any_cast<std::shared_ptr<LogRepository>>(registry.resolve("LogRepository"));

    if (bus) {
        tokenAdded = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::any &payload) {
            auto entry = std::any_cast<std::shared_ptr<LogEntry>>(payload);
            if (matchesFilter(entry)) {
                beginInsertRows(QModelIndex(), filteredLogs.size(), filteredLogs.size());
                filteredLogs.push_back(entry);
                endInsertRows();
            }
        });

        tokenCleared = bus->subscribe(RuntimeEvent::MemoryLogsCleared, [this](const std::any &payload) {
            (void)payload;
            beginResetModel();
            filteredLogs.clear();
            endResetModel();
        });
    }

    rebuildFilteredLogs();
}

LogListModel::~LogListModel() {
    if (bus) {
        bus->unsubscribe(tokenAdded);
        bus->unsubscribe(tokenCleared);
    }
}

int LogListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(filteredLogs.size());
}

QVariant LogListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= static_cast<int>(filteredLogs.size())) {
        return QVariant();
    }

    const auto &entry = filteredLogs[index.row()];
    switch (role) {
        case TimeRole: {
            if (entry->timestamp.size() >= 19) {
                return QString::fromStdString(entry->timestamp.substr(11, 8));
            }
            return QString::fromStdString(entry->timestamp);
        }
        case LevelRole: {
            switch (entry->level) {
                case LogLevel::Trace: return "TRACE";
                case LogLevel::Debug: return "DEBUG";
                case LogLevel::Info: return "INFO";
                case LogLevel::Success: return "SUCCESS";
                case LogLevel::Warning: return "WARN";
                case LogLevel::Error: return "ERROR";
                case LogLevel::Critical: return "CRITICAL";
            }
            return "UNKNOWN";
        }
        case CategoryRole: {
            switch (entry->category) {
                case LogCategory::Runtime: return "Runtime";
                case LogCategory::OBS: return "OBS";
                case LogCategory::UI: return "UI";
                case LogCategory::Plugin: return "Plugin";
                case LogCategory::Marketplace: return "Marketplace";
            }
            return "Unknown";
        }
        case ThreadRole: return QString::fromStdString(entry->threadId);
        case MessageRole: return QString::fromStdString(entry->message);
        case SessionIdRole: return QString::fromStdString(entry->sessionId);
        case ProcessIdRole: return entry->processId;
        case PlatformRole: return QString::fromStdString(entry->platform);
        case AppVersionRole: return QString::fromStdString(entry->applicationVersion);
        case SourceRole: return "AppBootstrap.cpp:42";
    }

    return QVariant();
}

QHash<int, QByteArray> LogListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TimeRole] = "time";
    roles[LevelRole] = "level";
    roles[CategoryRole] = "category";
    roles[ThreadRole] = "thread";
    roles[MessageRole] = "message";
    roles[SessionIdRole] = "sessionId";
    roles[ProcessIdRole] = "processId";
    roles[PlatformRole] = "platform";
    roles[AppVersionRole] = "appVersion";
    roles[SourceRole] = "source";
    return roles;
}

void LogListModel::setLevelFilter(const QString &val) {
    if (m_levelFilter != val) {
        m_levelFilter = val;
        emit levelFilterChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setCategoryFilter(const QString &val) {
    if (m_categoryFilter != val) {
        m_categoryFilter = val;
        emit categoryFilterChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setSearchQuery(const QString &val) {
    if (m_searchQuery != val) {
        m_searchQuery = val;
        emit searchQueryChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setCaseSensitive(bool val) {
    if (m_caseSensitive != val) {
        m_caseSensitive = val;
        emit caseSensitiveChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setRegexEnabled(bool val) {
    if (m_regexEnabled != val) {
        m_regexEnabled = val;
        emit regexEnabledChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setWholeWord(bool val) {
    if (m_wholeWord != val) {
        m_wholeWord = val;
        emit wholeWordChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setSessionFilter(const QString &val) {
    if (m_sessionFilter != val) {
        m_sessionFilter = val;
        emit sessionFilterChanged();
        rebuildFilteredLogs();
    }
}

void LogListModel::setAutoScroll(bool val) {
    if (m_autoScroll != val) {
        m_autoScroll = val;
        emit autoScrollChanged();
    }
}

void LogListModel::clearFilters() {
    m_levelFilter = "All";
    m_categoryFilter = "All";
    m_searchQuery = "";
    m_caseSensitive = false;
    m_regexEnabled = false;
    m_wholeWord = false;
    m_sessionFilter = "Current";
    m_autoScroll = true;
    emit levelFilterChanged();
    emit categoryFilterChanged();
    emit searchQueryChanged();
    emit caseSensitiveChanged();
    emit regexEnabledChanged();
    emit wholeWordChanged();
    emit sessionFilterChanged();
    emit autoScrollChanged();
    rebuildFilteredLogs();
}

QVariantMap LogListModel::getRow(int row) const {
    QVariantMap map;
    if (row >= 0 && row < static_cast<int>(filteredLogs.size())) {
        const auto &entry = filteredLogs[row];
        map["time"] = QString::fromStdString(entry->timestamp);
        
        switch (entry->level) {
            case LogLevel::Trace: map["level"] = "TRACE"; break;
            case LogLevel::Debug: map["level"] = "DEBUG"; break;
            case LogLevel::Info: map["level"] = "INFO"; break;
            case LogLevel::Success: map["level"] = "SUCCESS"; break;
            case LogLevel::Warning: map["level"] = "WARN"; break;
            case LogLevel::Error: map["level"] = "ERROR"; break;
            case LogLevel::Critical: map["level"] = "CRITICAL"; break;
        }

        switch (entry->category) {
            case LogCategory::Runtime: map["category"] = "Runtime"; break;
            case LogCategory::OBS: map["category"] = "OBS"; break;
            case LogCategory::UI: map["category"] = "UI"; break;
            case LogCategory::Plugin: map["category"] = "Plugin"; break;
            case LogCategory::Marketplace: map["category"] = "Marketplace"; break;
        }

        map["thread"] = QString::fromStdString(entry->threadId);
        map["message"] = QString::fromStdString(entry->message);
        map["sessionId"] = QString::fromStdString(entry->sessionId);
        map["processId"] = entry->processId;
        map["platform"] = QString::fromStdString(entry->platform);
        map["appVersion"] = QString::fromStdString(entry->applicationVersion);
        map["source"] = "AppBootstrap.cpp:42";
    }
    return map;
}

void LogListModel::rebuildFilteredLogs() {
    beginResetModel();
    filteredLogs.clear();
    if (repo) {
        auto allLogs = repo->getLogs();
        for (const auto &entry : allLogs) {
            if (matchesFilter(entry)) {
                filteredLogs.push_back(entry);
            }
        }
    }
    endResetModel();
}

bool LogListModel::matchesFilter(const std::shared_ptr<LogEntry> &entry) const {
    if (m_levelFilter != "All") {
        QString itemLevel;
        switch (entry->level) {
            case LogLevel::Trace: itemLevel = "TRACE"; break;
            case LogLevel::Debug: itemLevel = "DEBUG"; break;
            case LogLevel::Info: itemLevel = "INFO"; break;
            case LogLevel::Success: itemLevel = "SUCCESS"; break;
            case LogLevel::Warning: itemLevel = "WARN"; break;
            case LogLevel::Error: itemLevel = "ERROR"; break;
            case LogLevel::Critical: itemLevel = "CRITICAL"; break;
        }
        if (itemLevel != m_levelFilter) {
            return false;
        }
    }

    if (m_categoryFilter != "All") {
        QString itemCat;
        switch (entry->category) {
            case LogCategory::Runtime: itemCat = "Runtime"; break;
            case LogCategory::OBS: itemCat = "OBS"; break;
            case LogCategory::UI: itemCat = "UI"; break;
            case LogCategory::Plugin: itemCat = "Plugin"; break;
            case LogCategory::Marketplace: itemCat = "Marketplace"; break;
        }
        if (itemCat != m_categoryFilter) {
            return false;
        }
    }

    if (m_sessionFilter == "Current") {
        if (repo) {
            std::string currentSession = repo->getSessionId();
            if (!currentSession.empty() && entry->sessionId != currentSession) {
                return false;
            }
        }
    } else if (m_sessionFilter == "Previous") {
        if (repo) {
            std::string currentSession = repo->getSessionId();
            if (entry->sessionId == currentSession) {
                return false;
            }
        }
    }

    if (!m_searchQuery.isEmpty()) {
        QString text = QString::fromStdString(entry->message);
        if (m_regexEnabled) {
            QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
            if (!m_caseSensitive) {
                options |= QRegularExpression::CaseInsensitiveOption;
            }
            QString pattern = m_searchQuery;
            if (m_wholeWord) {
                pattern = "\\b" + pattern + "\\b";
            }
            QRegularExpression re(pattern, options);
            if (!re.match(text).hasMatch()) {
                return false;
            }
        } else {
            Qt::CaseSensitivity cs = m_caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
            if (m_wholeWord) {
                QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
                if (!m_caseSensitive) {
                    options |= QRegularExpression::CaseInsensitiveOption;
                }
                QRegularExpression re("\\b" + QRegularExpression::escape(m_searchQuery) + "\\b", options);
                if (!re.match(text).hasMatch()) {
                    return false;
                }
            } else {
                if (!text.contains(m_searchQuery, cs)) {
                    return false;
                }
            }
        }
    }

    return true;
}
