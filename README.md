# MQTT Geiger counter

You can get all of the components on AliExpress or any similar site. 

1. Geiger counter kit. Search for "diy geiger counter" 
2. Ethernet module W5500. 
3. Arduino Nano
4. Jumper wires
5. Stable 5V power supply.

The output pin from the DIY kit is connected to pin 3 on the Arduino



![Alt text](https://raw.githubusercontent.com/8666/arduino-mqtt-geiger-counter/master/photo.jpeg "The kit")

On the photo you can see the geiger counter (right) and a plastic box for the arduino and LAN module on the right. All is wall mounted (on a wooden board). The 3 wires between are 5V, GND and DATA.

Be sure to use good power supply as the measurments will be different with sligtlhy different/variable voltage input. 

The geiger coutnr kit should be calibrated. There is a potentiometer that should be ajdusted with a small screwdriver. Also I added heatshrink over the tube, that should eliminate beta radiation and the red tape just mark the positive side.



**Calibration**

TBD



**Processing data**

MQTT data are processed with Node-Red. I calculate hourly average and check if there is some probelm with the measurments (no new data avaialble)

TBD Post Node-Red  flow



**Publishing the data**


I use https://radmon.org/index.php to publish the data. Looks like the only platform of this kind.

Just join and then you will be able to upload your data. 

The webhook looks like this:

http://radmon.org/radmon.php?function=submit&user=USERNAME&password=PASSWORD&unit=CPM&value=MEASURED

Comparing the data with other people is almost impossible. Different tubes produce different measurments but after a month you will have a good picture about the average background radiation. 
