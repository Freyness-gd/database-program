#include "pch.h"
#include "userClass.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
#include <iomanip>
#include <boost/scoped_ptr.hpp>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <cppconn/metadata.h>

UserInstance::UserInstance(std::string server_db, std::string server_url)
{
  std::cout << "Username: " << '\n';
  std::cin >> username;

  std::cout << "Password: " << '\n';
  std::cin >> temp_pass;

}

int UserInstance::check_credentials()
{
  try
  {
    std::cout << username << '\n';
    std::cout << temp_pass << '\n';

    std::string log_com = "SELECT userPassword FROM users WHERE userName IN (\""
                              + username + "\")";

    std::cout << log_com << '\n';

    sql::Driver *user_driver = get_driver_instance();
    std::unique_ptr < sql::Connection > con(user_driver->connect(url, db_user, db_pass));
    con->setSchema(database);
    std::unique_ptr < sql::Statement > statement(con->createStatement());

    boost::scoped_ptr < sql::ResultSet >  login_res(statement->executeQuery(log_com));

    std::cout << "Rows: " << login_res->rowsCount() << '\n';
    login_res->next();
    std::cout << ((login_res->getString("userPassword")) == temp_pass) << '\n';
    std::cout << "Pass not deleted: " << temp_pass << '\n';
    temp_pass.clear();
    std::cout << "Pass deleted: " << temp_pass << '\n';

  }

  catch(sql::SQLException &error_code)
  {
    std::cout << "#ERR: " << error_code.what();
    std::cout << " (MySQL error code: " << error_code.getErrorCode();
    std::cout << ", SQLState: " << error_code.getSQLState() << " )" << std::endl;

    return 1;
  }
  return 0;
}
