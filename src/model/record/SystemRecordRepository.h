#ifndef SYSTEM_RECORD_REPOSITORY_H
#define SYSTEM_RECORD_REPOSITORY_H

#include <pqxx/pqxx>
#include "../DatabaseConnector.h"
#include "SystemRecord.h"
#include <vector>
#include <memory>

class SystemRecordRepository {
public:
    explicit SystemRecordRepository(std::shared_ptr<DatabaseConnector> dbConnector);
    std::vector<SystemRecord> getAllRecords();
    SystemRecord getRecordById(long id);
    void createRecord(const SystemRecord &record);
    void deleteRecordById(long id);
    void deleteAllRecords();

private:
    std::shared_ptr<DatabaseConnector> dbConnector;
    SystemRecord rowToSystemRecord(const pqxx::row &row);
    std::time_t parseTimestamp(const std::string &timestamp_str);
};

#endif // SYSTEM_RECORD_REPOSITORY_H
