var gateway = "ws://localhost:10003";
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

function onLoad(event) {
  console.log("Website loaded");
  initWebSocket();

  //setTimeout(websocketRefresh, 5000);
}

function onUnload() {  
  console.log("Website Unloaded");
  //websocket.close();
}

// ----------------------------------------------------------------------------
// WebSocket handling
// ----------------------------------------------------------------------------

function websocketRefresh() {
    //websocket.close();
    //initWebSocket();
    
    //location.reload();
}

function initWebSocket() {
    websocket = new WebSocket(gateway);
    console.log('Trying to open WebSocket connection');
    websocket.addEventListener('open', onOpen);
    websocket.addEventListener('message', onMessage);
    //websocket.send('Reply')
    websocket.addEventListener('error', onError);
    websocket.addEventListener('close', onClose);
    //websocket.onopen  = onOpen;
    //websocket.onSend = onSend;
    //websocket.onclose = onClose;
    // websocket.onmessage = onMessage;
}

function onOpen (event){
  console.log('Connection  opened');
  websocket.send('Here is the message that Server awaits to start connection')
}

/*
function onSend (event){
	message = ('Hello From Website');
	websocket.send(message);
  	console.log('Send message to server');
}
*/

function onClose (event){
  console.log(' Try to close Connection');
  if (event.wasClean) {
      alert(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
    } else {
      // e.g. server process killed or network down
      // event.code is usually 1006 in this case
      alert('[close] Connection died!');
    }
  //setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    console.log(`Received a notification from ${event.origin}`);
    console.log(event);
    let result = JSON.parse(event.data);
    console.log(result)
    
    console.log("Object.keys(result)")
    console.log(Object.keys(result))
    console.log("-----------------------")
    
    for (const [key, value] of Object.entries(result)) {
  	console.log(`${key}: ${value[0]}`);
  	
  	console.log(value[0])
  	
    eventnum = value[0].match(/\d+/)[0];
    console.log(eventnum)
    
    eventstring = value[0].substring(0, value[0].length - 2);

    console.log(eventstring)    
    var currenttime = new Date().toLocaleTimeString();

    // Check for eventnum of event and run respective function
    if (eventnum == 0) {
      console.log("State of " + eventstring + " not OK");
      changeViewToNotOK(eventstring, "Open - Warning!", currenttime);
    } else if (eventnum == 1) {
      console.log("State of " + eventstring + " OK");
      changeViewToOK(eventstring,"Closed - Status OK", currenttime );
    } else if (eventnum == 2) {
      console.log("State of " + eventstring + " unknown - No Connection!");
      changeViewToError(eventstring,"No connection - Status unknown" , currenttime);
    }else {
      console.log(`Cannot read message received`);
    }
  	
  }

    
  
    


  // -- Solution with JSON -- //
  //  let  = JSON.parse(event.data);
  //  document.getElementById('led').className = data.status; 
}

 function onError(error){
    alert(`[error] ${error.message}`);
  };

 function onClick(element) {
   // maybe give back state of window/door as text?
 }

// !Server Side!
// ----------------------------------------------------------------------------
// WebSocket initialization
// ----------------------------------------------------------------------------

//void onEvent(AsyncWebSocket       *server,
//             AsyncWebSocketClient *client,
//             AwsEventType          type,
//             void                 *arg,
//             uint8_t              *data,
//             size_t                len) {
//
//    switch (type) {
//        case WS_EVT_CONNECT:
//            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), ////client->remoteIP().toString().c_str());
//            break;
//        case WS_EVT_DISCONNECT:
//            Serial.printf("WebSocket client #%u disconnected\n", client->id());
//            break;
//        case WS_EVT_DATA:
//        case WS_EVT_PONG:
//        case WS_EVT_ERROR:
//            break;
//    }
//}

// INTERPRET DATA TO CHANGE WEB INTERFACE
// function onMessage(event) {
//     document.getElementById('sensor').className = event.data;
// }
