#ifndef SYSTEM_RECORD_SERVICE_H
#define SYSTEM_RECORD_SERVICE_H

#include <memory>
#include <ctime>
#include "../../model/record/SystemRecordRepository.h"
#include "../../model/record/SystemRecord.h"
#include "../data_reader/SystemDataReader.h"

class SystemRecordService {
public:
    explicit SystemRecordService(std::shared_ptr<SystemRecordRepository> repository);
    void createRecord();
    std::vector<SystemRecord> getAllRecords();
    SystemRecord getRecordById(long id);
    void deleteRecordById(long id);
    void deleteAllRecords();

private:
    std::shared_ptr<SystemRecordRepository> repository;
    std::unique_ptr<SystemDataReader> systemDataReader;
};

#endif // SYSTEM_RECORD_SERVICE_H
