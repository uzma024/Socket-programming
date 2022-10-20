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

 function getLocaleDateTimeString() { // date and time
  var timestamp = new Date();
  const offset = timestamp.getTimezoneOffset() * 60000; // milliseconds
  const local = new Date(timestamp.getTime() - offset);
  return (local).toISOString().slice(0, 19).replace("T", " ");
}

function getLocaleDateString() { // date only
  var timestamp = new Date();
  const offset = timestamp.getTimezoneOffset() * 60000; // milliseconds
  const local = new Date(timestamp.getTime() - offset);
  return (local).toISOString().slice(0, 10);
}

function getLocaleTimeString() { // time only
  var timestamp = new Date();
  const offset = timestamp.getTimezoneOffset() * 60000; // milliseconds
  const local = new Date(timestamp.getTime() - offset);
  return (local).toISOString().slice(11, 19);
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
    // var timestamp = new Date().getTime();
    // var timestamp = moment(msg);
    socket.send(msg+"\n sent at: "+getLocaleDateTimeString());

    //message trigger for every message sent from client for continuous chat
    sendMsg();
  });
};