addWebsocketCallback(function(data){
  if(data.type == "controller") {
    var str     = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == "CRANE") {
      if(strCopy[1] == "RAISE") {
        console.log("ici");
        updateBras(0);
      }
      if(strCopy[1] == "LOWER") {
        updateBras(1);
      }
      if(strCopy[1] == "STOP") {
        updateBras(2);
      }

    }
  }
});

const updateBras = (state) => {
    // nous avons 4 images pour représenter les états du line follower
    const lineBrasImg = $("#brasAnimation")[0];

    if (lineBrasImg) {
        switch (state) {
            case 0:
                lineBrasImg.setAttribute('style', 'display:block');
                lineBrasImg.setAttribute('src', 'img/arrow_up.gif');
                break;

            case 1:
                lineBrasImg.setAttribute('style', 'display:block');
                lineBrasImg.setAttribute('src', 'img/arrow_down.gif');
                break;

            case 2:
                lineBrasImg.setAttribute('style', 'display:none');
                break;

            default:
                break;
        }
    }
};
