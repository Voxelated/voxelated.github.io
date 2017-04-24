//==--- js/init.js -------------------------------------------- -*- .js -*- ==//
//
//                                     Voxel
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
//  \file  init.js
//  \brief Javascript initialization script for the documentation.
//
//==------------------------------------------------------------------------==//

$(document).ready(function(){
  $('.button-collapse').sideNav();
  $('.scrollspy').scrollSpy();
  $('.collapsible').collapsible();

  // Support for the menu:
  $('.button-collapse').on('click', function(){
    if ($(this).hasClass('active')) {
      $(this).removeClass('active');
      $('.site-content').removeClass('shift-right');
    } else {
      $(this).addClass('active');
      $('.site-content').addClass('shift-right');
    }
  });

  // Append hiding for small screens to all navbar elements:
  $('.voxel-navbar-element').addClass('hide-on-med-and-down');
  $('.voxel-navbar-element').addClass('hide-on-small-and-down');

  // Make table highlighted:
  $('table').addClass('highlighted');
});

$(document.body).click(function() {
  if ($('.button-collapse').hasClass('active')) {
    $('.button-collapse').removeClass('active');
    $('.site-content').removeClass('shift-right');
  }
});
     
