#include "../../model/system_record/SystemRecordRepository.h"
#include <ctime>

class SystemRecordService {
public:
    explicit SystemRecordService(std::shared_ptr<SystemRecordRepository> repository)
      : repository(repository) {}

    void createRecord() {
      repository->createRecord(getRecord());
    }

    std::vector<SystemRecord> getAllRecords() {
      return repository->getAllRecords();
    }

    SystemRecord getRecordById(long id) {
      return repository->getRecordById(id);
    }

    void deleteRecordById(long id) {
      repository->deleteRecordById(id);
    }

    void deleteAllRecords() {
      repository->deleteAllRecords();
    }

private:
    std::shared_ptr<SystemRecordRepository> repository;

    SystemRecord getRecord() {
      srand(time(NULL));
      double cpuUsage = static_cast<double>(rand() % 101);
      double memoryUsage = static_cast<double>(rand() % 101);
      int totalMemory = rand() % 32000 + 1000;
      int usedMemory = static_cast<int>(memoryUsage / 100 * totalMemory);
      double diskUsage = static_cast<double>(rand() % 101);
      int totalDiskSpace = rand() % 10000 + 1000;
      int usedDiskSpace = static_cast<int>(diskUsage / 100 * totalDiskSpace);
      int networkIn = rand() % 1000;
      int networkOut = rand() % 1000;
      return SystemRecord(cpuUsage, memoryUsage, totalMemory, usedMemory,
                          diskUsage, totalDiskSpace, usedDiskSpace,
                          networkIn, networkOut);
    }
};
