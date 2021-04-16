#include "Employee.h"

using namespace std;

namespace dbs211 {
Employee::Employee(int employeeNumber,
                   char lastName[50],
                   char firstName[50],
                   char extension[10],
                   char email[100],
                   char officeCode[10],
                   int reportsTo,
                   char jobTitle[50]
                   )
    : mEmployeeNumber(employeeNumber),
      mLastName(lastName),
      mFirstName(firstName),
      mExtension(extension),
      mEmail(email),
      mOfficeCode(officeCode),
      mReportsTo(reportsTo),
      mJobTitle(jobTitle) {}

int Employee::employeeNumber() const {
  return mEmployeeNumber;
}

string Employee::lastName() const {
  return mLastName;
}

string Employee::firstName() const {
  return mFirstName;
}

string Employee::extension() const {
  return mExtension;
}

string Employee::email() const {
  return mEmail;
}

string Employee::officeCode() const {
  return mOfficeCode;
}

int Employee::reportsTo() const {
  return mReportsTo;
}

string Employee::jobTitle() const {
  return mJobTitle;
}
};  // namespace dbs211