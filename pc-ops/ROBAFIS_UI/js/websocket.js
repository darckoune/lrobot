var websocket;
var onWebsocket;

function setupSocket(){
    websocket = new WebSocket("ws://localhost:8080/");
    websocket.onmessage = function(evt){
        if(onWebsocket){
            try {
                data = JSON.parse(evt.data);
                if (data){
                    onWebsocket(data);
                }
            } catch(e) {
                console.log("Failed to parse json");
            }
        }
    };
    websocket.onopen=function(evt){
        websocket.send("Connection !");
    };
    websocket.onclose=function(evt){
        setTimeout(() => {
            setupSocket();
        }, 50);
    };
}

window.onload = function(){
    setupSocket();
}

window.onclose=function(){
    ws.close();
}


// Pour controler le comportement du websocket, redéfinir onWebsocket
onWebsocket = function(data){
    console.log(data);
}