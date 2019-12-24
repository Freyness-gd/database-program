#pragma once
#ifndef USERCLASS_H
#define USERCLASS_H

#include "pch.h"

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




class UserInstance
{
public:
  std::string username {"guest"};
  std::string type {"guest"};
  std::string group {"guest"};
  std::string account {"CN default"};

private:

  struct Error
  {
    int error_code = 0;
    std::string error_text = "";
    std::string sql_state = "0";
  };

  Error error;

  std::string database {"users_mysql"};
  std::string url {"localhost:3306"};
  std::string db_user {"root"};
  std:: string db_pass {""};

    std::string temp_pass {""};

  sql::Driver *user_driver;
  std::unique_ptr < sql::Connection > user_conn;
  std::unique_ptr < sql::Statement > user_stmt;
  boost::scoped_ptr < sql::ResultSet > query_res;


public:

  UserInstance() = default;
  UserInstance(std::string server_db, std::string server_url,
               std::string server_user, std::string server_pass);

  int credentialCheck();

  void setUp();

  void printInfo();

  void account_recall();

  int create_invoice();

  void inbox();

  void finance_plan();

  int request_credit();

  void show_card();


private:
  void connError();

  void errorCheck(Error error);


};


#endif
