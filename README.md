# php-api-to-license-plugins-inc-
Include file and php api to license your plugins to ips:ports

# Requirements
PHP 7.0 or higher with PDO drivers enabled for one of these database systems:
MySQL 5.6 / MariaDB 10.0 or higher for spatial features in MySQL

# Installation
This is a single file application! Upload "api.php" somewhere and enjoy!
Add __**#include <ttony_protect>**__ to the top of your plugins source code

# Configuration
  1. Edit the following lines in the bottom of the file "api.php":
```
$config = new Config([
    'username' => 'xxx',
    'password' => 'xxx',
    'database' => 'xxx',
]);
```
