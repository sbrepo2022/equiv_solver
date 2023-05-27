#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <QCoreApplication>
#include <QDir>

class FileStorage
{
private:
    FileStorage() {}

    FileStorage(const FileStorage &) = delete;
    FileStorage& operator=(const FileStorage&) = delete;

public:
    static QDir baseDir() {
        return QDir(QCoreApplication::applicationDirPath());
    }

    static QDir appDataDir() {
        QDir appdata_dir = FileStorage::baseDir();
        appdata_dir.cdUp();

        QString appdata_path = "app_data";
        appdata_dir.mkdir(appdata_path);
        appdata_dir.cd(appdata_path);

        return appdata_dir;
    }

    static QDir tmpDir() {
        QDir tmp_dir = FileStorage::appDataDir();

        QString tmp_path = "tmp";
        tmp_dir.mkdir(tmp_path);
        tmp_dir.cd(tmp_path);

        return tmp_dir;
    }

};

#endif // FILESTORAGE_H
