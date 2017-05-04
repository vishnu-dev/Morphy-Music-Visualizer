#include "headers.h"

using namespace std;

vector< array<double,60> > avgarr(0); //for average value

/******************* BARS **********************/
void bars()
{
    glTranslatef(0,-10,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(10.0);
    glColor3f(1,0,1);
    for(int i=0; i<60; i++)
    {

        if((int)avgarr.size()<=j)
            exit(0);
        float x=-60+(i+i),y=avgarr[j][i],z=-4;
        //end of music data
        glBegin(GL_QUADS);
        //top
        glColor3f(0,1,1);
        glVertex3f(x+d,0,z); //x,y=0,z
        glColor3f(1,1,1);
        glVertex3f(x+d,y,z); //x,y,z
        glColor3f(1,1,0);
        glVertex3f(x-d,y,z); //-x,y,z
        glColor3f(0,1,0);
        glVertex3f(x-d,0,z); //-x,y=0,z
        //bottom
        /*
        glColor3f(0,1,1);
        glVertex3f(x+d,0,z); //x,y=0,z
        glColor3f(1,1,1);
        glVertex3f(x+d,-y,z); //x,y,z
        glColor3f(1,1,0);
        glVertex3f(x-d,-y,z); //-x,y,z
        glColor3f(0,1,0);
        glVertex3f(x-d,0,z); //-x,y=0,z
        */
        glEnd();
    }
    j++;
    Sleep(97);
}

/******************* CIRCLE3D **********************/
void circle3d()
{
    glTranslatef(0,-10,-50.0);
    //Translation motion along(x,y,z) axis
    //rotation after translation (order matters)
    glRotatef(deg,1,0,0);  //(degree, x,y,z);
    //deg+=1.5;
    d=0.8;
    glPointSize(10.0);
    glColor3f(1,0,1);
    float deg=0.0;
    for(int i=0; i<60; i++)
    {

        if((int)avgarr.size()<=j)
            exit(0);
        float x=r*cos(deg*(3.14/180)),y=avgarr[j][i],z=r*sin(deg*(3.14/180));
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
    j++;
    Sleep(97);
}
/******************* PENTAGON **********************/
void pentagon()
{
    glTranslatef(0,-10,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(2.0);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()<=j)
            exit(0);
        float x=0,r=avgarr[j][i],y=0,z=-4,deg=0;
        //end of music data
        glColor3f((float)(rand()%10)/10,(float)(rand()%10)/10,(float)(rand()%10)/10);
        glBegin(GL_LINE_LOOP);
            for(int c=0;c<5;c++)
            {
                x=r*cos(deg*(3.14/180));
                y=r*sin(deg*(3.14/180));
                glVertex2f(x,y);
                deg+=72;
            }
        glEnd();
    }
    j++;
    Sleep(97);
}


/******************* CUBICAL_MESH **********************/
void CubicalMesh()
{
    glTranslatef(-80,0,-50.0);
    //Translation motion along(x,y,z) axis
    float deg=60.0;
    //rotation after translation (order matters)
    glRotatef(deg,1,0,0);  //(degree, x,y,z);
    //deg+=1.5;
    d=3;
    glPointSize(10.0);
    glColor3f(1,0,1);
    int z=0,x=5*2*d;
    for(int i=0; i<60; i++)
    {

        if((int)avgarr.size()<=j)
            exit(0);
        float y=avgarr[j][i];
        if(i%10==0){
            z-=(2*d);
            x=5*2*d;
        }
        else{
            x+=(2*d);
        }
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
        //deg+=6;
        //deg+=5.625;
    }
    j++;
    Sleep(97);
}

/******************* DUST **********************/
void dust()
{
    glTranslatef(0,-10,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(2.0);
    glColor3f(1,0,1);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()<=j)
            exit(0);
        float x=0,r=avgarr[j][i],y=0,z=-4,deg=0;
        //end of music data
        for(int c=0;c<60;c++)
        {
            x=r*cos(deg*(3.14/180));
            y=r*sin(deg*(3.14/180));
            glBegin(GL_POINTS);
                glVertex2f(x,y);
            glEnd();
            deg+=6;
        }
    }
    j++;
    Sleep(97);
}

/******************* WAVES **********************/
void waves()
{
        glTranslatef(0,-10,-50.0);
    //Translation motion along(x,y,z) axis
    d=2;
    glPointSize(10.0);
    glColor3f(1,0,1);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()<=j)
            exit(0);
        float x=-60+(i*d),y=avgarr[j][i],z=-4;
        //end of music data
        glBegin(GL_LINES);
            //lines
            glVertex3f(x-(d/2),0,z);
            glVertex3f(x-(d/4),y,z);
            glVertex3f(x-(d/4),y,z);
            glVertex3f(x+(d/4),-y,z);
            glVertex3f(x+(d/4),-y,z);
            glVertex3f(x+(d/2),0,z);
        glEnd();
    }
    j++;
    Sleep(97);
}
