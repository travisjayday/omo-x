# Ocular Monocle X11 (OMo-X)
A 3D wearable VR Headset with Finger Tracking, Night Vision, and Face Recognition. Powered by Raspberry Pi, OpenCV, and Qt. For more information, refer to: <a target="_black" href='https://raw.githubusercontent.com/travisjayday/omo-x/master/screenshots/presentation.jpg'>presentation</a>

<img src='https://github.com/travisjayday/omo-x/blob/master/screenshots/pretty.jpg' width=500/>

# Finger Detection
<img src='https://github.com/travisjayday/omo-x/blob/master/screenshots/fingerdet.jpg' width=1000/>

Finger detection is achieved through infrared (IR) color segmentation. The IR LEDs mounted to the OMo-X illuminate the environment with IR light -- invisible to the human eye, but very visible to the IR camera attached to the OMo-X. So the IR camera picks up the IR light. Thus, objects closer to the camera appear brighter since they reflect more light. The algorithm implemented with OpenCV finds bright areas that could be fingers and then located the tip and moves the mouse pointer accordingly. The above screenshot comes from the omo-x-server as it plays a live video feed from the Raspberry Pi OMo-X. Note: Night vision works by illuminating the entire room / area with IR light by switching on many IR LEDs at the same time.

# Facial Recognition
<img src='https://raw.githubusercontent.com/travisjayday/omo-x/master/screenshots/facerec.jpg' width=1000/>

Facial recognition was implemented with OpenCV. Users can train faces through the Qt Server GUI. Then, when the OMo-X connects to the server, the server can perform real time facial recognition and send face data back to the OMo-X. This process minimizes lag, as the weak Raspberry Pi CPU cannot handle real time facial recognition. 

# Development Process
The omo-x-server was written in Qt Creator on a windows machine, while the OcularOS -- the program that runs on the Raspberry Pi and implements the main features of the OMo-X -- was written in Linux with Qt Creator. Dependencies for both programs include OpenCV. OcularOS also requires RPi GPIO drivers and the CPP Raspicam library to access the RPi camera. 

# Thanks
A thank you to other head set creators like Oculus Rift, Google Glass, and Meta Space Glasses for inspiring me to create my own headset. Going from idea to creation has been a blast, as I had to do so much research, debugging (both hardware & software), installing software, drivers, 3D modelling components and putting it all together in a finished product. The end result is very cool, and I'm glad I pulled it off. 
