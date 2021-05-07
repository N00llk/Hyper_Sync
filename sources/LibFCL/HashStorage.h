#pragma once

#include <QHash>
#include <QVector>
#include <QByteArray>


class HashStorage
{
public:
    HashStorage();
    void addFile(QString filePath);
private:
    QHash <QString, QVector<QByteArray>> storage;
};

