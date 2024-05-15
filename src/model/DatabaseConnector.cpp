#include "DatabaseConnector.h"
#include <stdexcept>

DatabaseConnector::DatabaseConnector(const std::string& connString) : connString(connString) {}

std::unique_ptr<pqxx::connection> DatabaseConnector::getConnection() {
  try {
    auto conn = std::make_unique<pqxx::connection>(connString);
    if (conn && conn->is_open()) {
      return conn;
    } else {
      throw std::runtime_error("Failed to open database connection");
    }
  } catch (const std::exception &e) {
    throw std::runtime_error("Database connection error: " + std::string(e.what()));
  }
}
