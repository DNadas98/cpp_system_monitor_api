#include "../../model/system_record/SystemRecord.h"
#include "../../includes/crow_all.h"

class SystemRecordConverter {
public:
    SystemRecord jsonToSystemRecord(const crow::json::rvalue &json) {
      return SystemRecord(
        json["cpu_usage"].d(),
        json["memory_usage"].d(),
        json["total_memory"].i(),
        json["used_memory"].i(),
        json["disk_usage"].d(),
        json["total_disk_space"].i(),
        json["used_disk_space"].i(),
        json["network_in"].i(),
        json["network_out"].i(),
        static_cast<std::time_t>(json["timestamp"].i())
      );
    }

    crow::json::wvalue systemRecordToJson(const SystemRecord &record) {
      crow::json::wvalue json;
      json["id"] = record.getId();
      json["cpu_usage"] = record.getCpuUsage();
      json["memory_usage"] = record.getMemoryUsage();
      json["total_memory"] = record.getTotalMemory();
      json["used_memory"] = record.getUsedMemory();
      json["disk_usage"] = record.getDiskUsage();
      json["total_disk_space"] = record.getTotalDiskSpace();
      json["used_disk_space"] = record.getUsedDiskSpace();
      json["network_in"] = record.getNetworkIn();
      json["network_out"] = record.getNetworkOut();
      json["timestamp"] = formatTimestampForJson(record.getTimestamp());
      return json;
    }

private:
    std::string formatTimestampForJson(std::time_t timestamp) {
      char buffer[20];
      std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
      return std::string(buffer);
    }
};