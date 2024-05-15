#include "SystemDataReader.h"
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
