var maximized = false;

function init() {
    document.getElementById("close").addEventListener("click", quit);
    document.getElementById("size").addEventListener("click", size);
    document.getElementById("hide").addEventListener("click", hidden);
}

function quit() {
    window.close();
}

function size() {

    if (maximized == true) {
        document.getElementById("size_img").src = "MaximizeButton.png";
        maximized = false;
    }
    else {
        document.getElementById("size_img").src = "MinimizeButton.png";
        maximized = true;
    }
}

function hidden() {
    window.hide();
}

window.addEventListener("DOMContentLoaded", init);