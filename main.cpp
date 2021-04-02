#include <occi.h>
#include <iomanip>
#include <iostream>
#include "Secrets.h"
#include "utils.h"

using oracle::occi::Connection;
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

    // Clean up.
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);
  } catch (SQLException& sqlExcp) {
    cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
  }
  return 0;
}
