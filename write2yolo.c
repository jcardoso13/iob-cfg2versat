
#include "iob-cfg2versat.h"


void write_generic_layer(FILE*yoloc,int i,layer darknet_layer)
{
//generic
    fprintf(yoloc,"/*GENERIC PARAMS-Layer %d*/\n",i);
    fprintf(yoloc,"[%d].type=%d,\t\t[%d].activation=%d,\t\t[%d].batch_normalize=%d,\t\t[%d].batch=%d,\n", 
            i, darknet_layer.type,       i, darknet_layer.activation,   i, darknet_layer.batch_normalize,     i, darknet_layer.batch);
        //with nweights
   // fprintf(yoloc,"[%d].inputs=%d,\t\t[%d].outputs=%d,\t\t[%d].nweights=%d,\t\t[%d].n=%d,\n", 
     //       i, darknet_layer.inputs,       i, darknet_layer.outputs,   i, darknet_layer.nweights,   i, darknet_layer.n);
     //without nweights
     fprintf(yoloc,"[%d].inputs=%d,\t\t[%d].outputs=%d,\t\t[%d].n=%d,\n", 
            i, darknet_layer.inputs,       i, darknet_layer.outputs,   i, darknet_layer.n);
   // fprintf(yoloc,"[%d].groups=%d,\n", 
     //       i, darknet_layer.groups);
    fprintf(yoloc,"[%d].h=%d,\t\t[%d].w=%d,\t\t[%d].c=%d,\n", 
            i, darknet_layer.h,     i, darknet_layer.w,   i, darknet_layer.c);
    fprintf(yoloc,"[%d].out_h=%d,\t\t[%d].out_w=%d,\t\t[%d].out_c=%d,\n", 
            i, darknet_layer.out_h,     i, darknet_layer.out_w,   i, darknet_layer.out_c);
    fprintf(yoloc,"[%d].size=%d,\t\t[%d].stride=%d,\t\t[%d].pad=%d,\n", 
            i, darknet_layer.size,     i, darknet_layer.stride,   i, darknet_layer.pad);
    fprintf(yoloc,"[%d].index=%d,\t\t[%d].classes=%d,\t\t[%d].total=%d", 
            i, darknet_layer.index,     i, darknet_layer.classes,   i, darknet_layer.total);

}

void write_convolutional_IO(FILE* yoloc, int i, layer darknet_layer,uint64_t *base)
{
fprintf(yoloc,"/*Layer %d-CONVOLUTIONAL*/\n",i);
//fprintf(yoloc,"fixed_t *output_%d=BASE+%ld, ", i, *base);
fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
*base+=darknet_layer.outputs;

if(darknet_layer.batch_normalize==1)
        {
            //fprintf(yoloc,"*scales_%d=BASE+%ld, ",i,*base);
            fprintf(yoloc,"#define FSCALES_%d BASE+%ld\n",i,*base);
            *base+=darknet_layer.n;
            fprintf(yoloc,"#define FR_MEAN_%d BASE+%ld\n#define FR_VARIANCE_%d BASE+%ld\n",i,*base,i,*base+darknet_layer.n);
            *base+=darknet_layer.n+darknet_layer.n;
        }
fprintf(yoloc,"#define FWEIGHTS_%d BASE+%ld\n#define FBIASES_%d BASE+%ld\n",i,*base,i,*base+darknet_layer.nweights);
*base+=darknet_layer.nweights+darknet_layer.n;
}
void write_convolutional_params(FILE* yoloc,int i,layer darknet_layer)
{
        fprintf(yoloc,"/*Layer %d-CONVOLUTIONAL*/\n",i);
        fprintf(yoloc,"g_layers[%d].forward=forward_convolutional_layer;\n", i);
        if(darknet_layer.batch_normalize==1){
            fprintf(yoloc,"g_layers[%d].scales=&fpvector[FSCALES_%d];\n",i,i);
            fprintf(yoloc,"g_layers[%d].rolling_mean=&fpvector[FR_MEAN_%d];\ng_layers[%d].rolling_variance=&fpvector[FR_VARIANCE_%d];\n",i,i,i,i);
        }
        fprintf(yoloc,"g_layers[%d].weights=&fpvector[FWEIGHTS_%d];\n",i,i);
        fprintf(yoloc,"g_layers[%d].biases=&fpvector[FBIASES_%d];\n",i,i);

}

void write_connected_IO(FILE* yoloc,int i,layer darknet_layer, uint64_t *base)
{       
        fprintf(yoloc,"/*Layer %d-CONNECTED*/\n",i);
        fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
        *base+=darknet_layer.outputs;
        if(darknet_layer.batch_normalize==1)
        {
                fprintf(yoloc,"#define FSCALES_%d BASE+%ld\n",i,*base);
                *base+=darknet_layer.n;
                fprintf(yoloc,"#define FR_MEAN_%d BASE+%ld\n#define FR_VARIANCE_%d BASE+%ld\n",i,*base,i,*base+darknet_layer.n);
                *base+=darknet_layer.n+darknet_layer.n;
        }
        fprintf(yoloc,"#define FR_MEAN_%d BASE+%ld\n#define FR_VARIANCE_%d BASE+%ld\n",i,*base,i,*base+darknet_layer.n);
        *base+=darknet_layer.nweights+darknet_layer.n;
}
void write_connected_params(FILE* yoloc,int i,layer darknet_layer)
{       
        fprintf(yoloc,"/*Layer %d-CONNECTED*/\n",i);
        if(darknet_layer.batch_normalize==1){
            fprintf(yoloc,"g_layers[%d].scales=&fpvector[FSCALES_%d];\n",i,i);
            fprintf(yoloc,"g_layers[%d].rolling_mean=&fpvector[FR_MEAN_%d];\ng_layers[%d].rolling_variance=&fpvector[FR_VARIANCE_%d];\n",i,i,i,i);
        }
        fprintf(yoloc,"g_layers[%d].weights=&fpvector[FWEIGHTS_%d];\n",i,i);
        fprintf(yoloc,"g_layers[%d].biases=&fpvector[FBIASES_%d];\n",i,i);

}
void write_dropout_layer(FILE* yoloc,int i,layer darknet_layer)
{
        fprintf(yoloc,"/*Layer %d-DROPOUT*/\n",i);
}

