#include "dbscan.h"

static void *data;
static int *data_class;
static int data_length;
static size_t data_size;
static get_distance_t get_distance;

static int get_neighbouring(float _radius, void *center, int *data_neighbouring);

static int get_all_neighboring(float _radius, int _min_pts, int *data_neighbouring);

extern void dbscan_init(void *_data, int *_data_class, int _data_length, size_t _size, get_distance_t get_dis) {
    data = _data;
    data_class = _data_class;
    data_length = _data_length;
    data_size = _size;
    get_distance = get_dis;
    memset(_data_class, 0, sizeof(int) * _data_length);
}

extern void dbscan_run(int _min_pts, float _radius) {
    int loop_i = 0, loop_class = 0, *data_neighbouring = (int *)malloc(sizeof(int) * data_length);
    while(loop_i < data_length) {
        if(data_class[loop_i]) {
            loop_i++;
            continue;
        }
        memset(data_neighbouring, 0, sizeof(int) * data_length);
        if(get_neighbouring(_radius, data + data_size * loop_i, data_neighbouring) >= _min_pts) {
            loop_class++;
            get_all_neighboring(_radius, _min_pts, data_neighbouring);
            for(int loop_j = 0; loop_j < data_length; ++loop_j) {
                if(data_neighbouring[loop_j]) data_class[loop_j] = loop_class;
            }
        }
        loop_i++;
    }
    free(data_neighbouring);
}

extern void dbscan_destroy() {
    //free(data_neighbouring);
}

static int get_neighbouring(float _radius, void *center, int *data_neighbouring) {
    int result = -1;
    for(int loop_i = 0; loop_i < data_length; ++loop_i) {
        if((*get_distance)(center, data + data_size * loop_i) <= _radius) {
            result++;
            data_neighbouring[loop_i] = 1;
        }
    }

    return result;
}

static int get_all_neighboring(float _radius, int _min_pts, int *data_neighbouring) {
    int *neighbouring_ququ = (int *) malloc(sizeof(int) * data_length);
    int neighbouring_length = 0;
    int *tmp_neighbouring = (int *) malloc(sizeof(int) * data_length);
    for (int loop_i = 0; loop_i < data_length; ++loop_i) {
        if(data_neighbouring[loop_i]) {
            neighbouring_ququ[neighbouring_length] = loop_i;
            neighbouring_length++;
        }
    }

    for(int loop_i = 0; loop_i < neighbouring_length; ++loop_i) {
        memset(tmp_neighbouring, 0, sizeof(int) * data_length);
        if(get_neighbouring(_radius, data + data_size * neighbouring_ququ[loop_i], tmp_neighbouring) >= _min_pts) {
            for(int loop_j = 0; loop_j < data_length; ++loop_j) {
                if(tmp_neighbouring[loop_j] && !data_class[loop_j] && !data_neighbouring[loop_j]) {
                    neighbouring_ququ[neighbouring_length] = loop_j;
                    ++neighbouring_length;
                    data_neighbouring[loop_j] = 1;
                }
            }
        }
    }
    free(neighbouring_ququ);
    free(tmp_neighbouring);
    return 0;
}