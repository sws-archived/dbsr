<?php

/**
 * @file
 * Drush plugin for global search and replace
 */


/**
 * Implementation of hook_drush_command().
 */
function dbsr_drush_command() {
  $items = array();
  
  // the "Database search and replace" command
  $items['database-search-replace'] = array(
    'description' => 'Performs a global search and replace on the Drupal database',
    'arguments' => array(
      'searchstring' => 'The string you would like to search for',
      'replacestring' => 'The replacement string',
    ),
    'options' => array(
      'dry-run' => 'Do a dry run. Do not replace.',
      'skip-backup' => 'Be dangerous. Do not back up the database.',
      'tables' => 'Limit search to specific table(s).',
    ),
    'examples' => array(
      'drush dbsr foo bar' => 'Replace every occurrence of "foo" with "bar" in the database',
    ),
    'aliases' => array('dbsr'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );
  return $items;
}

/**
 * Drush command callback.
 */
function drush_dbsr_database_search_replace($searchstring, $replacestring) {
  //--tables option is not set by default
  $has_table_option = FALSE;
  //if the user passes the --tables option
  if ($tables = drush_get_option('tables')) {
    //$tables is a numerically-keyed array of the list sent by the user
    $tables = explode(',', $tables);
    //and our option is true
    $has_table_option = TRUE;
  }
  else {
    //$tables is an numerically-keyed array of table names
    $schema = drupal_get_schema(NULL, TRUE);
    foreach ($schema as $key => $value) {
      $tables[] = $key;
    }
  }
  //prep for the confirmation step
  if ($has_table_option) {
    $selected_tables = 'in the following tables: ' . implode(',', $tables);
  }
  else {
    $selected_tables = 'throughout the entire database';
  }
  if (!drush_confirm(dt('You are going to search for "!searchstring" and replace it with "!replacestring" !selectedtables. Are you sure you want to do this?', array("!searchstring" => $searchstring, "!replacestring" => $replacestring, "!selectedtables" => $selected_tables)))) {
    return drush_user_abort();
  }
  drush_print("Search string is \"" . $searchstring . "\"");
  drush_print("Replacement string is \"" . $replacestring . "\"");
  // load a table (for each table) :
  foreach ($tables as $key => $table) {
    //get the table schema
    $schema = drupal_get_schema($table);
    // find primary keys, if it/they exist(s)
    drush_print_r($schema['primary key']);
    //TODO:
    //if (isset($schema['primary key'])) // not sure if we need to check this, or best way
    // load first row (for each row) :
      // for each column:
        // if primary key && value changes, make a note of it
        // run recursive serialization function - recursive_unserialize_replace() from searchreplacedb2.php
  }
}
