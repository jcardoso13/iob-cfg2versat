#include "iob-cfg2versat.h"





void parseDarknet(char* filename)
{
    network *net=NULL;
    int workspace_size=0;
    int outputs=0;
    uint64_t base=0;
    FILE* yoloc=fopen("../darknet-lite/src/yolo.c","w");
    //FILE* yoloc=fopen("./yolo.c","w");
    fprintf(yoloc,"#include \"../include/darknet.h\"\n");
    net=parse_network_cfg(filename);
    fprintf(yoloc,"#define NET_H %d\n",net->h);
    fprintf(yoloc,"#define NET_W %d\n",net->w);
    fprintf(yoloc,"#define NET_C %d\n",net->c);
    fprintf(yoloc,"#define N_LAYERS %d\n",net->n);
    printf("DBG:*** Printing all internal arrays for this Darknet Model***\n");
    for(int i=0;i<net->n;i++)
    {
        layer cur=net->layers[i];
        if (cur.workspace_size > workspace_size) workspace_size = cur.workspace_size;
        if (cur.outputs > outputs) outputs = cur.outputs;
        switch (cur.type)
        {
        case CONVOLUTIONAL:write_convolutional_IO(yoloc,i,cur,&base);
            break;
        case CONNECTED:write_connected_IO(yoloc,i,cur,&base);
            break;
        case MAXPOOL:write_maxpool_IO(yoloc,i,cur,&base);
            break;
        case DROPOUT:write_dropout_layer(yoloc,i,cur);
            break;
        case SOFTMAX:write_softmax_IO(yoloc,i,cur,&base);
            break;
        case AVGPOOL:write_avgpool_layer(yoloc,i,cur);
            break;
        case SHORTCUT:write_shortcut_IO(yoloc,i,cur,&base);
            break;
        case ROUTE:write_route_IO(yoloc,i,cur,&base);
            break;
        case RNN:write_rnn_layer(yoloc,i,cur);
            break;
        case YOLO:write_yolo_IO(yoloc,i,cur,&base);
            break;
        case UPSAMPLE:write_upsample_IO(yoloc,i,cur,&base);
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
    fprintf(yoloc,"layer g_layers[N_LAYERS]={");
    for(int i=0;i<net->n;i++)
    {
        layer cur=net->layers[i];
        write_generic_layer(yoloc,i,cur);
        if(i!=net->n-1)
            fprintf(yoloc,",\n");
    }
    fprintf(yoloc,"};");
    fprintf(yoloc,"\n#define WORKSPACE_SIZE %d\n",workspace_size);
    if(EMBEDDED==1)
    {
        fprintf(yoloc,"#define BASE 0x40000000\n");
    }
    else
    {
        fprintf(yoloc,"#define BASE 0x0\n");
    }
    fprintf(yoloc,"fixed_t fpvector[%ld]={0};",base);
    fprintf(yoloc,"fixed_t g_workspace[WORKSPACE_SIZE]={0};\n");
    fprintf(yoloc,"network g_network = {\n.n=N_LAYERS,\n    .w= NET_W,\n    .h = NET_H,\n   .c = NET_C,\n    .workspace=g_workspace,\n  .input = NULL,\n    .output = NULL,\n   .layers=NULL\n};\n");
    fprintf(yoloc,"void define_layer_mem()\n{\n");
    for(int i=0;i<net->n;i++)
    {
        layer cur=net->layers[i];
        fprintf(yoloc,"\ng_layers[%d].output=&fpvector[FOUTPUT_%d];\n",i,i);
        switch (cur.type)
        {
        case CONVOLUTIONAL:write_convolutional_params(yoloc,i,cur);
            break;
        case CONNECTED:write_connected_params(yoloc,i,cur);
            break;
        case MAXPOOL:write_maxpool_params(yoloc,i,cur);
            break;
        case AVGPOOL:write_avgpool_layer(yoloc,i,cur);
            break;
        case SHORTCUT:write_shortcut_params(yoloc,i,cur);
            break;
        case ROUTE:write_route_params(yoloc,i,cur);
            break;
        case YOLO:write_yolo_params(yoloc,i,cur);
            break;
        case UPSAMPLE:write_upsample_params(yoloc,i,cur);
            break;
        default:    printf("\nThis layer is not yet supported.Bye!\n");
                    exit(0);
            break;
        }
    }
    fprintf(yoloc,"g_network.layers=g_layers;\n");
    fprintf(yoloc,"\n}");
    fclose(yoloc);
    free_network(net);
    printf("DBG:*** Finished Printing all Internal Arrays***\n");

}
