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

int snake_len=3,dir_x=0,dir_y=-1;
int score=0;
struct Point snake[20]={
    [0]={.x=3,.y=3},
    [1]={.x=3,.y=4},
    [2]={.x=3,.y=5},
};

unsigned long last_move_time=0;
const unsigned long move_interval = 300;

LedControl lc=LedControl(DIN,CLK,CS,1);

void buffer_to_matrix()
{
    int y=0,x=0;
    for(y=0;y<HEIGHT;y++)
    {
        byte row_data=0x00;
        for(x=0;x<WIDTH;x++){
            int idx=(y*WIDTH)+x;
            if(frame_buffer[idx]>0){
                row_data|=(1<<(7-x));
            }
        }
        lc.setRow(0,y,row_data);
    }
}

void draw_snake_to_buffer(struct Point s[], int len){
    int idx,i=0;
    for(i=0;i<len;i++){
        idx=(s[i].y*WIDTH)+s[i].x;
        frame_buffer[idx]=1;
    }
}

void setup()
{
    lc.shutdown(0,false);
    lc.setIntensity(0,4);
    lc.clearDisplay(0);


    // struct Point food;

    memset(frame_buffer,0,sizeof(frame_buffer));    
    draw_snake_to_buffer(snake,snake_len);
    buffer_to_matrix();
}

void loop()
{

    unsigned long curr_time=millis();

    if(curr_time - last_move_time>=move_interval)
    {
        last_move_time=curr_time;
        int i;
        for(i=snake_len-1;i>0;i--)
        {
            snake[i]=snake[i-1];
        }

        snake[0].x+=dir_x;
        snake[0].y+=dir_y;
        if(snake[0].x<0){
            snake[0].x=WIDTH-1;
        }
        if(snake[0].x>=WIDTH){
            snake[0].x=0;
        }
        if(snake[0].y<0){
            snake[0].y=HEIGHT-1;
        }
        if(snake[0].y>=HEIGHT){
            snake[0].y=0;
        }
    
        memset(frame_buffer,0,sizeof(frame_buffer));
        draw_snake_to_buffer(snake,snake_len);
        buffer_to_matrix();
    }
}