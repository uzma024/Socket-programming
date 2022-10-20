const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 8080 });
const readline = require("readline");

console.log("Listening on port 8080");

//singleton readline
let rl;

/**
 * @description
 * 1. wss.on('connection') is triggered when the client is connected to the server
 * 2. ws.on('message') is triggered when the client sends a message to the server
 * 3. ws.on('close') is triggered when the client is disconnected from the server
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

function Decrypt(m,key){
  // let m=message.msg;
  // let key =message.key;
  console.log("Message ",m);
  var len=m.length;
  var mat = createArray(key,len);
  for(var i=0;i<key;i++){
    for(var j=0;j<len;j++){
      mat[i][j]='\n';
    }
  }
  
  for(var i=0;i<len;i++){
    var j;
    for(j=0;j<key;j++){
      if(i>=len)break;
      mat[j][i]='*';
      i++;
    }
    j-=2;
    for(j;j>0;j--){
      if(i>=len)break;
      mat[j][i]='*';
      i++;
    }
    i--;
  }
  console.log("matrix: ", mat);
  var k=0;
  for(var i=0;i<key;i++){
    for(var j=0;j<len;j++){
      if(k>=len)break;
      if(mat[i][j]=='*'){
        mat[i][j]=m[k];
        k++;
      }
    }
  }

  let dencrypted="";
  for(var i=0;i<len;i++){
    var j;
    for(j=0;j<key;j++){
      if(i>=len)break;
      dencrypted+=mat[j][i];
      i++;
    }
    j-=2;
    for(j;j>0;j--){
      if(i>=len)break;
      dencrypted+=mat[j][i];
      i++;
    }
    i--;
  }

  // let de ={
  //   msg:dencrypted,
  //   key:key
  // }
  
  console.log("Decrypted ",dencrypted);

  return dencrypted;
}


wss.on("connection", (ws) => {
  console.log("Client connected");

  //first message trigger
  sendMsg();

  ws.on("message", (message) => {
    console.log("\nClient message recieved: " + message);
    let key =3;
    let decrypted= Decrypt(""+message,key);
    console.log(decrypted);
    //message trigger for every message received from client for continuous chat
    sendMsg();
  });

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});

/**
 * @description
 * Method for sending messages to client
 */

const sendMsg = () => {
  //closing the previous readline
  if (rl) rl.close();

  //creating a new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">> ", (msg) => {
    wss.clients.forEach((client) => {
      var key=3;
      var encrypted = Encrypt(message,key);
  
      console.log("encrypted message: "+ encrypted);
      client.send(msg);
    });

    //message trigger for every message sent from server for continuous chat
    sendMsg();
  });
};
