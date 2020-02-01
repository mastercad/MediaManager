#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

class Database
{
public:
    Database();
    ~Database();

    bool connect();
    bool init();

    bool importDump(QString dumpFilePathName);
    unsigned int fetchVersion() const;

    bool fetch();
    bool insert();
    bool update();
    bool remove();
};

#endif // DATABASE_H
