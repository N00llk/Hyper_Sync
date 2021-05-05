#include "LibFCL.h"

#include <QFileInfo>
#include <QCryptographicHash>
#include <QDebug>

LibFCL::LibFCL():
    block1(new char [BLOCK_SIZE]),
    block2(new char [BLOCK_SIZE])
{
    clearBlocks();
}

LibFCL::~LibFCL()
{
    delete [] block1;
    delete [] block2;
}

int LibFCL::compare(QString firstFilePath, QString secondFilePath)
{
    QFileInfo firstFI(firstFilePath);
    QFileInfo secondFI(secondFilePath);

    if (!firstFI.exists())
        return FIRST_FILE_NOT_EXIST;

    if (!secondFI.exists())
        return SECOND_FILE_NOT_EXIST;

    if (firstFI.size() != secondFI.size())
    {
        qDebug() << firstFI.size() << " " << secondFI.size();
        if (firstFI.fileName() != secondFI.fileName())
        {
            return NAMES_DIFF_CONTENT_DIFF;
        }
        else
        {
            return NAMES_SAME_CONTENT_DIFF;
        }
    }

    QFile file1(firstFI.absoluteFilePath());
    QFile file2(secondFI.absoluteFilePath());

    if (!file1.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия первого файла!";
        return FIRST_FILE_NOT_EXIST;
    }

    if (!file2.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия второго файла!";
        return SECOND_FILE_NOT_EXIST;
    }

    QByteArray data_1;
    QByteArray data_2;

    QByteArray hash_1;
    QByteArray hash_2;

    bool fileDiff = false;
    uint64_t block_count = file1.size() / BLOCK_SIZE;
    uint64_t block = 0;

    while (true)
    {
        qDebug().noquote() << "Обработано блоков: " << block << "/" << block_count << '\r';
        block++;

        data_1 = file1.read(BLOCK_SIZE);
        data_2 = file2.read(BLOCK_SIZE);

        if (!data_1.size() || !data_2.size())
        {
            break;
        }

        data_1 = data_1.leftJustified(BLOCK_SIZE, '\0', true);
        data_2 = data_2.leftJustified(BLOCK_SIZE, '\0', true);

        hash_1 = QCryptographicHash::hash(data_1, QCryptographicHash::Sha1);
        hash_2 = QCryptographicHash::hash(data_2, QCryptographicHash::Sha1);

        if (hash_1 != hash_2)
        {
            fileDiff = true;
            break;
        }

        fileContent1.append(data_1);
        fileContent2.append(data_2);

        if ((fileContent1.size() >> 12) == BLOCK_COUNT)
        {
            hash_1 = QCryptographicHash::hash(fileContent1, QCryptographicHash::Sha3_256);
            hash_2 = QCryptographicHash::hash(fileContent2, QCryptographicHash::Sha3_256);

            fileContent1.clear();
            fileContent2.clear();

            if (hash_1 != hash_2)
            {
                fileDiff = true;
                break;
            }
        }
    }

    file1.close();
    file2.close();

    if (fileDiff)
    {
        if (firstFI.fileName() != secondFI.fileName())
        {
            return NAMES_DIFF_CONTENT_DIFF;
        }
        else
        {
            return NAMES_SAME_CONTENT_DIFF;
        }
    }
    else
    {
        if (firstFI.fileName() != secondFI.fileName())
        {
            return NAMES_DIFF_CONTENT_SAME;
        }
        else
        {
            return NAMES_SAME_CONTENT_SAME;
        }
    }
}

bool LibFCL::compareBlocks(char *block1, char *block2)
{
    char* tmp1 = block1;
    char* tmp2 = block2;

    for (int i = 0; i < BLOCK_SIZE; ++i, tmp1++, tmp2++)
    {
        if (*tmp1 != *tmp2)
        {
            return false;
        }
    }
    return true;
}

void LibFCL::clearBlocks()
{
    memset(block1, 0, BLOCK_SIZE);
    memset(block2, 0, BLOCK_SIZE);
}
