#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <vector>
#include <algorithm>    // std::sort
#include <SFML/Audio.hpp>
#include <chrono>
#include <array>
#include <sys/time.h>
#include "kissfft/kiss_fft.h"
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif
#define N 1024
//#define N 8192

std::vector<int> ampdb(0);
std::vector<int> frequency(0);

using namespace std;
double bin[2][60]={0.0};
int j=0,seq=0;
float r=20.0;  //circle "r"
float d=0.8;     //cuboid width/2
time_t st,et;
int jstart,jend;
float deg=30.0;
vector< array<double,60> > avgarr; //for average value
double SAMPLE_COUNT;
double SAMPLE_RATE;

//SFML global declarations for seeking play time
sf::SoundBuffer buffer;
sf::Sound sound(buffer);

kiss_fft_cpx in[N], out[N];

typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

void getFft(const kiss_fft_cpx in[N], kiss_fft_cpx out[N])
{
    kiss_fft_cfg cfg;
    if ((cfg = kiss_fft_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
    {
        size_t i;
        kiss_fft(cfg, in, out);
        free(cfg);
    }
    else
    {
        printf("not enough memory?\n");
        exit(-1);
    }

}
/** print vector **/
void print_vec(const std::vector<int> vec)
{
    for (auto x : vec)
    {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/(float)h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void circle3d()
{
    glTranslatef(0,0,-50.0);  //Translation motion along(x,y,z) axis
    //rotation after translation (order matters)
    glRotatef(deg,1,0,0);  //(degree, x,y,z);
    //deg+=1.5;
    glPointSize(10.0);
    glColor3f(1,0,1);
    float deg=0.0;
    jstart=j;
    for(int i=0; i<60; i++)
    {
        if(avgarr.size()<=j)
            exit(0);
        float x=r*cos(deg*(3.14/180)),y=avgarr[j][i],z=r*sin(deg*(3.14/180));
        //float x=30-i,y=avgarr[j][i],z=-2;
        //end of music data
        glBegin(GL_QUADS);
        //top
        glColor3f(1,1,0);
        glVertex3f(x-d,y,z+d); //-x,y,z
        glColor3f(1,1,1);
        glVertex3f(x+d,y,z+d); //x,y,z
        glColor3f(1,0,1);
        glVertex3f(x+d,y,z-d); //x,y,-z
        glColor3f(1,0,0);
        glVertex3f(x-d,y,z-d); //-x,y,-z

        //bottom
        glColor3f(0,1,0);
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glColor3f(0,1,1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(0,0,1);
        glVertex3f(x+d,0,z-d); //x,y=0,-z
        glColor3f(0,1,1);
        glVertex3f(x-d,0,z-d); //-x,y=0,-z

        //left
        glColor3f(0,1,0);
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glColor3f(0,1,1);
        glVertex3f(x-d,0,z-d); //-x,y=0,-z
        glColor3f(1,0,0);
        glVertex3f(x-d,y,z-d); //-x,y,-z
        glColor3f(1,1,0);
        glVertex3f(x-d,y,z+d); //-x,y,z

        //right
        glColor3f(0,1,1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(0,0,1);
        glVertex3f(x+d,0,z-d); //x,y=0,-z
        glColor3f(1,0,1);
        glVertex3f(x+d,y,z-d); //x,y,-z
        glColor3f(1,1,1);
        glVertex3f(x+d,y,z+d); //x,y,z

        //front
        glColor3f(0,1,1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(1,1,1);
        glVertex3f(x+d,y,z+d); //x,y,z
        glColor3f(1,1,0);
        glVertex3f(x-d,y,z+d); //-x,y,z
        glColor3f(0,1,0);
        glVertex3f(x-d,0,z+d); //-x,y=0,z

        //back
        glColor3f(0,0,1);
        glVertex3f(x+d,0,z-d); //x,y=0,z
        glColor3f(1,0,1);
        glVertex3f(x+d,y,z-d); //x,y,z
        glColor3f(1,0,0);
        glVertex3f(x-d,y,z-d); //-x,y,z
        glColor3f(0,1,1);
        glVertex3f(x-d,0,z-d); //-x,y=0,z
        glEnd();
        deg+=6;
        //deg+=5.625;
    }
    jend=j;
    j++;
    Sleep(97);
}

void init()
{
    //sets color buffer bit
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);  //enables DEPTH_TEST
    glDepthFunc(GL_LEQUAL);   //Lesser depth & EQUAL depth valued objects displayed in the front

    //Do anti alias
    glEnable(GL_MULTISAMPLE_3DFX);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POLYGON_SMOOTH);
}
void idle()
{
    glutPostRedisplay();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears display with buffer color & depth values set in init()
    //circle
    glLoadIdentity();  //Loads identity matrix for each iteration of display
    circle3d();
    glutSwapBuffers();
    //if(sound.getPlayingOffset().asSeconds()==buffer.getDuration().asSeconds())
    //    exit(0);
}
int BinSrch(int freq)
{
    int i;
    if(freq<=20||freq>20000)
        return -1;
    freq-=20;
    for(i=0;i<60;i++)
    {
        if(freq>(i*333) && freq<=(i+1)*333)
            break;
    }

    return i;
}
int main(int argc, char *argv[])
{
    //SFML usage error
    if (argc < 2)
    {
        std::cout << "Usage: wave_iteration <FILENAME>" << std::endl;
        return 1;
    }
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(argv[1]))
        return 0;
    sf::Sound sound(buffer);
    //sound.play(); called just before display

    std::cout<<"SampleRate:"<<(SAMPLE_RATE= buffer.getSampleRate())<< std::endl;
    std::cout<<"SampleCount:"<<(SAMPLE_COUNT= buffer.getSampleCount())<< std::endl;
    std::cout<<"SampleCount/2: "<<buffer.getSampleCount()/2<< std::endl;
    std::cout<<"expected no of samples:"<<(((int)(buffer.getSampleCount()/N))*N)/2<<std::endl;
    std::cout<<"channel:"<<buffer.getChannelCount()<<std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"<< std::endl;

    std::vector<int>::iterator it;
    std::vector<int>::iterator f_it;
    it = ampdb.begin();
    f_it = frequency.begin();

    timestamp_t t0 = get_timestamp();

    int i, j, x;
    int graph[N / 2];
    double mag[N / 2];
    double sf = buffer.getSampleRate();
    double roof = buffer.getSampleCount();
    double framePointer = 0;
    std::vector<double> data;
    auto array1 = buffer.getSamples();
    for (int i = 0; i < buffer.getSampleCount(); i++)
    {
        data.push_back((double)array1[i]);
    }

    while (framePointer < roof  )
    {

        for ( i = framePointer, j = 0; i < (framePointer + N) && framePointer < roof - N ; i++, j++  )
        {

            //Apply window function on the sample
            double multiplier = 0.5 * (1 - cos(2 * M_PI * j / (N - 1)));
            in[j].r = multiplier * data[i];
            in[j].i = 0;  //stores N samples
        }
        if (framePointer < roof - N )
        {
            framePointer = i;
        }
        else
        {
            timestamp_t t1 = get_timestamp();
            double secs = (t1 - t0) / 1000000.0L;
            // print_vec(ampdb);
            std::cout << "Total exec time: " << secs << std::endl;
            break;
        }

        //std::cout<<"Framepointer = "<<framePointer<<std::endl;
        getFft(in, out);

        // calculate magnitude of first n/2 FFT
        for (i = 0; i < N / 2; i++ )
        {
            int val,f;
            mag[i] = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
            f = (i*sf)/N;

            // N/2 Log magnitude values.
            //for (i = 0; i < N/2 ; ++i){
            //  x =   10 * log10(mag[i]) ;
            //  printf("  log x= %g ", log(x));
            val = graph[i] = abs((log(mag[i]) * 10)/6);
            //  std::cout<<graph[i]<<std::endl;
            it = ampdb.end();
            f_it = frequency.end();
            it = ampdb.insert(it, val);
            f_it = frequency.insert(f_it,f);
            //std::cout<<"f["<<i<<"]= "<<frequency[i]<<std::endl;
        }

    }
    //std::cout<<array[3]<<std::endl;;
    //print_vec(array);
    std::cout<<"actual no of samples: "<<ampdb.size();
    //std::vector<int>::size_type sz = ampdb.size();

    int k=0;
    for(int i=0;i<(SAMPLE_COUNT)/(SAMPLE_RATE*0.1);i++)
    {
            //cout<<i<<endl<<ampdb.size()<<endl;;
            array <double,60> temp={0};
            int cnt[60]={0};
            for(int j=0;j<(SAMPLE_RATE*0.1)/2;j++)
            {
                int index;
                if(k>ampdb.size()){
                    break;
                }
                if((index=BinSrch(frequency[k]))!=-1)
                {
                    temp[index]+=ampdb[k];
                    cnt[index]++;
                }
                k++;
            }
            for(int j=0;j<60;j++)
                temp[j]/=cnt[j];
            avgarr.push_back(temp);
    }

    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH|GL_MULTISAMPLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(700,10);
    glutCreateWindow("Morphy");

    sound.play();
    st=time(NULL);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;

}

