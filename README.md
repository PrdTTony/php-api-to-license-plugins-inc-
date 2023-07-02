# php-api-to-license-plugins-
Include file and php api to license your plugins to ips:ports

# Requirements
PHP 7.0 or higher with PDO drivers enabled for one of these database systems:

  MySQL 5.6 / MariaDB 10.0 or higher for spatial features in MySQL

SteamWorks running on the server

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
  2. Go to phpmyadmin and create a new table. Import the ServersLicense.sql file into the table.

  3. Add your api url to __**sUrl**__ in *plugin_protect.inc* file (line *55*)

     !!! Respect this format: __**https://yourwebsiteurl/api.php/records/ServersLicense**__

# How to license a server
  
  Insert into the table you just created the Server Name in **server_name** column 

  Insert the server ip and port in this format __**ip:port**__ (Example: 1.1.1.1:1) 
  
  !! At **Expires** column you have two options: 
        
        1. If you want to make the license never expire type: forever
        2. If you want to add a date use this format: year-month-day  (Example: 2024-05-21)

Forked from here and more details about the api: https://github.com/mevdschee/php-crud-api
  
  
