$(document).ready(function() {
  var scroll_elem_on; // WHICH ELEMENT SCROLLBAR IS ON
  var old_scroll; // PREVIOUS ELEMENT
  var header_height = 50; // FIXED HEIGHT OF HEADER
  var menu_clicked = 0; // Whether menu has been clicked in between hover
  var switch_s = 0; // Whether to switch menu in or out

  // SMOOTH SCROLLING IMPLEMENTATION, KEEPS NORMAL LINKS
  $('a, .oval-button-white, .oval-button-blue').click(function(){
    var link = $(this).attr('data-href');
    
    if(link.charAt(0) != '#') {
      document.location.href = link;
      return;
    }

    $('html, body').animate({scrollTop: $(link).offset().top - header_height + 2}, 500);
    return false;
  });
  
  // HOVER EFFECT ON ANCHOR ELEMENTS
  $('section a, footer a').hover(function() {
    prev_color = $(this).css("color");
    $(this).css("color", "rgba(255, 255, 255, 0.7)");
  }, function() {
    $(this).css("color", "");
  });
  
  var prev_color;

  // HOVER EFFECT ON MENU ITEMS
  $('header a').hover(function() {
    menu_clicked = 0;
    prev_color = $(this).css("color");

    if(switch_s)
      $(this).css("color", "#008B8B");
    else
      $(this).css("color", "rgba(255, 255, 255, 1");
  }, function() {
    if(menu_clicked)
      return;

    $(this).css("color", prev_color);
  });

  // COLOR TRANSITION ON BLUE BUTTON
  $('.oval-button-blue').hover(function() {
    prev_color = $(this).css("background");
    $(this).css("background", "rgba(0, 102, 102, 0.9)");
  }, function() {
    $(this).css("background", prev_color);
  });

  // COLOR TRANSITION ON WHITE BUTTON
  $('.oval-button-white').hover(function() {
    prev_color = $(this).css("background");
    $(this).css("background", "rgba(255, 255, 255, 0.9)");
  }, function() {
    $(this).css("background", prev_color);
  });

  // HOVER ANIMATION ON FEATURE ICONS
  $('#features .size-3').hover(function() {
    $(this).find(".icon").stop().animate({bottom: "20px"}, 500);
  }, function() {
    $(this).find(".icon").stop().animate({bottom: "0"}, 500);
  });
  
  // AUTOMATIC MENU AND MENU ITEM TRANSITIONS
  $(window).scroll(function() {
    if($(window).scrollTop() >= 20)
      menu_switch_in();

    else if($(window).scrollTop() <= 0)
      menu_switch_out();
  
    $('section').each(function(i, obj) {
      if(scroll_bar_on(obj))
        scroll_elem_on = obj;
    });

    if(old_scroll == scroll_elem_on)
      return;
    
    $("header nav a").css("color", "#333");
    
    var id = "#" + $(scroll_elem_on).attr('id');
    old_scroll = scroll_elem_on;
  
    $('header nav a').each(function(i, obj) {
      if($(obj).attr('data-href') == id) {
        set_color_transition(obj, "#008B8B");
        return;
      }
    });

  });
  
  // CHECK WHETHER THE SCROLLBAR IS ON AN ELEMENT OR NOT
  function scroll_bar_on(obj) {
    var scrolled = $(window).scrollTop();
    var top_offset = $(obj).offset().top - header_height - 2;

    if(scrolled >= top_offset)
      return true;

    return false;
  }

  // COLOR TRANSITION ON OBJ
  function set_color_transition(obj, color) { 
    $(obj).css("color",  color);
    menu_clicked = 1;
  }
  
  // MENU COLOR IN ANIMATION
  function menu_switch_in() {
    if(switch_s)
      return;
    
    switch_s = 1;

    $('header').css("background", "#FFF");
    $('header nav a').css("color", "#333");
    $('header .size-4 a').css("color", "#008B8B");
    $('header .size-4 a').css("font-size", "16px");
  }
  
  // MENU COLOR OUT ANIMATION
  function menu_switch_out() {
    if(! switch_s)
      return;

    switch_s = 0;

    $('header').css("background", "transparent");
    $('header nav a').css("color", "rgba(255, 255, 255, 0.8)");
    $('header .size-4 a').css("color", "rgba(255, 255, 255, 0.8)");
    $('header .size-4 a').css("font-size", "20px");
  }
});
