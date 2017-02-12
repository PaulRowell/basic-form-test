<?php

/**
 * @file.
 *
 * Custom page for product search form and results.
 */

/**
 * Implements hook_form().
 *
 * @param $form
 * @param $form_state
 * @return array
 */
function product_search_form($form, &$form_state) {
  $form = array();

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
    '#ajax' => array(
        'callback' => 'product_search_form_submit',
        'wrapper' => 'product-search-results',
        'method' => 'replace',
    ),
  );

  $form['#suffix'] = '<div id="product-search-results"></div>';

  return $form;
}

/**
 * Implements hook_submit().
 *
 * @param $form
 * @param $form_state
 */
function product_search_form_submit($form, &$form_state) {

     // Send request for results.
    $uri = 'https://atd.atdtravel.com/api/products';
    $search_term = $data['title'];

    $url = $uri . '?' . 'title=' . filter_xss($form_state['values']['title']);

    // Place curl here for simplicity, improve by making it a seperate request
    // via a router call allowing greater flexibility.
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_USERPWD, "dev-interview:asdf1234");
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-type: application/json'));
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

    $response = curl_exec($ch);

    // decode the json.
    $data = json_decode($response);

    // Check for error messages.
    // @TODO, any other type of response we could expect?
    if (isset($data->err_desc)) {
      $error = $data->err_desc;
       return '<div id="product-search-results"><p>' . $error . '</p></div>';
    }
    else {
      // We have data back.
      return _atd_test_search_page_format_results($data->data);


      // Create array of results to print out.
      foreach ($data->data as $d) {
        $results['results'][] = array(
          'img' => isset($d->img_sml) ? $d->img_sml : NULL,
          'title' => $d->title,
          'dest' => $d->dest,
          );
       }

    }

}


/**
 * Helper function to format the results from atd api.
 */
function _atd_test_search_page_format_results($results) {

  $return = '<div id="product-search-results"><table><th>Image</th><th>Title</th><th>Destination</th>';

  foreach ($results as $result) {
    $return .= '<tr>';
    $return .= '<td><img src="' . $result->img_sml . '" title="' . $result->title .' " /></td>';
    $return .= '<td>' . $result->title . '</td>';
    $return .= '<td>' . $result->dest . '</td>';
    $return .= '</tr>';
  }

  $return .= '</table></div>';

  return $return;

}
