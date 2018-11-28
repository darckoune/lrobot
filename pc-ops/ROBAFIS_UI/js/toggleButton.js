addWebsocketCallback(function(data){
  if(data.type == "controller") {
    if(data.message == "AUTOPILOT") {
      var button = document.getElementById("e");
      button.click();
    }
  }
});
