# MSP430FR2311 PCB Design

## Overview
A PCB is a printed circuit board that decreases that amount of wires and overall size of a circuit. They come in all different sizes and are easy changable. In this lab a two layer MSP430FR2311 breakout board was designed. This board can be used for low power and low frequency designs in a small and compact circuit. The board consists of a few main components, such as capacitors, resistors, header pins, and the MSP430FR2311. The capacitors and resistor help to regulate the power through the board, while the header pins allow for the board to be easily placed in a breadboard.
## Board Schematic
In the image below shows the schematic of the board. It illustrates how the components will be connected in a simple easy to understand fashion.

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/PCB%20Design/Assets/BoardSchematic.PNG" width="300"/>

## 2D Board
The layout of the components on the PCB board can be seen in the two images below. The traces connecting each part measure 0.013", while the entire board measure to be 1.199" wide by 1.127" long.

####Top

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/PCB%20Design/Assets/2DBoard.PNG" width="300"/> 

####Bottom

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/PCB%20Design/Assets/2DBoardBottom.PNG" width="300"/>

## 3D Model
The real world model of the device can be seen below. The components were placed on the top of the board and the header pins placed on the bottom pointing down. Since the PCB will be placed into the bread board this decision allows the MSP430FR2311 chip to be easily seen to distinguish which pin represents which header pin on the board. 

####Top

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/PCB%20Design/Assets/3DBoard.PNG" width="300"/>

####Bottom

<img src="https://github.com/RU09342/lab-5-sensing-the-world-around-you-nick-2-1/blob/master/PCB%20Design/Assets/3DBoardBottom.PNG" width="300"/>
## Bill of Materials

|Part     |Manufacturer Part #|Brand|Value|Sizes|Package      |Unit Price ($)|Website|
|------------|-------------------|-----|-------------------|-------------------|-------------|--------------|----|
|MSP430FR2311|MSP430FR2311IPW16R |TI   | N/A | 0.173" W| Tape and Reel | 0.63 | [Link](https://www.digikey.com/product-detail/en/texas-instruments/MSP430FR2311IPW16R/MSP430FR2311IPW16R-ND/6098078)|
|Resistor |RC0805JR-0747KL    |Yageo| 47k |0.079" L x 0.049" W|Cut Tape     |0.00245       |[Link](https://www.digikey.com/product-detail/en/yageo/RC0805JR-0747KL/311-47KARCT-ND/731283)|
|Capacitor|CC0805KKX5R6BB106  |Yageo|10uF |0.079" L x 0.049" W|Tape and Reel|0.19          |[Link](https://www.digikey.com/product-detail/en/yageo/CC0805KKX5R6BB106/311-1460-2-ND/2833625)|      
|Capacitor|C0805C102K5RACTU   |KEMET|1nF  |0.079" L x 0.049" W|Cut Tape     |0.00784       |[Link](https://www.digikey.com/product-detail/en/kemet/C0805C102K5RACTU/399-1147-1-ND/411422)|
|Capacitor|C0805C104K5RACTU   |KEMET|100nF|0.079" L x 0.049" W|Cut Tape     |0.01012       |[Link](https://www.digikey.com/product-detail/en/kemet/C0805C104K5RACTU/399-1170-1-ND/411445)|
