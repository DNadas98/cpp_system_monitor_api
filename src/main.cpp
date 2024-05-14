#include <cstdlib>
#include "includes/crow_all.h"

#define CROW_STATIC_ENDPOINT "/public/<path>";
#define CROW_STATIC_DIRECTORY "public/";

int main(void) {
  crow::SimpleApp app;

  // Routes
  CROW_ROUTE(app, "/")([]() {
      return "Hello world!";
  });

  // Static files

  char *port_env = std::getenv("PORT");
  int port = port_env ? std::atoi(port_env) : 8080;
  app.port(port).multithreaded().run();
}
