<?php

/**
 * @file
 * Example drush command.
 *
 * To run this *fun* command, execute `sudo drush --include=./examples mvt`
 * from within your drush directory.
 *
 * See `drush topic docs-commands` for more information about command authoring.
 *
 * You can copy this file to any of the following
 *   1. A .drush folder in your HOME folder.
 *   2. Anywhere in a folder tree below an active module on your site.
 *   3. /usr/share/drush/commands (configurable)
 *   4. In an arbitrary folder specified with the --include option.
 *   5. Drupal's /drush or /sites/all/drush folders, or in the /drush
 *        folder in the directory above the Drupal root.
 */

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 */
function modsviatwig_drush_command() {
  $items = array();

  // The 'mods-via-twig' command.
  $items['mods-via-twig'] = array(
    'description' => "Generate MODS .xml files from a collection's MASTER .csv file.",
    'arguments' => array(
      'collection' => 'The name of the collection to be processed.  Defaults to "social-justice".',
    ),
    'aliases' => array('mvt'),
    // No bootstrap at all?
    'bootstrap' => 'DRUSH_BOOTSTRAP_FULL',
  );

  return $items;
}

/**
 * Implements drush_hook_COMMAND_validate().
 *
 * The validate command should exit with
 * `return drush_set_error(...)` to stop execution of
 * the command.  In practice, calling drush_set_error
 * OR returning FALSE is sufficient.  See drush.api.php
 * for more details.
 */
function drush_modsviatwig_mods_via_twig_validate() { return TRUE; }

/**
 * Implements drush_hook_COMMAND().
 *
 * The command callback is where the action takes place.
 *
 * The function name should be same as command name but with dashes turned to
 * underscores and 'drush_commandfile_' prepended, where 'commandfile' is
 * taken from the file 'commandfile.drush.inc', which in this case is
 * 'modsviatwig'. Note also that a simplification step is also done in instances
 * where the commandfile name is the same as the beginning of the command name,
 * "drush_example_example_foo" is simplified to just "drush_example_foo".
 * To also implement a hook that is called before your command, implement
 * "drush_hook_pre_example_foo".  For a list of all available hooks for a
 * given command, run drush in --debug mode.
 *
 * If for some reason you do not want your hook function to be named
 * after your command, you may define a 'callback' item in your command
 * object that specifies the exact name of the function that should be
 * called.
 *
 * In this function, all of Drupal's API is (usually) available, including
 * any functions you have added in your own modules/themes.
 *
 * @see drush_invoke()
 * @see drush.api.php
 */
function drush_modsviatwig_mods_via_twig($target_collection = 'social-justice') {

  define('SEPERATOR', ",");
  define('TWIG', './sites/default/files/collections/Digital-Grinnell-MODS-Master-Rev17.twig');
  define('COLLECTIONS_PATH', './sites/default/files/collections/');
  define('STORAGE_PATH', '//STORAGE/LIBRARY/ALLSTAFF/DG-Metadata-Review-2020-r1');

  echo "\n\n\nWelcome to drush mods-via-twig!\n";

  // Twig handling is based on https://stackoverflow.com/questions/24888372/drupal-8-render-twig-from-string-with-twig-functions

  // read the Twig template into a string and remove all "data." variable prefixes
  // from the raw Twig template string
  $TwigString = file_get_contents(TWIG);
  if (!$TwigString) {
    return drush_set_error('Failed to Read TWIG', dt("The specified Twig template, ".TWIG." could not be read."));
  }

  // create a new Twig environment
  $Twig = new \Twig_Environment(new \Twig_Loader_String());
  $Twig->setLoader(new \Twig_Loader_String());
  // $Twig->addExtension(new Jasny\Twig\PcreExtension());  // lifted from IMI utilities.inc

  // check the COLLECTIONS_PATH, it is a directory?
  if (!is_dir(COLLECTIONS_PATH)) {
    return drush_set_error('Invalid COLLECTIONS_PATH', dt("The specified collections path, ".COLLECTIONS_PATH.", is not a valid directory."));
  }

  // loop through all the directories in COLLECTIONS_PATH
  $paths = scandir(COLLECTIONS_PATH);   // echo "$paths: ", print_r($paths, TRUE);

  foreach ($paths as $collection) {    // drush_print("Now processing $collection.");
    if ($collection == $target_collection && $collection != '.' && $collection != '..' && is_dir(COLLECTIONS_PATH."/".$collection)) {
      drush_print("Now processing the collection in: $collection.");
      // look for one, and only one *.csv file inside
      $files = glob(COLLECTIONS_PATH."/$collection/*.csv");
      $count = count($files);
      if ($count != 1) {
        return drush_set_error('Bad CSV count', dt("The $collection directory contains $count .csv files."));
      }

      // process the one and only .csv file in $collection
      // read the .csv exploded into an array of $lines
      $lines = explode("\n", file_get_contents($files[0]));  // echo "$lines: ", print_r($lines, TRUE);

      // break out the $headers, assuming a \t (tab) seperator, into an array, and create an empty $data array
      $headers = str_getcsv(array_shift( $lines ), SEPERATOR);  // echo "headers: \n", print_r($headers, TRUE), "\n\n";
      $data = array();

      // loop on the .csv line-by-line, one object at a time
      foreach ($lines as $line) {
        if (strlen($line) > 0) {    // skip any blank rows in the .csv
          $row = array();
          foreach (str_getcsv($line, SEPERATOR) as $key => $field )
            // echo "key => field: " . print_r($key, TRUE) . " => " . print_r($field, TRUE) . "\n";
            $row[ strtolower($headers[ $key ]) ] = trim($field);    // make sure we convert headers (keys) to lowercase!
          $data = array_filter( $row );  // echo "data: \n", print_r($data, TRUE), "\n";

          $pid = $data['pid'];    // fetch the PID

          if (!isset($data['import_source'])) {
            $data['import_source'] = STORAGE_PATH . "/$collection/mods.csv";  // push the .csv path into dg_importSource if that field is empty
          }

          $xml_path = COLLECTIONS_PATH . "/$collection/$xml" . str_replace(":", "_", $pid) . "_MODS.xml";
          $imi_like_data['data'] = $data;
          $rendered = $Twig->render($TwigString, $imi_like_data);    // echo "rendered: \n".$rendered."\n\n";

          // pretty-print the $rendered xml to a pid-named file in the $collection directory
          $dom = new DOMDocument('1.0','UTF-8');
          $dom->formatOutput = true;
          $dom->preserveWhiteSpace = false;
          $dom->loadXML($rendered);
          $dom->save($xml_path) or die('XML Create Error');
        }
      }    // end: foreach($lines as $line)...
    }    // end: if (is_dir($collection)...
  }    // end: foreach (scandir(COLLECTIONS_PATH)...

  echo "\n\ndrush mods-via-twig is finished!\n\n";

}
