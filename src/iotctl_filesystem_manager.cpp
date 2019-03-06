
#include <iotctl_filesystem_manager.h>
#include <QDebug>

namespace iotctl {

// Required ot be in compilation unit
constexpr char FileSystemManger::kLogTag[];

FileSystemManger& FileSystemManger::GetInstance() {
    static FileSystemManger singleton;
    return singleton;
}

FileSystemManger::FileSystemManger() :
    data_dir_(kDataPathName)
{
    CreateDataDir();
}


void FileSystemManger::CreateDataDir() {
    if(data_dir_.exists()) {
      qDebug() << kLogTag << "Path: " << data_dir_.absolutePath() << " already exists";
      return;
    }

    // Attempt to just make the directory
    auto success = data_dir_.mkpath(data_dir_.absolutePath());
    if(success) {
        qDebug() << kLogTag << "Opened path: " << data_dir_.absolutePath();
    } else {
        qWarning() << kLogTag << "Failed to open path: " << data_dir_.absolutePath();
        // Diagnose why
        QDir temp_dir_info(data_dir_);
        QFileInfo info(temp_dir_info.absolutePath());
        while(!info.isDir()) {
            temp_dir_info.cdUp();
            info.setFile(temp_dir_info.absolutePath());
        }
        QString owner = info.owner();
        qWarning() << kLogTag << "Path: " << temp_dir_info.absolutePath() << "is owned by: " << owner;
    }
}

}// iotctl
