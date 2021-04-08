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
