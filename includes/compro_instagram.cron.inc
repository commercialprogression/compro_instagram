<?php

/**
 * @file
 * Cron function for the Instagram feature.
 */

/**
 * Retrieves Instagram posts.
 *
 * @param array $settings
 *  Settings for the feature.
 */
function compro_instagram_retrieve_posts($settings) {
  // Ensure instagram retrieve is enabled.
  if (isset($settings['enable']) && $settings['enable']) {
    // Build request.
    $access_token = $settings['access_token'];
    $count = $settings['count'];
    $endpoint = $settings['endpoint'];

    $data = array(
      'access_token' => $access_token,
      'count' => $count,
    );

    $url = url($endpoint, array('query' => $data));

    // Make request.
    $request = drupal_http_request($url);

    // Parse request.
    if ($request->code == 200) {
      $result = drupal_json_decode($request->data);

      // Create instagram entities.
      compro_instagram_create_entities($result);
    }
  }
}

/**
 * Creates instagram entities.
 *
 * @param object $result
 *  Parsed JSON from Instagram GET request.
 */
function compro_instagram_create_entities($result) {
  // Create an entity for each result.
  foreach ($result['data'] as $post) {
    // Check to see if post already exists.
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'social')
      ->entityCondition('bundle', 'instagram')
      ->fieldCondition('field_instagram_id', 'value', $post->id, '=');

    $result = $query->execute();

    // Create entity if this is a new post.
    if (!isset($result['social'])) {
      // Set up entity.
      $entity_type = 'social';
      $entity = entity_create($entity_type, array('type' => 'instagram'));
      $wrapper = entity_metadata_wrapper($entity_type, $entity);

      // Grab image.
      $image_url = $post['images']['standard_resolution']['url'];
      $image = system_retrieve_file($image_url, 'public://', TRUE, FILE_EXISTS_REPLACE);

      // Grab user image.
      $user_image_url = $post['caption']['from']['profile_picture'];
      $user_image = system_retrieve_file($user_image_url, 'public://', TRUE, FILE_EXISTS_REPLACE);

      // Fields.
      $wrapper->field_instagram_image->file->set($image);
      $wrapper->field_instagram_user_photo->file->set($user_image);
      $wrapper->field_instagram_user->set($post['caption']['from']['username']);
      $wrapper->field_instagram_caption->set($post['caption']['text']);
      $wrapper->field_instagram_id->set($post['id']);
      $wrapper->field_instagram_link->set($post['link']);

      // Save the entity.
      $wrapper->save();
    }
  }
}