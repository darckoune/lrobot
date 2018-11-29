addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str     = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == "AUTOPILOT") {
      changeAutopilot(strCopy[1]);
    }
  }
});

function changeAutopilot(status) {
  var button = document.getElementById("e");
  if(status == 1) {
    button.checked = true;
  } else if (status == 0) {
    button.checked = false; ;
  }
}
