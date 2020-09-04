function init() {
    document.getElementById("close").addEventListener("click", closed);
}

function closed() {
    window.close();
}

window.addEventListener("DOMContentLoaded", init);