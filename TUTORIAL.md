# Tutorial

This will be an in depth tutorial on the structure of *CHL web applications*, and a walk through on how to get started and how to use the *CHL API* properly. The tutorial is divided into various sections, which you can have a look on here: [contents](#contents). The first section is a quick introduction to let you know what *CHL* is all about and what it can do for you. The next section will go through the whole structure of *CHL*, teaching you how to cooperate different types of files to end up with a good working and good structured *CHL web application*. We will then dwell deeper and deeper into the *CHL API* for your pleasure.

Before you start reading this tutorial, make sure you have CHL installed and that everything is properly set up. [Setting up CHL](https://github.com/it4e/CHL/blob/master/SETUP.md).

## <a name="contents">Contents</a>

> #### [Introduction](#intro)
  - [What is CHL?](#whatischl)
  - [What can CHL do?](#whatcanchldo)
  - [How does CHL work?](#howdoeschlwork)

## <a name="intro">Introduction</a>

### <a name="whatischl">What is CHL?</a>

*CHL*, short for *C Hypertext Library*, is a library written in C to be used to write web applications. If you have ever used a language designed for creating server-side webscripts, PHP or ASP for instance, you will feel quite familiar with *CHL*, since CHL is used for the exact same purpose. The only difference, however, is that *CHL* provides you with the ability to write those Web applications in pure C, instead of having to learn a new language. Many people, including myself, also finds great joy in writing code in C, so why not do it for developing Web applications as well?

### <a name="whatcanchldo">What can CHL do?</a>

Just like any other programming language designed for developing web applications, *CHL (although a library)* provides you with the same features. *CHL* enables you to easily parse and fetch *HTTP data*, such as *POST and GET*. CHL gives you all the functionality you need to *create your own headers*, including a dedicated API for creating and deleting *cookies*. *CHL* also comes shipped with a very special, *handcrafted parser and interpreter* to give you the ability to *execute CHL functions* within HTML files, using a very straight-forward syntax. These are only a small number of things that CHL can do for you.

As *CHL is open-source*, people are able to contribute with their own APIs, plugins and code which means that *CHL* is constantly upgraded and provided with new features. Do you have an idea for a new CHL function and want to contribute? See (added later).

### <a name="howdoeschlwork">How does CHL work?</a>

Web applications written in C must somehow be executed by the Web server, since C is a compiled langauge. To make this possible CHL is based on CGI (Common Gateway Interface), which in short means that the server executes your program and passes it data through environment variables. CHL does all the parsing and handling of CGI in the background, and provides you with some easy to use functions instead. 

Curious huh? Feel free to take a look through the [source code](https://github.com/it4e/CHL/tree/master/core), or maybe even [contribute]() yourself? *(although I strongly recommend you read this tutorial first).*

