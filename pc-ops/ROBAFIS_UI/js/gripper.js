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
                gripperImg.setAttribute('src', 'img/gripper1.png');
                break;

            case 1:
                gripperImg.setAttribute('src', 'img/gripper2.png');
                break;

            case 2:
                gripperImg.setAttribute('src', 'img/gripper3.png');
                break;

            case 3:
                gripperImg.setAttribute('src', 'img/gripper4.png');
                break;

            case 4:
                gripperImg.setAttribute('src', 'img/gripper5.png');
                break;

            case 5:
                gripperImg.setAttribute('src', 'img/gripper6.png');
                break;

            case 6:
                gripperImg.setAttribute('src', 'img/gripper7.png');
                break;

            case 7:
                gripperImg.setAttribute('src', 'img/gripper8.png');
                break;

            default:
                break;
        }
    }
};

$(document).ready(function(){
    (function test () {
        initGripperImg();
        for (let i = 0; i < 8; i++) {
            setTimeout(function() {
                let state = i;
                updateGripperImg(state);
            }, i*500);
        }
    })();
});
