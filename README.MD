# Cubicle Presence Detector - Project Description

My cubicle entrance is behind me, and when I’m listening to music with headphones on, I often can’t detect when someone is trying to get my attention. This usually results in them tapping me on the shoulder or waiting for eye contact, which can be awkward and sometimes startling since I’m not expecting anyone.

This project solves that problem by detecting when someone is present at my cubicle entrance and notifying me instantly.

The system uses an ESP8266 paired with an ultrasonic sensor to monitor the cubicle entrance. When a person is detected, the ESP8266 sends a message to a local server running on my home network (also powered by an ESP8266 using socket communication). The server then immediately notifies both my workstation and my phone.

With this setup, I can acknowledge or speak to the person without them needing to awkwardly wave, tap my shoulder, or wait for visual cues.