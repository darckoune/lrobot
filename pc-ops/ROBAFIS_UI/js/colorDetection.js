var colorContext = undefined;

  function createColorCanvas () {
    var colorContainer = document.getElementById('colorDetection');
    var colorCanvas = document.createElement('canvas');
    colorCanvas.id = 'colorCanvas';
    colorCanvas.width = 400;
    colorCanvas.height = 300;
    colorContainer.appendChild(colorCanvas);

    colorContext=colorCanvas.getContext('2d');

    noColorDetected(colorContext);
  }

  function noColorDetected(colorContext) {
    //green
    colorContext.beginPath();
    colorContext.arc(120, 75, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#b1bfb4';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#dbdbdb';*/
    colorContext.stroke();

    //red
    colorContext.beginPath();
    colorContext.arc(280, 75, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#ce9c9c';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#dbdbdb';*/
    colorContext.stroke();

    //yellow
    colorContext.beginPath();
    colorContext.arc(200, 200, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#cec994';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#dbdbdb';*/
    colorContext.stroke();
  }

  function greenDetected (colorContext) {
    colorContext.beginPath();
    colorContext.arc(120, 75, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#00B651';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#ffffff';*/
    colorContext.stroke();
  }

  function redDetected (colorContext) {
    colorContext.beginPath();
    colorContext.arc(280, 75, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#EF0000';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#ffffff';*/
    colorContext.stroke();
  }

  function yellowDetected (colorContext) {
    colorContext.beginPath();
    colorContext.arc(200, 200, 50, 0, 2 * Math.PI);
    colorContext.fillStyle = '#F4FF00';
    colorContext.fill();
    /*colorContext.lineWidth = 5;
    colorContext.strokeStyle = '#ffffff';*/
    colorContext.stroke();
  }

$(document).ready(function(){
    createColorCanvas();
});

addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str     = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == "COLOR") {
      switch (strCopy[1]) {
        case "GREEN":
          noColorDetected(colorContext)
          greenDetected(colorContext);
          setTimeout(() => {
            timer.stop();
          }, 2900);
          break;
        case "RED":
          noColorDetected(colorContext)
          redDetected(colorContext);
          break;
        case "YELLOW":
          noColorDetected(colorContext)
          yellowDetected(colorContext);
          break;
        default:
          noColorDetected(colorContext);
      }
    }
  }
});
