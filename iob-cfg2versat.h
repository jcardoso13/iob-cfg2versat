#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fixed-point.h"
#include "../darknet/include/darknet.h"


void parseDarknet(char* filename);
void parseDarknet(char* filename);

void write_generic_layer(FILE*yoloc,int i,layer darknet_layer);
void write_convolutional_layer1(FILE* yoloc,int i,layer conv);
void write_convolutional_layer2(FILE* yoloc,int i,layer conv);
int write_connected_layer(FILE* yoloc,int i,layer conv);
int write_dropout_layer(FILE* yoloc,int i,layer conv);
int write_softmax_layer(FILE* yoloc,int i,layer conv);
void write_avgpool_layer(FILE* yoloc,int i,layer conv);
void write_shortcut_layer1(FILE* yoloc,int i,layer conv);
void write_shortcut_layer2(FILE* yoloc,int i,layer conv);
void write_route_layer1(FILE* yoloc,int i,layer conv);
void write_route_layer2(FILE* yoloc,int i,layer conv);
void write_rnn_layer(FILE* yoloc,int i,layer conv);
void write_yolo_layer1(FILE* yoloc,int i,layer conv);
void write_yolo_layer2(FILE* yoloc,int i,layer conv);
void write_upsample_layer1(FILE* yoloc,int i,layer conv);
void write_upsample_layer2(FILE* yoloc,int i,layer conv);
int write_maxpool_layer(FILE* yoloc,int i,layer conv);