
 char SCRIPT_page[] PROGMEM = R"=====(  const update = (data) => {
    const jsonData = JSON.parse(data);
    document.getElementById("status").textContent = jsonData.status;
    document.getElementById("fullValue").textContent = jsonData.fullValue;
    document.getElementById("emptyValue").textContent = jsonData.emptyValue;
    document.getElementById("value").textContent = jsonData.value;
};

const updateButton = document.getElementById("updateButton");

const fetchAndUpdateStatus = () => {
    fetch("/status")
        .then(response => {
            return response.text();
        })
        .then(data => {
            update(data);
        });
};
setInterval(fetchAndUpdateStatus, 5000);
updateButton.addEventListener("click", fetchAndUpdateStatus);

)=====";