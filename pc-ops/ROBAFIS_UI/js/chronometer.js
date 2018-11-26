var timer = new Timer();
timer.start();
timer.addEventListener('secondsUpdated', function (e) {
    $('#chronometer').html(timer.getTimeValues().toString());
});
