#include <stdio.h>

int main(){
    float latitude;
    float longitude;
    char info[80];
    int started = 0;

    puts("[");
    while(scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {
        if(started) 
            printf(",\n");
        else
            started=1;
        if(latitude > 90){
            fprintf(stderr, "Latitude cannot be more than 90. You've entered %f\n", latitude);
            return 1;
        }
        else if(latitude < -90){
            fprintf(stderr,"Latitude cannot be less than -90. You've entered %f\n", latitude);
            return 2;
        }
        if(longitude > 180){
            fprintf(stderr, "Longitude cannot be more than 180. You've put %f\n", longitude);
            return 3;
        }
        else if(longitude < -180){
            fprintf(stderr, "Longitude cannot be less than -180. You've entered %f\n", longitude);
            return 4;
        }
        printf("\t{\n\t\t\"latitude\": %f, \n\t\t\"longitude\": %f, \n\t\t\"info\": \"%s\"\n\t}", latitude, longitude, info);
    }
    puts("\n]");
    return 0;
}