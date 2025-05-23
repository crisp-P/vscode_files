#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct s_spaceship {
    int x;
    int y;
    char *direction;
}spaceship;

void memory_allocate_check(char *);
void change_direction_right(spaceship *, char change_direction[4][6]);
void change_direction_left(spaceship *, char change_direction[4][6]);
void move_ship(spaceship *);
char *my_spaceship(char *);

int main () {
    
    char *p_coordinates = NULL;
    char param_1[] = "RAARA";
    p_coordinates = my_spaceship(param_1);
    printf("%s", p_coordinates);
    free(p_coordinates);
    return 0;
}

void memory_allocate_check(char *string) {
    if (!string) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void change_direction_right (spaceship *spaceship1 , char change_direction[4][6]) {
    
    if(spaceship1->direction[0] == 'u') {
        
        spaceship1->direction = change_direction[1];
    
    } else if(spaceship1->direction[0] == 'r') {
        
        spaceship1->direction = change_direction[2];
    
    } else if(spaceship1->direction[0] == 'd') {
        
        spaceship1->direction = change_direction[3];

    } else if(spaceship1->direction[0] == 'l'){

        spaceship1->direction = change_direction[0];
    }
    printf("%s\n" , spaceship1->direction);

}

void change_direction_left (spaceship *spaceship1, char change_direction[4][6]) {
    if(spaceship1->direction[0] == 'u') {
        
        spaceship1->direction = change_direction[3];           
    
    } else if(spaceship1->direction[0] == 'l') {
        
        spaceship1->direction = change_direction[2];
    
    } else if(spaceship1->direction[0] == 'd') {
        
        spaceship1->direction = change_direction[1];

    } else if(spaceship1->direction[0] == 'r'){

        spaceship1->direction = change_direction[0];
    }
    printf("%s\n" , spaceship1->direction);
}

void move_ship(spaceship *spaceship1) {

    if(spaceship1->direction[0] == 'u') {
        
        spaceship1->y--;
    
    } else if(spaceship1->direction[0] == 'r') {
        
        spaceship1->x++;
    
    }else if(spaceship1->direction[0] == 'd') {
        
        spaceship1->y++;

    }else if(spaceship1->direction[0] == 'l'){

        spaceship1->x--;
    }
}

char *my_spaceship(char *param_1) {
    
    char *send_coordinates = malloc(100 * sizeof(char));
    memory_allocate_check(send_coordinates);
    send_coordinates[0] = '\0';
    spaceship spaceship1 = {0 , 0 , "up"};
    char change_direction[4][6] = {"up" , "right" , "down" , "left"};
    for(int i = 0; param_1[i] != '\0'; i++) {
        if(param_1[i] == 'R') {
        
            change_direction_right(&spaceship1, change_direction);
        }
        if(param_1[i] == 'L') {

            change_direction_left(&spaceship1, change_direction);
        }
        if(param_1[i] == 'A') {
            move_ship(&spaceship1);
        }
    }
    snprintf(send_coordinates , 100 , "{x: %d, y: %d, direction: '%s'}", spaceship1.x, spaceship1.y, spaceship1.direction);
    
    return send_coordinates;
}

