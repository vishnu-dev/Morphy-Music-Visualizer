# Morphy

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

### How to run?
1. Download release from [here](https://github.com/vishnu-dev/Morphy/releases/latest).
2. Extract the zip.
3. Open command prompt in that directory and run the following command
```
Morphy.exe <FILENAME>
```
_NOTE : Make sure you provide an audio file format that is supported_ 

***

### LICENSE
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

