# CHL
C Hypertext Library - A library for writing web applications in C

```c
#include <chl/chl.h>

int main() {
 chl_set_default_headers();
 chl_print_headers();
 
 printf("Hello world");
 
 return 0;
}
```
 (*Simple Hello World in CHL*)

[See examples](https://github.com/it4e/CHL/wiki/Examples)<br />
[Tutorial](https://github.com/it4e/CHL/wiki/Tutorial), 
[Setup](https://github.com/it4e/CHL/wiki/Setup), 
[API](https://github.com/it4e/CHL/wiki), 
[Contribute](https://github.com/it4e/CHL/wiki/Contribute)<br />
[FastCGI](https://github.com/it4e/CHL/wiki/FastCGI)

## What is CHL?

CHL, short for *C Hypertext Library*, is a library used to write web applications of all sorts in the C programming language. CHL provides you with a lot of useful features:

> 
  - *FastCGI implementation*
  - *MySQL library*
  - *Parsing and fetching HTTP data, such as POST and GET.*
  - *Creating and deleting HTTP headers.*
  - *A dedicated API for creating and deleting cookies.*
  - *The ability to execute CHL functions within HTML files*

and a lot more...

## Why CHL?

What makes CHL uniqe is the support for executing functions inside HTML files, much like PHP using the *<?php ?>* syntax, though *CHL* uses the *<{ }>* syntax.

> Example

```html
<body>
 <{ import("header.vw"); }>
</body>
```

## How does it work?

Web applications written in C must somehow be executed by the Web server since C is a compiled language. To make this possible CHL is based on CGI (Common Gateway Interface), which in short means that the server executes your program and passes it data through environment variables. CHL does all the parsing and handling of CGI in the background, and provides you with some easy to use functions instead. CHL also provides an interface for FastCGI.

## API

The *Application Programming Interface* is written with *Github Wikis*: [API](https://github.com/it4e/CHL/wiki).

## Setup

For a proper guide on how to install and configure CHL on your system, read the following document: https://github.com/it4e/CHL/wiki/Setup.

As of now, CHL is only officially available on Linux, but I am planning to port it to other operating systems as well if the interest is big enough. Otherwise you could of course make a port of it yourself, see [contribute](https://github.com/it4e/CHL/wiki/Contribute).

## Tutorial

To read an in depth tutorial on the structure of *CHL web applications*, and a walk through on how to get started and how to use the *CHL API* properly see https://github.com/it4e/CHL/wiki/Tutorial.

The tutorial is divided into various sections. The first section is a quick introduction to let you know what *CHL* is all about and what it can do for you. We will then dig deeper and deeper into the CHL API.

Before you start reading this tutorial, make sure you have CHL installed and that everything is properly set up. [Setting up CHL](https://github.com/it4e/CHL/wiki/Setup).


## <a name="contribute">Contribute</a>

There are several ways you can contribute to CHL. Take a look at the [*issues page*](https://github.com/it4e/CHL/issues) for an overview of what you can contribute to. If you have any ideas of your own for new features to implement, feel free to contribute with a pull request.

For a detailed guide on contribution to CHL, see [contribute](https://github.com/it4e/CHL/wiki/Contribute).

## <a name="examples">Examples</a>

See [examples](https://github.com/it4e/CHL/wiki/Examples), for a page with detailed examples of CHL in use.
