#pragma once

#include <QHash>


class HashStorage
{
public:
    HashStorage();
    void addFile(QString filePath);
private:
    QHash <QString, QVector<QByteArray>> storage;
};

