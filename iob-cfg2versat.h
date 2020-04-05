#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fixed-point.h"
#include "../darknet/include/darknet.h"


void parseDarknet(char* filename);
void parseDarknet(char* filename);

int write_convolutional_layer(FILE* yoloc,int i,layer conv);
int write_connected_layer(FILE* yoloc,int i,layer conv);
int write_dropout_layer(FILE* yoloc,int i,layer conv);
int write_softmax_layer(FILE* yoloc,int i,layer conv);
int write_avgpool_layer(FILE* yoloc,int i,layer conv);
int write_shortcut_layer(FILE* yoloc,int i,layer conv);
int write_route_layer(FILE* yoloc,int i,layer conv);
int write_rnn_layer(FILE* yoloc,int i,layer conv);
int write_yolo_layer(FILE* yoloc,int i,layer conv);
int write_upsample_layer(FILE* yoloc,int i,layer conv);
int write_maxpool_layer(FILE* yoloc,int i,layer conv);