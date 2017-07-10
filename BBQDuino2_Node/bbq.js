// https://www.safaribooksonline.com/blog/2013/07/25/an-arduino-powered-bbq-thermometer/
// resistors required 18k Ohm and 180k Ohm
var j5 = require("johnny-five");
var app = require('express')();

var board = new j5.Board();
var LEDPIN = 8;
var THMPIN = "A0";

board.on("ready", function(){
  var led = new j5.Led(LEDPIN);
  var thm = new j5.Sensor({ pin: THMPIN, freq: 1000 });

  var alertTemperatureF = 135;
  var currentTemp;
  
    thm.on("change",  function(thmVoltage){
      currentTemp = convertVoltToTemp(thmVoltage);

        if (currentTemp.tempF  >= alertTemperatureF) {
          led.on(500);
        } else {
          led.off(500);
        }

      console.log("Current TempF: ", currentTemp.tempF);

    });


});

function convertVoltToTemp(volt){
  var tempK, tempC, tempF;

  // get the Kelvin temperature
  tempK = Math.log(((10240000/volt) - 10000));
  tempK = 1 / (0.001129148 + (0.000234125 * tempK) + (0.0000000876741 * tempK * tempK * tempK));

  // convert to Celsius and round to 1 decimal place
  tempC = tempK - 273.15;
  tempC = Math.round(tempC*10)/10;

  // get the Fahrenheit temperature, rounded
  tempF = (tempC * 1.8) + 32;
  tempF = Math.round(tempF*10)/10;

  // return all three temperature scales
  return {
    tempK: tempK,
    tempC: tempC,
    tempF: tempF
  };
};

app.listen(3000, function () {
  console.log('Example app listening on port 3000');
});