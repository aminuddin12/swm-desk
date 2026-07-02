#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "WindowId.h"

class WindowFactory {
public:
    static QObject* createWindow(WindowId id, QQmlApplicationEngine *engine, QObject *parent = nullptr);
};

#endif
