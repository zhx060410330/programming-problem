#include <stdio.h>

#define PLAYER_CHECK(status) ((status & 0xF0) >> 4)
#define PLAYER_MOVE(status) (status = status + 0x10)

#define OPPONENT_CHECK(status) (status & 0x0F)
#define OPPONENT_MOVE(status) (status = status + 1)
#define OPPONENT_RESET(status) (status = (status & 0xF0) + 1)

int main(int argc, char *argv[])
{
    /// the first way
    printf ("the first way\n");
    /* the upper 4 bit stands for player status */
    /* the lower 4 bit stands for opponent status */
    char status = 0x11;

    for (; PLAYER_CHECK(status) <= 9; PLAYER_MOVE(status)){
        for (; OPPONENT_CHECK(status) <= 9; OPPONENT_MOVE(status)){
            if (PLAYER_CHECK(status) % 3 != OPPONENT_CHECK(status) % 3){
                printf ("player: %d opponent: %d\n",
                        PLAYER_CHECK(status), OPPONENT_CHECK(status));
            }
        }
        OPPONENT_RESET(status);
    }

    /// the second way
    printf ("the second way\n");
    int state = 1;
    for (; state <= 81; state ++){
        if (state / 9 % 3 != state % 9 % 3){
            printf ("player: %d opponent: %d\n",
                    state / 9 + 1, state % 9 + 1);
        }
    }
    
    return 0;
}
