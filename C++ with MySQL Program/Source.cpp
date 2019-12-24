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
#define DB "users_mysql"

void menuAdmin()
{
	std::cout << "ADMIN MENU" << '\n';
	std::cout << "//////////" << '\n' << '\n';

	std::cout << "Commands:" << '\n'
						<< "&/&/&/&/&" << '\n' << '\n'
						<< "1. INSERT User" << '\n'
						<< "2. READ User Info" << '\n'
						<< "3. READ All Users" << '\n'
						<< "4. DELETE User" << '\n'
						<< "5. CHANGE User Info" << '\n';

	
}

///////////////////////////////////////////////////////////////////////////////

void menuPrivate()
{
	std::cout << "PRIVATE MENU" << '\n';
}

///////////////////////////////////////////////////////////////////////////////

void menuBusiness()
{
	std::cout << "BUSINESS MENU" << '\n';
}

///////////////////////////////////////////////////////////////////////////////

void menuWorker()
{
	std::cout << "WORKER MENU" << '\n';
}

///////////////////////////////////////////////////////////////////////////////

int main()
{
	UserInstance user(DB, HOST, USER, PASS);

	std::cout << "Welcome to C+SQL Bank!" << '\n';

	int pass_through = 1;
	do
	{
		pass_through = user.credentialCheck();
	}
	while(pass_through != 0);

	user.setUp();

	if (user.type == "administrator")
	{	menuAdmin(); }

	else if (user.type == "private")
	{ menuPrivate(); }

	else if (user.type == "business")
	{ menuBusiness(); }

	else if (user.type == "worker")
	{ menuWorker(); }

	else
	{
		std::cout << "Unknown Type " << '\n';
		exit(-1);
	}

}

///////////////////////////////////////////////////////////////////////////////
