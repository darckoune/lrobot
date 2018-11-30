var Ihm = "PILOT";
var phase = 2;
addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == 'STEP') {
      valideEtat(strCopy[1]);
      phase = strCopy[1];
      if (phase == 0 || phase == 1 || phase == 3 || phase == 5 || phase == 6){
        choseIHM("PILOT");
      } else {
        choseIHM("MANU");
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
    $('#colorDetection').css('display', 'none');
    $('#lineFollower').css('display', 'none');
  } else {
    $("#bras").css('display', 'none');
    $("#pince").css('display', 'none');
    $('#colorDetection').css('display', 'block');
    $('#lineFollower').css('display', 'block');
  }
}
// Fonction pour changer manuellement d'IHM
function choseIHM(type) {
  if (type == "MANU") {
    $("#bras").css('display', 'block');
    $("#pince").css('display', 'block');
    $('#colorDetection').css('display', 'none');
    $('#lineFollower').css('display', 'none');
  } else if (type == "PILOT") {
    $("#bras").css('display', 'none');
    $("#pince").css('display', 'none');
    $('#colorDetection').css('display', 'block');
    $('#lineFollower').css('display', 'block');
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
