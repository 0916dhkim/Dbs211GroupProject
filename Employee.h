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

#ifndef DBS211_EMPLOYEE_H
#define DBS211_EMPLOYEE_H
#include <string>
namespace dbs211 {
struct Employee {
  int employeeNumber;
  char lastName[50];
  char firstName[50];
  char extension[10];
  char email[100];
  char officecode[10];
  int reportsTo;
  char jobTitle[50];
};
}  // namespace dbs211
#endif
