#include "SystemRecordService.h"

SystemRecordService::SystemRecordService(std::shared_ptr<SystemRecordRepository> repository)
  : repository(repository), systemDataReader(SystemDataReader::create()) {}

void SystemRecordService::createRecord() {
  if (systemDataReader) {
    auto record = systemDataReader->getSystemData();
    repository->createRecord(record);
  }
}

std::vector<SystemRecord> SystemRecordService::getAllRecords() {
  return repository->getAllRecords();
}

SystemRecord SystemRecordService::getRecordById(long id) {
  return repository->getRecordById(id);
}

void SystemRecordService::deleteRecordById(long id) {
  repository->deleteRecordById(id);
}

void SystemRecordService::deleteAllRecords() {
  repository->deleteAllRecords();
}
