#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>


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
            switch(frame_buffer[idx]){
                case 1:
                    printf("#");
                    break;
                case 2:
                    printf("o");
                    break;
                case 3:
                    printf("a");
                    break;
                default:
                    printf(".");
                    break;
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

void draw_food_to_buffer(struct Point f){
    int food_idx=(f.y*WIDTH)+f.x;
    frame_buffer[food_idx]=3;
}

int food_collision_check(struct Point s[], int len, struct Point f ){
    int i;
    int food_idx=(f.y*WIDTH)+f.x;
    for(i=0;i<len;i++){
        if(s[i].x==f.x && s[i].y==f.y){
            return 1;
        }
    }
    return 0;
}

void clr(unsigned char *a){
    int i;
    for(i=0;i< WIDTH*HEIGHT;i++){
        *(a+i)=0;
    }
}

void spawn_food(struct Point s[],int len,struct Point *f){
    int i,conflict;
    while(1){
        int tgt_x=rand()%8;
        int tgt_y=rand()%8;
        conflict=0;
        for(i=0;i<len;i++){
            if(s[i].x==tgt_x&&s[i].y==tgt_y){
                conflict=1;
                break;
            }
        }
        if(conflict ==0){
            f->x=tgt_x;
            f->y=tgt_y;
            break;
        }
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
    srand(time(NULL));
    int snake_len=3,dir_x=1,dir_y=0;
    int ch;
    struct Point snake[20]={
        [0]={.x=3,.y=3},
        [1]={.x=3,.y=4},
        [2]={.x=3,.y=5},
    };
    
    struct Point food;
    spawn_food(snake,snake_len,&food);
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


        update_snake_physics(snake,snake_len,dir_x, dir_y);
        if(check_collision(snake,snake_len)==1){
            printf("GAME OVER!");
            break;
        }
        clr(frame_buffer);
        if(food_collision_check(snake,snake_len,food)==1){
            int curr_tail_idx=snake_len-1;
            snake_len++;

            snake[snake_len-1].x=snake[curr_tail_idx].x;
            snake[snake_len-1].y=snake[curr_tail_idx].y;
            spawn_food(snake,snake_len,&food);
        } else {
            draw_food_to_buffer(food);
        }
        draw_snake_to_buffer(snake,snake_len);
        print_buffer();
        Sleep(300);
   }
    return 0;
    
}