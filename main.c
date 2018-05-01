#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dbscan.h"

float my_get_distance(void *a, void *b) {
    float *fa = a, *fb = b;
    return (*fa-*fb) * (*fa-*fb) + (*(fa + 1)-*(fb + 1)) * (*(fa + 1)-*(fb + 1));
}

int main(int argc, char *argv[]) {
    if(argc < 5) {
        printf(
"arg is not enough.\n"
"usage: ./main input_file output_file radius MinPts\n"
        );
        return 1;
    }
    //MinPts 领域参数 data_length数据长度 储存数据分类
    int MinPts = 0, data_length = 0, *data_class;
    //圆的大小
    float radius, *mdata_array;
    //输入输出文件句柄
    FILE *inputfile, *outputfile;
    MinPts = atoi(argv[4]);
    radius = (atof(argv[3]));
    radius *= radius;
    //读取数据
    inputfile = fopen(argv[1], "rb+");
    if(inputfile == NULL) {
        printf("input file is not exits\n");
        return 1;
    } 
    fscanf(inputfile, "%d", &data_length);
    mdata_array = (float *)malloc(data_length * sizeof(float) * 2);
    data_class = (int *)malloc(data_length * sizeof(int));
    for(int loop_i = 0; loop_i < data_length; ++loop_i) {
        fscanf(inputfile, "%f,%f,%*d", (mdata_array + loop_i* 2), (mdata_array + loop_i* 2 + 1));
    }
    fclose(inputfile);
    dbscan_init(mdata_array, data_class, data_length, sizeof(float) * 2, my_get_distance);
    dbscan_run(MinPts, radius);
    outputfile = fopen(argv[2], "wb+");
    for(int loop_i = 0; loop_i < data_length; ++loop_i) {
        fprintf(outputfile, "%f,%f,%d\n", *(mdata_array + loop_i* 2), *(mdata_array + loop_i* 2 + 1), *(data_class + loop_i));
    }
    fclose(outputfile);
    free(mdata_array);
    free(data_class);
    return 0;
}