//http://www.gerardolarios.com/plugins-and-tools/jqmeter/
var dynamicRaised= '80';
// initialser toutes les variables pour que jQMeterUpdate fonctionne correctement
let jQMeterOptions = {
    goal:'100',
    raised:'80',
    meterOrientation:'vertical',
    width:'50px',
    height:'200px',
    barColor: "#00F6D5",
    bgColor: "#324050",
    animationSpeed : 500,
    counterSpeed : 500,
    displayTotal: true
};

function jQMeterUpdate(elem, jQMeterOptions) {
    if(jQMeterOptions.meterOrientation == 'vertical') {
        $(elem).children('.outer-therm').children('.inner-therm').animate({height : (jQMeterOptions.raised / jQMeterOptions.goal) * 100 + '%'},jQMeterOptions.animationSpeed);
    }
    if(jQMeterOptions.displayTotal) {
        var from = parseInt($(elem).children('.outer-therm').children('.inner-therm').children().text());
        var difference = 0;

        //from - jQMeterOptions.raised > 0 ? difference = from - jQMeterOptions.raised : difference = jQMeterOptions.raised - from;
        $({ Counter: 0 }).animate({ Counter: from - jQMeterOptions.raised }, {
            duration : jQMeterOptions.counterSpeed,
            easing : 'swing',
            step : function() {
                $(elem).children('.outer-therm').children('.inner-therm').children().text(from - Math.round(this.Counter) + '%');
            }
        });
    }
}

function jQMeterInit(selector) {
    $(selector).jQMeter(jQMeterOptions);
}

$(document).ready(function(){
    (function test () {
        const selector = '#jqmeter-container';
        jQMeterInit(selector);
        //test
        setTimeout(function() {
            jQMeterOptions.raised = '20';
            jQMeterUpdate('#jqmeter-container', jQMeterOptions);
        }, 3000);
        setTimeout(function() {
            jQMeterOptions.raised = '50';
            jQMeterUpdate('#jqmeter-container', jQMeterOptions);
        }, 6000);
        setTimeout(function() {
            jQMeterOptions.raised = '5';
            jQMeterUpdate('#jqmeter-container', jQMeterOptions);
        }, 8000);
    })();
});
