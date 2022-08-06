#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

int main(){
    std::string file = "beans";
    //std::string file = "rainbow";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string gifFiles;
    for(float i = 0; i <=1 ; i+=0.01){
        test->read(file +".ppm");
        //std::cout << *test;
        test->PPMtoPGM_luminosity();
        test->PGMtoPBM_threshold(i);
        test->PBMtoPPM();
        test->save( file + "Output");
        PNM::ppmtogif( file + "Output.ppm", file + std::to_string(i) + "Output.gif");
        gifFiles = gifFiles +file + std::to_string(i) + "Output.gif ";
        //PNM::pnmtopng( file +"Output.ppm", file + std::to_string(i) + "Output" + ".png");
    }
    PNM::giftoanimatedgif(gifFiles,"Output.gif",10);
    return 0;
}