#include "headers.h"

using namespace std;
vector< array<double,60> > avgarr(0); //for average value

/******************* BARS **********************/
void bars()
{
    glTranslatef(0,-13,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(10.0);

    for(int i=0; i<60; i++)
    {
        if(i<=25)
            glColor3f((i*10)/255.0,1,0);
        else if(i>25 && i<50)
            glColor3f(1,((50-i)*10)/255.0,0);
        else
            glColor3f(1,0,(abs(50-i))*10/255.0);
        if((int)avgarr.size()-2<=j)
            exit(0);
        float x=-60+(i+i),y=avgarr[j][i],z=-4;
        //end of music data
        glBegin(GL_QUADS);
        //top
        glVertex3f(x+d,0,z); //x,y=0,z
        glVertex3f(x+d,y,z); //x,y,z
        glVertex3f(x-d,y,z); //-x,y,z
        glVertex3f(x-d,0,z); //-x,y=0,z
        glEnd();
    }
    //sync
    if( curtime > (j*100+100))
    {
        j++;
    }
}

/******************* CIRCLE3D **********************/
void circle3d()
{
    glTranslatef(0,-10,-56.0);
    //Translation motion along(x,y,z) axis
    //rotation after translation (order matters)
    glRotatef(deg,1,0,0);  //(degree, x,y,z);
    glRotatef(220,0,1,0);
    //deg+=1.5;
    d=0.8;
    glPointSize(10.0);
    float deg=0.0;
    float r1=38/255.0,g1=87/255.0,b1=235/255.0;
    float r2=countr/255.0,g2=countg/255.0,b2=countb/255.0;

    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()-2 <=j)
            exit(0);
        float x=r*cos(deg*(3.14/180)),y=avgarr[j][i],z=r*sin(deg*(3.14/180));
        //end of music data
        {
        glBegin(GL_QUADS);
        //top
        glColor3f(r2,g2,b2);
        glVertex3f(x-d,y,z+d); //-x,y,z
        glVertex3f(x+d,y,z+d); //x,y,z
        glVertex3f(x+d,y,z-d); //x,y,-z
        glVertex3f(x-d,y,z-d); //-x,y,-z

        //bottom
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z-d); //x,y=0,-z
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z-d); //-x,y=0,-z

        //left
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z-d); //-x,y=0,-z
        glColor3f(r2,g2,b2);
        glVertex3f(x-d,y,z-d); //-x,y,-z
        glColor3f(r2,g2,b2);
        glVertex3f(x-d,y,z+d); //-x,y,z

        //right
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z-d); //x,y=0,-z
        glColor3f(r2,g2,b2);
        glVertex3f(x+d,y,z-d); //x,y,-z
        glColor3f(r2,g2,b2);
        glVertex3f(x+d,y,z+d); //x,y,z

        //front
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glColor3f(r2,g2,b2);
        glVertex3f(x+d,y,z+d); //x,y,z
        glColor3f(r2,g2,b2);
        glVertex3f(x-d,y,z+d); //-x,y,z
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z+d); //-x,y=0,z

        //back
        glColor3f(r1,g1,b1);
        glVertex3f(x+d,0,z-d); //x,y=0,z
        glColor3f(r2,g2,b2);
        glVertex3f(x+d,y,z-d); //x,y,z
        glColor3f(r2,g2,b2);
        glVertex3f(x-d,y,z-d); //-x,y,z
        glColor3f(r1,g1,b1);
        glVertex3f(x-d,0,z-d); //-x,y=0,z
        glEnd();
        }
        glLineWidth(0.8);
        {

        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
        //left
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glVertex3f(x-d,0,z-d); //-x,y=0,-z
        glVertex3f(x-d,y,z-d); //-x,y,-z
        glVertex3f(x-d,y,z+d); //-x,y,z
        glEnd();

        //back
        glBegin(GL_LINE_LOOP);
        glVertex3f(x+d,0,z-d); //x,y=0,z
        glVertex3f(x+d,y,z-d); //x,y,z
        glVertex3f(x-d,y,z-d); //-x,y,z
        glVertex3f(x-d,0,z-d); //-x,y=0,z
        glEnd();

        //right
        glBegin(GL_LINE_LOOP);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glVertex3f(x+d,0,z-d); //x,y=0,-z
        glVertex3f(x+d,y,z-d); //x,y,-z
        glVertex3f(x+d,y,z+d); //x,y,z
        glEnd();

        //front
        glBegin(GL_LINE_LOOP);
        glVertex3f(x+d,0,z+d); //x,y=0,z
        glVertex3f(x+d,y,z+d); //x,y,z
        glVertex3f(x-d,y,z+d); //-x,y,z
        glVertex3f(x-d,0,z+d); //-x,y=0,z
        glEnd();

        //top
        glBegin(GL_LINE_LOOP);
        glVertex3f(x-d,y,z+d); //-x,y,z
        glVertex3f(x+d,y,z+d); //x,y,z
        glVertex3f(x+d,y,z-d); //x,y,-z
        glVertex3f(x-d,y,z-d); //-x,y,-z
        glEnd();

        }
        deg+=6;
    }

    //sync
    if( curtime > (j*100+100))
    {
        j++;
    }
}

