# Morphy

[![Build Status](https://travis-ci.com/Himanshu4746/Morphy.svg?branch=linux)](https://travis-ci.com/Himanshu4746/Morphy)
[![License](https://img.shields.io/badge/license-MIT%20License-blue.svg)](https://github.com/vishnu-dev/Morphy-Music-Visualizer/blob/master/LICENSE)

### Abstract
Morphy is a simple implementation of audio data visualization. For the given input audio file, program will give amplitude vs frequency plot by performing Fast Fourier Transform(FFT) on the audio samples. Visualization is achieved using OpenGL. This Project is implemented in C++ using OpenGL, LodePNG, SFML & Kiss FFT. User interaction is achieved using keyboard.

### GIFs
![Home Page](/assets/bars.gif)   ![Home Page](/assets/circle3d-2.gif)

![Home Page](/assets/color-pentagon.gif)   ![Home Page](/assets/particle-circle.gif)

### Prerequisities
* SFML
* Freeglut
* KissFFT

***

### Supported audio formats
WAV, OGG/Vorbis and FLAC. Due to licensing issues MP3 is not supported.

***

### How to run on Windows?
1. Download release from [here](https://github.com/vishnu-dev/Morphy/releases/latest).
2. Extract the zip.
3. Open command prompt in that directory and run the following command
```batch
Morphy.exe <FILENAME>
```
_NOTE : Make sure you provide an audio file format that is supported_ 

***

### How to build & run on Linux?
1. ```git clone https://github.com/vishnu-dev/Morphy-Music-Visualizer.git```
2. ```cd ./Morphy-Music-Visualizer/```
3. ```git checkout linux```
4. ```cd ./make/```
5. ```Install Linux Dependencies stated below if needed```
6. ```sudo make install```
7. ```make```
8. ```cd ./../bin/```
9. ```morphy <path/to/wav/ogg/flac/file>```
  #### Linux Dependencies
  1) SFML - [Simple and Fast Multimedia Library](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)
  ```
      sudo apt-get install libsfml-dev
  ```
  2) FreeGLUT - [OpenGL Utility Toolkit](https://stackoverflow.com/questions/11318510/installing-freeglut-on-linux)
  ```
      sudo apt-get install freeglut3-dev
  ```

### LICENSE
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

