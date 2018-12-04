var timer = new Timer();
timer.addEventListener('secondsUpdated', function (e) {
    $('#chronometer').html(timer.getTimeValues().toString());
});
