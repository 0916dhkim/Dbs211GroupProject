#ifndef DBS211_UTILS_H
#define DBS211_UTILS_H
#include <occi.h>
#include <vector>
#include <iostream>
#include "Employee.h"
namespace dbs211 {
//--------------- Assignment Specification ---------------

/*
 * Print menu & get user input.
 * @author Danny Ou
 */
int menu(void);

/*
 * Find and save an employee to the given address.
 * Returns 0 if the employee does not exist. Returns 1 otherwise.
 * @author Donghyeon Kim
 */
int findEmployee(oracle::occi::Connection* conn,
                 int employeeNumber,
                 Employee* emp);

/*
 * Print employee information to cout.
 * @author Donghyeon Kim
 */
void displayEmployee(oracle::occi::Connection* conn, Employee emp);

/*
 * Select all employees from the database and print them.
 * @author Donghyeon Kim
 */
void displayAllEmployees(oracle::occi::Connection* conn);

//------------------- Helper Functions -------------------

/*
 * Fool-proof intger input.
 * @author Donghyeon Kim
 */
int getInt(const char* prompt = nullptr);
int getInt(
    int min,                             // minimum acceptable value
    int max,                             // maximum acceptable value
    const char* prompt = nullptr,        // User entry prompt
    const char* errorMessage = nullptr,  // Invalid value error message
    bool showRangeAtError = true  // Display the range if invalid value entered
);

/*
 * Convert SQL ResultSet to Vector.
 * @author Donghyeon Kim
 */
std::vector<Employee> resultSetToVector(oracle::occi::ResultSet*);

/*
* Easy dash printing.
* @author Donghyeon Kim
*/
class Dash {
 public:
  unsigned count;
  Dash(unsigned count) : count(count){};
};
std::ostream& operator<<(std::ostream& ostr, const Dash& dash);
}  // namespace dbs211
#endif
