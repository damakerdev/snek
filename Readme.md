# snek 
snek is a classic Snake game clone that is made from scratch in pure C. It is basically a arcade snake game engine that i built to get my hands dirty on low level game dev. Stripping away the abstraction layers from code really helped me brush up my low level skills.

** REVIEWER NOTES: I am porting this basic c project to be displayed in an 8x8 Led Matrix module using esp3 ** 

## peek
<img width="276" height="352" alt="image" src="https://github.com/user-attachments/assets/c9c3fd59-0cb8-4a78-85fe-f39ba80ff28f" />
<img width="277" height="295" alt="image" src="https://github.com/user-attachments/assets/260c3e22-6848-4196-817f-c61e8a4c5b04" />


## dev workflow
the development workflow for `snek` was quite simple, simpler than i thought. 

1. firstly, I mapped out a raw 1D array called `frame_buffer` which stores the game's internal spatial grid. and I created some functions to actually render the data in the array in form of a visual grid.
2. I created a structure called Point and made an array of structure for the snek's body. rendered it using the function. 
3. Then, for the movement of the snake I made a function that shifts the coordinates of the snake from front to back on every cycle. 
4. Used conio.h functions like kbht() to detect keyboard clicks for movement of the snake smoothly.
5. Added collisions for checking game over and eventually for the food ( added food as the instance of the same `Poin t` structure)
6. Lastly, did some bug fixes and UI improvements and `snek` was ready!!!

### how to play
- Download the attached `snake.exe` binary below.
- Run it inside Windows terminal or Command prompt for optimal ANSI sequence rendering. ( tried in git bash but didn't work well ).
- Use `W`, `A`, `S`, `D` to navigate.
 
