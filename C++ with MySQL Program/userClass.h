#pragma once
#ifndef USERCLASS_H
#define USERCLASS_H
#include <string>

class UserInstance
{

private:
  std::string username;
  std::string password;
  std::string group;
  std::string account;

public:
  UserInstance(std::string username, std::string password, std::string group, std::string account);

  int check_credentials(std::string username, std::string password);

  void account_recall();
  int create_invoice();
  void inbox();
  void finance_plan();
  int request_credit();
  void show_card();

};

#endif
