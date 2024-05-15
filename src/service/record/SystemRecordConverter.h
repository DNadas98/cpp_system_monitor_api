#ifndef SYSTEM_RECORD_CONVERTER_H
#define SYSTEM_RECORD_CONVERTER_H

#include "crow.h"
#include "../../model/record/SystemRecord.h"

class SystemRecordConverter {
public:
    SystemRecord jsonToSystemRecord(const crow::json::rvalue &json);
    crow::json::wvalue systemRecordToJson(const SystemRecord &record);

private:
    std::string formatTimestampForJson(std::time_t timestamp);
};

#endif // SYSTEM_RECORD_CONVERTER_H
