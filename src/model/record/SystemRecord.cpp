#include "SystemRecord.h"

SystemRecord::SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                           int diskUsage, int totalDiskSpace, int usedDiskSpace,
                           int networkIn, int networkOut, std::time_t timestamp)
  : cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
    used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
    used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut),
    timestamp(timestamp) {}

SystemRecord::SystemRecord(int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                           int diskUsage, int totalDiskSpace, int usedDiskSpace,
                           int networkIn, int networkOut)
  : cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
    used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
    used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut) {}

SystemRecord::SystemRecord(long id, int cpuUsage, int memoryUsage, int totalMemory, int usedMemory,
                           int diskUsage, int totalDiskSpace, int usedDiskSpace,
                           int networkIn, int networkOut, std::time_t timestamp)
  : id(id), cpu_usage(cpuUsage), memory_usage(memoryUsage), total_memory(totalMemory),
    used_memory(usedMemory), disk_usage(diskUsage), total_disk_space(totalDiskSpace),
    used_disk_space(usedDiskSpace), network_in(networkIn), network_out(networkOut), timestamp(timestamp) {}

long SystemRecord::getId() const { return id; }
void SystemRecord::setId(int value) { id = value; }

double SystemRecord::getCpuUsage() const { return cpu_usage; }
void SystemRecord::setCpuUsage(double value) { cpu_usage = value; }

double SystemRecord::getMemoryUsage() const { return memory_usage; }
void SystemRecord::setMemoryUsage(double value) { memory_usage = value; }

int SystemRecord::getTotalMemory() const { return total_memory; }
void SystemRecord::setTotalMemory(int value) { total_memory = value; }

int SystemRecord::getUsedMemory() const { return used_memory; }
void SystemRecord::setUsedMemory(int value) { used_memory = value; }

double SystemRecord::getDiskUsage() const { return disk_usage; }
void SystemRecord::setDiskUsage(double value) { disk_usage = value; }

int SystemRecord::getTotalDiskSpace() const { return total_disk_space; }
void SystemRecord::setTotalDiskSpace(int value) { total_disk_space = value; }

int SystemRecord::getUsedDiskSpace() const { return used_disk_space; }
void SystemRecord::setUsedDiskSpace(int value) { used_disk_space = value; }

int SystemRecord::getNetworkIn() const { return network_in; }
void SystemRecord::setNetworkIn(int value) { network_in = value; }

int SystemRecord::getNetworkOut() const { return network_out; }
void SystemRecord::setNetworkOut(int value) { network_out = value; }

std::time_t SystemRecord::getTimestamp() const { return timestamp; }
void SystemRecord::setTimestamp(std::time_t value) { timestamp = value; }
