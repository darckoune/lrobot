addWebsocketCallback(function(data){
    //a faire avec le lineFollower
    if(data.type == "robot" ) {
      var str     = data.message;
      var strCopy = str.split(':');
      if(strCopy[0] == "LINE") {
        if(strCopy[1] == 1 && strCopy[2] == 1) {
          updateLineFollowerImg(0); //flèche direction avant
        } else if(strCopy[1] == 1 && strCopy[2] == 0) {
          updateLineFollowerImg(2); //fleche avant gauche
        } else if(strCopy[1] == 0 && strCopy[2] == 1) {
          updateLineFollowerImg(1); //fleche avant droit
        } else if(strCopy[1] == 0 && strCopy[2] == 0) {
          updateLineFollowerImg(3); //fleche direction arrière
        }
      }
    } else if (phase == 5) {
      updateLineFollowerImg(3); //désactive le lineFollower
    }
});

const initLineFollowerImg = (mode) => {
    var lineFollowerImg = document.createElement('img');
    lineFollowerImg.setAttribute('id', 'lineFollowerImg'+mode);
    lineFollowerImg.setAttribute('src', 'img/lineFollower_centered.png');
    $("#lineFollower"+mode).append(lineFollowerImg);
};

/*const setState = () => {
    //TODO
}*/

const updateLineFollowerImg = (state) => {
    // nous avons 4 images pour représenter les états du line follower
    const lineFollowerImg = $("#lineFollowerImg"+Ihm)[0];

    if (lineFollowerImg) {
        switch (state) {
            case 0:
                lineFollowerImg.setAttribute('src', 'img/lineFollower_centered.png');
                break;

            case 1:
                lineFollowerImg.setAttribute('src', 'img/lineFollower_right.png');
                break;

            case 2:
                lineFollowerImg.setAttribute('src', 'img/lineFollower_left.png');
                break;

            case 3:
                lineFollowerImg.setAttribute('src', 'img/lineFollower_lost.png');
                break;

            default:
                break;
        }
    }
};

$(document).ready(function(){
    (function test () {
        initLineFollowerImg("MANU");
        initLineFollowerImg("PILOT");
        // for (let i = 0; i < 4; i++) {
        //     setTimeout(function() {
        //         let state = i;
        //         updateLineFollowerImg(state);
        //     }, i*500);
        // }
    })();
});
