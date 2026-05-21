#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define WIDTH 8
#define HEIGHT 8

static unsigned char frame_buffer[WIDTH*HEIGHT];

struct Point {
    int x;
    int y;
};

void print_buffer(void){
    int x,y;
    for(y=0;y<HEIGHT;y++){
        for(x=0;x<WIDTH;x++){
            int idx=(y*WIDTH)+x;
            if(frame_buffer[idx]==2){
                printf("0");
            } else if(frame_buffer[idx]==1){
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
};

void update_snake_physics(struct Point s[],int len, int dir_x,int dir_y){
    int i;
    for(i=len-1;i>=1;i--){
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    s[0].x=s[0].x+dir_x;
    s[0].y=s[0].y+dir_y;
}

void draw_snake_to_buffer(struct Point s[], int len){
    int idx,i;
    for(i=0;i<len;i++){
        idx=(s[i].y*WIDTH)+s[i].x;
        if(i==0){
            frame_buffer[idx]=2;
        }
        else {
            frame_buffer[idx]=1;
        }
    }
}

void clr(unsigned char *a){
    int i;
    for(i=0;i< WIDTH*HEIGHT;i++){
        *(a+i)=0;
    }
}

int check_collision(struct Point s[], int len){
    int i;

    if(s[0].x<0 || s[0].x>7 || s[0].y<0 || s[0].y>7){
        return 1;
    }

    for(i=1;i<len;i++){
        if(s[0].x==s[i].x && s[0].y==s[i].y){
            return 1;
        }
    }
    return 0;
}

int main(){
    int snake_len=3,dir_x=1,dir_y=0;
    int ch;
    struct Point snake[20]={
        [0]={.x=3,.y=3},
        [1]={.x=3,.y=4},
        [2]={.x=3,.y=5},
    };
    
    while(1){
        if(kbhit()){
            ch=getch();
            switch(ch){
                case 119: //w
                    dir_x = 0; 
                    dir_y = -1;
                    break;

                case 97: //a
                    dir_x = -1; 
                    dir_y = 0;
                    break;
                    
                case 115: //s
                    dir_x = 0; 
                    dir_y = 1;
                    break;
                    
                case 100: //d
                    dir_x = 1; 
                    dir_y = 0;
                    break;
                    
                default:
                    break;
            }
        }
        if(check_collision(snake,snake_len)==1){
            printf("GAME OVER!");
            break;
        }
        update_snake_physics(snake,snake_len,dir_x, dir_y);
        clr(frame_buffer);
        draw_snake_to_buffer(snake,snake_len);
        print_buffer();
        Sleep(300);
   }
    return 0;
    
}