var zeromq = require('zmq');

EdisonZMQPubSubService.prototype.interface = "edison-service-interface";
EdisonZMQPubSubService.prototype.socket = null;
EdisonZMQPubSubService.prototype.receivedMsgHandler = null;

function EdisonZMQPubSubService(serviceDescription) {
    "use strict";
  this.socket = zeromq.socket('pub');
  if (serviceDescription.address) {
    this.socket.bindSync('tcp://' + serviceDescription.address + ':' + serviceDescription.port);
  } else {
    this.socket.bindSync('tcp://*:' + serviceDescription.port);
  }
}

EdisonZMQPubSubService.prototype.sendTo = function (client, msg, context) {

};

EdisonZMQPubSubService.prototype.publish = function (msg, context) {
  "use strict";
  this.socket.send(msg);
};

EdisonZMQPubSubService.prototype.manageClient = function (client, context) {

};

EdisonZMQPubSubService.prototype.setReceivedMessageHandler = function (handler) {

};

EdisonZMQPubSubService.prototype.done = function () {
    this.socket.close();
};

module.exports = EdisonZMQPubSubService;