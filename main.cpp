#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

void threshold_sweep_gif(){
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
}

int main(){
    std::string file = "beans";
    //std::string file = "rainbow";
    std::string makeCleanINFIX = "Output";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string gifFiles;
        test->read(file +".ppm");
        //test->PPMtoPGM_luminosity();
        //test->PGMtoPBM_threshold(0.06);
        //test->PBMtoPPM();
        test->save( file + makeCleanINFIX);
        PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(), 256, true);
        PNM::ppmtogif( file + makeCleanINFIX + ".ppm", file + std::to_string(0.06) + makeCleanINFIX + ".gif");
        gifFiles = gifFiles +file + std::to_string(0.06) + makeCleanINFIX +".gif ";
        PNM::pnmtopng( file + makeCleanINFIX + ".ppm", file + std::to_string(0.06) + makeCleanINFIX + ".png");
    return 0;
}
