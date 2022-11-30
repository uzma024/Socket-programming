const WebSocket = require("ws");
const socket = new WebSocket("ws://localhost:8080");
const readline = require("readline");

//singleton readline interface
let rl;

/**
 * @description
 * 1. socket.on('open') is triggered when the client is connected to the server
 * 2. socket.on('message') is triggered when the client receives a message from the server
 * 3. socket.on('error') is triggered when the client encounters an error
 */
socket.on("open", () => {
  console.log("Connected to server");

  sendMsg();
});

socket.on("message", (message) => {
  console.log("\nServer: " + message);

  //message trigger for every message received from server for continuous chat
  sendMsg();
});

socket.on("error", () => {
  console.log("Error connecting to server");
});

/**
 * @description
 * Method for sending messages to server
 */

function createArray(length) {
  var arr = new Array(length || 0),
      i = length;

  if (arguments.length > 1) {
      var args = Array.prototype.slice.call(arguments, 1);
      while(i--) arr[length-1 - i] = createArray.apply(this, args);
  }

  return arr;
}

function Encrypt(m){
  // let m=message.msg;
  // let key =message.key;
  console.log("Message ",m);
  var len=m.length;
  let key=3;
  var mat = createArray(key,len);
  for(var i=0;i<key;i++){
    for(var j=0;j<len;j++){
      mat[i][j]='\n';
    }
  }
  
  // console.log("matrix: ", mat);
  for(var i=0;i<len;i++){
    var j=0;
    for(j;j<key;j++){
      if(i>=len)break;
      mat[j][i]=m[i];
      i++;
    }

  // console.log("matrix: ", mat);
    j-=2;
    for(j;j>0;j--){
      if(i>=len)break;
      mat[j][i]=m[i];
      i++;
    }
    i--;
  }
  console.log("matrix: ", mat);

  let Encrypted="";
  for(var i=0;i<key;i++){
    for(j=0;j<len;j++){
      if(mat[i][j]!='\n'){
        Encrypted+=mat[i][j];
      }
    }
  }
  console.log("Encrypted ",Encrypted);
  return Encrypted;
}


const sendMsg = () => {
  //closing the previous readline
  if (rl) rl.close();

  //creating a new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  rl.question(">> ", (msg) => {
    let message = Encrypt(msg);
    // Suppose key is changed;
    // message.key++;
    socket.send(message);

    //message trigger for every message sent from client for continuous chat
    sendMsg();
  });
};