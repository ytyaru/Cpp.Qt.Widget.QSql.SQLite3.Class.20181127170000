#include "memodb.h"

MemoDb::MemoDb()
{
    this->Open();
}

MemoDb::~MemoDb()
{
    this->Close();
}

void MemoDb::Open(QString path)
{
    if (!QSqlDatabase::contains("MemoDb")) {
        this->dbPath = QDir(path).filePath("memo.sqlite3");
        this->db = QSqlDatabase::addDatabase("QSQLITE", "MemoDb");
        this->db.setDatabaseName(this->dbPath);
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "MemoDb");
//        db.setDatabaseName(this->dbPath);
        this->CreateTable();
    }
}

void MemoDb::Close()
{
//    if (this->db.isOpen()) { this->db.close(); }
    qDebug() << this->db.isOpen();
    qDebug() << this->db.connectionNames();
//    if (this->db.isOpen()) { qDebug() << "Close() " + this->db.connectionName(); this->db.close(); QSqlDatabase::removeDatabase(this->db.connectionName()); }
    this->db.close();
    QSqlDatabase::removeDatabase("MemoDb");
}

bool MemoDb::IsExsistTable()
{
//    QSqlDatabase db = this->db.database();
//    QSqlDatabase db = this->db.database("MemoDb");
//    QSqlDatabase db = QSqlDatabase::database("MemoDb");
//    QSqlQuery query(db);
    QSqlQuery query(this->db);
    query.exec("select count(*) from sqlite_master where type='table' and name='Memo'");
    int count = 0;
    while (query.next()) { count = query.value(0).toInt(); }
    db.close();
    if (0 < count) { return true; }
    else { return false; }

    /*
    QSqlQuery query(this->db);
    query.exec("select count(*) from sqlite_master where type='table' and name='Memo'");
    int count = 0;
    while (query.next()) { count = query.value(0).toInt(); }
    if (0 < count) { return true; }
    else { return false; }
    */
}

void MemoDb::CreateTable()
{
//    QSqlDatabase db = this->db.database();
    QSqlDatabase db = QSqlDatabase::database("MemoDb");
    if (!this->IsExsistTable()) {
//        QSqlQuery query(db);
        QSqlQuery query(this->db);
        query.exec("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo text, DateTime text)");
    }
    db.close();
    /*
    if (!this->IsExsistTable()) {
        QSqlQuery query(this->db);
        query.exec("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo text, DateTime text)");
    }
    */
}

void MemoDb::Write(QStringList record)
{
//    QSqlDatabase db = this->db.database();
    QSqlDatabase db = QSqlDatabase::database("MemoDb");
//    QSqlQuery query(db);
    QSqlQuery query(this->db);
    query.prepare("insert into Memo (Memo, DateTime) values (?, ?)");
    for (int i = 0; i < record.size(); i++) {
        query.bindValue(i, record[i]);
    }
    query.exec();
    qDebug() << record;
    db.close();

//    QSqlQuery query(this->db);
//    query.prepare("insert into Memo (Memo, DateTime) values (?, ?)");
//    for (int i = 0; i < record.size(); i++) {
//        query.bindValue(i, record[i]);
//    }
//    query.exec();
//    qDebug() << record;
}
