#include "SystemDataReader.h"
#ifdef __linux__
#include "LinuxSystemDataReader.h"
#else
#error "Unsupported platform"
#endif

std::unique_ptr<SystemDataReader> SystemDataReader::create() {
#ifdef __linux__
  return std::make_unique<LinuxSystemDataReader>();
#else
  return nullptr;
#endif
}