/******************* PENTAGON **********************/
void pentagon()
{
    glTranslatef(0,0,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(2.0);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()-2<=j)
            exit(0);
        float x=0,r=avgarr[j][i],y=0,z=-4,deg=0;
        //end of music data
        glColor3f((float)(rand()%10)/10,(float)(rand()%10)/10,(float)(rand()%10)/10);
        glBegin(GL_LINE_LOOP);
        for(int c=0; c<5; c++)
        {
            x=r*cos(deg*(3.14/180));
            y=r*sin(deg*(3.14/180));
            glVertex3f(x,y,z);
            deg+=72;
        }
        glEnd();
    }
    if( curtime > (j*100+100))
    {
        j++;
    }
}

/******************* CUBICAL_MESH **********************/
/*
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

        if((int)avgarr.size()-2<=j)
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
    if( curtime > (j*100+100))
    {
        j++;
        //cout<<"arr_sz: "<<(int)avgarr.size()<<" j:"<<j<<" cur time:"<<curtime<<endl;
        //sync++;
    }
}
*/
/******************* DUST **********************/
void dust()
{
    glTranslatef(0,0,-50.0);
    //Translation motion along(x,y,z) axis
    d=0.7;
    glPointSize(2.0);
    glColor3ub(0xFF,0xCA,0x28);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()-2<=j)
            exit(0);
        float x=0,r=avgarr[j][i],y=0,z=-4,deg=0;
        //end of music data
        for(int c=0;c<60;c++)
        {
            x=r*cos(deg*(3.14/180));
            y=r*sin(deg*(3.14/180));
            glBegin(GL_POINTS);
                glVertex3f(x,y,z);
            glEnd();
            deg+=6;
        }
    }
    if( curtime > (j*100+100))
        j++;
}

/******************* WAVES **********************/
void waves()
{
    glTranslatef(0,0,-50.0);
    //Translation motion along(x,y,z) axis
    d=2;
    glPointSize(10.0);
    glColor3ub(0xf9,0x26,0x72);
    for(int i=0; i<60; i++)
    {
        if((int)avgarr.size()-2<=j)
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
    if( curtime > (j*100+100))
    {
        j++;
    }
}

/******************* DWaves **********************/
/*
void DWaves()
{
    glTranslatef(-155,-40,-50.0);
    //Translation motion along(x,y,z) axis
    float deg=60.0;
    //rotation after translation (order matters)
    //+glRotatef(deg,1,0,0);  //(degree, x,y,z);
    //deg+=1.5;
    d=3;
    glPointSize(5.0);
    glColor3f(1,0,1);
    int z=0,x=-5*5*d;
    for(int i=0; i<60; i++)
    {

        if((int)avgarr.size()-2<=j)
            exit(0);
        float y=avgarr[j][i];
        if(i%10==0){
            z-=(5*d);
            x=5*5*d;
        }
        else{
            x+=(5*d);
        }
        //end of music data
        glBegin(GL_POINTS);
            glVertex3f(x+=2,y,z);
        glEnd();
        //deg+=6;
        //deg+=5.625;
    }
    if( curtime > (j*100+100))
    {
        j++;
        //cout<<"arr_sz: "<<(int)avgarr.size()<<" j:"<<j<<" cur time:"<<curtime<<endl;
        //sync++;
    }
//    j++;
//    Sleep(97);
}
*/
/****************** 3D MESH **********************/

//void mesh3D()
//{
//    glTranslatef(0.0,0.0,-4.5);
//    glPointSize(2.0);
//    for(int i=-200; i<=200; i+=5)
//        for(int j=-100; j<=300; j+=10)
//        {
//
//            glBegin(GL_POINTS);
//            glColor3f(0.0f,1.0f,0.0f);
//            glVertex3f( i/100.0,-1.0f, j/100.0);
//            glEnd();
//        }
//    glFlush();
//}

/***************** PAUSE BUTTON *******************/
void pausebutton()
{
    glColor3f(0,128/255.0,128/255.0);
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < 100; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(100);//get the current angle
        float x = 100 * cosf(theta);//calculate the x component
        float y = 100 * sinf(theta);//calculate the y component
        glVertex3f(x, y,-200.0);  //output vertex
    }
    glEnd();
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex3f(-50,-50,-200);
    glVertex3f(-50,50,-200);
    glVertex3f(-25,50,-200);
    glVertex3f(-25,-50,-200);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(25,-50,-200);
    glVertex3f(25,50,-200);
    glVertex3f(50,50,-200);
    glVertex3f(50,-50,-200);
    glEnd();
}

/**************** NAVIGATION *****************/
void nav()
{
    glColor3f(128/255.0,222/255.0,234/255.0);
    glBegin(GL_POLYGON);
    glVertex3f(-275,-50,-200);
    glVertex3f(-275,50,-200);
    glVertex3f(-250,50,-200);
    glVertex3f(-250,-50,-200);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(275,-50,-200);
    glVertex3f(275,50,-200);
    glVertex3f(250,50,-200);
    glVertex3f(250,-50,-200);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(265,0,-200);
    glVertex3f(255,5,-200);
    glVertex3f(255,-5,-200);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-265,0,-200);
    glVertex3f(-255,5,-200);
    glVertex3f(-255,-5,-200);
    glEnd();


}
