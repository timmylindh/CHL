# CHL
C Hypertext Library - A library for writing web applications in C

## What is CHL?

CHL, short for *C Hypertext Library*, is a library written in C to be used to write web applications of all sorts. CHL provides a lot of useful features:

> - *Set, configure and remove cookies and sessions.*
- *File management: upload and store files on the server.*
- *Inline functions and variables in Hypertext documents using the '<{ function(variable); }>' syntax.*
- *Database management using the Mysql API.*
- *Functions for handling of POST and GET data.*
- *Set and change various HTTP headers.*

and a lot more...

## How does it work?

Web applications written in C must somehow be executed by the Web server since C is a compiled langauge. To make this possible CHL is based on CGI (Common Gateway Interface), which in short means that the server executes your program and passes it data through environment variables. CHL does all the parsing and handling of CGI in the background, and provides you with some easy to use functions instead.

## Setup

For a proper guide on how to install and configure CHL on your system, read the following: (link).

## Enable CGI

First you will want to enable CGI scripts in the Apache2 configuration file (*/etc/apache2/apache2.conf*).


```bash
vim /etc/apache2/apache2.conf
```
Look for a line that says: *"\<Directory /var/www/>"*. Add the following inside of it:

```bash
Options +ExecCGI
AddHandler cgi-script .chl
```

This tells Apache to handle all files with the *.chl* ending as CGI scripts.


Now you will have to enable the CGI module as well.

```bash
a2enmod cgi
```

Restart Apache and you are good to go.

```bash
service apache2 restart
```

## Contribute

Comming soon....







