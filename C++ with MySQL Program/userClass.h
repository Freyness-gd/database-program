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
private:
  std::string database {"users_mysql"};
  std::string url {"localhost:3306"};
  std::string db_user {"root"};
  std:: string db_pass {""};
  std::string username {"default"};
  std::string temp_pass {""};
  std::string account {"CN default"};
  std::string group {"default"};
  std::string type {"default"};

public:
  UserInstance() = default;
  UserInstance(std::string server_db, std::string server_url);

  int check_credentials();
  void account_recall();
  int create_invoice();
  void inbox();
  void finance_plan();
  int request_credit();
  void show_card();

};


#endif
