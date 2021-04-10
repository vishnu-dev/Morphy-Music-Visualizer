# Morphy

Morphy is a visually and acoustically pleasing music visualizer for Windows and Linux. 

This project was developed during Computer Graphics and Visualizations Lab of our Engineering course in Computer Science.

The project was awarded first place in _JIT Graphics Day - An Intercollegiate Project Exhibition_ for its stellar presentation and applications.

Team: [Himanshu Kumar](https://github.com/Himanshu4746), [Vishnudev K](https://github.com/vishnu-dev)

### Overview
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

### How to run?
#### Windows
1. Download release from [here](https://github.com/vishnu-dev/Morphy/releases/latest).
2. Extract the zip.
3. Open command prompt in that directory and run the following command
```batch
Morphy.exe <FILENAME>
```
_NOTE : Make sure you provide an audio file format that is supported_ 
#### Linux
Refer to [linux branch](https://github.com/vishnu-dev/Morphy-Music-Visualizer/tree/linux) Readme.
***

### LICENSE
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

