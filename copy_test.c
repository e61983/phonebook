#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    struct timespec start, end;
    double cpu_time1, cpu_time2,cpu_time3,cpu_time4;
    unsigned long TEST_SIZE = 1024;
    if(argc>1)TEST_SIZE = atoi(argv[1])*1024l;
    printf("TEST_SIZE = %ld\n",TEST_SIZE);
    char src[TEST_SIZE];
    memset(src,'a',TEST_SIZE-2);
    src[TEST_SIZE-1]='\0';
    char des[TEST_SIZE];

    /* strcpy test  */
    clock_gettime(CLOCK_REALTIME, &start);
    strcpy(des,src);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    memset(des,0,TEST_SIZE);

    /* strlen cast time */
    clock_gettime(CLOCK_REALTIME, &start);
    int len=strlen(src)+1;
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    memset(des,0,TEST_SIZE);

    /* memcpy test */
    clock_gettime(CLOCK_REALTIME, &start);
    memcpy(des,src,TEST_SIZE);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time3 = diff_in_second(start, end);

    memset(des,0,TEST_SIZE);

    /* memcpy with strlen test */
    clock_gettime(CLOCK_REALTIME, &start);
    memcpy(des,src,strlen(src)+1);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time4 = diff_in_second(start, end);

    FILE *output;
    output = fopen("copy_test.txt", "a");
    fprintf(output, "strcpy() memcpy() %lf %lf\n", cpu_time1, cpu_time3);
    fclose(output);

    printf("execution time of strcpy() : %lf sec\n", cpu_time1);
    printf("execution time of strlen() : %lf sec\n", cpu_time2);
    printf("execution time of memcpy() : %lf sec\n", cpu_time3);
    printf("execution time of memcpy() using strlen(): %lf sec\n", cpu_time4);

    return 0;
}
