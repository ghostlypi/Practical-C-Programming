# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

struct point
{
    int x;
    int y;
    int (*getx)(const struct point);
    int (*gety)(const struct point);
};

int get_x(const struct point p)
{
    return p.x;
}

int get_y(const struct point p)
{
    return p.y;
}

int main(void)
{
    struct point p1 = { 2, 4, get_x, get_y};

    printf("x: %d\n", p1.getx(p1));
    printf("x: %d\n", p1.gety(p1));

    return 0;
}