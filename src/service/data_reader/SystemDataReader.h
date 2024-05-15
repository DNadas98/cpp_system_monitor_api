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

#ifdef __linux__
#include "LinuxSystemDataReader.h"
#endif

std::unique_ptr<SystemDataReader> SystemDataReader::create() {
#ifdef __linux__
  return std::make_unique<LinuxSystemDataReader>();
#else
  throw std::runtime_error("Platform support not yet implemented");
#endif
}

#endif // SYSTEM_DATA_READER_H
