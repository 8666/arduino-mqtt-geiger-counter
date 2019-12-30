# MQTT Geiger counter

You can get all of the components on AliExpress or any similar site. 

1. Geiger counter kit. Search for "diy geiger counter" ( ~30 EUR )
2. Ethernet module W5500.  ( ~3 EUR )
3. Arduino Nano ( ~2 EUR )
4. Jumper wires
5. Stable 5V power supply.

The output pin from the DIY kit is connected to pin 3 on the Arduino



![Alt text](https://raw.githubusercontent.com/8666/arduino-mqtt-geiger-counter/master/photo.jpeg "The kit")

On the photo you can see the geiger counter (right) and a plastic box for the arduino and LAN module (left). Power and LAN cable enter from the left side on the box. All is wall mounted (on a wooden board). The 3 wires between are 5V, GND and DATA.

Be sure to use angood power supply as the measurments will be different with sligtlhy different/variable voltage input. 
Also I added heatshrink over the tube, that should eliminate beta radiation and the red tape just mark the positive side.



**Calibration**

TBD


The geiger coutner kit should be calibrated. There is a potentiometer that should be ajdusted with a small screwdriver. You will need a multimeter to measure the volage on the test point.

Different tubes need different voltage but there is a good chance that the adjustment is already done in factory. Calibration is done without the tube.

1. Trim R100 potentiometer to approximately 50 ohm when kit power is off.
2. Short J4 with a jumper. This will expose the high voltage on J2 point
3. Set your multimeter on 200V DC range.
4. Connect 5V
5. Measure voltage between GND and J2 point

Most likely you will get a kit with J305β tube
The recommended voltsge for it is 350V

For example, adjust voltage with R100 to 6.5V if you use 1M multimeter (internal resistance) or adjust the voltage to 57V if you
use 10M multimeter. This will get you 400V on the tube. Refer to tubes.png for the value that you need

Use formula: Vout=Vread*((60M+Rvoltmeter)/Rvoltmeter.)

Do NOT measure the high voltage directly on the tube 



**Processing data**

MQTT data are processed with Node-Red. I calculate hourly average and check if there is some probelm with the measurments (no new data avaialble)

TBD Post Node-Red flow..



**Publishing the data**


I use https://radmon.org/index.php to publish the data. Looks like the only platform of this kind.

Just join and then you will be able to upload your data. 

The webhook looks like this:

http://radmon.org/radmon.php?function=submit&user=USERNAME&password=PASSWORD&unit=CPM&value=MEASURED

Comparing the data with other people is almost impossible. Different tubes produce different measurments but after a month you will have a good picture about the average background radiation. 
