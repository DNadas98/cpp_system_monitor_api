// SystemRecordRepository.h
#ifndef SYSTEM_RECORD_REPOSITORY_H
#define SYSTEM_RECORD_REPOSITORY_H

#include <pqxx/pqxx>
#include "../DatabaseConnector.h"
#include "SystemRecord.h"
#include <vector>
#include <memory>

class SystemRecordRepository {
public:
    explicit SystemRecordRepository(std::shared_ptr<DatabaseConnector> dbConnector)
      : dbConnector(dbConnector) {}

    std::vector<SystemRecord> getAllRecords() {
      std::vector<SystemRecord> records;
      auto conn = dbConnector->getConnection();
      pqxx::work txn(*conn);
      pqxx::result r = txn.exec("SELECT * FROM system_record ORDER BY timestamp DESC");
      if (r.empty()){
        return {};
      }
      for (auto row: r) {
        records.push_back(rowToSystemRecord(row));
      }
      txn.commit();
      return records;
    }

    SystemRecord getRecordById(long id) {
      auto conn = dbConnector->getConnection();
      pqxx::work txn(*conn);
      pqxx::result r = txn.exec("SELECT * FROM system_record WHERE id = " + txn.quote(id));
      if (r.size() != 1) throw std::runtime_error("Record not found");
      txn.commit();
      return rowToSystemRecord(r[0]);
    }

    void createRecord(const SystemRecord &record) {
      auto conn = dbConnector->getConnection();
      pqxx::work txn(*conn);
      txn.exec(
        "INSERT INTO system_record (cpu_usage, memory_usage, total_memory, used_memory, disk_usage, total_disk_space, used_disk_space, network_in, network_out) VALUES (" +
        txn.quote(record.getCpuUsage()) + ", " + txn.quote(record.getMemoryUsage()) + ", " +
        txn.quote(record.getTotalMemory()) + ", " + txn.quote(record.getUsedMemory()) + ", " +
        txn.quote(record.getDiskUsage()) + ", " + txn.quote(record.getTotalDiskSpace()) + ", " +
        txn.quote(record.getUsedDiskSpace()) + ", " + txn.quote(record.getNetworkIn()) + ", " +
        txn.quote(record.getNetworkOut()) + ")");
      txn.commit();
    }

    void deleteRecordById(long id) {
      auto conn = dbConnector->getConnection();
      pqxx::work txn(*conn);
      pqxx::result result = txn.exec("DELETE FROM system_record WHERE id = " + txn.quote(id));
      txn.commit();
      if (result.affected_rows() == 0) {
        throw std::runtime_error("Record not found");
      }
    }

    void deleteAllRecords() {
      auto conn = dbConnector->getConnection();
      pqxx::work txn(*conn);
      txn.exec("DELETE FROM system_record");
      txn.commit();
    }

private:
    std::shared_ptr<DatabaseConnector> dbConnector;

    SystemRecord rowToSystemRecord(const pqxx::row &row) {
      std::string timestamp_str = row["timestamp"].as<std::string>();

      return SystemRecord(
        row["id"].as<long>(),
        row["cpu_usage"].as<double>(),
        row["memory_usage"].as<double>(),
        row["total_memory"].as<int>(),
        row["used_memory"].as<int>(),
        row["disk_usage"].as<double>(),
        row["total_disk_space"].as<int>(),
        row["used_disk_space"].as<int>(),
        row["network_in"].as<int>(),
        row["network_out"].as<int>(),
        parseTimestamp(timestamp_str));
    }

    std::time_t parseTimestamp(const std::string &timestamp_str) {
      struct tm tm;
      strptime(timestamp_str.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
      return mktime(&tm);
    }
};

#endif // SYSTEM_RECORD_REPOSITORY_H
