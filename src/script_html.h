
 char SCRIPT_page[] PROGMEM = R"=====(  const update = (data) => {
    const jsonData = JSON.parse(data);
    document.getElementById("status").textContent = jsonData.status;
    document.getElementById("fullValue").textContent = jsonData.fullValue;
    document.getElementById("emptyValue").textContent = jsonData.emptyValue;
    document.getElementById("value").textContent = jsonData.value;
};

const fullButton = document.getElementById("fullButton");
const emptyButton = document.getElementById("emptyButton");

fullButton.addEventListener("click", function() {
    fetch("/full")
        .then(response => {
            return response.text();
        })
        .then(data => {
            update(data);
            location.reload();
        });
});

emptyButton.addEventListener("click", function() {
    fetch("/empty")
        .then(response => {
            return response.text();
        })
        .then(data => {
            update(data);
            location.reload();
        });
});

fetch("/status")
    .then(response => {
        return response.text();
    })
    .then(data => {
        update(data);
    });

)=====";