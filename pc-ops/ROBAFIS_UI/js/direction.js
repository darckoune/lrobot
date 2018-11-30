addWebsocketCallback(function(data){
  if(phase == 1 || phase == 6 || phase == 3) {
    //a faire avec le lineFollower
    if(data.type == "robot" ) {
      var str     = data.message;
      var strCopy = str.split(':');
      if(strCopy[0] == "LINE") {
        if(strCopy[1] == 1 && strCopy[2] == 1) {
          updateArrowImg(0); //flèche direction avant
        } else if(strCopy[1] == 1 && strCopy[2] == 0) {
          updateArrowImg(2); //fleche avant gauche
        } else if(strCopy[1] == 0 && strCopy[2] == 1) {
          updateArrowImg(3); //fleche avant droit
        } else if(strCopy[1] == 0 && strCopy[2] == 0) {
          updateArrowImg(1); //fleche direction arrière
        }
      }
    }
  } else {
    if(data.type == "controller") {
      var str     = data.message;
      var strCopy = str.split(':');
      const arrowImg = $("#arrowImg");
      arrowImg.css('display', 'block');
      if(strCopy[0] == "MOVE") {
        if (strCopy[2] < 50 && strCopy[2] > -50 && strCopy[1] < 100 && strCopy[1] > 0) {
          updateArrowImg(0); //flèche direction avant
        } else if(strCopy[2] < 50 && strCopy[2] > -50 && strCopy[1] > -100 && strCopy[1] < 0) {
          updateArrowImg(1); //fleche direction arrière
        } else if(strCopy[1] < 50 && strCopy[1] > -50 && strCopy[2] < 100 && strCopy[2] > 0){
          updateArrowImg(2); //fleche avant gauche
        } else if(strCopy[1] < 50 && strCopy[1] > -50 && strCopy[2] > -100 && strCopy[2] < 0){
          updateArrowImg(3); //fleche avant droit
        } else if(strCopy[1] == 0 && strCopy[2] == 0){
          console.log("OK");
          arrowImg.css('display', 'none');
        }
      }
    }
  }
});

const initArrowImg = () => {
    var arrowImg = document.createElement('img');
    arrowImg.setAttribute('id', 'arrowImg');
    arrowImg.setAttribute('src', 'img/arrow-up-straight.png');
    $("#arrow").append(arrowImg);
};

const updateArrowImg = (state) => {
    const arrowImg = $("#arrowImg")[0];

    if (arrowImg) {
        switch (state) {
            case 0:
                arrowImg.setAttribute('src', 'img/arrow-up-straight.png');
                break;

            case 1:
                arrowImg.setAttribute('src', 'img/arrow-down-straight.png');
                break;

            case 2:
                arrowImg.setAttribute('src', 'img/arrow-curve-pointing-to-right.png');
                break;

            case 3:
                arrowImg.setAttribute('src', 'img/arrow-curve-pointing-to-left.png');
                break;

            default:
                break;
        }
    }
};

$(document).ready(function(){
    (function test () {
        initArrowImg();
        // for (let i = 0; i < 8; i++) {
        //     setTimeout(function() {
        //         let state = i;
        //         updateArrowImg(state);
        //     }, i*500);
        // }
    })();
});
