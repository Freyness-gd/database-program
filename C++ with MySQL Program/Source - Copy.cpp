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


#define EXAMPLE_HOST "localhost:3306"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS ""
#define EXAMPLE_DB "users_mysql"

int insert_function(std::string database, int uIndex, int uScore, const std::string url, const std::string user, const std::string pass, std::string uName)

{
	try
	{
		sql::Driver *driver = get_driver_instance();
		std::unique_ptr < sql::Connection > con(driver->connect(url, user, pass));
		con->setSchema("test");
		std::unique_ptr < sql::Statement > stmt(con->createStatement());

		boost::scoped_ptr< sql::PreparedStatement > prep_stmt(con->prepareStatement("INSERT INTO uname(id, name, score) VALUES (?, ?, ?)"));
		prep_stmt->setInt(1, uIndex);
		prep_stmt->setString(2, uName);
		prep_stmt->setInt(3, uScore);

		prep_stmt->execute();

		/*boost::scoped_ptr < sql::ResultSet > res(stmt->executeQuery("SELECT userPassword FROM users WHERE userIndex IN(\"1\")"));

		std::string password = "adminx";

		std::cout << "Rows: " << res->rowsCount() << '\n';
		res->next();
		std::cout << ((res->getString("userPassword")) == password) << '\n';

		*/
	}

	catch (sql::SQLException &e) {
		/*
		  MySQL Connector/C++ throws three different exceptions:
		  - sql::MethodNotImplementedException (derived from sql::SQLException)
		  - sql::InvalidArgumentException (derived from sql::SQLException)
		  - sql::SQLException (derived from std::runtime_error)
		*/
		/*std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

		return 1;

	}

	return 0;

}

int read_function(std::string database, int uIndex, int uScore, const std::string url, const std::string user, const std::string pass, std::string uName)
{
	try {

		size_t row;

		sql::Driver* driver = get_driver_instance();
		std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
		con->setSchema(database);
		std::unique_ptr<sql::Statement> stmt(con->createStatement());


		boost::scoped_ptr <sql::ResultSet> res(stmt->executeQuery("SELECT id, name, score FROM uname ORDER BY ID ASC"));
		std::cout << "#\t Running SELECT id, name, score" << '\n';

		std::cout << "#\t\t Number of row\t";
		std::cout << "res->rowsCount() = " << res->rowsCount() << '\n';

		row = 0;
		while (res->next())
		{
			std::cout << "#\t\t Fetching row" << row << "\t";
			std::cout << "id = " << res->getInt(1);
			std::cout << ", name = " << res->getString("name");
			std::cout << ", score = " << res->getInt(3) << '\n';
		}



		// get Version of MySQL Server
		std::cout << "# " << driver->getName() << ", version ";
		std::cout << driver->getMajorVersion() << "." << driver->getMinorVersion();
		std::cout << "." << driver->getPatchVersion() << std::endl;
		// get MetaData
		std::cout << con->getMetaData() << std::endl;
		sql::DatabaseMetaData * conData = con->getMetaData();
		std::cout << conData->getCDBCMajorVersion() << std::endl;
		// List of Available schematics/databases
		std::cout << "# List of available databases: " << std::endl;
		boost::scoped_ptr<sql::ResultSet> res_sch(conData->getSchemas());
		res_sch->afterLast();
		while (res_sch->previous()) {
			std::cout << res_sch->getString("TABLE_SCHEM");
			if (!res_sch->isFirst()) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		/*if (!res_sch->isBeforeFirst() || res_sch->isFirst())
			throw std::runtime_error("Cursor should be positioned before first row");
		boost::scoped_ptr<sql::ResultSet> res2(conData->getSchemaObjectTypes());
		while (res2->next())
		{
			std::cout << res2->getString(1);
			if (!res2->isLast())
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		if (!res2->isAfterLast() || res->isLast())
			throw std::runtime_error("Cursor should be positioned after last row");*/
			// We need not check the return value explicitly. If it indicates
			// an error, Connector/C++ generates an exception.
			//stmt->execute("INSERT INTO test(id, name, score) VALUES ('', '', '');");
			//stmt->execute("DELETE FROM test WHERE id = 0;");

	}



	catch (sql::SQLException &e) {
		/*
		  MySQL Connector/C++ throws three different exceptions:
		  - sql::MethodNotImplementedException (derived from sql::SQLException)
		  - sql::InvalidArgumentException (derived from sql::SQLException)
		  - sql::SQLException (derived from std::runtime_error)
		*/
		/*std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		/* what() (derived from std::runtime_error) fetches error message */
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

		return 1;
	}

	return 0;

}

int main(void)
{
	/*std::string databaseVar;
	std::string tableVar;
	std::cout << "Enter the database name: " << '\n';
	std::cin >> databaseVar;
	std::cout << "Enter the table name: " << '\n';
	std::cin >> tableVar;


	int uIndex = NULL;
	std::string uName = " ";
	int uScore = NULL;

	std::cout << "Index: " << '\n';
	std::cin >> uIndex;
	std::cout << "Name: " << '\n';
	std::cin >> uName;
	std::cout << "Score: " << '\n';
	std::cin >> uScore;

	const std::string url = EXAMPLE_HOST;
	const std::string user = EXAMPLE_USER;
	const std::string pass = EXAMPLE_PASS;
	const std::string database = EXAMPLE_DB;

	int option = 0;
	std::cout << "Choose between 1. Insert and 2. Read" << std::endl;
	std::cin >> option;


	switch (option)
	{
	case 1:
		insert_function(database, uIndex, uScore, url, user, pass, uName);
		break;
	case 2:
		read_function(database, uIndex, uScore, url, user, pass, uName);
		break;
	}

	// Initialisation of variables needed for Connection with server and actions

	std::cout << "Done." << std::endl;*/

	UserInstance user_obj(EXAMPLE_DB, EXAMPLE_HOST);
	user_obj.check_credentials();


	return EXIT_SUCCESS;
}
