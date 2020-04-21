
#include "iob-cfg2versat.h"


void write_generic_layer(FILE*yoloc,int i,layer darknet_layer)
{
//generic
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
    fprintf(yoloc,"[%d].index=%d,\t\t[%d].classes=%d,\t\t[%d].total=%d,\n", 
            i, darknet_layer.index,     i, darknet_layer.classes,   i, darknet_layer.total);

}

void write_convolutional_layer1(FILE* yoloc, int i, layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-CONVOLUTIONAL*/\n",i);
fprintf(yoloc,"fixed_t output_%d[%d]={0}, ", i, darknet_layer.outputs);
if(darknet_layer.batch_normalize==1)
        {
            fprintf(yoloc,"scales_%d[%d]={0}, ",i,darknet_layer.n);
        }
//fprintf(yoloc,"weights_%d[%d]={0}, biases_%d[%d]={0}, mean_%d[%d]={0}, variance_%d[%d]={0}, r_mean_%d[%d]={0}, r_variance_%d[%d]={0};\n"
//,i,darknet_layer.nweights,i, darknet_layer.n,i, darknet_layer.n,i, darknet_layer.n,i, darknet_layer.n,i,darknet_layer.n);
fprintf(yoloc,"weights_%d[%d]={0}, biases_%d[%d]={0}, r_mean_%d[%d]={0}, r_variance_%d[%d]={0};\n"
,i,darknet_layer.nweights,i, darknet_layer.n,i, darknet_layer.n,i,darknet_layer.n);
}
void write_convolutional_layer2(FILE* yoloc,int i,layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-CONVOLUTIONAL*/\n",i);

        fprintf(yoloc,"[%d].forward=forward_convolutional_layer,\n", i);
        fprintf(yoloc,"[%d].mask=0,\n", i);
        fprintf(yoloc,"[%d].input_layers=0,\t\t\t\t[%d].input_sizes=0,\n", i, i);
        fprintf(yoloc,"[%d].biases=biases_%d,\n", i, i);
        fprintf(yoloc,"[%d].weights=weights_%d,\t\t\t\t[%d].output=output_%d,\n", i, i, i, i);
        //fprintf(yoloc,"[%d].mean=mean_%d,\t\t\t\t[%d].variance=variance_%d,\n", i, i, i, i);
        fprintf(yoloc,"[%d].rolling_mean=r_mean_%d,\t\t\t\t[%d].rolling_variance=r_variance_%d", i, i, i, i);
        
        if(darknet_layer.batch_normalize == 1)
            {
            fprintf(yoloc,",[%d].scales=scales_%d", i, i);
            }


}

int write_connected_layer(FILE* yoloc,int i,layer darknet_layer)
{       
        fprintf(yoloc,"-CONNECTED*/\n");

                return 0;
}

int write_dropout_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-DROPOUT*/\n");
                return 0;

}

int write_softmax_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-SOFTMAX*/\n");
                return 0;

}

void write_avgpool_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-AVGPOOL*/\n");
}


void write_shortcut_layer1(FILE* yoloc,int i,layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-SHORTCUT*/\n",i);
fprintf(yoloc,"fixed_t output_%d[%d]={0};\n", i, darknet_layer.outputs);
}


void write_shortcut_layer2(FILE* yoloc,int i,layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-SHORTCUT*/\n",i);
fprintf(yoloc,"[%d].forward=forward_shortcut_layer,\n", i);
fprintf(yoloc,"[%d].output=output_%d", i, i);
}

void write_route_layer1(FILE* yoloc,int i,layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-ROUTE*/\n",i);
fprintf(yoloc,"int input_layers_%d[%d]={0}, input_sizes_%d[%d]={0};\n", i, 2, i, 2);
fprintf(yoloc,"fixed_t output_%d[%d]={0};\n", i, darknet_layer.outputs);
}

void write_route_layer2(FILE* yoloc, int i, layer darknet_layer)
{
fprintf(yoloc,"/*Layer %d-ROUTE*/\n",i);
fprintf(yoloc,"[%d].forward=forward_route_layer,\n", i);
fprintf(yoloc,"[%d].input_layers=input_layers_%d,\t\t\t\t[%d].input_sizes=input_sizes_%d,\n", i, i, i, i);
fprintf(yoloc,"[%d].output=output_%d", i, i);
}

void write_rnn_layer(FILE* yoloc,int i,layer darknet_layer)
{
            fprintf(yoloc,"-RNN*/\n");
}

