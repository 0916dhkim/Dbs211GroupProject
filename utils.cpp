#include "utils.h"
#include <iostream>
using namespace std;

int dbs211::menu() {
  int option;
  bool check = false;
  cout << "********************* HR Menu *********************" << endl;
  cout << "1) Find Employee" << endl;
  cout << "2) Employees Report" << endl;
  cout << "3) Add Employee" << endl;
  cout << "4) Update Employee" << endl;
  cout << "5) Remove Employee" << endl;
  cout << "0) Exit" << endl;
  cout << "Enter Option: ";
  while (check == false) {
    check = true;
    cin >> option;
    if (cin.fail() || option > 5 || option < 0) {
      check = false;
      cout << "Invalid Option try again: ";
      cin.clear();
      cin.ignore(1000, '\n');
    }
  }
  return option;
}
