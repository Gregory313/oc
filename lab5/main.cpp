// #include <iostream>
// #include <sys/statvfs.h>
// #include <mntent.h>
// #include <set>
// #include <cstring>

// void getSpecificFilesystemTypes() {
//     FILE* fp = setmntent("/etc/mtab", "r");
//     if (fp == nullptr) {
//         perror("setmntent");
//         return;
//     }

//     std::set<std::string> uniqueFilesystemTypes; // Для хранения уникальных типов файловых систем
//     struct mntent* mnt;

//     while ((mnt = getmntent(fp)) != nullptr) {
//         struct statvfs buf;
//         if (statvfs(mnt->mnt_dir, &buf) == 0) {
//             // Проверяем, является ли тип файловой системы ext4 или fat32
//             if (std::string(mnt->mnt_type) == "ext4" || std::string(mnt->mnt_type) == "vfat") {
//                 // Формируем строку вывода для текущей файловой системы
//                 std::cout << "Device: " << mnt->mnt_fsname << std::endl;
//                 std::cout << "Mountpoint: " << mnt->mnt_dir << std::endl;
//                 std::cout << "Filesystem type: " << mnt->mnt_type << std::endl;
//                 std::cout << "Options: " << mnt->mnt_opts << std::endl;

//                 unsigned long totalSize = buf.f_blocks * buf.f_frsize;
//                 unsigned long freeSize = buf.f_bfree * buf.f_frsize;
//                 unsigned long usedSize = totalSize - freeSize;

//                 std::cout << "  Total Size: " << totalSize / (1024 * 1024) << " MB" << std::endl;
//                 std::cout << "  Used: " << usedSize / (1024 * 1024) << " MB" << std::endl;
//                 std::cout << "  Free: " << freeSize / (1024 * 1024) << " MB" << std::endl;
//                 std::cout << "  Usage Percentage: " << (usedSize * 100.0 / totalSize) << "%" << std::endl;
//                 std::cout << "----------------------------------------" << std::endl;
//             }
//         }
//     }

//     endmntent(fp);
// }

// int main() {
//     getSpecificFilesystemTypes();
//     return 0;
// }
































#include <iostream>
#include <sys/statvfs.h>
#include <mntent.h>
#include <set>
#include <cstring>

void analyzeFilesystems() {
    FILE* fp = setmntent("/etc/mtab", "r");
    if (fp == nullptr) {
        perror("setmntent");
        return;
    }

    unsigned long totalExt4Size = 0, totalExt4Used = 0, totalFat32Size = 0, totalFat32Used = 0;
    int ext4Count = 0, fat32Count = 0;

    struct mntent* mnt;
    while ((mnt = getmntent(fp)) != nullptr) {
        struct statvfs buf;
        if (statvfs(mnt->mnt_dir, &buf) == 0) {
            if (std::string(mnt->mnt_type) == "ext4") {
                unsigned long totalSize = buf.f_blocks * buf.f_frsize;
                unsigned long freeSize = buf.f_bfree * buf.f_frsize;
                unsigned long usedSize = totalSize - freeSize;

                std::cout << "Device: " << mnt->mnt_fsname << std::endl;
                std::cout << "Mountpoint: " << mnt->mnt_dir << std::endl;
                std::cout << "Filesystem type: " << mnt->mnt_type << std::endl;
                std::cout << "Options: " << mnt->mnt_opts << std::endl;
                std::cout << "  Total Size: " << totalSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Used: " << usedSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Free: " << freeSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Usage Percentage: " << (usedSize * 100.0 / totalSize) << "%" << std::endl;

                totalExt4Size += totalSize;
                totalExt4Used += usedSize;
                ext4Count++;

                std::cout << "----------------------------------------" << std::endl;
            } else if (std::string(mnt->mnt_type) == "vfat") {
                unsigned long totalSize = buf.f_blocks * buf.f_frsize;
                unsigned long freeSize = buf.f_bfree * buf.f_frsize;
                unsigned long usedSize = totalSize - freeSize;

                std::cout << "Device: " << mnt->mnt_fsname << std::endl;
                std::cout << "Mountpoint: " << mnt->mnt_dir << std::endl;
                std::cout << "Filesystem type: " << mnt->mnt_type << std::endl;
                std::cout << "Options: " << mnt->mnt_opts << std::endl;
                std::cout << "  Total Size: " << totalSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Used: " << usedSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Free: " << freeSize / (1024 * 1024) << " MB" << std::endl;
                std::cout << "  Usage Percentage: " << (usedSize * 100.0 / totalSize) << "%" << std::endl;

                totalFat32Size += totalSize;
                totalFat32Used += usedSize;
                fat32Count++;

                std::cout << "----------------------------------------" << std::endl;
            }
        }
    }

    endmntent(fp);
}

int main() {
    analyzeFilesystems();
    return 0;
}
