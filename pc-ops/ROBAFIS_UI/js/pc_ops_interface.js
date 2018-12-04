var Ihm = "PILOT";
var phase = 2;
addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == 'STEP') {
      valideEtat(strCopy[1]);
      phase = strCopy[1];
      if (phase == 0) {
        choseIHM("PILOT");
        init();
      }
      if (phase == 1 || phase == 3 || phase == 5 || phase == 6){
        choseIHM("PILOT");
      } else if (phase == 2 || phase == 4 ){
        choseIHM("MANU");
      }

      if (phase == 0){
        $('#chronometer').html("00:00:00");
        timer.reset();
        timer.stop();
      } else if (phase == 1){
        timer.start();
      }
    }
  }

  // if(data.type == "controller") {
  //   var str = data.message;
  //   var strCopy = str.split(':');
  //   if(strCopy[1] == "MANU") {
  //     var Ihm = "MANU";
  //     changeIHM();
  //   }
  //   if(strCopy[1] == "PILOT") {
  //     var Ihm = "PILOT";
  //     changeIHM();
  //   }
  // }
});

// Fonction pour passer de IHM manu à pilot
function changeIHM() {
  if (Ihm == "PILOT") {
    $("#bras").css('display', 'block');
    $("#pince").css('display', 'block');
    $('#colorDetection').css('display', 'block');
    $('#lineFollowerPILOT').css('display', 'none');
    $('#lineFollowerMANU').css('display', 'block');
  } else {
    $("#bras").css('display', 'none');
    $("#pince").css('display', 'none');
    $('#colorDetection').css('display', 'none');
    $('#lineFollowerPILOT').css('display', 'none');
    $('#lineFollowerMANU').css('display', 'block');
  }
}
// Fonction pour changer manuellement d'IHM
function choseIHM(type) {
  if (type == "MANU") {
    $("#bras").css('display', 'block');
    $("#pince").css('display', 'block');
    $('#colorDetection').css('display', 'block');
    $('#lineFollowerPILOT').css('display', 'none');
    $('#lineFollowerMANU').css('display', 'block');
  } else if (type == "PILOT") {
    $("#bras").css('display', 'none');
    $("#pince").css('display', 'none');
    $('#colorDetection').css('display', 'none');
    $('#lineFollowerPILOT').css('display', 'block');
    $('#lineFollowerMANU').css('display', 'none');
  }
}
// fonction de changement etat (étape du parcours)
  function valideEtat(etat) {
    for(i = etat ; i >= 0 ; i--) {
      $('#'+i).html('&#10003;');
      $('#'+i).css('background-color', 'green');
      $('#circle'+i).css('background-color', 'green');
    }
  }

  function init() {
    for(i = 6 ; i >= 0 ; i--) {
      $('#'+i).html(i);
      $('#'+i).css('background-color', '#075C93');
      $('#circle'+i).css('background-color', '#075C93');
    }
  }
