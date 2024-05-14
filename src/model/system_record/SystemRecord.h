// SYSTEM_RECORD_H
#ifndef SYSTEM_RECORD_H
#define SYSTEM_RECORD_H

#include <string>
#include <ctime>

class SystemRecord {
public:
    SystemRecord() = default;

    SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut, std::time_t timestamp)
      : cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
        used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
        used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut),
        timestamp(timestamp) {}

    SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut)
      : cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
        used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
        used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut) {}

    SystemRecord(long id, int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                 int diskUsage, int totalDiskSpace, int usedDiskSpace,
                 int networkIn, int networkOut, std::time_t timestamp)
      : id(id), cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
        used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
        used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut), timestamp(timestamp) {}

    long getId() const { return id; }
    void setId(int value) { id = value; }

    double getCpuUsage() const { return cpu_usage; }
    void setCpuUsage(double value) { cpu_usage = value; }

    double getMemoryUsage() const { return memory_usage; }
    void setMemoryUsage(double value) { memory_usage = value; }

    int getTotalMemory() const { return total_memory; }
    void setTotalMemory(int value) { total_memory = value; }

    int getUsedMemory() const { return used_memory; }
    void setUsedMemory(int value) { used_memory = value; }

    double getDiskUsage() const { return disk_usage; }
    void setDiskUsage(double value) { disk_usage = value; }

    int getTotalDiskSpace() const { return total_disk_space; }
    void setTotalDiskSpace(int value) { total_disk_space = value; }

    int getUsedDiskSpace() const { return used_disk_space; }
    void setUsedDiskSpace(int value) { used_disk_space = value; }

    int getNetworkIn() const { return network_in; }
    void setNetworkIn(int value) { network_in = value; }

    int getNetworkOut() const { return network_out; }
    void setNetworkOut(int value) { network_out = value; }

    std::time_t getTimestamp() const { return timestamp; }
    void setTimestamp(std::time_t value) { timestamp = value; }

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
