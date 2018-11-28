var state = 0;
var status = undefined;
addWebsocketCallback(function(data){
  if(data.type == "controller") {
    var str = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == "PLIERS") {
      if(strCopy[1] == "OPEN") {
        updateGripperImg(0);
      }
      if(strCopy[1] == "CLOSE"){
        updateGripperImg(1);
      }
      if(strCopy[1] == "STOP"){
        updateGripperImg(2);
      }
    }
  }
});

const initGripperImg = () => {
    var gripperImg = document.createElement('img');
    gripperImg.setAttribute('id', 'gripperImg');
    gripperImg.setAttribute('src', 'img/gripper1.png');
    $("#gripper").append(gripperImg);
};

// const setState = () => {
//     //
// }

const updateGripperImg = (state) => {
    // nous avons 8 images pour représenter les états de la pince
    const gripperImg = $("#gripperImg")[0];

    if (gripperImg) {
        switch (state) {
            case 0:
                gripperImg.setAttribute('src', 'img/gripper_opening.gif');
                break;

            case 1:
                gripperImg.setAttribute('src', 'img/gripper_closing.gif');
                break;

            case 2:
                gripperImg.setAttribute('src', 'img/gripper1.png');
                break;
            default:
                break;
        }
    }
};

$(document).ready(function(){
    (function test () {
        initGripperImg();
        // for (let i = 0; i < 8; i++) {
        //     setTimeout(function() {
        //         let state = i;
        //         updateGripperImg(state);
        //     }, i*500);
        // }
    })();
});
