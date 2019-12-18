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

UserInstance::UserInstance(std::string username, std::string password, std::string group, std::string account)
{
  check_credentials(username, password);
}

int UserInstance::check_credentials(std::string username, std::string password)
{
  const std::string url = "localhost:3306";
  const std::string user = "root";
  const std::string pass = "";
  const std::string database = "users_mysql";
  std::string testIndex = "1";
//  std::string command = "SELECT userIndex FROM users WHERE userIndex IN" + " (" + testIndex + ")";

  std::string command;

  try
  {
    sql::Driver *driver = get_driver_instance();
    std::unique_ptr < sql::Connection > con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::unique_ptr < sql::Statement > stmt(con->createStatement());

    boost::scoped_ptr< sql::PreparedStatement > prep_stmt(con->prepareStatement(command));
    int executeReturn = prep_stmt->execute();

    std::cout << "executeReturn: " << executeReturn << '\n';
  }

  catch (sql::SQLException &e)
  {
    std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

		return 1;
  }

  return 0;

}
