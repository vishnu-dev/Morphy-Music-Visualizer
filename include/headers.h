#ifndef __HEADERS_H
#define __HEADERS_H

#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>     // For searching current directory
#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <array>

#include <SFML/Audio.hpp>
#include <GL/freeglut.h>
#include <kiss_fft.h>
#include <GL/glext.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

#define LOGO_PATH   "./../logo/logo.png"
#define N           1024
#define THREAD_MAX  1

using namespace std;

extern std::vector<int> frequency;
extern std::vector<int> ampdb;

extern int  countr,
            countg,
            countb,
            j;

extern float    r,  /* circle "r" */
                d,     /* cuboid width/2 */
                deg,
                curtime;

extern vector< array<double,60> > avgarr;   // for average value

extern double   SAMPLE_COUNT,
                SAMPLE_RATE;

extern kiss_fft_cpx in[N],
                    out[N];

//void CubicalMesh();
void pausebutton();
void circle3d();
void pentagon();
//void DWaves();
//void mesh3D();
void waves();
void bars();
void dust();
void nav();

#endif
