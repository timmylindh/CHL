# CHL
C Hypertext Library - A library for writing web applications in C

## What is CHL?

CHL, short for *C Hypertext Library*, is a library written in C to be used to write web applications of all sorts. CHL will provide a lot of useful features:

> - *Set, configure and remove cookies and sessions.*
- *File management: upload and store files on the server.*
- *Inline functions and variables in Hypertext documents using the '<{ function(variable); }>' syntax.*
- *Database management using the Mysql API.*
- *Functions for handling of POST and GET data.*
- *Set and change various HTTP headers.*

and a lot more...

## How does it work?

Web applications written in C must somehow be executed by the Web server since C is a compiled langauge. To make this possible CHL is based on CGI (Common Gateway Interface), which in short means that the server executes your program and passes it data through environment variables. CHL does all the parsing and handling of CGI in the background, and provides you with some easy to use functions instead.
