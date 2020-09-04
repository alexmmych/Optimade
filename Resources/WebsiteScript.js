function init() {
    document.getElementById("close").addEventListener("click", close);
}

function close() {
    alert(window.CefFunc());
}

window.addEventListener("DOMContentLoaded", init);