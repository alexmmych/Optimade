function init() {
    document.getElementById("close").addEventListener("click", close);
}

function close() {
    alert("Window closed!");
}

window.addEventListener("DOMContentLoaded", init);