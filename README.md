![HomeKit Garage](https://github.com/will-lumley/GarageDoorOpener-ESP32/main/GarageDoor.png)

# HomeKit Integrated Garage Door

<div align="center">
    <br/>
    <br/> 

<strong>
    Turn any dumb garage door opener into a full HomeKit accessory for under <em>$22 AUD</em>.
</strong>

<br/><br/> 

<img src="https://img.shields.io/badge/ESP32-Supported-0080ff?logo=espressif&logoColor=white" /> 
<img src="https://img.shields.io/badge/HomeSpan-Ready-44cc11?logo=apple&logoColor=white" /> 
<img src="https://img.shields.io/badge/HomeKit-Compatible-f5b042?logo=apple&logoColor=white" /> 
<img src="https://img.shields.io/badge/License-MIT-blue.svg" /> 
</div>

## 🌟 Overview

This project transforms almost any garage door opener into a local, secure, Siri-enabled smart garage accessory powered by the ESP32 and HomeSpan.
No cloud services.
No subscriptions.
No $250 proprietary garage controller.

Just a small microcontroller, a relay, and a bit of code.

## ✨ Features

🏠 Native HomeKit Accessory — appears as a real Garage Door Opener
🎙️ Siri Commands — “Hey Siri, open the garage”
⚙️ Automations — open on arrival, close on departure
🔒 Fully Local Control — uses Apple’s encrypted HAP protocol
⚡ Reliable Relay Triggering
🚪 Door State Reporting — Opening, Open, Closing, Closed
💻 Custom Firmware Included
🧩 Cheap hardware — ESP32 + relay + buck converter = <$22

## 🚀 Installation

Download the **Arduino IDE** here.
https://www.arduino.cc/en/software/

Once you have the Arduino IDE you will need to install ESP32 support for the IDE.

- Go to File > Preferences (on Windows/Linux) or Arduino IDE > Preferences (on macOS).
- Find the "Additional Boards Manager URLs" field and add `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
- Select the "OK" button
- Go to Tools > Board > Boards Manager
- In the Boards Manager, type "ESP32" into the search bar
- Find "esp32 by Espressif Systems" in the search results
- Click the "Install" button next to it.

Once this is done, open up the `garage-door-opener.ino`, select the ESP32 device in the top toolbar, and press the "Upload" button.