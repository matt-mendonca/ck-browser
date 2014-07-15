<?php
  /**
   * Callback function that builds the config form
   */
  function ck_browser_config_form($form, &$form_state) {
    $views = views_get_all_views();
    $browser_view_options = array();
    $browser_view_default = variable_get('ck_browser_browser_view');

    if(empty($view)) : 
      foreach ($views as $view_name => $view) :
        if(isset($view->in_code_only) && $view->in_code_only):
          continue;
        endif;

        foreach ($view->display as $view_type => $view_display) :
          if($view_type === 'default'):
            continue;
          endif;

          $option_value_array = array(
            'view_name' => $view_name,
            'view_type' => $view_type,
            'path' => "/{$view_display->display_options['path']}"
          );

          $option_value = json_encode($option_value_array);

          $option_text = "{$view->human_name} : {$view_display->display_title}";
          $browser_view_options[$option_value] = $option_text;
        endforeach;
      endforeach;
    else: 
      $browser_view_options[0] = "Please create a view.";
    endif;

    $styler_rules = variable_get('styler_rules');
    $styler_rules = json_decode($styler_rules);

    $styler_rules_options = array();
    $styler_rules_default = variable_get('ck_browser_styler_rule');
    
    if(count($styler_rules) > 0) :
      foreach ($styler_rules as $rule_id => $rule) :
        $styler_rules_options[$rule_id] = $rule->rule_name;
      endforeach;
    else: 
      $styler_rules_options[0] = "Please create a styler rule.";
    endif;

    $wysiwyg_button_label = variable_get('ck_browser_wysiwyg_button_label');

    $form = array(
      '#action' => '#', 

      'browser_view' => array( 
        '#type' => 'select',
        '#title' => t('Browser View'),
        '#description' => t('This is the view that will be used to populate the wysiwyg browser.'),
        '#options' => $browser_view_options,
        '#default_value' => $browser_view_default
      ),

      'styler_rule' => array( 
        '#type' => 'select',
        '#title' => t('Styler Rule'),
        '#description' => t('This is the Styler rule that will be applied to the browser view.'),
        '#options' => $styler_rules_options,
        '#default_value' => $styler_rules_default
      ),

      'wysiwyg_button_label' => array( 
        '#type' => 'textfield',
        '#title' => t('WYSIWYG Button Label'),
        '#description' => t('Enter the label you want to display for the button in the WYSIWYG.'),
        '#default_value' => $wysiwyg_button_label
      ),

      'submit' => array( 
        '#type' => 'submit',
        '#value' => t('Save'),
      )
    );
    
    return $form;
  }

  /**
   * Callback function that saves form data
   */
  function ck_browser_config_form_submit($form, &$form_state) {
    variable_set('ck_browser_browser_view', $form_state['values']['browser_view']);
    variable_set('ck_browser_styler_rule', $form_state['values']['styler_rule']);

    variable_set('ck_browser_wysiwyg_button_label', $form_state['values']['wysiwyg_button_label']);
    
    drupal_set_message(t('Your configuration has been saved.'));
  }
