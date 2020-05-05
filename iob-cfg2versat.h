#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fixed-point.h"
#include "../darknet/include/darknet.h"


#define EMBEDDED 0

void parseDarknet(char* filename);
void parseDarknet(char* filename);

void write_generic_layer(FILE*yoloc,int i,layer darknet_layer);
void write_convolutional_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_convolutional_params(FILE* yoloc,int i,layer darknet_layer);
void write_connected_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_connected_params(FILE* yoloc,int i,layer darknet_layer);
void write_dropout_layer(FILE* yoloc,int i,layer darknet_layer);
void write_softmax_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_softmax_params(FILE* yoloc,int i,layer darknet_layer);
void write_avgpool_layer(FILE* yoloc,int i,layer darknet_layer);
void write_shortcut_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_shortcut_params(FILE* yoloc,int i,layer darknet_layer);
void write_route_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_route_params(FILE* yoloc,int i,layer darknet_layer);
void write_rnn_layer(FILE* yoloc,int i,layer darknet_layer);
void write_yolo_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_yolo_params(FILE* yoloc,int i,layer darknet_layer);
void write_upsample_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_upsample_params(FILE* yoloc,int i,layer darknet_layer);
void write_maxpool_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base);
void write_maxpool_params(FILE* yoloc,int i,layer darknet_layer);