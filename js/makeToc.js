//==--- js/makeToc.js ----------------------------------------- -*- .js -*- ==//
//
//                                     Voxel
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==------------------------------------------------------------------------==//
//
//  \file  makeToc.js
//  \brief Makes a table of contents from page headings. The main heading and
//         sub heading can be defined at the top of the file.
//
//==------------------------------------------------------------------------==//

var mainHeading = "h2";
var subHeading  = "h3";

$(document).ready(function(){
  var tableOfContents = 
    "<ul id='tocscroll' class='collapsible popout table-of-contents " + 
    "hide-on-med-and-down' data-collapsible='accordion'>";

  var element,  // The element we are looking at.
      title  ,  // The element's title.
      link   ;  // The element's link.
  $(mainHeading).each(function() {
    element = $(this);
    title   = element.text();
    link    = "#" + element.attr("id");

    newLine =
      "<li><div class='collapsible-header z-depth-1'><a href='" + 
      link + "'>" + title + "</a></div>"                        +
      "<div class='collapsible-body'><ul>";

    // Search through the next bit of the content and check if we find som sub
    // headers we should add:
    var contents = $(this).nextUntil(mainHeading).text();
    $(subHeading).each(function() { 
      subtitle = $(this).text();
      if (contents.search(subtitle) != -1) {
        sublink  = "#" + $(this).attr("id");
        newLine += "<li><a href='" + sublink + "'>" + subtitle + "</a></li>";
      }
    });

    newLine         += "</ul></div></li>";
    tableOfContents += newLine
  });

  tableOfContents += "</ul>";

  // Add the built table of contents to the table of contents div:
  var toc = document.getElementById("tabofcontents");
  toc.innerHTML = tableOfContents;

  // Set properties of the TOC widget:
  document.getElementById("tocscroll").style.position  = "fixed";
  //document.getElementById("tocscroll").style.width     = "17%";
  document.getElementById("tocscroll").style.marginTop = "3%";

  // Initialize the added elements:
  $('.collapsible').collapsible();
});
