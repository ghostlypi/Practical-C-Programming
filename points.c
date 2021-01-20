#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    double x;
    double y;
} Point;


double distance(Point p1, Point p2){
    return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}

double perimeter(Point *p,size_t num){
    if(num >= 3){
        double total = 0;
        for(size_t i = 1; i < num; i++){
            total += distance(p[i-1],p[i]);
        }
        return total + distance(p[0],p[num-1]);
    } else {
        return 0;
    }
}

double area(Point *p, size_t num){
    if(num >= 3){
        double sum = 0;
        for(size_t i = 1; i < num; i++){
            sum += (p[i].x+p[i-1].x)*(p[i].y-p[i-1].y);
        }
        return sum/2;
    } else {
        return 0;
    }
}

//This allows you to skip the second number if it is a 0.
//I was processing these with the first single digit number as a value, not the number of points
Point *readPoints(size_t num){
    Point *arr = malloc(sizeof(Point)*num);
    for(size_t i = 0; i <= num; i++){
        char *buffer = malloc(sizeof(char)*255);
        fgets(buffer, sizeof(buffer),stdin);
        if(i != 0){
            bool processed = false;
            double x;
            double y;
            for(int i = 0; i < sizeof(buffer); i++){
                if(buffer[i] == 32){
                    x = buffer[i-1] == 0 ? 0 : buffer[i-1]-48;
                    y = buffer[i+1] == 0 ? 0 : buffer[i+1]-48;
                    processed = true;
                }else if (!processed && buffer[i] == 10){
                    x = buffer[i-1] == 0 ? 0 : buffer[i-1]-48;
                    y = 0;
                }
            }
            Point p = {.x = x,.y = y};
            arr[i-1] = p;
        }
    }
    return arr;
}

void main(size_t argc, char* argv){
    printf("How many points are on your polygon? ");
    size_t num;
    scanf("%lu", &num);

    printf("Enter your points, clockwise or counterclockwise,\none per line, with a space between the x and y coordinates.\n");
    Point *arr = readPoints(num);
    printf("Perimeter: %lf\nArea: %lf\n",perimeter(arr, num),area(arr,num));
}