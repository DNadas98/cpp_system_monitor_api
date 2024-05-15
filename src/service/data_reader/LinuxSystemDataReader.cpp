#include "LinuxSystemDataReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <thread>
#include <chrono>

SystemRecord LinuxSystemDataReader::getSystemData() {
  double cpuUsage = getCPUUsage();
  auto [memoryUsage, totalMemory] = getMemoryStats();
  int usedMemory = static_cast<int>(memoryUsage / 100.0 * totalMemory);
  auto [diskUsage, totalDiskSpace] = getDiskStats();
  int usedDiskSpace = static_cast<int>(diskUsage / 100.0 * totalDiskSpace);
  auto [networkIn, networkOut] = getNetworkUsage();

  return SystemRecord(cpuUsage, memoryUsage, totalMemory, usedMemory,
                      diskUsage, totalDiskSpace, usedDiskSpace,
                      networkIn, networkOut);
}

double LinuxSystemDataReader::getCPUUsage() {
  auto [total1, active1] = readCPUStats();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  auto [total2, active2] = readCPUStats();

  double usage = ((active2 - active1) / (total2 - total1)) * 100.0;
  return usage;
}

std::pair<double, double> LinuxSystemDataReader::readCPUStats() {
  std::ifstream file("/proc/stat");
  std::string line;
  std::getline(file, line);
  std::istringstream iss(line);

  std::string cpu;
  double user, nice, system, idle;
  iss >> cpu >> user >> nice >> system >> idle;

  double totalIdle = idle;
  double totalActive = user + nice + system;
  double total = totalIdle + totalActive;

  return {total, totalActive};
}

std::pair<double, double> LinuxSystemDataReader::getMemoryStats() {
  struct sysinfo memInfo;
  sysinfo(&memInfo);

  long totalMemory = memInfo.totalram;
  totalMemory *= memInfo.mem_unit;
  long freeMemory = memInfo.freeram;
  freeMemory *= memInfo.mem_unit;
  long buffers = memInfo.bufferram;
  buffers *= memInfo.mem_unit;
  long cached = 0;
  std::ifstream file("/proc/meminfo");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key;
    long value;
    std::string unit;
    iss >> key >> value >> unit;
    if (key == "Cached:") {
      cached = value * 1024;
      break;
    }
  }

  long actualFreeMemory = freeMemory + buffers + cached;
  double memoryUsage = 100.0 - (actualFreeMemory / static_cast<double>(totalMemory) * 100.0);

  return {memoryUsage, totalMemory / (1024 * 1024)};
}

std::pair<int, int> LinuxSystemDataReader::getDiskStats() {
  struct statvfs stat;
  if (statvfs("/", &stat) != 0) {
    return {0, 0};
  }

  double total = stat.f_blocks * stat.f_frsize;
  double available = stat.f_bavail * stat.f_frsize;
  double used = total - available;

  return {
    (used / total) * 100.0,
    total / (1024 * 1024)
  };
}

std::pair<int, int> LinuxSystemDataReader::getNetworkUsage() {
  const int TRANSMIT_BYTES_OFFSET = 7;
  std::ifstream networkStatsFile("/proc/net/dev");
  std::string line;
  int networkIn = 0;
  int networkOut = 0;

  std::getline(networkStatsFile, line);
  std::getline(networkStatsFile, line);

  while (std::getline(networkStatsFile, line)) {
    std::istringstream iss(line);
    std::string interfaceName;

    iss >> interfaceName;

    if (interfaceName != "lo:") {
      long receiveBytes;
      iss >> receiveBytes;
      for (int i = 0; i < TRANSMIT_BYTES_OFFSET; ++i) {
        std::string skipped;
        iss >> skipped;
      }
      long transmitBytes;
      iss >> transmitBytes;

      networkIn += receiveBytes / 1024;
      networkOut += transmitBytes / 1024;
    }
  }
  return {networkIn, networkOut};
}
