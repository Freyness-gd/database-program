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

///////////////////////////////////////////////////////////////////////////////

UserInstance::UserInstance(std::string server_db, std::string server_url,
                           std::string server_user, std::string server_pass)
{
  database = server_db;
  url = server_url;
  db_user = server_user;
  db_pass = server_pass;

}

///////////////////////////////////////////////////////////////////////////////

int UserInstance::credentialCheck()
{
  try
  {
    std::cout << "Username: " << '\n';
    std::cin >> username;
    std::cout << "Password: " << '\n';
    std::cin >> temp_pass;

    user_driver = get_driver_instance();

    user_conn.reset((user_driver->connect(url, db_user, db_pass)));
    user_conn->setSchema(database);

    user_stmt.reset((user_conn->createStatement()));

    std::string com = "";

    com = "SELECT COUNT(1) FROM users WHERE userName = \""
           + username + "\"";
    query_res.reset((user_stmt->executeQuery(com)));
    query_res->next();

    switch(query_res->getInt("COUNT(1)"))
    {
      case 0: std::cout << "Username not found" << '\n';
              return 1;
      case 1: break;

      default: std::cout << "Unexpected OUTPUT" << '\n';
    }


    com = "SELECT userPassword FROM users WHERE userName IN (\""
           + username + "\")";

    query_res.reset((user_stmt->executeQuery(com)));
    query_res->next();

    switch((query_res->getString("userPassword")) == temp_pass)
    {
        case 1:  temp_pass.clear(); return 0;
        case 0: temp_pass.clear(); std::cout << "Wrong Pasword" << '\n';
                return 1;
    }

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

///////////////////////////////////////////////////////////////////////////////

void UserInstance::errorCheck(Error error)
{
  std::cout << error.error_code << '\n';
  std::cout << error.sql_state << '\n';
  std::cout << error.error_text << '\n';

  switch(error.error_code)
  {
    case 0: std::cout << "SQL Query ERROR: " << error.error_text << '\n';
            break;
    case 1049: std::cout << "Unknown Database!" << '\n'; exit(1049);
    case 2003: std::cout << "Connection with Server Failed" << '\n';
               connError();
               std::cout << "Connection Established" << '\n';
               break;
    default: std::cout << "Uknown Problem with code: " <<
                           error.error_code << '\n'; exit(error.error_code);
  }
}

///////////////////////////////////////////////////////////////////////////////

void UserInstance::connError()
{
  bool conn_stat = true;

  while(conn_stat)
  {
    try
    {
      user_driver->connect(url, db_user, db_pass);
      conn_stat = false;
    }
    catch(sql::SQLException &e)
    { std::cout << "Trying to connect to Server!" << '\n'; }
  }

}

///////////////////////////////////////////////////////////////////////////////

void UserInstance::setUp()
{
  try
  {
    std::string com = "";

    com = "SELECT userType FROM users WHERE userName in (\"" +
           username + "\")";
    query_res.reset(user_stmt->executeQuery(com));
    query_res->next();
    type = query_res->getString("userType");

    com = "SELECT userGroup FROM users WHERE userName in (\"" +
           username + "\")";
    query_res.reset(user_stmt->executeQuery(com));
    query_res->next();
    group = query_res->getString("userGroup");

    com = "SELECT userAccount FROM users WHERE userName in (\"" +
           username + "\")";
    query_res.reset(user_stmt->executeQuery(com));
    query_res->next();
    account = query_res->getString("userAccount");
  }

  catch (sql::SQLException &e)
  {
    error.error_code = e.getErrorCode();
    error.error_text = e.what();
    error.sql_state = e.getSQLState();

    UserInstance::errorCheck(error);
  }

}

///////////////////////////////////////////////////////////////////////////////

void UserInstance::printInfo()
{
  std::cout << "User Name: " << username << '\n';
  std::cout << "Type: " << type << '\n';
  std::cout << "Group: " << group << '\n';
  std::cout << "ACCCOUNT: " << account << '\n';
}

///////////////////////////////////////////////////////////////////////////////
