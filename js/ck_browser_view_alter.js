;(function($) {
  Drupal.behaviors.ckBrowserViewAlter = {
    attach: function (context, settings) {
      $('body').once(function() {
        $(this).addClass('ck-browser-view');
      });

      $('.view-content a').click(function(e) {
        $('a.selected').removeClass('selected');
        $(this).addClass('selected'); 

        return false;
      });
    }
  }
})(jQuery);