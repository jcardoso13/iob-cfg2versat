#include "iob-cfg2versat.h"

int main(int argc, char** argv)
{
    if(argc!=2)
        {
        printf("1 (.cfg) or (.prototxt) file should be inserted as Input\n");
        exit(1);
        }
    if(strlen(argv[1])<strlen(".cfg"))
        exit(1);

    char* point=&(argv[1][strlen(argv[1])-strlen(".cfg")]);
    char* point2=&argv[1][strlen(argv[1])-strlen(".prototxt")];
    printf("string is %s\n",point);
    bool cond1=strcmp(point,".cfg")==0;
    bool cond2=strcmp(point2,".prototxt")==0;
    if(cond1==false && cond2==false)
    {   
        printf("File isn't (.prototxt) nor (.cfg)\n");
        exit(1);
    }
    if(cond1==true) 
    {
        parseDarknet(argv[1]);
    }
    if(cond2==true)
    {
        //parseCaffe(argv[1]); //TODO at a later time
    }

}