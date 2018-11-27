# このソフトウェアについて

　Qt5学習。QtでSQLite3を使ってみる。Class化した。

# 問題

　`QSqlDatabasePrivate::removeDatabase: connection 'MemoDb' is still in use, all queries will cease to work.`という表示が出る。

## 前回まで

* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127160000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127130000

## コード抜粋

mainwindow.cpp
```cpp
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MemoDb memoDb;
    memoDb.Open(QApplication::applicationDirPath());
    QStringList record;
    record.append("ABCDEFG");
    record.append("2000-01-01 00:00:00.000");
    memoDb.Write(record);
    memoDb.Close();
}
```

memodb.cpp
```cpp
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
void MemoDb::CreateTable() {
//    QSqlDatabase db = QSqlDatabase::database("MemoDb");
//    QSqlQuery query(db);
    QSqlQuery query(this->db);
    query.exec("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo text, DateTime text)");
}
void MemoDb::Close() {
    QSqlDatabase::removeDatabase("MemoDb");
}
```

　`QSqlDatabase::addDatabase`の戻り値をメンバ変数`this->db`にセットした。そしてクエリを発行するときに`    QSqlQuery query(this->db);`とした。

　実行するとQt Creatorのアプリケーション出力欄に以下のような表示が出る。

```
QSqlDatabasePrivate::removeDatabase: connection 'MemoDb' is still in use, all queries will cease to work.
```

　`QSqlDatabase::removeDatabase`を実行したが、`MemoDb`はまだ使用中だと怒られた。メンバ変数で参照して`QSqlDatabase db = QSqlDatabase::database("MemoDb");`の一文を省略しようとしたのだが、できないという認識でOK？

# 参考

* http://tomokiit.hatenablog.jp/entry/Qt_SQLite
* https://blogs.yahoo.co.jp/hmfjm910/10815002.html
* https://forum.qt.io/topic/18700/sqlite-connection-qsqldatabaseprivate-adddatabase-duplicate-connection-name-qt_sql_default_connection-old-connection-removed/7

## Qt要素

* http://doc.qt.io/qt-5/qsql.html
    * http://doc.qt.io/qt-5/qsqldatabase.html
    * http://doc.qt.io/qt-5/qsqlquery.html

# 開発環境

* [Raspberry Pi](https://ja.wikipedia.org/wiki/Raspberry_Pi) 3 Model B+
    * [Raspbian](https://www.raspberrypi.org/downloads/raspbian/) GNU/Linux 9.0 (stretch) 2018-06-27
        * Qt 5.7.1

## 環境構築

* [Raspbian stretch で Qt5.7 インストールしたもの一覧](http://ytyaru.hatenablog.com/entry/2019/12/17/000000)

# ライセンス

　このソフトウェアはCC0ライセンスである。

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png "CC0")](http://creativecommons.org/publicdomain/zero/1.0/deed.ja)

## 利用ライブラリ

ライブラリ|ライセンス|ソースコード
----------|----------|------------
[Qt](http://doc.qt.io/)|[LGPL](http://doc.qt.io/qt-5/licensing.html)|[GitHub](https://github.com/qt)

* [参考1](https://www3.sra.co.jp/qt/licence/index.html)
* [参考2](http://kou-lowenergy.hatenablog.com/entry/2017/02/17/154720)
* [参考3](https://qiita.com/ynuma/items/e8749233677821a81fcc)
