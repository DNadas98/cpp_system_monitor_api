#include "../data_reader/SystemDataReader.h"
#include "../../model/record/SystemRecord.h"
#include "../../model/record/SystemRecordRepository.h"
#include <memory>
#include <ctime>

class SystemRecordService {
public:
    explicit SystemRecordService(std::shared_ptr<SystemRecordRepository> repository)
      : repository(repository), systemDataReader(SystemDataReader::create()) {}

    void createRecord() {
      if (systemDataReader) {
        auto record = systemDataReader->getSystemData();
        repository->createRecord(record);
      }
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
    std::unique_ptr<SystemDataReader> systemDataReader;
};
