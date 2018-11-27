const initLineFollowerImg = () => {
    var lineFollowerImg = document.createElement('img');
    lineFollowerImg.setAttribute('id', 'lineFollowerImg');
    lineFollowerImg.setAttribute('src', 'img/lineFollower_centered.png');
    $("#lineFollower").append(lineFollowerImg);
};

/*const setState = () => {
    //TODO
}*/

const updateLineFollowerImg = (state) => {
    // nous avons 4 images pour représenter les états du line follower
    const lineFollowerImg = $("#lineFollowerImg")[0];

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
        initLineFollowerImg();
        for (let i = 0; i < 4; i++) {
            setTimeout(function() {
                let state = i;
                updateLineFollowerImg(state);
            }, i*500);
        }
    })();
});