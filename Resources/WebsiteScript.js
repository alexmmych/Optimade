var maximized = false;

function init() {
    document.getElementById("close").addEventListener("click", quit);
    document.getElementById("size").addEventListener("click", resize);
    document.getElementById("hide").addEventListener("click", hidden);
}


function quit() {
    window.close();
}

function resize() {
    if (maximized == true) {
        document.getElementById("size_img").src = "MaximizeButton.png";
        maximized = false;
    }
    else {
        document.getElementById("size_img").src = "MinimizeButton.png";
        maximized = true;
    }
    window.size();
}

function change() {
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
