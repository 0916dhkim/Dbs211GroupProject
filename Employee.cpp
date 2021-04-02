#include "Employee.h"

using namespace std;

namespace dbs211 {
Employee::Employee(int employeeNumber,
                   std::string lastName,
                   std::string firstName,
                   std::string extension,
                   std::string email,
                   std::string officeCode,
                   int reportsTo,
                   std::string jobTitle

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