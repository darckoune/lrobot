const initArrowImg = () => {
    var arrowImg = document.createElement('img');
    arrowImg.setAttribute('id', 'arrowImg');
    arrowImg.setAttribute('src', 'img/arrow-up-straight.png');
    $("#arrow").append(arrowImg);
};

const setState = () => {
    //TODO
}

const updateArrowImg = (state) => {
    // nous avons 8 images pour représenter les états de la pince
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
        for (let i = 0; i < 8; i++) {
            setTimeout(function() {
                let state = i;
                updateArrowImg(state);
            }, i*500);
        }
    })();
});