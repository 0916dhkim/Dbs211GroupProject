// Donghyeon Kim
// dkim167@myseneca.ca
// 2021/03/18

#include <occi.h>
#include <iostream>
#include <iomanip>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

/* Easy dash printing */
class Dash {
public:
	unsigned count;
	Dash(unsigned count) : count(count) {};
};

ostream& operator<<(ostream& ostr, const Dash& dash) {
	for (unsigned i = 0; i < dash.count; i++) ostr << '-';
	return ostr;
}

/* Print report header */
void printHeader(unsigned reportNumber, string reportName) {
	// First row.
	string title = " (" + to_string(reportNumber) + " " + reportName + " Report) ";
	cout << Dash((80 - title.length()) / 2); // Left dash
	cout << title;
	cout << Dash(80 - title.length() - (80 - title.length()) / 2) << endl; // Right dash

	// Second row.
	cout << setw(13) << left << "Employee ID";
	cout << setw(20) << left << "First Name";
	cout << setw(20) << left << "Last Name";
	cout << setw(17) << left << "Phone";
	cout << setw(10) << left << "Extension";
	cout << endl;

	// Third row.
	cout << Dash(12) << ' ';
	cout << Dash(19) << ' ';
	cout << Dash(19) << ' ';
	cout << Dash(16) << ' ';
	cout << Dash(10);
	cout << endl;
}

/* Print one row of formatted data */
void printRow(ResultSet& result) {
	cout << setw(13) << left << result.getInt(1);
	cout << setw(20) << left << result.getString(2);
	cout << setw(20) << left << result.getString(3);
	cout << setw(17) << left << result.getString(4);
	cout << setw(10) << left << result.getString(5);
	cout << endl;
}

/* Print all rows of query result */
void printResult(string query, Connection& connection) {
	Statement* statement = connection.createStatement(query);
	ResultSet* result = statement->executeQuery();

	if (!result->next()) {
		cout << "ResultSet is empty." << endl;
	}
	else {
		do {
			printRow(*result);
		} while (result->next());
	}

	connection.terminateStatement(statement);
}

int main(void)
{
	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	/* Used Variables */
	string user = "dbs211_211b14";
	string pass = "23540718";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);

		// PART 1
		printHeader(1, "Employee");
		printResult(
			"SELECT e.employeeNumber, e.firstName, e.lastName, o.phone, e.extension "
			"FROM employees e "
			"LEFT JOIN offices o ON e.officeCode = o.officeCode "
			"WHERE UPPER(o.city) = 'SAN FRANCISCO' "
			"ORDER BY e.employeeNumber",
			*conn
		);

		// PART 2
		printHeader(2, "Manager");
		printResult(
			"SELECT DISTINCT m.employeeNumber, m.firstName, m.lastName, o.phone, m.extension "
			"FROM employees e "
			"INNER JOIN employees m ON e.reportsTo = m.employeeNumber "
			"LEFT JOIN offices o ON m.officeCode = o.officeCode "
			"ORDER BY m.employeeNumber",
			*conn
		);

		// Clean up.
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}
