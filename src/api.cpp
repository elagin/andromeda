#include "api.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver/mysql_public_iface.h>

extern "C"
{
#ifdef WIN32
#include <Rpc.h>
#else
#include <uuid/uuid.h>
#endif
}

Api::Api() {}

std::string Api::newUUID()
{
#ifdef WIN32
	UUID uuid;
	UuidCreate ( &uuid );

	unsigned char * str;
	UuidToStringA ( &uuid, &str );

	std::string s( ( char* ) str );

	RpcStringFreeA ( &str );
#else
	uuid_t uuid;
	uuid_generate_random ( uuid );
	char s[37];
	uuid_unparse ( uuid, s );
#endif
	return s;
}



string Api::login(string name, string pass)
{
	string dbUser = "";
	string dbPass = "";
	string dbUrl ="";
	string database = "monitoring";
	string res = "";

	try {
		res = newUUID();
		sql::Driver* driver = sql::mysql::get_driver_instance();
		std::auto_ptr< sql::Connection > con(driver->connect(dbUrl, dbUser, dbPass));
		std::auto_ptr< sql::Statement > stmt(con->createStatement());
		stmt->execute("USE " + database);

		stringstream sql;
		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT password FROM md_user WHERE login = 'demo'"));
		cout << "res->rowsCount() = " << res->rowsCount() << endl;
		//sql << "SELECT password FROM md_user WHERE login = demo";
		//sql << pass;

		//std::auto_ptr< sql::ResultSet > res(stmt->executeQuery(sql.str()));
		//if(res->rowsCount() > 0)
			//while (res->next()) {
			//cout << "#\t\t Fetching row " << row << "\t";
			/* You can use either numeric offsets... */
		while (res->next()) {
			cout << "pass = " << res->getString(1);
		}
		/*
		The MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
	}catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		//		cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		cout << "not ok 1 - examples/connect.php" << endl;

		//return EXIT_FAILURE;
	} catch (std::runtime_error &e) {

		cout << "# ERR: runtime_error in " << __FILE__;
		//cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << "not ok 1 - examples/connect.php" << endl;

		//return EXIT_FAILURE;
	} catch (exception& e) {
		cout << e.what();
	} catch (...) {
		cout << "...";
	}

	return res;
}