void write_yolo_layer1(FILE* yoloc,int i,layer darknet_layer)
{
        int j=0;
        fixed_t biases=0;
        fprintf(yoloc,"/*Layer %d-YOLO*/\n",i);
        fprintf(yoloc,"fixed_t output_%d[%d]={0}, biases_%d[%d]={", i, darknet_layer.outputs, i, 2*darknet_layer.total);
        for(j=0;j<darknet_layer.total-1;j++)
        {
                biases=darknet_layer.biases[j]*FIXED16;
                fprintf(yoloc,"%d,",biases);
        }
        biases=darknet_layer.biases[darknet_layer.total-1]*FIXED16;
        fprintf(yoloc,"%d};\n",biases);
        fprintf(yoloc,"int mask_%d[%d]={",i,darknet_layer.n);
        for(j=0;j<darknet_layer.n-1;j++)
        {
                fprintf(yoloc,"%d,",darknet_layer.mask[j]);
        }
        fprintf(yoloc,"%d};\n",darknet_layer.mask[darknet_layer.n-1]);
}

void write_yolo_layer2(FILE* yoloc, int i, layer darknet_layer)
{
        fprintf(yoloc,"/*Layer %d-YOLO*/\n",i);
        fprintf(yoloc,"[%d].forward=forward_yolo_layer,\n", i);
        fprintf(yoloc,"[%d].mask=mask_%d,\n", i, i);
        fprintf(yoloc,"[%d].biases=biases_%d,\n", i, i);
        fprintf(yoloc,"[%d].output=output_%d", i, i);
}

void write_upsample_layer1(FILE* yoloc,int i,layer darknet_layer)
        {
        fprintf(yoloc,"/*Layer %d-UPSAMPLE*/\n",i);
        //upsample
        fprintf(yoloc,"fixed_t output_%d[%d]={0};\n", i, darknet_layer.outputs);
}

void write_upsample_layer2(FILE* yoloc,int i,layer darknet_layer)
        {
        fprintf(yoloc,"/*Layer %d-UPSAMPLE*/\n",i);
        //upsample
        fprintf(yoloc,"[%d].forward=forward_upsample_layer,\n", i);
        fprintf(yoloc,"[%d].output=output_%d", i, i);
}

int write_maxpool_layer(FILE* yoloc,int i,layer darknet_layer)
{
        //maxpool
        fprintf(yoloc,"-MAXPOOL*/\n");

        //generic
        
        fprintf(yoloc,"g_layers[%d].type=%d,\t\tg_layers[%d].activation=%d,\t\tg_layers[%d].batch_normalize=%d,\t\tg_layers[%d].batch=%d,\n", 
                i, darknet_layer.type,       i, darknet_layer.activation,   i, darknet_layer.batch_normalize,     i, darknet_layer.batch);
        fprintf(yoloc,"g_layers[%d].inputs=%d,\t\tg_layers[%d].outputs=%d,\t\tg_layers[%d].nweights=%d,\t\tg_layers[%d].n=%d,\n", 
                i, darknet_layer.inputs,       i, darknet_layer.outputs,   i, darknet_layer.nweights,   i, darknet_layer.n);
        fprintf(yoloc,"g_layers[%d].groups=%d,\n", 
                i, darknet_layer.groups);
        fprintf(yoloc,"g_layers[%d].h=%d,\t\tg_layers[%d].w=%d,\t\tg_layers[%d].c=%d,\n", 
                i, darknet_layer.h,     i, darknet_layer.w,   i, darknet_layer.c);
        fprintf(yoloc,"g_layers[%d].out_h=%d,\t\tg_layers[%d].out_w=%d,\t\tg_layers[%d].out_c=%d,\n", 
                i, darknet_layer.out_h,     i, darknet_layer.out_w,   i, darknet_layer.out_c);
        fprintf(yoloc,"g_layers[%d].size=%d,\t\tg_layers[%d].stride=%d,\t\tg_layers[%d].pad=%d,\n", 
                i, darknet_layer.size,     i, darknet_layer.stride,   i, darknet_layer.pad);
        fprintf(yoloc,"g_layers[%d].index=%d,\t\tg_layers[%d].classes=%d,\t\tg_layers[%d].total=%d", 
                i, darknet_layer.index,     i, darknet_layer.classes,   i, darknet_layer.total);
                fprintf(yoloc,";\n");

        return 0;

    //maxpool
}
