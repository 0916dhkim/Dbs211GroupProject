#ifndef DBS211_EMPLOYEE_H
#define DBS211_EMPLOYEE_H
#include <string>
namespace dbs211 {
class Employee {
 private:
  int mEmployeeNumber;
  std::string mLastName;
  std::string mFirstName;
  std::string mExtension;
  std::string mEmail;
  std::string mOfficeCode;
  int mReportsTo;
  std::string mJobTitle;

 public:
  Employee(int employeeNumber,
           std::string lastName,
           std::string firstName,
           std::string extension,
           std::string email,
           std::string officeCode,
           int reportsTo,
           std::string jobTitle

  );

  int employeeNumber() const;
  std::string lastName() const;
  std::string firstName() const;
  std::string extension() const;
  std::string email() const;
  std::string officeCode() const;
  int reportsTo() const;
  std::string jobTitle() const;
};
}  // namespace dbs211
#endif
