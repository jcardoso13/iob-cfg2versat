# README #

#Run#

>make

>./iob-cfg2versat file.cfg

with file.cfg being the needed file to translate to Versat



#Timeline#

Without using Versat

-Parse CFG to Embedded CPU code (and then to be ran on Versat)- Done for Yolo and Tiny Yolo CFG layers

-Adapt "YoloLite" Project into "DarknetLite", able to run all layers on embedded CPUs with static memory

-Run iob-cfg2versat and DarknetLite on Desktop 


With Versat

-Testing acceleration of 1 layer (convolutional)

-Do Yolo and Tiny Yolo CFG layer  Acceleration

-Extend to all CFG layers

