/*THIS PROJECT WAS FULLY CREATED BY:

 - Marc Nicolas Oliva
 - Danny Ou
 - Donghyeon Kim
 - Jonathan Forrester

 All the code shown in this project is original content created by the authors mentioned above.

 Submission - Date
        MS1 - 09/04/2021
        MS2 - 16/04/2021
 */

#include <occi.h>
#include <iomanip>
#include <iostream>
#include "Secrets.h"
#include "utils.h"

using oracle::occi::Environment;

using namespace oracle::occi;
using namespace std;
using namespace dbs211;

int main(void) {
  /* OCCI Variables */
  Environment* env = nullptr;
  Connection* conn = nullptr;

  try {
    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(user, pass, constr);

    bool shouldExit = false;

    while (!shouldExit) {
      int menuSelection = menu();

      switch (menuSelection) {
        case 1: {
          Employee target;
          int employeeNumber = getInt("Enter Employee Number: ");
          if (findEmployee(conn, employeeNumber, &target)) {
            displayEmployee(conn, target);
          } else {
            cout << "Employee " << employeeNumber << " does not exist." << endl;
          }
          break;
        }
        case 2: {
          displayAllEmployees(conn);
          break;
        }
        case 3: {
            Employee emp{};
            insertEmployee(conn, emp);
            break; 
        }
        case 4: {
            int employeeNumber = getInt("Enter Employee Number: ");
            updateEmployee(conn, employeeNumber);
            break;
        }
        case 5: {
            int employeeNumber = getInt("Enter Employee Number: ");
            deleteEmployee(conn, employeeNumber);
            break;
        }
        default:
          shouldExit = true;
          break;
      }
    }

    // Clean up.
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);
  } catch (SQLException& sqlExcp) {
    cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
  }
  return 0;
}
