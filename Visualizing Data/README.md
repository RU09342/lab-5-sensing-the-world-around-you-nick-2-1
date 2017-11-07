# Visualizing Data
#### Nick<sup>2</sup>
In this section, the data gathered on the ADC12 is displayed on various peripherals. The display methods used here is a RGB LED and a LCD display.

## RGB LED
### Description
RGB LEDs have been controlled in the past, but the controller will be sensors instead of UART. 2 sensors were used to control the LED, a temperature sensor, and a photoresistor.
### Temperature Sensor
Using the MSPFR5994, a LM34 external temperature sensor is connected to the ADC, whose output will set the value of the LED colors. The circuit must be wired according to the follwing diagram.

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Visualizing%20Data/Assets/Temp_RGB_Circuit.PNG"  width="300"/>

The LED will change colors as the temperature rises. At the coldest temperature, it glows blue, and gets more red as the temperature. At room temperature, the LED glows purple. The easiest methods to manipulate the sensor is to use a dry ice pack or a hair dryer.
### Photo-Resistor
Using the MSP430F5529, a 10 M&#937; photoresistor is used in a voltage divider. The output of the voltage divider is attached to the ADC input of the MSP430. From there, the resistance is calculated, and used to control the LED. The circiut must be wired according to the following diagram.

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Visualizing%20Data/Assets/Photo_RGB_Circuit.PNG" width ="300"/>

The LED changes colors the same as before, but red indicates lower resistance instead of temperature. A demonstration can be found below as a gif.

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Visualizing%20Data/Assets/LED%20example.gif" width="300"/>

## LCD Display
Having an LED visualize data is nice, but it only provides a reference. LEDs cannot provide absolute values for temperature or brightness, but an LCD can. The MSP430FR6989 has a built in LCD Display, and a driver was provided to display alphanumerical characters on the display. The internal ADC takes the values off of the same setup as the photoresistor, but without the LED. The the voltage gets converted and displayed on the LCD display. An example can be found below.

<img src ="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Visualizing%20Data/Assets/LCD%20example.gif" width="300"/>

As the light source gets closer, the number on the LCD goes up. The number on the LCD represents Lumens, a measurement commonly used to measure the brightness of flashlights. To calibrate the conversion, a series of known flashlights were used, including the flashlight seen in the example. 
