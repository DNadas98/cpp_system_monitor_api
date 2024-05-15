#include "SystemRecordConverter.h"
#include <ctime>

SystemRecord SystemRecordConverter::jsonToSystemRecord(const crow::json::rvalue &json) {
  return SystemRecord(
    json["cpu_usage_percentage"].d(),
    json["memory_usage_percentage"].d(),
    json["total_memory_MB"].i(),
    json["used_memory_MB"].i(),
    json["disk_usage_percentage"].d(),
    json["total_disk_space_MB"].i(),
    json["used_disk_space_MB"].i(),
    json["network_in_KB"].i(),
    json["network_out_KB"].i(),
    static_cast<std::time_t>(json["timestamp_UTC"].i())
  );
}

crow::json::wvalue SystemRecordConverter::systemRecordToJson(const SystemRecord &record) {
  crow::json::wvalue json;
  json["id"] = record.getId();
  json["cpu_usage_percentage"] = record.getCpuUsage();
  json["memory_usage_percentage"] = record.getMemoryUsage();
  json["total_memory_MB"] = record.getTotalMemory();
  json["used_memory_MB"] = record.getUsedMemory();
  json["disk_usage_percentage"] = record.getDiskUsage();
  json["total_disk_space_MB"] = record.getTotalDiskSpace();
  json["used_disk_space_MB"] = record.getUsedDiskSpace();
  json["network_in_KB"] = record.getNetworkIn();
  json["network_out_KB"] = record.getNetworkOut();
  json["timestamp_UTC"] = formatTimestampForJson(record.getTimestamp());
  return json;
}

std::string SystemRecordConverter::formatTimestampForJson(std::time_t timestamp) {
  char buffer[20];
  std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
  return std::string(buffer);
}
