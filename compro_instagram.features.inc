<?php
/**
 * @file
 * compro_instagram.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function compro_instagram_eck_bundle_info() {
  $items = array(
    'social_instagram' => array(
      'machine_name' => 'social_instagram',
      'entity_type' => 'social',
      'name' => 'instagram',
      'label' => 'Instagram',
      'config' => array(),
    ),
  );
  return $items;
}
