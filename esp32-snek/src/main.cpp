#include <Arduino.h>
#include <LedControl.h>

#define DIN 23
#define CS 5
#define CLK 18

#define WIDTH 8
#define HEIGHT 8

static unsigned char frame_buffer[WIDTH*HEIGHT];

struct Point {
    int x;
    int y;
};

LedControl lc=LedControl(DIN,CLK,CS,1);

void buffer_to_matrix()
{
    int y=0,x=0;
    for(y=0;y<HEIGHT;y++)
    {
        byte row_data=0x00;
        for(x=0;x<HEIGHT;x++){
            int idx=(y*WIDTH)+x;
            if(frame_buffer[idx]>0){
                row_data|=(1<<(7-x));
            }
        }
        lc.setRow(0,y,row_data);
    }
}

void setup()
{
    lc.shutdown(0,false);
    lc.setIntensity(0,4);
    lc.clearDisplay(0);

    memset(frame_buffer,0,sizeof(frame_buffer));
    int idx=(2*WIDTH)+4;
    frame_buffer[idx]=1;

    buffer_to_matrix();
    // lc.setLed(0,0,0,true);
}

void loop()
{

}