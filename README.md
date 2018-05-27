# vcl
Voltage Controlled Light

Created by Itai Asseo // 

The purpose of this code is to support an LED strip that will communicate with a modular synth, and trigger light bursts when receiving gate signals

**features** 
* CV gate signal triggers light to go on
* You can control how long the fade is (from immediate/no fade, to infinite)
* there are 2 ways to control the color:
1. with a potentiometer knob
2. with voltage receiving 0-5v
** to select between the 2 options, there is a switch selector

To see what this looks like, check out this IG post: https://www.instagram.com/p/BiyIKKpAeJm/?taken-by=iiitaiii

**parts**
Arduino (Uno or equvilant)
LED Strip - Analog (I used 2 meters)
3 Mosfet 30v/60a
2 Potentiometers (10k)
2 1/4" mono audio jacks
1 toggle switch
power supply (12v 5A recommended) *for a 2 meter strip 1A should be enough

**instructions** (See diagram image)
1. Connect LED strip to Arduino through the MOSFETS to ports 3,5,6 (B,R,G) - connect the P from LED to the 12v power. Mosfets must also connect to ground.
2. Connect the potentiometers to A4 and A5 (and to the 5v + ground)
3. Connect the jacks to A0 and A1 (and to the 5v + ground)
4. connect the toggle switch to 8
5. Upload code and test

This works best when light is diffused. See pictures/diagrams in this github repo to get an idea how to build it
