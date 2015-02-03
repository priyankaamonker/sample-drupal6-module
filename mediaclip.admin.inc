<?php
// $Id: mediaclip, v 6.x-8.1-dev 07/05/2013

/**
* Mediaclip Module Data
* @return array An array of form data.
*/
function mediaclip_message() {
    $page_content = '';
    $page_content .= drupal_get_form('mediaclip_message_form');
    return $page_content;
}

/**
* The callback function (form constructor) that creates the HTML form for mediaclip_message_form().
* @return form an array of form data.
*/
function mediaclip_message_form() {
	global $base_url;
	$mc_wsdl              = variable_get('mc_wsdl', '');
	$mc_organizationName  = variable_get('mc_organizationName', '');	
	$mc_organizationCode  = variable_get('mc_organizationCode', '');	

	$form['mc_wsdl'] = array(
	'#type' => 'textfield',
	'#title' => t('Service WSDL Path'),
    '#description' => t('This is the path where the web service WSDL is defined.'),
	'#default_value' => $mc_wsdl ? $mc_wsdl : '',
	'#required' => TRUE,
	);

	$form['mc_organizationName'] = array(
	'#type' => 'textfield',
	'#title' => t('Organization Name'),
	'#description' => t('The Username/Organization Name we have registered with.'),
	'#default_value' => $mc_organizationName ? $mc_organizationName : '',
	'#required' => TRUE,	
	);

	$form['mc_organizationCode'] = array(
	'#type' => 'textfield',
	'#title' => t('Organization Code'),
    '#description' => t('The Password/Organization Code we have registered with.'),
	'#default_value' => $mc_organizationCode ? $mc_organizationCode : '',
	'#required' => TRUE,
	);
	
	//Submit button:
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
   
    return $form;
}

function mediaclip_message_form_validate($form, &$form_state) {
    $has_errors = FALSE;

    //Form requires rebuilding form so codes and expiration blocks will display correctly
	if ($has_errors) {
		$form_state["rebuild"] = TRUE;
	}
}

/**
* Form submission for user data.
* @param form an array that contains user data
* @param form_state an array that contains user data
*/
function mediaclip_message_form_submit($form, &$form_state) {
	//delete previous entries
	variable_del('mc_wsdl');
	variable_del('mc_organizationName');	
	variable_del('mc_organizationCode');	

	//set new entries
	variable_set('mc_wsdl', $form_state['values']['mc_wsdl']);
	variable_set('mc_organizationName', $form_state['values']['mc_organizationName']);
	variable_set('mc_organizationCode', $form_state['values']['mc_organizationCode']);

    $msg = 'Updated Mediaclip settings';
    watchdog('mediaclip', $msg, '', WATCHDOG_INFO);
    drupal_set_message(t('Updated Mediaclip Settings'));
   
    $form_state['redirect'] = 'admin/settings/mediaclip';
}