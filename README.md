# mods-via-twig
Drush script uses IMI Twig template to generate new MODS .xml files from .csv data.

> This project was created on `Marks-Mac-Mini` as `lando-d8` but has been successfully ported to `MA7053`, my _Grinnell College_ MacBook Air.  The new project name is `lando-mods-via-twig` and it can be found in _GitHub_ at [DigitalGrinnell/mods-via-twig](https:/github.com/DigitalGrinnell/mods-via-twig).

## The Original `lando-d8` Project

> The documentation that follows will talk about the creation of my original `lando-d8` project on `Marks-Mac-Mini`.

This project resides in `mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›` where I'm attempting to spin up a local _Drupal 8_ instance using _Lando_.  In this instance there is a set of files and directories at `~/GitHub/lando-d8/sites/default/files`, namely:

  - main.php - my primary PHP script for this work
  - mods-via-twig.md - this document
  - Digital-Grinnell-MODS-Master-Rev16beta.twig - an export of my latest _DG MASTER_ _Twig_ import template for _MODS_
  - test/ - a directory of miscellaneous files used for testing
  - social-justice/ - a directory containting files exported from _DG_'s "Social Justice" collection

With this configuration it should be possible to run the _main.php_ script using a command sequence like this:

  - `lando ssh` - opens a bash shell into the running PHP container
  - `cd sites/default/files` - change the working directory inside to the container
  - `php main.php` - launch the _main.php_ script inside the container


## My Original Drupal 7 Attempt

Everything you see above, and below, I first had working in _Drupal 7_, but D7 doesn't include native support for _Twig_, so it turned out to be a bit of a dead-end.  There's more to this document than you see now, but a big chunk of my D7 experience has been commented out.

<!--

```
╭─mark@Marks-Mac-Mini ~/GitHub/Generate-MODS-XML-from-CSV-via-Twig
╰─$ lando init \
  --source remote \
  --remote-url https://ftp.drupal.org/files/projects/drupal-7.69.tar.gz \
  --remote-options="--strip-components 1" \
  --recipe drupal7 \
  --webroot . \
  --name mods-via-twig
```

Your app has been initialized!

Go to the directory where your app was initialized and run lando start to get rolling.
Check the LOCATION printed below if you are unsure where to go.

Oh... and here are some vitals:

 NAME      mods-via-twig
 LOCATION  /Users/mark/GitHub/Generate-MODS-XML-from-CSV-via-Twig
 RECIPE    drupal7
 DOCS      https://docs.lando.dev/config/drupal7.html

```
╭─mark@Marks-Mac-Mini ~/GitHub/Generate-MODS-XML-from-CSV-via-Twig
╰─$ lando info
[ { service: 'appserver',
    urls:
     [ 'https://localhost:32794',
       'http://localhost:32795',
       'http://mods-via-twig.lndo.site/',
       'https://mods-via-twig.lndo.site/' ],
    type: 'php',
    via: 'apache',
    webroot: '.',
    config: { php: '/Users/mark/.lando/config/drupal7/php.ini' },
    version: '7.2',
    meUser: 'www-data',
    hostnames: [ 'appserver.modsviatwig.internal' ] },
  { service: 'database',
    urls: [],
    type: 'mysql',
    internal_connection: { host: 'database', port: '3306' },
    external_connection: { host: 'localhost', port: '32791' },
    creds: { database: 'drupal7', password: 'drupal7', user: 'drupal7' },
    config: { database: '/Users/mark/.lando/config/drupal7/mysql.cnf' },
    version: '5.7',
    meUser: 'www-data',
    hostnames: [ 'database.modsviatwig.internal' ] } ]
```

Copied `main.php` and `Digital-Grinnell-MODS-Master-Rev16beta.twig` to the `sites/defaults/files` directory.  Then do `lando ssh` to open a shell into the PHP container where we can do...

 ```
 www-data@11e5c9a97cd5:/app/sites/default/files$ clear; php main.php
 ```

 ...to run the script!

-->

# Restart with a Drupal 8 Target

Since _Drupal 7_ does not easily support the use of _TWIG_, I'm going to try this again but in a _Lando_ _Drupal 8_ client.

