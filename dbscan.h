#ifndef __DBSCAN_H
#define __DBSCAN_H 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef float (*get_distance_t)(void *a, void *b);

extern void dbscan_init(void *data, int *data_class, int data_length, size_t size, get_distance_t get_dis);

extern void dbscan_run(int _min_pts, float _radius);

extern void dbscan_destroy();
#endif