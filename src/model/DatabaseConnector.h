#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <pqxx/pqxx>
#include <string>
#include <memory>

class DatabaseConnector {
public:
    DatabaseConnector(const std::string& connString);
    std::unique_ptr<pqxx::connection> getConnection();

private:
    const std::string connString;
};

#endif // DATABASE_CONNECTOR_H
