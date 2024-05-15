#ifndef SYSTEM_DATA_READER_H
#define SYSTEM_DATA_READER_H

#include <memory>
#include "../../model/record/SystemRecord.h"

class SystemDataReader {
public:
    virtual ~SystemDataReader() = default;
    virtual SystemRecord getSystemData() = 0;
    static std::unique_ptr<SystemDataReader> create();
};

#endif // SYSTEM_DATA_READER_H
