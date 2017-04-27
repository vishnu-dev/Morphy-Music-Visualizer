#include "headers.h"
#include "lodepng/lodepng.h"
#include "lodepng/lodepng.cpp"

using namespace std;

vector<int> ampdb(0);
vector<int> frequency(0);
vector<unsigned char> logo;

//SFML global declarations for seeking play time
sf::SoundBuffer buffer;
sf::Sound sound(buffer);
int flag=0,temp=0;
int W,H;
typedef unsigned long long timestamp_t;
int j=0;
float r=20.0;  //circle "r"
float d=0.3;     //cuboid width/2
float deg=30.0;
double SAMPLE_COUNT;
double SAMPLE_RATE;
kiss_fft_cpx in[N], out[N];
int styleselect=0;
int NO_STYLE=3;

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
    W=w;
    H=h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,(float)w/(float)h, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawStrokeText(char*str,int x,int y,int z)
{
	  char *c;
	  float wt = glutStrokeLength(GLUT_STROKE_ROMAN,(unsigned char*)str)*0.4;
	  glPushMatrix();
	  glTranslatef(-(wt/2), y+8,z);
	  glScalef(0.4f,0.4f,0.4f);

	  for (c=str; *c !=0 /*NULL*/; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}

void instructText(char*str,int x,int y,int z)
{
	  char *c;
	  float wt = glutStrokeLength(GLUT_STROKE_ROMAN,(unsigned char*)str)*0.1;
	  glPushMatrix();
	  glTranslatef(-wt/2, y+8,z);
	  glScalef(0.1f,0.1f,0.1f);

	  for (c=str; *c != 0 /*NULL*/ ; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
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

void processKeys(unsigned char key, int x, int y) {

      if (key == 27) // escape key
            exit(0);
      else if(key == 32) // spacebar key
      {
        if(temp==0){
            flag=1;
            temp++;
            sound.play();
        }
        else if(temp==1){
            sound.pause();
            temp--;
        }
    }
}

void processSpecialKeys(int key, int x, int y)
{
      switch(key) {
            case GLUT_KEY_LEFT:
                if(styleselect==0){
                    styleselect=NO_STYLE-1;
                }
                else{
                    styleselect--;
                }
                break;
            case GLUT_KEY_RIGHT:
                styleselect=(styleselect+1)%NO_STYLE;
                break;
      }
}

void idle()
{
    //Sleep(100);
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clears display with buffer color & depth values set in init()
    //circle
    glLoadIdentity();  //Loads identity matrix for each iteration of display
    //circle3d();
    glColor3f(0,1,0);

    if(flag==0){
        glRasterPos3f(-180,-125,-500);
        glDrawPixels(250,250,GL_RGBA,GL_UNSIGNED_BYTE,&logo[0]);
        drawStrokeText((char *)"MORPHY",-100,125,-200);
        instructText((char *)"Press space to continue!",-75,-100,-200);
    }
    else{
        glClearColor(0,0,0,0);
        if(temp==1){
            if(styleselect==0){
                circle3d();
            }
            else if(styleselect==1){
                bars();
            }
            else if(styleselect==2){
                dust();
            }
        }
        else{
            instructText((char *)"Paused!",-75,-100,-200);
        }
    }
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

void loadlogo(){
    int error;
    unsigned width = 250;
    unsigned height = 250;
    const char* name = "logo.png";
    if((error=lodepng::decode(logo,width,height,name))){
            printf("Error %s",lodepng_error_text(error));
            exit(0);
    }
}

int main(int argc, char *argv[])
{
    loadlogo();    //SFML usage error
    if (argc < 2)
    {
        std::cout << "Usage: wave_iteration <FILENAME>" << std::endl;
        return 1;
    }

    if (!buffer.loadFromFile(argv[1]))
        return 0;
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

    int i;
    int graph[N / 2];
    double mag[N / 2];
    double sf = buffer.getSampleRate();
    double roof = buffer.getSampleCount();
    double framePointer = 0;
    std::vector<double> data;
    auto array1 = buffer.getSamples();
    for (int i = 0; i < (int)buffer.getSampleCount(); i++)
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

            /*
            Frequency_Range	Frequency_Values
            Sub-bass	    20 to 60 Hz
            Bass	        60 to 250 Hz
            Low midrange	250 to 500 Hz
            Midrange	    500 Hz to 2 kHz
            Upper midrange	2 to 4 kHz
            Presence	    4 to 6 kHz
            Brilliance	    6 to 20 kHz
            */

            if (f<=60){
                val = graph[i] = abs( (float)(log(mag[i]) * 10)/9.0);
            }
            else if (f>60 && f<=250){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/8.0);
            }
            else if (f>250 && f<=500){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/7.0);
            }
            else if (f>500 && f<=2000){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/6.0);
            }
            else if (f>2000 && f<=4000){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/5.0);
            }
            else if (f>4000 && f<=6000){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/4.0);
            }
            else if (f>6000 && f<=20000){
                val = graph[i] = abs((float)(log(mag[i]) * 10)/3.5);
            }
            else{
                val = graph[i] = abs((float)(log(mag[i]) * 10)/2.0);
            }

            //std::cout<<"amp: "<<val<<" freq: "<<f<<std::endl;
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
                if(k>(int)ampdb.size()){
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
            {
                temp[j]/=cnt[j];
            }
            avgarr.push_back(temp);
    }

    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH|GL_MULTISAMPLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Morphy");
    glutKeyboardFunc( processKeys );
    glutSpecialFunc( processSpecialKeys );

    //st=time(NULL);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;

}

