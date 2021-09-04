#include <cstdlib>
#include <iostream>
#include <string>

#include "absl/strings/str_format.h"
#include "pqxx/pqxx"

int main() {
  const std::string host = std::getenv("DB_HOST");
  const std::string port = std::getenv("DB_PORT");
  const std::string name = std::getenv("DB_NAME");
  const std::string user = std::getenv("DB_USERNAME");
  const std::string password = std::getenv("DB_PASSWORD");

  try {
    // Connect to the database.
    pqxx::connection c(
        absl::StrFormat("host=%s port=%s dbname=%s user=%s password=%s", host,
                        port, name, user, password));

    // Start a transaction.  In libpqxx, you always work in one.
    pqxx::work w(c);

    // work::exec1() executes a query returning a single row of data.
    // We'll just ask the database to return the number 1 to us.
    pqxx::row r = w.exec1("SELECT 1");

    // Commit your transaction.  If an exception occurred before this
    // point, execution will have left the block, and the transaction will
    // have been destroyed along the way.  In that case, the failed
    // transaction would implicitly abort instead of getting to this point.
    w.commit();

    // Look at the first and only field in the row, parse it as an integer,
    // and print it.
    //
    // "r[0]" returns the first field, which has an "as<...>()" member
    // function template to convert its contents from their string format
    // to a type of your choice.
    std::cout << r[0].as<int>() << std::endl;

    c.close();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}