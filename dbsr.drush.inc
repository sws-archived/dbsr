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

