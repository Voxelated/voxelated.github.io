$(document).ready(function(){
  $('.button-collapse').sideNav();
  $('.scrollspy').scrollSpy();
  $('.collapsible').collapsible();

  $('.button-collapse').on('click', function(){
    if ($(this).hasClass('active')) {
      $(this).removeClass('active');
      $('.site-content').removeClass('shift-right');
    } else {
      $(this).addClass('active');
      $('.site-content').addClass('shift-right');
    }
  });

  $('table').addClass('highlighted');
});

$(document.body).click(function() {
  if ($('.button-collapse').hasClass('active')) {
    $('.button-collapse').removeClass('active');
    $('.site-content').removeClass('shift-right');
  }
});
     