The following is based on [https://www.jeffgeerling.com/blog/2018/getting-started-lando-testing-fresh-drupal-8-umami-site](https://www.jeffgeerling.com/blog/2018/getting-started-lando-testing-fresh-drupal-8-umami-site)...

```
╭─mark@Marks-Mac-Mini ~/GitHub
╰─$ git clone --branch 8.6.x https://git.drupal.org/project/drupal.git lando-d8
Cloning into 'lando-d8'...
warning: redirecting to https://git.drupalcode.org/project/drupal.git/
remote: Enumerating objects: 3190, done.
remote: Counting objects: 100% (3190/3190), done.
remote: Compressing objects: 100% (1615/1615), done.
remote: Total 725431 (delta 1663), reused 2903 (delta 1472), pack-reused 722241
Receiving objects: 100% (725431/725431), 161.75 MiB | 15.37 MiB/s, done.
Resolving deltas: 100% (526786/526786), done.
Checking out files: 100% (13476/13476), done.
```

```
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x›
╰─$ lando init
? From where should we get your app's codebase? current working directory
? What recipe do you want to use? drupal8
? Where is your webroot relative to the init destination? .
? What do you want to call this app? mods-via-twig

   _  __                       _
  / |/ /__ _    __  _    _____( )_______
 /    / _ \ |/|/ / | |/|/ / -_)// __/ -_)
/_/|_/\___/__,__/  |__,__/\__/ /_/  \__/

  _________  ____  __ _______  _______  _      ______________ __  ___________  ______
 / ___/ __ \/ __ \/ //_/  _/ |/ / ___/ | | /| / /  _/_  __/ // / / __/  _/ _ \/ __/ /
/ /__/ /_/ / /_/ / ,< _/ //    / (_ /  | |/ |/ // /  / / / _  / / _/_/ // , _/ _//_/
\___/\____/\____/_/|_/___/_/|_/\___/   |__/|__/___/ /_/ /_//_/ /_/ /___/_/|_/___(_)

Your app has been initialized!

Go to the directory where your app was initialized and run lando start to get rolling.
Check the LOCATION printed below if you are unsure where to go.

Oh... and here are some vitals:

 NAME      mods-via-twig
 LOCATION  /Users/mark/GitHub/lando-d8
 RECIPE    drupal8
 DOCS      https://docs.lando.dev/config/drupal8.html

╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando start
Let's get this party started! Starting app mods-via-twig...
landoproxyhyperion5000gandalfedition_proxy_1 is up-to-date
Creating network "modsviatwig_default" with the default driver
Creating volume "modsviatwig_data_appserver" with default driver
Creating volume "modsviatwig_home_appserver" with default driver
Creating volume "modsviatwig_data_database" with default driver
Creating volume "modsviatwig_home_database" with default driver
Creating modsviatwig_appserver_1 ... done
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   619  100   619    0     0    147      0  0:00:04  0:00:04 --:--:--   147
100 4775k  100 4775k    0     0   384k      0  0:00:12  0:00:12 --:--:--  855k
 Drush Version   :  8.3.2

  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  811k  100  811k    0     0   261k      0  0:00:03  0:00:03 --:--:--  261k
Killing modsviatwig_appserver_1 ... done
Starting modsviatwig_appserver_1 ... done
Creating modsviatwig_database_1  ... done
Waiting until database service is ready...
Waiting until appserver service is ready...
Waiting until database service is ready...
Waiting until database service is ready...
Waiting until database service is ready...
Waiting until database service is ready...
Waiting until database service is ready...

   ___                      __        __        __     __        ______
  / _ )___  ___  __ _  ___ / /  ___ _/ /_____ _/ /__ _/ /_____ _/ / / /
 / _  / _ \/ _ \/  ' \(_-</ _ \/ _ `/  '_/ _ `/ / _ `/  '_/ _ `/_/_/_/
/____/\___/\___/_/_/_/___/_//_/\_,_/_/\_\\_,_/_/\_,_/_/\_\\_,_(_|_|_)


Your app has started up correctly.
Here are some vitals:

 NAME            mods-via-twig
 LOCATION        /Users/mark/GitHub/lando-d8
 SERVICES        appserver, database
 APPSERVER URLS  https://localhost:32808
                 http://localhost:32809
                 http://mods-via-twig.lndo.site/
                 https://mods-via-twig.lndo.site/

╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando composer install
...lots of output...

╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando info
[ { service: 'appserver',
    urls:
     [ 'https://localhost:32808',
       'http://localhost:32809',
       'http://mods-via-twig.lndo.site/',
       'https://mods-via-twig.lndo.site/' ],
    type: 'php',
    via: 'apache',
    webroot: '.',
    config: { php: '/Users/mark/.lando/config/drupal8/php.ini' },
    version: '7.2',
    meUser: 'www-data',
    hostnames: [ 'appserver.modsviatwig.internal' ] },
  { service: 'database',
    urls: [],
    type: 'mysql',
    internal_connection: { host: 'database', port: '3306' },
    external_connection: { host: 'localhost', port: '32807' },
    creds: { database: 'drupal8', password: 'drupal8', user: 'drupal8' },
    config: { database: '/Users/mark/.lando/config/drupal8/mysql.cnf' },
    version: '5.7',
    meUser: 'www-data',
    hostnames: [ 'database.modsviatwig.internal' ] } ]

```

Now, visiting [https://localhost:32808](https://localhost:32808) brings up the site for configuration.  When prompted there be sure to use the database "Advanced Options" and change the target from "localhost" to "database"!

I then set super-user creds to **admin** across the board.

## It Works!

Just confirming here that the aforementioned set of commands, which is reiterated below, does work...

  - `lando ssh` - opens a bash shell into the running PHP container
  - `cd sites/default/files` - change the working directory inside to the container
  - `php main.php` - launch the _main.php_ script inside the container

## Engaging Twig

So now, how do I programattically engage _Twig_?  Well, as luck would have it, [Jeff Geerling](https://www.jeffgeerling.com) asked and answered that same question some time ago.  His work can be found [here](https://www.jeffgeerling.com/blog/2019/rendering-twig-templates-programmatically-drupal-8). But simply following his lead with a script doesn't seem to work right-out-of-the-box because I'm getting errors like this:

```
www-data@6db17e5163ef:/app/sites/default/files$ php main.php
PHP Fatal error:  Uncaught Error: Class 'Drupal' not found in /app/sites/default/files/main.php:8
```

Since I am running _drush 8.x_ (my output from `lando drush --version` is  `Drush Version : 8.3.2`), I am going to try to follow the guidance provided [here](https://docs.drush.org/en/8.x/commands/) to create a new _drush_ command in my _Lando_-based instance of _Drupal 8_.

## Where To Put My Script?

This is where things currently stand...

```
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando drush status
 Drupal version                  :  8.6.19-dev
 Site URI                        :  http://default
 Database driver                 :  mysql
 Database hostname               :  database
 Database port                   :  3306
 Database username               :  drupal8
 Database name                   :  drupal8
 Database                        :  Connected
 Drupal bootstrap                :  Successful
 Drupal user                     :
 Default theme                   :  bartik
 Administration theme            :  seven
 PHP configuration               :
 PHP OS                          :  Linux
 Drush script                    :  /usr/local/bin/drush
 Drush version                   :  8.3.2
 Drush temp directory            :  /tmp
 Drush configuration             :
 Drush alias files               :
 Install profile                 :  standard
 Drupal root                     :  /app
 Drupal Settings File            :  sites/default/settings.php
 Site path                       :  sites/default
 File directory path             :  sites/default/files
 Temporary file directory path   :  /tmp
 Sync config path                :  sites/default/files/config_XGF3iTl5ukT-2H38IGr2FJvhbRslVnI8I-jN14TKmn5OucLACAs4YPLbljJMuZWZ4UDDPeu5TA/sync
```

So the [guidance](https://docs.drush.org/en/8.x/commands/) that I'm following says:

> Drush searches for commandfiles in the following locations:
>
>   - Folders listed in the 'include' option (see drush topic docs-configuration).
>   - The system-wide Drush commands folder, e.g. /usr/share/drush/commands
>   - The ".drush" folder in the user's HOME folder.
>   - /drush and /sites/all/drush in the current Drupal installation
>   - All enabled modules in the current Drupal installation

Unfortunately, none of these locations appear to be exposed in my host (workstation), and are only available from inside _Lando_'s PHP container, but it does appear that my host's `~/GitHub/lando-d8/sites` folder might be visible within the container.  So I'm going to try adding a path of `/all/drush` to that folder and see if the system will pick up the files that I park there.

```
cd ~/GitHub/lando-d8/sites
mkdir -p all/drush
```

Next, I retrieved a copy of [sandwich.drush.inc](https://raw.githubusercontent.com/drush-ops/drush/8.x/examples/sandwich.drush.inc) to use as an example, and I parked it on my host at `~/GitHub/lando-d8/sites/all/drush/sanwich.drush.inc`.  I followed that with:

```
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando drush mmas
The drush command 'mmas' could not be found.  Run `drush cache-clear drush` to clear the commandfile cache if you have installed new extensions.                           [error]
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando drush cc drush
'drush' cache was cleared.                                   [success]
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8 ‹8.6.x*›
╰─$ lando drush mmas
What? Make your own sandwich.                                [error]
```

In spite of the `[error]` return, the command clearly works!

## Making My "Sandwich"

So, the next logical step is to replace the "logic" of _make-me-a-sandwich_, with something more useful, namely _mods-via-twig_.  And the "sandwich" is ready with more details to follow...

# lando-mods-via-twig on MA7053

As mentioned at the top of this post, this project and the `drush mods-via-twig` command that it creates has been moved to MacBook Air `MA7053` where it resides at `/Users/markmcfate/GitHub/lando-mods-via-twig`.  The control copy can also be found in [DigitalGrinnell/mods-via-twig](https:/github.com/DigitalGrinnell/mods-via-twig) where this `README.md` file can also be found.

## Launching the _Lando_ Environment

This project uses [Lando](https://lando.dev) to spin up a pristine, local _Drupal 8_ instance to work in.  You can start, stop, and otherwise manage the project using `lando` commands issued from `markmcfate@ma7053 ~/GitHub/lando-mods-via-twig` like so: 

  - `lando info` - Prints the status of this `Lando` project. A sample of the command and its output are posted below.
  - `lando start` - Launch the project.  This is necessary before running the script itself.
  - `lando stop` - Stop the project.
  - `lando drush mvt social-justice` - Run the script to process to process the `mods.csv` file for a specified collection. Details can be found in the next section below.
  
```bash
╭─markmcfate@ma7053 ~/GitHub/lando-mods-via-twig ‹ruby-2.3.0› ‹master*›
╰─$ lando info
[ { service: 'appserver',
    urls: [ 'http:/mods-via-twig.lndo.site:8000/', 'https:/mods-via-twig.lndo.site/' ],
    type: 'php',
    healthy: true,
    via: 'apache',
    webroot: '.',
    config: { php: '/Users/markmcfate/.lando/config/drupal8/php.ini' },
    version: '7.2',
    meUser: 'www-data',
    hostnames: [ 'appserver.modsviatwig.internal' ] },
  { service: 'database',
    urls: [],
    type: 'mysql',
    healthy: true,
    internal_connection: { host: 'database', port: '3306' },
    external_connection: { host: '127.0.0.1', port: true },
    healthcheck: 'bash -c "[ -f /bitnami/mysql/.mysql_initialized ]"',
    creds: { database: 'drupal8', password: 'drupal8', user: 'drupal8' },
    config: { database: '/Users/markmcfate/.lando/config/drupal8/mysql.cnf' },
    version: '5.7',
    meUser: 'www-data',
    hostnames: [ 'database.modsviatwig.internal' ] } ]
 ```   

## The `lando drush mvt` Command

The `mvt`, or `mods-via-twig` command, is used to generate individual `<PID>_MODS.xml` files in a specified collection's `~/GitHub/lando-mods-via-twig/sites/default/files/collections/` directory.  The command expects to find a single `mods.csv` file in the specified collection directory, and it will create one `<PID>_MODS.xml` file for each object listed in that `mods.csv` file.  `<PID>` in the filename will match the `PID` column entry from the `mods.csv` but with the colon (:) seperator replaced by an underscore (_).  For example, the command `lando drush mvt social-justice` will process `~/GitHub/lando-mods-via-twig/sites/default/files/collections/social-justice/mods.csv` and generate corresponding `grinnell_<PID>_MODS.xml` files in the `~/GitHub/lando-mods-via-twig/sites/default/files/collections/social-justice/` directory.  

