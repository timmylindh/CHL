# CHL
C Hypertext Library - A library for writing web applications in C

## What is CHL?

CHL, short for *C Hypertext Library*, is a library written in C to be used to write web applications of all sorts. CHL provides you with a lot of useful features:

> - *Parsing and fetching HTTP data, such as POST and GET.*
- *Creating and deleting HTTP headers.*
- *A dedicated API for creating and deleting cookies.*
- *The ability to execute CHL functions within HTML files*


and a lot more...

## How does it work?

Web applications written in C must somehow be executed by the Web server since C is a compiled langauge. To make this possible CHL is based on CGI (Common Gateway Interface), which in short means that the server executes your program and passes it data through environment variables. CHL does all the parsing and handling of CGI in the background, and provides you with some easy to use functions instead.

## Setup ([link](https://github.com/it4e/CHL/blob/master/SETUP.md))

For a proper guide on how to install and configure CHL on your system, read the following document: https://github.com/it4e/CHL/blob/master/SETUP.md

As of now, CHL is only officially available on Linux, but I am planning to port it to other operating systems as well if the interest is big enough. Otherwise you could of course make a port of it yourself, see [contribute](#contribute).

## Tutorial ([link](https://github.com/it4e/CHL/blob/master/TUTORIAL.md))

To read an in depth tutorial on the structure of *CHL web applications*, and a walk through on how to get started and how to use the *CHL API* properly see https://github.com/it4e/CHL/blob/master/TUTORIAL.md.

The tutorial is divided into various sections. The first section is a quick introduction to let you know what *CHL* is all about and what it can do for you. We will then dig deeper and deeper into the CHL API.

Before you start reading this tutorial, make sure you have CHL installed and that everything is properly set up. [Setting up CHL](https://github.com/it4e/CHL/blob/master/SETUP.md).


## <a name="contribute">Contribute</a>
