

 char INDEX_page[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <title>WifiAuto!</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script>
$(document).ready(function(){
  $("button").keydown(function(){
    $.get("oikea", function(data, status){    
    });
  });
});

$(document).ready(function(){
  $("button").keyup(function(){
    $.get("vasen", function(data, status){    
    });
  });
});


$(document).ready(function(){
  $("button").keypress(function(){
    $.get("keypress", function(data, status){    
    });
  });
});


</script>
</head>
<body>
  <body>
    <h1>WifiAuto!</h1>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/js/bootstrap.bundle.min.js" integrity="sha384-b5kHyXgcpbZJO/tY9Ul7kGkf1S0CWuKcCD38l8YkeH8z8QjE0GmW1gYU5S9FOnJ0" crossorigin="anonymous"></script>
<button>Ohjaus</button>


  </body>
</html>)=====";