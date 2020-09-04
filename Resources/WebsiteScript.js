function init() {
    document.getElementById("close").addEventListener("click", quit);
    document.getElementById("hide").addEventListener("click", hidden);
}

function quit() {
    window.close();
}

function hidden() {
    window.hide();
}

window.addEventListener("DOMContentLoaded", init);