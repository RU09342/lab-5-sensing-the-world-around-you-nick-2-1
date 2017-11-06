# Sensors and Signal Conditioning

## Overview
For this section of the lab to implement the an ADC12 the MSP430FR5994 was used, while implement an ADC10 the MSP430G2553 was used. 
<!--- ====================================================== -->
## Photoresistor

### Description
A photoresister is a variable passive circuit component whose resistance can increase and decrease. In the dark the resistance can increase into the Mohm range, while in the light the restistance can decrease to a couple hundred ohms.

### Schematic
A voltage divide can be created using the photoresister and a 1kohm resistor. As seen in the circuit below the ADC reads the voltage inbetween the two resistors. It then converts it to a value which is then used to calculate the resistance of the photoresister.
<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/PhotoResistor.PNG" width="300"/>
<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/FR5994_PhotoDiode.jpg" width="300"/>

### Conclusion
Finally, once the resistance of the photoresister was found the value was transmitted via UART and displayed on RealTerm. This allowed the resistance to be easily viewed and analyzed.

<!--- ====================================================== -->


## Photodiode

### Description
Photodiodes are devices that convert light into current. When they are in a dark room very small amounts of current will be produced while in a lot of light, big amounts of current will be generated.

### Schematic
In order to calculate the current producted by the photodiode, it must be placed in series with a voltage source, a 1kohm resistor, and ground. As seen in the figure below the ADC will read in the voltage just before the resistor. Then the current can be calculated by dividing the voltage by the value of the resistor. 

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/Photodiode.PNG" width="300"/>

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/PhotoDiode.jpg" width="150"/>


### Conclusion
Finally, once the current of the photodiode was found the value was transmitted via UART and displayed on RealTerm. This allowed the current to be easily viewed and analyzed.
<!--- ====================================================== -->

## Temperature Sensor

### Description
The temperature sensor is able to vary its output voltage depending on the temperature in a room. When the temperature is cooler the lower the voltage, when the room is warmer the higher the voltage will be. 
### Schematic
The circuit to measure current is simple. The outer pins of the sensor are used to connect to Vcc and ground, while the middle pin outputs the variable voltage. The ADC is connected to the middle pin, converting the voltage to a digital value. This value is then taken and converted to celsius, then celsius can easily be converted to fahrenheit. 
<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/TempSensor.PNG" width="300"/>
<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/Sensors%20and%20Signal%20Conditioning/Assets/FR5994_TempSensor.jpg" width="300"/>


### Conclusion
Finally, once the voltage of the temperature sensor was found the value was transmitted via UART and displayed on RealTerm. This allowed the voltage to be easily viewed and analyzed.
