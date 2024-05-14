#ifndef LINUX_SYSTEM_DATA_READER_H
#define LINUX_SYSTEM_DATA_READER_H

#include "SystemDataReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

class LinuxSystemDataReader : public SystemDataReader {
public:
    SystemRecord getSystemData() override {
      double cpuUsage = getCPUUsage();
      double memoryUsage = getMemoryUsage();
      int totalMemory = 16000; // Example static value, fetch dynamically if needed
      int usedMemory = static_cast<int>(memoryUsage / 100.0 * totalMemory);
      int diskUsage = 50; // Example static value
      int totalDiskSpace = 256000; // in Megabytes, example static value
      int usedDiskSpace = static_cast<int>(diskUsage / 100.0 * totalDiskSpace);
      int networkIn = 120; // Example static value
      int networkOut = 150; // Example static value
      std::time_t timestamp = std::time(nullptr);

      return SystemRecord(cpuUsage, memoryUsage, totalMemory, usedMemory,
                          diskUsage, totalDiskSpace, usedDiskSpace,
                          networkIn, networkOut, timestamp);
    }

private:
    double getCPUUsage() {
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

      return ((totalActive - lastActive) / (total - lastTotal)) * 100.0;
    }

    double getMemoryUsage() {
      std::ifstream file("/proc/meminfo");
      std::string line;
      int totalMemory = 0, freeMemory = 0;
      std::string key;
      int value;
      std::string kb;

      while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> key >> value >> kb;

        if (key == "MemTotal:") {
          totalMemory = value;
        } else if (key == "MemFree:") {
          freeMemory = value;
        }

        if (totalMemory > 0 && freeMemory > 0) {
          break;
        }
      }

      return 100.0 - (freeMemory / static_cast<double>(totalMemory) * 100.0);
    }

    double lastTotal = 0.0, lastActive = 0.0;
};

#endif // LINUX_SYSTEM_DATA_READER_H