void write_softmax_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
{
        fprintf(yoloc,"/*Layer %d-SOFTMAX*/\n",i);                   
        fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
        *base+=darknet_layer.n; //perhaps change it!
}
void write_softmax_params(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"/*Layer %d-SOFTMAX*/\n",i);
            fprintf(yoloc,"g_layers[%d].forward=forward_softmax_layer;\n",i);
}

void write_avgpool_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-AVGPOOL*/\n");
}


void write_shortcut_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
{
fprintf(yoloc,"/*Layer %d-SHORTCUT*/\n",i);
fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
*base+=darknet_layer.outputs;
}


void write_shortcut_params(FILE* yoloc,int i,layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-SHORTCUT*/\n",i);
fprintf(yoloc,"g_layers[%d].forward=forward_shortcut_layer;\n", i);
}

void write_route_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
{
int j=0;
fprintf(yoloc,"/*Layer %d-ROUTE*/\n",i);
fprintf(yoloc,"int input_layers_%d[%d]={", i, darknet_layer.n);
for(j=0;j<darknet_layer.n;j++)
{
        if(j==darknet_layer.n-1)
        {
                fprintf(yoloc,"%d},",darknet_layer.input_layers[j]);
        }
        else
        {
                fprintf(yoloc,"%d,",darknet_layer.input_layers[j]);
        }
}
fprintf(yoloc,"input_sizes_%d[%d]={",i,darknet_layer.n);
for(j=0;j<darknet_layer.n;j++)
{
        if(j==darknet_layer.n-1)
        {
                fprintf(yoloc,"%d};\n",darknet_layer.input_sizes[j]);
        }
        else
        {
                fprintf(yoloc,"%d,",darknet_layer.input_sizes[j]);
        }
}
fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
*base+=darknet_layer.outputs;
}

void write_route_params(FILE* yoloc, int i, layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-ROUTE*/\n",i);
fprintf(yoloc,"g_layers[%d].forward=forward_route_layer;\n", i);
fprintf(yoloc,"g_layers[%d].input_layers=input_layers_%d;\ng_layers[%d].input_sizes=input_sizes_%d;\n", i, i, i, i);
}

void write_rnn_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-RNN*/\n");
}

void write_yolo_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
{
        int j=0;
        fixed_t biases=0;
        fprintf(yoloc,"/*Layer %d-YOLO*/\n",i);
        fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
        fprintf(yoloc,"fixed_t biases_%d[%d]={",i, 2*darknet_layer.total);
        for(j=0;j<2*darknet_layer.total-1;j++)
        {
                biases=darknet_layer.biases[j]*FIXED16;
                fprintf(yoloc,"%d,",biases);
        }
        biases=darknet_layer.biases[2*darknet_layer.total-1]*FIXED16;
        *base+=darknet_layer.outputs;
        fprintf(yoloc,"%d};\n",biases);
        fprintf(yoloc,"int mask_%d[%d]={",i,darknet_layer.n);
        for(j=0;j<darknet_layer.n-1;j++)
        {
                fprintf(yoloc,"%d,",darknet_layer.mask[j]);
        }
        fprintf(yoloc,"%d};\n",darknet_layer.mask[darknet_layer.n-1]);
}

void write_yolo_params(FILE* yoloc, int i, layer darknet_layer)
{
        fprintf(yoloc,"/*Layer %d-YOLO*/\n",i);
        fprintf(yoloc,"g_layers[%d].forward=forward_yolo_layer;\n", i);
        fprintf(yoloc,"g_layers[%d].mask=mask_%d;\n", i, i);
        fprintf(yoloc,"g_layers[%d].biases=biases_%d;\n", i, i);
}

void write_upsample_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
        {
        fprintf(yoloc,"/*Layer %d-UPSAMPLE*/\n",i);
        //upsample
        fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
        *base+=darknet_layer.outputs;
}

void write_upsample_params(FILE* yoloc,int i,layer darknet_layer)
        {
        fprintf(yoloc,"/*Layer %d-UPSAMPLE*/\n",i);
        //upsample
        fprintf(yoloc,"g_layers[%d].forward=forward_upsample_layer;\n", i);
}

void write_maxpool_IO(FILE* yoloc,int i,layer darknet_layer,uint64_t *base)
{
        //maxpool
        fprintf(yoloc,"/*Layer %d-MAXPOOL*/\n",i);
        fprintf(yoloc,"#define FOUTPUT_%d BASE+%ld\n",i,*base);
        *base+=darknet_layer.outputs;
}

void write_maxpool_params(FILE* yoloc,int i,layer darknet_layer)
{
        //maxpool
        fprintf(yoloc,"/*Layer %d-MAXPOOL*/\n",i);
        fprintf(yoloc,"g_layers[%d].forward=forward_maxpool_layer;\n", i);


}
