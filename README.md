# Pi Cap Interface
A sampler/looper/rtp-midi interface for the Bareconductive PiCap & Raspberry Pi 
**This currently is not functional!!**

Loads .wav's from memory and USB drive.
Single Playback
Continuous playback (speed set in conf)
Loop playback (with optional volume control)
RTP-Midi out (all credit to RaveloxMidi)

## Requirements

#* Requires [WiringPi](http://wiringpi.com/) (`apt-get install wiringpi`)

#* Requires [Bare Conductive's MPR121 libary for WiringPi](https://github.com/BareConductive/wiringpi-mpr121) (`sudo apt-get install picap`)(`after install don't forget to run "picap-setup"`);

#* Requires [RaveloxMidi](https://github.com/ravelox/pimidi)(`Follow Instructions to Setup`)

[see here for other instructions if it doesn't work](https://www.bareconductive.com/make/setting-up-pi-cap-raspberry-pi/);

## Install / Build

* Clone this repository with `git clone https://github.com/magumbos/PiCapInterface.git`

N.B. must be run as root    

To run at start-up
"sudo nano /etc/rc.local"
add before 'exit 0' "/home/pi/the/location/of/script/run &"
Ctrl+X
Y
Enter
