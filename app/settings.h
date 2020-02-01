#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    Settings();
private:
    unsigned int id;
    QString key;
    QString value;
};

#endif // SETTINGS_H
