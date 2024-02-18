const socket = io();

const temperatureDisplay = document.getElementById('temperature');

socket.on('temperature', data => temperatureDisplay.innerHTML = `${data}°C`);