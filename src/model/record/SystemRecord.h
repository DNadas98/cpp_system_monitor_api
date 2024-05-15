#ifndef SYSTEM_RECORD_H
#define SYSTEM_RECORD_H

#include <string>
#include <ctime>

class SystemRecord {
public:
    SystemRecord() = default;
    SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut, std::time_t timestamp);
    SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut);
    SystemRecord(long id, int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut, std::time_t timestamp);

    long getId() const;
    void setId(int value);

    double getCpuUsage() const;
    void setCpuUsage(double value);

    double getMemoryUsage() const;
    void setMemoryUsage(double value);

    int getTotalMemory() const;
    void setTotalMemory(int value);

    int getUsedMemory() const;
    void setUsedMemory(int value);

    double getDiskUsage() const;
    void setDiskUsage(double value);

    int getTotalDiskSpace() const;
    void setTotalDiskSpace(int value);

    int getUsedDiskSpace() const;
    void setUsedDiskSpace(int value);

    int getNetworkIn() const;
    void setNetworkIn(int value);

    int getNetworkOut() const;
    void setNetworkOut(int value);

    std::time_t getTimestamp() const;
    void setTimestamp(std::time_t value);

private:
    long id;
    double cpu_usage;
    double memory_usage;
    int total_memory;
    int used_memory;
    double disk_usage;
    int total_disk_space;
    int used_disk_space;
    int network_in;
    int network_out;
    std::time_t timestamp;
};

#endif // SYSTEM_RECORD_H
