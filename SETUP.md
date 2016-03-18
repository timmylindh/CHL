# Setup

This is a detailed post on how to install and configure CHL on your system. As of now *CHL* is only officially available on Linux, but I am planning to port it to other operating systems as well if the interest is big enough. Otherwise you could of course make a port of it yourself.

## Contents
> #### [Linux](#linux)
  - [Apache2](#apache2)
      - [Enable CGI](#apacheenablecgi)
      - [Download Files](#apachedownload)
        - [Git](#apachedownloadgit)
        - [Manually](#apachemandownload)
      - [Installation](#apacheinstall)
      - [Configuration](#apacheconfig)
        - [Enable index.chl](#apacheenableindex)
  
## <a name="linux">Linux</a>

This is for those of you who use a distribution of Linux, whether Ubuntu, Debian or Fedora, this will work for all Linux distributions. A little knowledge of how to use the Terminal and how to navigate the filesystem might be a good thing to have in your bagage, although not required to follow this guide.

## Apache2

### <a name="apacheenablecgi">1. Enable CGI</a>

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

### <a name="apachedownload">2. Download Files</a>

#### <a name="apachedownloadgit">Using Git</a>

This how you download a copy of CHL using Git and a terminal. If you prefer to do it manually, see [manual download](#apachemandownload)

Clone CHL: https://github.com/it4e/CHL

```bash
git clone https://github.com/it4e/CHL
```

This will create a folder named *'CHL'*, in your current working directory

#### <a name="apachemandownload">Manual Download</a>

You can download CHL as a zip file manually, using the link https://github.com/it4e/CHL/archive/master.zip.
Unzip it and you are good to go.

### <a name="apacheinstall">3. Installation</a>

Once you have [downloaded](#apachedownload) the CHL source files you are ready to install CHL.
Go ahead and change to the CHL directory containing all of the source files you just downloaded using a Terminal.

```bash
cd CHL
```

Issue the following command to finish the installation process. (Make sure to run as root)

```bash
sudo make install
```

This will compile all the files inside *'core/*'* to their corresponding object files. The object files will then be smashed into a statically linked library (*'libchl.a'*), which is then copied into '*/usr/lib/chl/.*'. The standard CHL header *'chl.h'* is also moved, to '*/usr/include/chl/.*'

### <a name="apacheconfig">(4.) Configuartion</a>

#### <a name="apacheenableindex">Enable *index.chl* as default index page</a>

Open file '*/etc/apache2/sites-available/000-default.conf*', alt. '*/etc/apache2/sites-available/default*' for editing.

```bash
vim /etc/apache2/sites-available/000-default.conf
```

Change the *DirectoryIndex* of *\<VirtualHost \*:80\>* to include *'index.chl'*

```bash
<virtualhost *:80>

  ServerName  domain.com
  ServerAlias www.domain.com

  # Index file and Document Root (where the public files are located)
  DirectoryIndex home.html index.html index.chl
  DocumentRoot /var/www

</virtualhost>
```

Restart Apache2 to enable changes
```bash
service apache2 restart
```

Now that you have successfully installed CHL on your system, learn how to use CHL here: (link soon)
