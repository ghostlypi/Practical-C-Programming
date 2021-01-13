#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct{
    int x;
    int y;
} point;

typedef struct{
    point p1;
    point p2;
} line;

double distance(point p1, point p2){
    return sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
}

double length(line l){
    return distance(l.p1, l.p2);
}

double slope(line l){
    return ((double)(l.p2.y-l.p1.y))/((double)(l.p2.x-l.p1.x));
}

bool point_on_line(line l, point p){

    /*
    if(l.p2.x >= p.x && l.p1.x <= p.x){
        if(slope(l)*p.x+l.p1.y == p.y){
            return true;
        }
    }else{
        return false;
    }
    */

    return (l.p2.x >= p.x && l.p1.x <= p.x && slope(l)*p.x+l.p1.y == p.y) ? true : false;
}

int main(size_t argc, char *argv){
    point o = {0,0};
    point p = {1,1};

    line l = {{1,1},{5,7}};

    double d = distance(o,p);

    double len = length(l);

    double s = slope(l);

    line xaxis = {{0,0},{5,0}};

    point onxaxis = {3,0};

    point notonxaxis = {0,3};

    printf("Distance: %lf\n", d);
    printf("Length: %lf\n",len);
    printf("Slope: %lf\n", s);
    printf("On x axis: %d\n", point_on_line(xaxis, onxaxis));
    printf("Not on x axis: %d\n", point_on_line(xaxis, notonxaxis));

    return 0;

}