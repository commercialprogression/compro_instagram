<?php

/**
 * @file
 * Setting form for Instagram feature.
 */

/**
 * Form callback for Instagram feature.
 */
function compro_instragram_settings($form, &$form_state) {
  // Grab any existing values.
  $settings = variable_get('compro_instagram');

  $form['#tree'] = TRUE;

  $form['compro_instagram']['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#default_value' => isset($settings['enable']) ? $settings['enable'] : '',
  );

  $form['compro_instagram']['endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Endpoint'),
    '#default_value' => isset($settings['endpoint']) ? $settings['endpoint'] : 'https://api.instagram.com/v1/users/self/media/recent/',
  );

  $form['compro_instagram']['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of posts retrieve'),
    '#description' => t('Posts will be retrieved on cron run.'),
    '#size' => 2,
    '#default_value' => isset($settings['count']) ? $settings['count'] : '3',
    '#required' => TRUE,
  );

  $form['compro_instagram']['access_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Access token'),
    '#default_value' => isset($settings['access_token']) ? $settings['access_token'] : '',
    '#required' => TRUE,
  );

  return system_settings_form($form);
}