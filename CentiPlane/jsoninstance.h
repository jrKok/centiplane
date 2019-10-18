#ifndef JSONINSTANCE_H
#define JSONINSTANCE_H

#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QDebug>

class JsonInstance
{
public:
    JsonInstance();
    void ReadInstanceData();
    void WriteInstanceData();
private:
    bool isGroup;
};

#endif // JSONINSTANCE_H
