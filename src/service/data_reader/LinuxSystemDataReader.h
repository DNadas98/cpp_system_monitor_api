#ifndef LINUX_SYSTEM_DATA_READER_H
#define LINUX_SYSTEM_DATA_READER_H

#include "SystemDataReader.h"
#include "crow.h"
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <thread>
#include <chrono>

class LinuxSystemDataReader : public SystemDataReader {
public:
    SystemRecord getSystemData() override {
      double cpuUsage = getCPUUsage();
      auto [memoryUsage, totalMemory] = getMemoryStats();
      int usedMemory = static_cast<int>(memoryUsage / 100.0 * totalMemory); // to %
      auto [diskUsage, totalDiskSpace] = getDiskStats();
      int usedDiskSpace = static_cast<int>(diskUsage / 100.0 * totalDiskSpace); // to %
      auto [networkIn, networkOut] = getNetworkUsage();

      return SystemRecord(cpuUsage, memoryUsage, totalMemory, usedMemory,
                          diskUsage, totalDiskSpace, usedDiskSpace,
                          networkIn, networkOut);
    }

private:
    /**
     * @brief Get CPU usage as %.
     * This reads CPU stats 2 times with delay and calculates CPU usage based on the difference.
     * @return double The CPU usage percentage.
     */
    double getCPUUsage() {
      auto [total1, active1] = readCPUStats();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      auto [total2, active2] = readCPUStats();

      double usage = ((active2 - active1) / (total2 - total1)) * 100.0; // to %
      return usage;
    }

    /**
     * @brief Read CPU stats from the `/proc/stat` file.
     * This reads the first line of the `/proc/stat` which contains the CPU stats.
     * It parses user, nice, system, and idle times and calculates the total and active times.
     * @return std::pair<double, double> A pair of the total and active time.
     */
    std::pair<double, double> readCPUStats() {
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

    /**
     * @brief Get memory usage as % and total RAM in MB.
     * This uses `sysinfo` system call and calculates the memory usage.
     * Buffers and cached memory are also considered as free memory.
     * @return double The memory usage % and total RAM in MB.
     */
    std::pair<double, double> getMemoryStats() {
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
          cached = value * 1024; // KB to B
          break;
        }
      }

      long actualFreeMemory = freeMemory + buffers + cached;
      double memoryUsage = 100.0 - (actualFreeMemory / static_cast<double>(totalMemory) * 100.0);

      return {memoryUsage, totalMemory / (1024 * 1024)}; // to % and MB
    }

    /**
     * @brief Get disk usage as % and total disk space in MB.
     * This uses the `statvfs` system call to get disk usage data.
     * @return int The disk usage % and total disk space in MB.
     */
    std::pair<int, int> getDiskStats() {
      struct statvfs stat;
      if (statvfs("/", &stat) != 0) { // statvfs return !=0 ==> error
        CROW_LOG_ERROR << "Failed to read disk usage - statvfs error";
        return {0, 0};
      }

      double total = stat.f_blocks * stat.f_frsize;
      double available = stat.f_bavail * stat.f_frsize;
      double used = total - available;

      return {
        (used / total) * 100.0,
        total / (1024 * 1024)
      }; // to % and MB
    }

    /**
     * @brief Get network usage (in and out as pair) in KB.
     * This reads the `/proc/net/dev` file to get the total network input and output bytes
     * for all non-loopback interfaces.<br/>
     * File: | Interface name | Receive bytes | ...7 other fields... | Transmit bytes | ...
     * @see https://en.wikipedia.org/wiki/Loopback#Virtual_network_interface
     * @return std::pair<int, int> A pair of the network input and output in KB.
     */
    std::pair<int, int> getNetworkUsage() {
      const int TRANSMIT_BYTES_OFFSET = 7;
      std::ifstream networkStatsFile("/proc/net/dev");
      std::string line;
      int networkIn = 0;
      int networkOut = 0;

      // skip header lines
      std::getline(networkStatsFile, line);
      std::getline(networkStatsFile, line);

      while (std::getline(networkStatsFile, line)) {
        std::istringstream iss(line);
        std::string interfaceName;

        iss >> interfaceName;
        CROW_LOG_DEBUG << "Interface: " << interfaceName;

        if (interfaceName != "lo:") {
          long receiveBytes;
          iss >> receiveBytes;
          for (int i = 0; i < TRANSMIT_BYTES_OFFSET; ++i) {
            std::string skipped;
            iss >> skipped;
            CROW_LOG_DEBUG << "Skipped field: " << skipped << "\n";
          }
          long transmitBytes;
          iss >> transmitBytes;
          CROW_LOG_DEBUG << "Received: " << receiveBytes << " Transmit: " << transmitBytes << " for " << interfaceName;

          networkIn += receiveBytes / 1024; // to KB
          networkOut += transmitBytes / 1024; // to KB
        }
      }
      CROW_LOG_DEBUG << "Final Network In (KB): " << networkIn;
      CROW_LOG_DEBUG << "Final Network Out (KB): " << networkOut;
      return {networkIn, networkOut};
    }
};

#endif // LINUX_SYSTEM_DATA_READER_H
