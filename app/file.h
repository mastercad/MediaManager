#ifndef FILE_H
#define FILE_H

#include <QString>

class File
{
public:
    File();

private:
    unsigned int id;
    QString name;
    QString path;
    QString extension;
    QString origin;
    QString originUrl;
    QString originId;
    QString state;
    QString description;
    QString previewPath;
    unsigned int ranking;
};

#endif // FILE_H
