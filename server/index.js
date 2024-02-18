const { io } = require('socket.io-client')

// const socket = io('http://localhost:3000');
const socket = io('https://remote-temp.fly.dev/');

//conexion
socket.on('ping', () => {
  console.log('conectado a ' +  socket.id)
});

//*Comunicación serial
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const port = new SerialPort({
  path: 'COM4', //puerto del arduino
  baudRate: 9600 //velocidad de transmición
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

parser.on('open', () => console.log('Connection is open'));
port.on('error', (err) => console.log(err.message));
parser.on('data', (data) => {
  console.log(data);
  socket.emit('temp', data);
});

//*data sending emulation
// var data = 0
// setInterval(() => {
//   socket.emit('temp', data++);
// }, 5000);