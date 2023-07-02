# php-api-to-license-plugins-inc-
Include file and php api to license your plugins to ips:ports

# Requirements
PHP 7.0 or higher with PDO drivers enabled for one of these database systems:

MySQL 5.6 / MariaDB 10.0 or higher for spatial features in MySQL

# Installation
This is a single file application! Upload "api.php" somewhere and enjoy!

Add __**#include <plugin_protect>**__ to the top of your plugin source code

# Configuration
  1. Edit the following lines in the bottom of the file "api.php":
```
$config = new Config([
    'username' => 'xxx',
    'password' => 'xxx',
    'database' => 'xxx',
]);
```
  2. Go to phpmyadmin and create a new table. Import the ServersLicense.sql file to the table.

  3. Add your api url to __**sUrl**__ in *plugin_protect.inc* (line *55*)

     !!! Respect this format: __**https://yourwebsiteurl/api.php/records/Db_Table_Name_YouChoseAtSecondStep**__

# How to add a server to DB
  
  