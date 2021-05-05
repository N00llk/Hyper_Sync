#pragma once

#define NAMES_SAME_CONTENT_DIFF 1
#define NAMES_DIFF_CONTENT_DIFF 2
#define NAMES_DIFF_CONTENT_SAME 3
#define NAMES_SAME_CONTENT_SAME 4

#define FIRST_FILE_NOT_EXIST  -1
#define SECOND_FILE_NOT_EXIST -2

#define BLOCK_SIZE  (1 << 20)
#define BLOCK_COUNT (1 << 6)

#include <QString>
#include <QByteArray>

class LibFCL
{
public:
    LibFCL();
    ~LibFCL();
    int compare(QString firstFilePath, QString secondFilePath);
private:
    bool compareBlocks(char* block1, char* block2);
    void clearBlocks(void);

    QString firstFile;
    QString secondFile;

    char* block1;
    char* block2;

    QByteArray fileContent1;
    QByteArray fileContent2;
};
