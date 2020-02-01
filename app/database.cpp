#include "database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QSqlError>
#include <QFile>
#include <QTextStream>

#include <QDebug>

Database::Database() {
    const unsigned int VERSION = 1;
    connect();

    unsigned int currentDbVersion = fetchVersion();

    if (currentDbVersion < VERSION) {
        init();
    }
}

Database::~Database() {
    QSqlDatabase db;
    db.close();
}

bool Database::connect() {
    const QString DRIVER("QSQLITE");
    //    QString path =":memory:";
    QString path = QCoreApplication::applicationDirPath() + "/MediaManager.db";

    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(path);

        if(!db.open()) {
            qWarning() << "Database::connect - ERROR: " << db.lastError().text();
            return false;
        }
    } else {
        qWarning() << "Database::connect - ERROR: no driver " << DRIVER << " available";
        return false;
    }
    return true;
}

bool Database::importDump(QString dumpFilePathName) {
    QFile file(dumpFilePathName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qFatal(QString("Database::init - ERROR: Database dump not found!").toLocal8Bit());
    }
    QTextStream in(&file);
    QStringList createQueriesContent = in.readAll().split(';');
    QSqlDatabase db;
    QSqlQuery query(db);

    foreach (QString createQuery, createQueriesContent) {
        if (createQuery.trimmed().isEmpty()) {
            continue;
        }
        if (!query.exec(createQuery)) {
            qFatal(QString("Dump cant imported! Error detail: " + query.lastError().text()).toLocal8Bit());
        }
        query.finish();
    }
    return true;
}

bool Database::init() {
    return importDump(QCoreApplication::applicationDirPath() + "/db_create_2.sql");
}

unsigned int Database::fetchVersion() const {
    QSqlDatabase db;
    QSqlQuery query(db);

    query.exec("SELECT version FROM migrations ORDER BY date_time ASC LIMIT 1");
    QString lastError = query.lastError().text();

    if (query.first()) {
        return query.value(0).toUInt();
    }

    // no migration started before
    if (query.lastError().isValid()
        && lastError.contains("no such table: migrations", Qt::CaseInsensitive)
    ) {
        return 0;
    }

    qFatal(QString("Database::fetchVersion - ERROR: "+lastError).toLocal8Bit());
}

bool Database::fetch() {

}

bool Database::insert() {

}


bool Database::update() {

}

bool Database::remove() {

}
