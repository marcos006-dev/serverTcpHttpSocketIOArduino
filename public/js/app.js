const socket = new io.connect({ port: 8090, rememberTransport: false});

function turnOn() {
  socket.send('1');
  console.log('Mensaje enviado para el socket io: 1');
}

function turnOff() {
  socket.send('0');
  console.log('Mensaje enviado para el socket io: 0');
};

socket.on('message', function(obj){
  console.log(obj.message);
});

socket.on('connect', function(){
  console.log('Cliente web conectado.');
});


socket.on('reconnect', function(){
  console.log('Cliente web reconectado.');
});


socket.on('disconnect', function(){
  console.log('Cliente web desconectado.');
});

jQuery('document').ready(function(){
  jQuery('#btnOn').click(function() { turnOn() });
  jQuery('#btnOff').click(function() { turnOff() });
})
