$(document).ready(function(){
    var textElem = document.getElementById("clocktext");

    /*
    // Heure à l'américaine
    function updateClock() {
        var d = new Date();
        var s = "";
        s += ((d.getHours() + 11) % 12 + 1) + ":";
        s += (10 > d.getMinutes() ? "0" : "") + d.getMinutes() + "\u00A0";
        s += d.getHours() >= 12 ? "pm" : "am";
        textElem.textContent = s;
        setTimeout(updateClock, 60000 - d.getTime() % 60000 + 100);
    }*/

    // Heure à la française
    function updateClock() {
        var d = new Date();
        var s = "";
        s += (10 > d.getHours  () ? "0" : "") + d.getHours  () + ":";
        s += (10 > d.getMinutes() ? "0" : "") + d.getMinutes();
        textElem.textContent = s;
        setTimeout(updateClock, 60000 - d.getTime() % 60000 + 100);
    }

    updateClock();
});