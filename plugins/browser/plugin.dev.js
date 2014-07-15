;(function($) {
  // Expose some CK Editor stuff as a JS module (Revealing Module Pattern)
  // Potenial to extend / override behavior - still needs work
  window.CKBrowser = function() {
    var editorInstance = null,
        defaultInit = function (editor, plugin) {
          CKBrowser.editorInstance = editor;

          editor.addCommand('browserDialog', new CKEDITOR.dialogCommand('browserDialog'));

          editor.ui.addButton('CKBrowser', {
            label: Drupal.settings.CKBrowser.wysiwygButtonLabel || 'Browse',
            command: 'browserDialog',
            icon: plugin.path + 'add.png'
          });

          CKEDITOR.dialog.addIframe('browserDialog', 
            Drupal.settings.CKBrowser.wysiwygButtonLabel || 'Browse', 
            Drupal.settings.CKBrowser.browserView.path+"?"+Drupal.settings.CKBrowser.styler.parameterName+"="+Drupal.settings.CKBrowser.styler.parameterValue, 
            400, 
            400, 
            function() { 
              //console.log('content loaded');
              //$('.cke_dialog_ui_iframe').contents().find('body').addClass('ck-browser-view')
            },
            {
              onOk: function() {
                CKBrowser.defaultOnOk(editor, plugin);
              }
            }
          );
        },

        defaultOnOk = function (editor, plugin) {
          var link_text = null,
              active_link = null,
              selection = editor.getSelection(),
              link = editor.document.createElement('a'),
              frame = $('.cke_dialog_ui_iframe');
              
          active_link = frame.contents().find('a.selected').clone();
        
          link.setAttribute('href', active_link.attr('href'));
          link_text = selection.getSelectedText() || active_link.html();
          link.setHtml(link_text);

          editor.insertElement(link);
        };

    return {
      editorInstance: editorInstance,
      defaultInit: defaultInit,
      defaultOnOk: defaultOnOk
    };
  }();

  // CK plugin
    CKEDITOR.plugins.add('drupal_ck_browser', {
      init: function(editor, pluginPath) {
        CKBrowser.defaultInit(editor, this);
      }
    });
})(jQuery);