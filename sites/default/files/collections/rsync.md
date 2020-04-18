# rsync - Fetch All mods.csv

With the Grinnell College _//STORAGE_ server mounted to iMac _MA8660_ you can run the following `rsync` command to fetch all of the latest _mods.csv_ files and directories after they have been created using the `Map-MODS-to-MASTER` Python 3 script on _MA8660_...

```
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8/sites/default/files/collections ‹8.6.x*›
╰─$ rsync -aruvi --exclude '*.xml' --exclude '*.log' --exclude '*.remainder' --progress markmcfate@132.161.216.145:/Volumes/LIBRARY/ALLSTAFF/DG-Metadata-Review-2020-r1/. ~/GitHub/lando-d8/sites/default/files/collections/.
```

The command alone is:

```
rsync -aruvi --exclude '*.xml' --exclude '*.log' --exclude '*.remainder' --progress markmcfate@132.161.216.145:/Volumes/LIBRARY/ALLSTAFF/DG-Metadata-Review-2020-r1/. ~/GitHub/lando-d8/sites/default/files/collections/.
```

# rsync - Pushing New .xml Files Back for Update

Once a new set of .xml files has been generated, they need to be copied to node _DGDocker1_ so they can be imported into the _Digital Grinnell_ repository. Specifically, they should be copied to a collection-named directory at _dgdocker1.grinnell.edu:/opt/ISLE/persistent/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/_.  The _social-justice_ collection, for example, would occupy _dgdocker1.grinnell.edu:/opt/ISLE/persistent/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/social-justice_.

An example for the _social-justice_ collection is shown here:

```
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8/sites/default/files/collections ‹8.6.x*›
╰─$ collection=social-justice
╭─mark@Marks-Mac-Mini ~/GitHub/lando-d8/sites/default/files/collections ‹8.6.x*›
╰─$ rsync -aruvi --progress ~/GitHub/lando-d8/sites/default/files/collections/${collection}/. islandora@dgdocker1.grinnell.edu:/opt/ISLE/persistent/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/${collection}/.
```

You must define the _collection_ variable before running the _rsync_ command and both commands are:

```
collection=
rsync -aruvi --progress ~/GitHub/lando-d8/sites/default/files/collections/${collection}/. islandora@dgdocker1.grinnell.edu:/opt/ISLE/persistent/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/${collection}/.
```

# Importing the New .xml Using Drush

The whole point of this entire process is to get us back to this point with a set of reviewed and modified _.xml_ files that can be successfully passed to the _drush islandora_datastream_replace_ command.  The documentation for that command is presented below.

```
root@122092fe8182:/var/www/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/social-justice# drush islandora_datastream_replace --help
Replaces a datastream in all objects given a file list in a directory.

Examples:
 drush -u 1 islandora_datastream_replace  Replacing MODS datastream in object.
 --source=/tmp --dsid=MODS
 --namespace=test2

Options:
 --dsid                                    The datastream id of the datastream. Required.
 --namespace                               The namespace of the pids. Required.
 --source                                  The directory to get the datastreams and pid# from. Required.

Aliases: idre
```

It's worth noting that this command looks for any files named _*MODS*_ in whatever *ABSOLUTE* directory is named with the _--source_ parameter.  The command shown below was executed inside the _Apache_ container, _isle-apache-dg_, on node _DGDocker1_, in order to process _Digital Grinnell_'s _social-justice_ collection.

```
root@122092fe8182:/var/www/html/sites/default# drush -u 1 islandora_datastream_replace --source=/var/www/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/social-justice --dsid=MODS --namespace=grinnell
```

The same command could have been executed directly from node _DGDocker1_ like so:

```
docker exec isle-apache-dg drush -u 1 -w /var/www/html/sites/default islandora_datastream_replace --source=/var/www/html/sites/default/files/DG-Metadata-Review-2020-r1/Ready-to-Process/social-justice --dsid=MODS --namespace=grinnell
```
