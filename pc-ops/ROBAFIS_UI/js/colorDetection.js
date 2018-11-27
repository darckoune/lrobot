function test (colorContext) {
    setTimeout(function() {
       greenDetected(colorContext);
    }, 1000);
    
    setTimeout(function() {
       noColorDetected(colorContext);
    }, 3000);
    
    setTimeout(function() {
       yellowDetected(colorContext);
    }, 4000);
    
    setTimeout(function() {
       noColorDetected(colorContext);
    }, 5000);
    
    setTimeout(function() {
       redDetected(colorContext);
    }, 6000);
  }
  
  
  function createColorCanvas () {
    var colorContainer = document.getElementById('colorDetection');
    var colorCanvas = document.createElement('canvas');
    colorCanvas.id = 'colorCanvas';
    colorCanvas.width = 400;
    colorCanvas.height = 300;
    colorContainer.appendChild(colorCanvas);
  
    var colorContext=colorCanvas.getContext('2d');
  
    noColorDetected(colorContext);
    
    //to remove
    test(colorContext);
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