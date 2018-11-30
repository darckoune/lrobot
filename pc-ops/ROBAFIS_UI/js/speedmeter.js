//https://github.com/kottenator/jquery-circle-progress
const circleMax = 0.75;
const maxSpeed = 80;
let actualSpeed = 0;

addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str     = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == "SPEED") {
      actualSpeed = strCopy[1];
      circle.circleProgress('value', (actualSpeed / maxSpeed) * circleMax);
    }
  }
});

var circle = $('#circle').circleProgress({
  startAngle: Math.PI,
  reverse: true,
  thickness: 20,
  lineCap: "round",
  fill: { gradient: ["#614fdf", "#00d1f4", "#ff0054"], gradientAngle: Math.PI / 4 },
  value: circleMax,
  size: 1000,
  emptyFill: "#929ba3",
  animation: { duration: 800, easing: "circleProgressEasing" }
});

circle.resizable();

const getActualSpeed = () => {
  console.log(actualSpeed);
  return actualSpeed;
};

circle.on('circle-animation-progress', function(e, v) {
  var obj = $(this).data('circle-progress'),
      ctx = obj.ctx,
      s = obj.size,
      sv = (100 * v).toFixed(),
      fill = obj.arcFill;

  ctx.save();

  /*
  ** DEBUT Texte
  */
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';

  //Vitesse
  if(phase == 4 || phase == 5 ) {
    if(actualSpeed <= 15 ){
      ctx.font = "normal " + s / 2.5 + "px sans-serif";
      ctx.fillStyle = "#99ff99";
      ctx.fillText(getActualSpeed(), s / 2, s / 2);
    } else {
      ctx.font = "normal " + s / 2.5 + "px sans-serif";
      ctx.fillStyle = "red";
      ctx.fillText(getActualSpeed(), s / 2, s / 2);
    }
  } else {
    if(actualSpeed <= 80 ){
      ctx.font = "normal " + s / 2.5 + "px sans-serif";
      ctx.fillStyle = "#99ff99";
      ctx.fillText(getActualSpeed(), s / 2, s / 2);
    } else {
      ctx.font = "normal " + s / 2.5 + "px sans-serif";
      ctx.fillStyle = "red";
      ctx.fillText(getActualSpeed(), s / 2, s / 2);
    }
  }


  //Unité de la vitesse
  ctx.fillStyle = "#ffffff";
  ctx.font="50px sans-serif";
  ctx.fillText("Mm/s", s / 2, s / 1.35);

  //Distance parcourue
  // ctx.fillStyle = "#979fa7";
  // ctx.font="35px sans-serif";
  // ctx.fillText("Distance parcourue", s / 2, s / 1.2);
  //
  // ctx.fillStyle = "#979fa7";
  // ctx.font="35px sans-serif";
  // ctx.fillText("100 m", s / 2, s / 1.135);

  ctx.restore();

  /*
  ** FIN Texte
  */
});

//pour modifier dynamiquement la position du cercle
//setTimeout(function() { circle.circleProgress('value', 0.5); }, 3000);
// (function test() {
//
//   setTimeout(function() {
//     circle.circleProgress('value', (actualSpeed / maxSpeed) * circleMax);
//   }, 1000);
//
//   setTimeout(function() {
//     actualSpeed = 90;
//     circle.circleProgress('value', (actualSpeed / maxSpeed) * circleMax);
//   }, 2000);
//
//   setTimeout(function() {
//     actualSpeed = 20;
//     circle.circleProgress('value', (actualSpeed / maxSpeed) * circleMax);
//   }, 3000);
// })();
