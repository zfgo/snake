#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/select.h>
#include <termios.h>

#define UNUSED __attribute__((unused))
#define STDIN_FILENO 0
#define NB_DISABLE 0
#define NB_ENABLE 1

int kb_hit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); // STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void kb_nonblock(int state)
{
    struct termios ttystate;

    // get the terminal state 
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE)
    {
        // turn off canonical mode 
        ttystate.c_lflag &= ~ICANON;
        // minimum number of input read. 
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state == NB_DISABLE)
    {
        // turn on canonical mode 
        ttystate.c_lflag |= ICANON;
    }
    // set terminal attributes 
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

bool process_input()
{
    char c = fgetc(stdin);
    switch (c)
    {
        case 'w':
            break;
        case 'a':
            break;
        case 's':
            break;
        case 'd':
            break;
        case 'q':
            return true;
        default:
            break;
    }
    return false;
}


int main(UNUSED int argc, UNUSED char *argv[])
{
    char c;
    bool quit_game = false;
    int i = 0;

    kb_nonblock(NB_ENABLE);

    while (!quit_game)
    {
        if (kb_hit() != 0)
        {
            quit_game = process_input();
        }
    }
    /*
    while (!i)
    {
        usleep(1);
        i = kb_hit();
        if (i != 0)
        {
            c = fgetc(stdin);
            system("clear");
            printf("the previously printed character: %c ", c);
            if (c == 'q')
                i = 1;
            else 
                i = 0;
        }

        // fprintf(stderr, "%d ", i);
    }
    printf("\nyou hit %c\n", c);
    */
    kb_nonblock(NB_DISABLE);

    return 0;
}
