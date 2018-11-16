$(document).ready(function(){

    var chrono = document.getElementById('chronometer');
    var seconds = 0, minutes = 0, hours = 0;
    var t;

    console.log(chrono.textContent, typeof chrono.textContent);

    (function test() {
        setTimeout(function() {
            startTimer(t, chrono, seconds, minutes, hours);
        }, 2000);
        setTimeout(function() {
            stopTimer(t);
        }, 6000);
        setTimeout(function() {
            resetTimer(chrono, seconds, minutes, hours);
        }, 7000);
    })();
});

function add(t, chrono, seconds, minutes, hours) {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
        }
    }
    console.log(chrono, chrono.textContent, typeof chrono.textContent);
    chrono.textContent = (hours ? (hours > 9 ? hours : "0" + hours) : "00") + ":" + (minutes ? (minutes > 9 ? minutes : "0" + minutes) : "00") + ":" + (seconds > 9 ? seconds : "0" + seconds);

    startTimer(t);
}
function startTimer(t, chrono, seconds, minutes, hours) {
    t = setTimeout(add(t, chrono, seconds, minutes, hours), 1000);
}

/* Stop button */
function stopTimer(t) {
    clearTimeout(t);
}

function resetTimer(chrono, seconds, minutes, hours) {
    chrono.textContent = "00:00:00";
    seconds = 0; minutes = 0; hours = 0;
}