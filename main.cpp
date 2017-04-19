#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <SFML/Audio.hpp>
#include <chrono>
#include <sys/time.h>
#include "kiss_fft.h"
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif
#define N 2048

std::vector<int> array(0);


using namespace std;

int j=0,seq=0;
float r=15.0;  //circle "r"
float d=0.8;     //cuboid width/2
time_t st,et;
int jstart,jend;
float deg=30.0;
std::vector<double> avgarr; //for average value

//sfml global declarations for seeking play time
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

void print_vec(const std::vector<int> vec)
{
  for (auto x : vec) {
    std::cout << ' ' << x;
  }
  std::cout << '\n';
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(View_angle, Aspect_ratio, Near, Far);
    gluPerspective(60,(float)w/(float)h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
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
    glTranslatef(0,0,-50.0);  //Translation motion along(x,y,z) axis
    //rotation after translation (order matters)
    glRotatef(deg,1,0,0);  //(degree, x,y,z);
    //deg+=1.5;
    glPointSize(10.0);
    glColor3f(1,0,1);
    float deg=0.0;
    jstart=j;
    for(int i=0;i<64;i++)
    {
        float x=r*cos(deg*(3.14/180)),y=avgarr[j++],z=r*sin(deg*(3.14/180));
        // if(y<3){
        //     glColor3f(0,1,0);
        // }
        // else if(y<6){
        //     glColor3f(0,0,1);
        // }
        // else{
        //     glColor3f(1,0,0);
        // }
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
        deg+=5.625;
   }
    jend=j;
    Sleep(100);
//    et=time(NULL);
//    if((et-st)*1000<seq*100+100)
//    {
//        j=jstart;
//    }
//        else
//    {
//        j=jend;
//        seq++;
//    }
    /*
    //Sleep(100);
    // Loop while the sound is playing
    //std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
    if((sound.getPlayingOffset().asSeconds())*1000<seq*100+100)
    {
        j=jstart;
    }
    else
    {
        j=jend;
        seq++;
    }
    */
    glutSwapBuffers();
    //if(sound.getPlayingOffset().asSeconds()==buffer.getDuration().asSeconds())
    //    exit(0);
}

int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    std::cout << "Usage: wave_iteration <FILENAME>" << std::endl;
    return 1;
  }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(argv[1]))
        return 0;

    sf::Sound sound(buffer);
    sound.play();
    st=time(NULL);
    std::cout<<"SampleRate:"<<buffer.getSampleRate()<< std::endl;
    std::cout<<"SampleCount:"<<buffer.getSampleCount()<< std::endl;
    std::cout<<"channel:"<<buffer.getChannelCount()<<std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"<< std::endl;

  std::vector<int>::iterator it;

  it = array.begin();
  timestamp_t t0 = get_timestamp();

  int i, j, x;
  int graph[N / 2];
  double mag[N / 2];
  double roof = buffer.getSampleCount();
  double framePointer = 0;
  std::vector<double> data;
  auto array1 = buffer.getSamples();
  for (int i = 0; i < buffer.getSampleCount(); i++)
  {
    data.push_back((double)array1[i]);
  }

  while (framePointer < roof  ) {

    for ( i = framePointer, j = 0; i < (framePointer + N) && framePointer < roof - N ; i++, j++  )
    {

      //Apply window function on the sample
      double multiplier = 0.5 * (1 - cos(2 * M_PI * j / (N - 1)));
      in[j].r = multiplier * data[i];
      in[j].i = 0;  //stores N samples
    }

    if (framePointer < roof - N ) {
      framePointer = i;

    }
    else {

      timestamp_t t1 = get_timestamp();
      double secs = (t1 - t0) / 1000000.0L;

// print_vec(array);
      std::cout << "Total exec time: " << secs << std::endl;
      break;

    }

//std::cout<<"Framepointer = "<<framePointer<<std::endl;

    getFft(in, out);

// calculate magnitude of first n/2 FFT
    for (i = 0; i < N / 2; i++ ) {
      int val;
      mag[i] = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));


// N/2 Log magnitude values.
//for (i = 0; i < N/2 ; ++i){
//  x =   10 * log10(mag[i]) ;
//  printf("  log x= %g ", log(x));
      val = graph[i] = abs((log(mag[i]) * 10)/4);
//  std::cout<<graph[i]<<std::endl;
      it = array.end();
      it = array.insert(it, val);

    }

  }
//std::cout<<array[3]<<std::endl;;
//print_vec(array);

  std::vector<int>::size_type sz = array.size();

  //average
  double sum=0,cnt=0,maxv=(int)(buffer.getSampleRate()/(10*64));
  int si=0,ei=(int)maxv;
  for (size_t i = 0; i < (int)sz/maxv; i++)
  {
    sum=0;
    for(int j=si;j<ei;j++)
    {
        sum+=array[si];
    }
    avgarr.push_back((sum/(int)maxv)/4);
    si=ei;
    ei=ei+(int)maxv;
    //std::cout <<"display val: "<<avgarr[i] << std::endl;
  }



    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH|GL_MULTISAMPLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(700,10);
    glutCreateWindow("Morphy");


    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;

}
