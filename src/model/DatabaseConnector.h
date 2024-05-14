// DATABASE_CONNECTOR_H
#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <pqxx/pqxx>
#include <stdexcept>
#include <string>
#include <memory>

class DatabaseConnector {
public:
    DatabaseConnector(const std::string& connString) : connString(connString) {}

    /**
     * `unique_ptr` = smart pointer that owns and manages another object through a pointer and disposes of that object when the `unique_ptr` goes out of scope<br>
     * @see https://en.cppreference.com/w/cpp/memory/unique_ptr
     */
    std::unique_ptr<pqxx::connection> getConnection() {
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

private:
    const std::string connString;
};

#endif // DATABASE_CONNECTOR_H
