#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace oracle::occi;
using namespace std;

namespace dbs211 {
int menu() {
  int option;
  bool check = false;
  cout << "********************* HR Menu *********************" << endl;
  cout << "1) Find Employee" << endl;
  cout << "2) Employees Report" << endl;
  cout << "3) Add Employee" << endl;
  cout << "4) Update Employee" << endl;
  cout << "5) Remove Employee" << endl;
  cout << "0) Exit" << endl;

  return getInt(0, 5, "Enter Option: ", "Invalid Option try again: ", false);
}

void deleteEmployee(oracle::occi::Connection* conn, int employeeNumber) {
    string query = "DELETE FROM employees WHERE employeeNumber = :1";
    try {
        Employee emp;

        if (findEmployee(conn, employeeNumber, &emp)) {
            Statement* stmt = conn->createStatement(query);
            stmt->setInt(1, employeeNumber);
            ResultSet* result = stmt->executeQuery();

            conn->commit();
            conn->terminateStatement(stmt);
            cout << "The employee with ID " << employeeNumber << " is deleted successfully." << endl << endl;
        }
        else {
            cout << "The employee with ID " << employeeNumber << " does not exist." << endl << endl;
        }
    }
    catch (SQLException& e) {
        cerr << e.getErrorCode() << ": " << e.getMessage() << endl;
    }
}

int findEmployee(oracle::occi::Connection* conn, int employeeNumber, Employee* emp) {
  bool found = false;
  string query =
      "SELECT "
      "employeeNumber, lastName, firstName, extension, email, officeCode, "
      "reportsTo, jobTitle "
      "FROM employees "
      "WHERE employeeNumber = :1";
  try {
    Statement* statement = conn->createStatement(query);
    statement->setInt(1, employeeNumber);
    ResultSet* result = statement->executeQuery();
    auto employees = resultSetToVector(result);
    if (employees.size() > 0) {
      // Found.
      found = true;
      *emp = employees[0];
    }
    conn->terminateStatement(statement);
  } catch (SQLException& e) {
    cerr << e.getErrorCode() << ": " << e.getMessage() << endl;
  }

  return found ? 1 : 0;
}

void displayEmployee(oracle::occi::Connection* conn, Employee emp) {
  cout << "-------------- Employee Information --------------" << endl;
  cout << "Employee Number: " << emp.employeeNumber << endl;
  cout << "Last Name: " << emp.lastName << endl;
  cout << "First Name" << emp.firstName << endl;
  cout << "Extension: " << emp.extension << endl;
  cout << "Email: " << emp.email << endl;
  cout << "Office Code: " << emp.officecode << endl;
  cout << "Manager ID: " << emp.reportsTo << endl;
  cout << "Job Title: " << emp.jobTitle << endl;
}

void displayAllEmployees(oracle::occi::Connection* conn) {
  string query =
      "SELECT e.employeeNumber, e.firstName, e.lastName, "
      "       e.email, o.phone, e.extension, "
      "       m.firstName, m.lastName "
      "FROM employees e "
      "LEFT JOIN employees m ON e.reportsTo = m.employeeNumber "
      "LEFT JOIN offices o ON m.officeCode = o.officeCode "
      "ORDER BY e.employeeNumber";
  try {
    Statement* statement = conn->createStatement(query);
    ResultSet* result = statement->executeQuery();
    if (!result->next()) {
      // Empty.
      cout << "There is no employees' information to be displayed." << endl;
    } else {
      // First line.
      cout << Dash(5) << ' ';
      cout << Dash(20) << ' ';
      cout << Dash(40) << ' ';
      cout << Dash(16) << ' ';
      cout << Dash(9) << ' ';
      cout << Dash(20) << endl;

      // Column Names.
      cout << setw(6) << left << "ID";
      cout << setw(21) << left << "Employee Name";
      cout << setw(41) << left << "Email";
      cout << setw(17) << left << "Phone";
      cout << setw(10) << left << "Extension";
      cout << setw(20) << left << "Manager Name" << endl;

      // Second line.
      cout << Dash(5) << ' ';
      cout << Dash(20) << ' ';
      cout << Dash(40) << ' ';
      cout << Dash(16) << ' ';
      cout << Dash(9) << ' ';
      cout << Dash(20) << endl;

      do {
        cout << setw(6) << left << result->getInt(1);
        cout << setw(21) << left
             << result->getString(2) + ' ' + result->getString(3);
        cout << setw(41) << left << result->getString(4);
        cout << setw(17) << left << result->getString(5);
        cout << setw(10) << left << result->getString(6);
        cout << setw(20) << left
             << result->getString(7) + ' ' + result->getString(8) << endl;
      } while (result->next());
    }
    conn->terminateStatement(statement);
  } catch (SQLException& e) {
    cerr << e.getErrorCode() << ": " << e.getMessage() << endl;
  }
}

int getInt(int min,
           int max,
           const char* prompt,
           const char* errorMessage,
           bool showRangeAtError) {
  int ret = 0;
  string extras = "";
  bool complete = false;

  if (prompt != nullptr)
    cout << prompt;

  do {
    cin >> ret;
    bool inputSuccess = cin.good();
    cin.clear();
    getline(cin, extras);
    complete = cin && extras == "" && min <= ret && ret <= max;
    if (!inputSuccess) {
      cout << "Bad integer value, try again: ";
    } else if (extras != "") {
      cout << "Enter only an integer, try again: ";
    } else if (min > ret || max < ret) {
      if (errorMessage != nullptr) {
        cout << errorMessage;
      }
      if (showRangeAtError) {
        cout << "[" << min << " <= value <= " << max << "]: ";
      }
    }
  } while (!complete);

  return ret;
}

int getInt(const char* prompt) {
  return getInt(numeric_limits<int>::min(), numeric_limits<int>::max(), prompt,
                "", false);
}

vector<Employee> resultSetToVector(ResultSet* result) {
  if (!result->next()) {
    // Empty result set.
    return vector<Employee>();
  }

  vector<Employee> res;
  do {
    Employee element;

    element.employeeNumber = result->getInt(1);
    strcpy(element.lastName, result->getString(2).c_str());
    strcpy(element.firstName, result->getString(3).c_str());
    strcpy(element.extension, result->getString(4).c_str());
    strcpy(element.email, result->getString(5).c_str());
    strcpy(element.officecode, result->getString(6).c_str());
    element.reportsTo = result->getInt(7);
    strcpy(element.jobTitle, result->getString(8).c_str());

    res.push_back(element);
  } while (result->next());

  return res;
}

ostream& operator<<(ostream& ostr, const Dash& dash) {
  for (unsigned i = 0; i < dash.count; i++)
    ostr << '-';
  return ostr;
}
}  // namespace dbs211