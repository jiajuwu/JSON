/*************************************************************************
    > File Name: mars_rovers.c
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Fri 17 Jun 2016 12:41:54 PM CST
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define bool unsigned char
#define TRUE 1
#define FALSE 0

int x, y;
char rovers[2] = "O";
char final_position[5][5] = {0};
struct path
{
    char name;
    int x;
    int y;
    struct path *next;
};
struct path *head = NULL;
#define len sizeof(struct path)

void safe_flush(FILE *fp)
{
    int ch;
    while((ch = fgetc(fp)) != EOF && ch != '\n');          
}

struct path *find_path_list(char name, int x, int y)
{
    struct path *p1 = NULL;
    p1 = head->next;
    while (NULL != p1) {
        if ((p1->name != name) || (p1->x != x) || (p1->y != y))
            p1 = p1->next;
        else
            return p1;
    }
}

void save_path_list(int x_pos, int y_pos)
{
    struct path *p1 = NULL, *p2 = NULL;
    p2 = head;

    p1 = find_path_list(rovers[0], x_pos, y_pos);
    if (NULL == p1) {
        p1 = (struct path *)malloc(len);
        if (NULL == p1)
            printf("Malloc failed!\n");
        p1->name = rovers[0];
        p1->x = x_pos;
        p1->y = y_pos;
        p1->next = NULL;
        if (NULL == head->next)
            head->next = p1;
        else {
            while (NULL != p2->next)
                p2 = p2->next;
            p2->next = p1;
        }
    }
}

void destory_path_list()
{
    struct path *p1 = NULL, *p2 = NULL;
    p2 = p1 = head;
    while (NULL != p1) {
        p2 = p1->next;
        free(p1);
        p1 = p2;
    }

}

void print_path_list()
{
    struct path *p;
    p = head->next;
    if (NULL == head)
        printf("List is NULL!\n");
    else {
        while(NULL != p) {
            printf("%c %d %d\n", p->name, p->x, p->y);
            p = p->next;
        }
    }
}

void init_list()
{
   head = (struct path *)malloc(len);
   if (NULL == head)
       printf("Malloc failed!\n");
   head->next = NULL;
}

bool print_final_position(int i, int j)
{
    int k;
    char __x[2] = "0", __y[2] = "0";
    for (k = 0; k < 5; k++) {
        __y[0] = final_position[k][2];
        __x[0] = final_position[k][1];
        if (strncmp(&final_position[k][0], "\0", 1) != 0) {
            if ((y - i == atoi(__y)) && (j == atoi(__x))) {
                printf("%c ", final_position[k][0]);
                return TRUE;
            }
        }
    }
    return FALSE;
}

bool isexistence(int x, int y)
{
    int i;
    char __x[2] = "0", __y[2] = "0";
    for (i = 0; i < 5; i++)
    {
        if (strncmp(&final_position[i][0], &rovers[0], 1) == 0) {
            __y[0] = final_position[i][2];
            __x[0] = final_position[i][1];
            if ((atoi(__y) == y) && (atoi(__x) == x))
                return TRUE;
        }
    }
    return FALSE;
}

void print_position(int x_pos, int y_pos)
{
    int i, j;
    bool isprint = FALSE, isexistence = FALSE;
    system("clear");
    for (i = 0; i <= y; i++) {     //i(y)
        for (j = 0; j <= x; j++) { //j(x)
            if ((j == x_pos) && (y - i == y_pos))
                printf("%c ", rovers[0]);
            else {
                isexistence = isexistence(j, y - i);
                if (isexistence == FALSE)
                    isprint = print_final_position(i, j);
                if (isprint == FALSE) printf("%c ", 'O');
            }
        }
        printf("\n");
    }
}

bool judge_rovers_conflict(int x_pos, int y_pos, char *direc)
{
    int i;
    char __x[2] = "0", __y[2] = "0";
    bool isconflict = FALSE;
    for (i = 0; i < 3; i++) {
        __y[0] = final_position[i][2];
        __x[0] = final_position[i][1];
        if (strcmp(direc, "N") == 0) {
            if (i == 0) y_pos++;
            if ((y_pos == atoi(__y)) && (x_pos == atoi(__x))) {
                if ((strcmp(&final_position[i][0], "\0") != 0) && (strncmp(&final_position[i][0], &rovers[0], 1)))
                    isconflict = TRUE;
            }
        }
        if (strcmp(direc, "S") == 0) {
            if(i == 0) y_pos--;
            if ((y_pos == atoi(__y)) && (x_pos == atoi(__x))) {
                if ((strcmp(&final_position[i][0], "\0") != 0) && (strncmp(&final_position[i][0], &rovers[0], 1)))
                    isconflict = TRUE;
            }
        }
        if (strcmp(direc, "W") == 0) {
            if (i == 0) x_pos--;
            if ((y_pos == atoi(__y)) && (x_pos == atoi(__x))) {
                if ((strcmp(&final_position[i][0], "\0") != 0) && (strncmp(&final_position[i][0], &rovers[0], 1)))
                    isconflict = TRUE;
            }
        }
        if (strcmp(direc, "E") == 0) {
            if (i == 0) x_pos++;
            if ((y_pos == atoi(__y)) && (x_pos == atoi(__x))) {
                if ((strcmp(&final_position[i][0], "\0") != 0) && (strncmp(&final_position[i][0], &rovers[0], 1)))
                    isconflict = TRUE;
            }
        }
    }
    return isconflict;
}

bool calculate_position(int *x_pos, int *y_pos, char *direc, char order)
{
    int x_init = *x_pos, y_init = *y_pos;
    int x_tmp = *x_pos, y_tmp = *y_pos;
    bool isconflict = FALSE;
    char dir = *direc;
    if (order == 'M') {
        if (strcmp(direc, "N") == 0) {
            isconflict = judge_rovers_conflict(x_init, y_init, direc);
            if (isconflict == FALSE) y_init++;
            else y_tmp++;
        }
        if (strcmp(direc, "S") == 0) {
            isconflict = judge_rovers_conflict(x_init, y_init, direc);
            if (isconflict == FALSE) y_init--;
            else y_tmp--;
        }
        if (strcmp(direc, "W") == 0) {
            isconflict = judge_rovers_conflict(x_init, y_init, direc);
            if (isconflict == FALSE) x_init--;
            else x_tmp--;
        }
        if (strcmp(direc, "E") == 0) {
            isconflict = judge_rovers_conflict(x_init, y_init, direc);
            if (isconflict == FALSE) x_init++;
            else x_tmp++;
        }
        if (x_init < 0) x_init = x;
        else if (y_init < 0) y_init = y;
        else if (x_init > x) x_init = 0;
        else if (y_init > y) y_init = 0;

        if (FALSE == isconflict) save_path_list(x_init, y_init);
    }
    if (order == 'L') {
        if (strcmp(direc, "N") == 0) dir = 'W';
        if (strcmp(direc, "S") == 0) dir = 'E';
        if (strcmp(direc, "W") == 0) dir = 'S';
        if (strcmp(direc, "E") == 0) dir = 'N';
    }
    if (order == 'R') {
        if (strcmp(direc, "N") == 0) dir = 'E';
        if (strcmp(direc, "S") == 0) dir = 'W';
        if (strcmp(direc, "W") == 0) dir = 'N';
        if (strcmp(direc, "E") == 0) dir = 'S';
    }

    *x_pos = x_init;
    *y_pos = y_init;
    *direc = dir;
    sleep(1);
    print_position(x_init, y_init);
    if (isconflict == TRUE) printf("Conflict, There is a obstacle, x = %d, y = %d\n", x_tmp, y_tmp);

    return isconflict;
}

void save_position(char rov, int x_pos, int y_pos, char dire)
{
    int i, time = 0, j;
    bool isfind = FALSE;
    for (i = 0; i < 3; i++) {
        if ((strncmp(&final_position[i][0], &rov, 1) == 0)) {
            time = i;
            isfind = TRUE;
        }
    }
    if (isfind == FALSE) {
        for (i = 0; i < 3; i++) {
            if (strcmp(&final_position[i][0], "\0") == 0) {
                time = i;
                break;
            }
        }
    }
    sprintf(final_position[time], "%c%d%d%c", rov, x_pos, y_pos, dire);
    printf("Final:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            printf("%c", final_position[i][j]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int i, x_position, y_position;
    char direction[2] = "0", order[100] = "0";
    bool isconflict = FALSE;
    scanf("%d %d", &x, &y);
    safe_flush(stdin);
    print_position(0, 0);
    init_list();
    while(1) {
        scanf("%c %d %d %c", rovers, &x_position, &y_position, direction);
        safe_flush(stdin);
        print_position(x_position, y_position);
        save_path_list(x_position, y_position);
        if ((strcmp(rovers, "A") == 0) || (strcmp(rovers, "B") == 0) ||
            (strcmp(rovers, "C") == 0)) {
            scanf("%s", order);
            safe_flush(stdin);
            for (i = 0; i < strlen(order); i++) {
                if (calculate_position(&x_position, &y_position, direction, order[i])) break;
            }
        }
        printf("%c %d %d %c\n", rovers[0], x_position, y_position, direction[0]);
        save_position(rovers[0], x_position, y_position, direction[0]);
        print_path_list(); 
    }

    destory_path_list();
    return 0;
}

