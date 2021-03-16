//NOTE: RUN WITH ./download https://misterfifths.github.io/file-dump/curl/big-sequence > big-sequence

# include <stdio.h>
# include <curl/curl.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <errno.h>
# include <error.h>

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res);

    return res;
}

int progress_callback(void *ptr, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    char slow = 0; //SET SLOW TO TRUE TO ENJOY THE PROGRESS BAR ON SMALL DOWNLOADS
    double percent = (dlnow/(double)dltotal*100);
    if(percent != percent){
        percent = 0;
    }
    fprintf(stderr, "\r");
    fflush(stderr);
    fprintf(stderr, "[[");
    for(int i = 0; i < percent; i++){
        fprintf(stderr, "=");
    }
    fprintf(stderr, ">");
    for(int i = 0; i < 100-percent; i++){
        fprintf(stderr, "-");
    }
    fprintf(stderr, "]");
    fprintf(stderr, "[%ld/%ldKib](%lf)",dlnow/8192, dltotal/8192, percent);
    fprintf(stderr, "]");  
    if(slow) msleep(200);
    return 0;
}


size_t fileSize(FILE *f){
    fseek(f, 0L, SEEK_END);
    size_t pos = ftell(f);
    rewind(f);
    return pos;
}

size_t numLines(FILE *f){
    rewind(f);
    size_t fs = fileSize(f);
    size_t i = 0;
    while(ftell(f) < fs){
        char* current = malloc(fs);
        fgets(current,fs,f);
        free(current);
        i++;
    }
    rewind(f);
    return i;
}

void stringify(char* string, FILE *f){
    size_t fs = fileSize(f);
    size_t lines = numLines(f);
    for(int i = 0; i < lines; i++){
        char* line = malloc(fs);
        fgets(line,fs,f);
        string = strcat(string,line);
        free(line);
    }
}

char* download_URL(const char *url){
    CURL *curl = curl_easy_init();
    
    if(curl) {
        FILE *writer = fopen("dlfile","w+");
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, writer);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fprintf(stderr,"\n");
        char *string = malloc(fileSize(writer));
        stringify(string, writer);
        fclose(writer);
        remove("dlfile");
        return string;
    }
    return NULL;
}


int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr,"Insufficient Arguments\n");
        return 22;
    }else if(argc > 2){
        fprintf(stderr,"Too Many Arguments\n");
        return 7;
    }else{
        fprintf(stdout, "%s", download_URL(argv[1]));
    }
    return 0;
}