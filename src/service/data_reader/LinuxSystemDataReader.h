#ifndef LINUX_SYSTEM_DATA_READER_H
#define LINUX_SYSTEM_DATA_READER_H

#include "SystemDataReader.h"

class LinuxSystemDataReader : public SystemDataReader {
public:
    SystemRecord getSystemData() override;

private:
    double getCPUUsage();
    std::pair<double, double> readCPUStats();
    std::pair<double, double> getMemoryStats();
    std::pair<int, int> getDiskStats();
    std::pair<int, int> getNetworkUsage();
};

#endif // LINUX_SYSTEM_DATA_READER_H
