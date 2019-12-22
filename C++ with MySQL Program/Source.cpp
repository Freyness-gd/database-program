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

#define HOST "localhost:3306"
#define USER "root"
#define PASS ""
#define DB "users_mysq"



int main()
{
	UserInstance user(DB, HOST, USER, PASS);

	int pass_through = 1;

	do
	{
		pass_through = user.credentialCheck();
	}
	while(pass_through != 0);


	std::cout << "LOGIN SUCCES" << '\n';

}
