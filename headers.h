#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <vector>
#include <array>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <sys/time.h>
#include "kissfft/kiss_fft.h"
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif
#define N 1024

using namespace std;

extern std::vector<int> ampdb;
extern std::vector<int> frequency;

extern int j;
extern float r;  //circle "r"
extern float d;     //cuboid width/2
extern float deg;
extern vector< array<double,60> > avgarr; //for average value
extern double SAMPLE_COUNT;
extern double SAMPLE_RATE;

extern kiss_fft_cpx in[N], out[N];

void circle3d();
void bars();
void dust();
void pentagon();
void CubicalMesh();
void waves();
void mesh3D();
void pausebutton();
void nav();

