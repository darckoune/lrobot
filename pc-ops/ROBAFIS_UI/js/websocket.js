var websocket;
var onWebsocket;
var onWebsocketCallbacks = [];


function setupSocket(){
    if(onWebsocket){
        onWebsocket({type:"socket", "message":"CONNECTING"});
    }
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
        if(onWebsocket){
            onWebsocket({type:"socket", "message":"CONNECTED"});
        }
    };
    websocket.onclose=function(evt){
        if(onWebsocket){
            onWebsocket({type:"socket", "message":"DISCONNECTED"});
        }
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
    onWebsocketCallbacks.forEach((callback) => {
        callback(data);
    });
}

function addWebsocketCallback(callback){
    onWebsocketCallbacks.push(callback);
}