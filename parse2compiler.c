#include "iob-cfg2versat.h"





void parseDarknet(char* filename)
{
    network *net=NULL;
    int workspace_size=0;
    //FILE* yoloc=fopen("../YOLOLite/src/yolo.c","w");
    FILE* yoloc=fopen("./yolo.c","w");
    fprintf(yoloc,"#include \"../include/darknet.h\"\n");
    net=parse_network_cfg(filename);
    fprintf(yoloc,"#define NET_H %d\n",net->h);
    fprintf(yoloc,"#define NET_W %d\n",net->w);
    fprintf(yoloc,"#define NET_C %d\n",net->c);
    fprintf(yoloc,"#define N_LAYERS %d\n",net->n);
    fprintf(yoloc,"layer g_layers[N_LAYERS]={0};\n");
    printf("DBG:*** Printing all internal arrays for this Darknet Model***\n");
    for(int i=0;i<net->n-1;i++)
    {
        layer cur=net->layers[i];
        fprintf(yoloc,"/*Layer %d",i);
        if (cur.workspace_size > workspace_size) workspace_size = cur.workspace_size;
        switch (cur.type)
        {
        case CONVOLUTIONAL:write_convolutional_layer(yoloc,i,cur);
            break;
        case CONNECTED:write_connected_layer(yoloc,i,cur);
            break;
        case MAXPOOL:write_maxpool_layer(yoloc,i,cur);
            break;
        case DROPOUT:write_dropout_layer(yoloc,i,cur);
            break;
        case SOFTMAX:write_softmax_layer(yoloc,i,cur);
            break;
        case AVGPOOL:write_avgpool_layer(yoloc,i,cur);
            break;
        case SHORTCUT:write_shortcut_layer(yoloc,i,cur);
            break;
        case ROUTE:write_route_layer(yoloc,i,cur);
            break;
        case RNN:write_rnn_layer(yoloc,i,cur);
            break;
        case YOLO:write_yolo_layer(yoloc,i,cur);
            break;
        case UPSAMPLE:write_upsample_layer(yoloc,i,cur);
            break;
        // Other layers needed to be adressed
        case GRU:
        case CROP:
        case REGION:
        case DETECTION:
        case COST:
        default:    printf("\nThis layer is not yet supported.Bye!\n");
                    exit(0);
            break;
        }
    }
    fprintf(yoloc,"\n#define WORKSPACE_SIZE %d\n",workspace_size);
    fprintf(yoloc,"fixed_t g_workspace[WORKSPACE_SIZE]={0}\n"); 
    fprintf(yoloc,"network g_network = {\n  .w= NET_W,\n    .h = NET_H,\n   .c = NET_C,\n    .workspace=g_workspace,\n  .input = NULL,\n    .output = NULL,\n   .layers=g_layers\n};\n");

    fclose(yoloc);
    free_network(net);
    printf("DBG:*** Finished Printing all Internal Arrays***\n");

}
