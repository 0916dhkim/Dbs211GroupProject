# Dbs211GroupProject
Seneca College DBS211 Course Group Project.

## Setup
This project requires Microsoft Visual Studio and Oracle Instant Client.

### Configure Visual C++
1. In "Configuration Manager" set "Active solution configuration" to "Release" and "Active solution platform" to "x64".
1. Project Properties > C/C++ > General > Additional Include Directories: `C:\app\<username>\product\12.2.0\client_1\oci\include`
1. Project Properties > Linker > General > Additional Library Directories : `C:\app\<username>\product\12.2.0\client_1\oci\lib\msvc;C:\app\<username>\product\12.2.0\client_1\oci\lib\msvc\vc14`
1. Project Properties > Linker > Input > Additional Dependencies : `oraocci12.lib`

### Enter Database Credentials.
Open `Secrets.h` file and enter your database username & password.
