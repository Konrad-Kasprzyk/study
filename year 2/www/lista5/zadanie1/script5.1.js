var nrZdjecia = 1;
var szybkosc = 3000;
var timer;


$( document ).ready(function() {

  przypiszSlajder();
  timer = setInterval(zmienZdjecie, 3000);
   
   $( function() {
    
    $( "#slajder" ).slider({
      min: 1000,
      max: 5000,
      value: 3000,
      step: 1000,
      slide: function(event, ui) {
        szybkosc = ui.value;
        $('#suwak').html(szybkosc/1000);
        /*
        var pobierzSzybkosc = $("#slajder").slider("value");
        */
        $("#aaa").text(ui.value);
        clearInterval(timer);
        timer = setInterval(zmienZdjecie, ui.value);
        
    }
    });
  });

  

});

function zmienZdjecie(){
  
  if (nrZdjecia == 5) 
      nrZdjecia = 1;
  else 
      nrZdjecia++;

  $( function() { 
    $("#slodziaki").animate({opacity: '0'}, function() {
          $("#slodziaki").attr('src','zdjecia/slodziak' + nrZdjecia + '.jfif');
          $("#aaa").append(szybkosc);
        });
    });
  $( function() { $("#slodziaki").animate({opacity: '1'}); });
}

function przypiszSlajder(){

$('#slodziaki').on('mouseenter', function(){
  clearInterval(timer);
});

$('#slodziaki').on('mouseleave', function(){
  clearInterval(timer);
  timer = setInterval(zmienZdjecie, szybkosc);
});
/*
$('#suwak').on("mouseup", function() {
  var pobierzSzybkosc = $("#slajder").slider("value");
  $("#aaa").text(pobierzSzybkosc);
  timer = setInterval(zmienZdjecie, pobierzSzybkosc);
});
*/
}