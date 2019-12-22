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


UserInstance::UserInstance(std::string server_db, std::string server_url,
                           std::string server_user, std::string server_pass)
{
  database = server_db;
  url = server_url;
  db_user = server_user;
  db_pass = server_pass;

}

int UserInstance::credentialCheck()
{
  try
  {
    std::cout << "Username: " << '\n';
    std::cin >> username;
    std::cout << "Password: " << '\n';
    std::cin >> temp_pass;

    std::string log_com = "SELECT userPassword FROM users WHERE userName IN (\""
                              + username + "\")";

    std::cout << log_com << '\n';

    sql::Driver *user_driver = get_driver_instance();
    std::unique_ptr < sql::Connection > con(user_driver->connect(url, db_user, db_pass));
    con->setSchema(database);
    std::unique_ptr < sql::Statement > statement(con->createStatement());

    boost::scoped_ptr < sql::ResultSet >  login_res(statement->executeQuery(log_com));

    login_res->next();
    std::cout << ((login_res->getString("userPassword")) == temp_pass) << '\n';
    switch((login_res->getString("userPassword")) == temp_pass)
    {
        case 1:  return 0;
        case 0: std::cout << "Wrong Pasword" << '\n'; return 1;
    }

    temp_pass.clear();

  }

  catch(sql::SQLException &e)
  {
    error.error_code = e.getErrorCode();
    error.error_text = e.what();
    error.sql_state = e.getSQLState();

    UserInstance::errorCheck(error);

    return 1;
  }

  return 0;
}


void UserInstance::errorCheck(Error error)
{
  std::cout << "Error Check" << '\n';
  std::cout << error.error_code << '\n';
  std::cout << error.sql_state << '\n';
  std::cout << error.error_text << '\n';

  switch(error.error_code)
  {
    case 0: std::cout << "SQL Query ERROR: " << error.error_text << '\n'; break;
    case 1049: std::cout << "Unknown Database!" << '\n'; exit(1049);
    case 2003: std::cout << "Connection with Server Failed" << '\n';
               connError();
               std::cout << "Connection Established" << '\n';
               break;
    default: std::cout << "Uknown Problem with code: " <<
                           error.error_code << '\n'; exit(error.error_code);
  }
}

void UserInstance::connError()
{
  bool conn_index = true;
  sql::Driver *driver = get_driver_instance();

  while(conn_index)
  {
    try
    {
      driver->connect(url, db_user, db_pass);
      conn_index = false;
    }
    catch(sql::SQLException &e)
    { std::cout << "Trying to connect to Server!" << '\n'; }
  }

}
