# RaveBeast
Custom single handed gaming keyboard

![kbd](https://github.com/flamepygmy/RaveBeast/blob/main/pictures/fully_assembled.jpg?raw=true)

(Better picture coming soon, when I took the picture I had pulled the thumb keys out so they were hanging
 and the whole thing is a bit out of focus)

Software is licensed under the MIT license. Do whatever you want with it. See LICENSE_FOR_SOFTWARE.txt for details.

The 3D parts and PCB files are licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license. See LICENSE_FOR_MODELS_AND_PCB.txt for the details. If you want to use this for commercial use, contact me on github.

This is a custom 3D printed gaming keyboard for left handed use meant for gaming. I use this as my keyboard when playing Destiny 2.

Files included:
   - PCB schematic files that can be used to order PCBs (I used PCBWay for mine and these files in a zip file were enough for the order)
   - 3D printer files for the parts of the body
   - 3D printer files for custom key caps (but any Cherry MX compatible ones can be used)
   - 3D printing instructions (recommended nozzle diameter, supports, etc.)
   - Source code for the microcontroller (Teensy 4.0)

Extra hardware required:
   - Teensy 4.0 with headers installed (others may work if they are pin compatible and dimensionally equivalent)
   - 23 key switches that are dimensionally compatible with Cherry MX PCB switches (I use Cherry MX Red on mine),
     make sure to get the PCB switches
   - Micro USB cable (will be used for programming and for running it as a USB keyboard)
   - 4x 20mm M3 screws
   - 4x M3 heat set inserts
   - some wiring to connect the 3 thumb controlled keys to the PCB
    
Tools needed:
   - M3 driver
   - solder
   - soldering iron
   - tools for cleaning the 3D prints

## 3D printing instructions

3D printed parts needed:
 - 1x base
 - 1x top
 - 1x wristrest
 - 10x keyhat_10degrees
 - 10x keyhat_20degrees
 - 3x keyhat_neutral (I personally use non-printed key hats for the thumb section)

base:
  - can be printed in various nozzle sizes, printed mine on 0.6
  - no need for supports

top:
  - can be printed in various nozzle sizes, printed mine on 0.6
  - print upside down (top against the build plate)
  - no need for supports

wristrest:
  - can be printed in various nozzle sizes, printed mine on 0.6
  - smaller nozzle size benefits printing the wire holes for the thumb control cherry MX switches more accurately
  - add support for the bottom most cherry MX switch location from build plate,
    may be OK without depending on your printer (no supports needed elsewhere)

keyhats:
  - print with as small nozzle as possible, 0.4 maximum
  - use supports, add cylindrical support blocker around the cylinder that connects to the key switch, (I used 35%-35%-100% scaling in Prusa Slicer)
    otherwise it'll be near impossible to clean the support that gets generated inside the cross

Set the support blocker radius large enough so that it doesn't hug the cylinder with the cross.

You don't want this:

![kbd](https://github.com/flamepygmy/RaveBeast/blob/main/pictures/30_radius_support_blocker.png?raw=true)

This can be still cleaned, but it's annoying to peel what seems like an extra layer on the part that you want to keep.

You want the bottom of the keycap to look like this:

![kbd](https://github.com/flamepygmy/RaveBeast/blob/main/pictures/35_radius_support_blocker.png?raw=true)

## Assembly instructions

The assembly should be fairly straightforward once you have all the parts printed and PCB at hand.

### PCB and wiring preparation

- prepare the PCB by inserting 20 key switches in correct orientation to the top side of the PCB (copyright text on top side), solder the switches on the bottom side

- insert the Teensy 4.0 with headers onto the PCB, solder every pin on the bottom side

- take the 3d printed "base" model, use soldering iron to push in the heat set inserts into place (if unsure, search in internet on how to do it)

- prepare the thumb section wire holes by making sure that they are open and you may need to widen them a little bit for step (5)

- prepare three key switches by soldering wires onto the legs of the key switches (2 wires each), do not trim the wires yet
  and make sure to solder the wire inline with the pin to make the whole thing very narrow so that it still fits through wire holes of the 3d printed part

- put the thumb key wires through the holes in the thumb key section and route the cables underneath

Here is a picture of how the underside of an assembled keyboard looks like:

![kbd](https://github.com/flamepygmy/RaveBeast/blob/main/pictures/cable_routing_bottom.jpg?raw=true)

- align the palm section with the base section, screw holes should align and the cable routing holes should be on the right side and

- continue routing the cables coming from the thumb section through the routing holes on the right side of the base, the wires should
  reach the last larger section and have a little bit of extra room to manouver for soldering

- take the PCB and lay it on top of the base just to see how everything lines up, screw holes should line up and the placement for the
  Teensy 4.0 should be on the top left with it's USB port facing left

- once everything looks right, take one cable coming from each thumb key, peel the cable shielding and and push them all from underside
  of the PCB (top side is the one with the copyright texts) so that they go through the TGND1 hole and come top the top side and then
  solder all 3 wires to TGND1

- similarly to the previous steps, prepare the other wires coming from the thumb section, but this time solder one wire from each key
  switch to T0, T1, and T2
  
- align the PCB to the base so that the screw holes match the heat set inserts

- align the palm section with the heat set inserts as well

- put the top section on top everything and screw everything together with 4 screws, this step may be a little bit tedious

- slap on key caps of your liking (3D printed ones or regular Cherry MX compatible key caps)

Done. Next step is to load the keyboard software to it and it's ready to go. 

## Uploading software to the Teensy

Install Arduino and support for Teensy (4.0).

- Plug in the USB cable to the board
- Under Tools->Board menu select "Teensy 4.0"
- Under Tools->USB Type menu select "Keyboard"
- Under Tools->Port select the correct USB port (with Teensy 4.0 if you have only one, if multiple, consider disconnecting other ones during this)
- Press Sketch->Upload

Code will get compiled and uploaded to the Teensy board after which the keyboard is immediately active.

Note: there is a 1 second delay in the beginning of the code to let everything settle before sampling initial state of the pins.
      No keypresses will be processed during this time, recommend not typing anything during this period.


 
