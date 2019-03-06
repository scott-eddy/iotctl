#ifndef IOTCTL_FILESYSTEM_MANAGER_H
#define IOTCTL_FILESYSTEM_MANAGER_H


#include <QVector>
#include <QDir>

namespace iotctl {

class FileSystemManger {
public:

    static FileSystemManger& GetInstance();

private:

    FileSystemManger();

    void CreateDataDir();

    /**
     * @brief kDataPath
     */
    const char* kDataPathName;

    /**
     * @brief File name that stores username/password
     */
    const char* kLoginFileName;

    static constexpr char kLogTag[] = "[FS Mgmt]";

    QDir data_dir_;
};

} // iotctl

#endif // IOTCTL_FILESYSTEM_MANAGER_H
