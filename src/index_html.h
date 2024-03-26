

 char INDEX_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BmbxuPwQa2lc/FVzBcNJ7UAyJxM6wuqIj61tLrc4wSX0szH/Ev+nYRRuWlolflfl" crossorigin="anonymous">
    <title>MoccaMaster</title>
</head>
<body>
    <h1>MoccaMaster</h1>
    <button id="fullButton">Update</button>
  
    <div>
        <label for="status">Status:</label>
        <span id="status" class="bigger-text"></span>
    </div>
    <div>
        <label for="fullValue">Full Value:</label>
        <span id="fullValue"></span>
    </div>
    <div>
        <label for="emptyValue">Empty Value:</label>
        <span id="emptyValue"></span>
    </div> 
    <div>
        <label for="value">Value:</label>
        <span id="value"></span>
    </div>
    <script src="script.js"></script>
</body>
</html>
)=====";