#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

void threshold_sweep_gif(std::string file, int frameDuration){
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
    PNM::giftoanimatedgif(gifFiles,file + "_threshold_sweep_result.gif",frameDuration);
}
void quant_sweep_gif(){

    std::string file = "beans";
    //std::string file = "rainbow";
    std::string makeCleanINFIX = "Output";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string frameFiles = "";
    std::string gifFiles;
        test->read(file +".ppm");
        //test->PPMtoPGM_average();
        //test->PGMtoPPM();
        test->save( file + makeCleanINFIX);
        int nColor[] = {2,3,4,5,6,8,10,12,15,18,23,28,34,40,48};
        for(int i = 0; i < 15 ; i++){
        PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(),"quant_" +file + makeCleanINFIX + std::to_string(nColor[i]) + test->getExtention(), nColor[i], true);
        PNM::ppmtogif( "quant_" + file + makeCleanINFIX + std::to_string(nColor[i]) +  ".ppm", file + makeCleanINFIX + std::to_string(nColor[i]) +  ".gif");
        frameFiles = frameFiles +file + makeCleanINFIX + std::to_string(nColor[i]) + ".gif ";
        }
    PNM::giftoanimatedgif(frameFiles,file +"_quant_sweep_result.gif",25);
}
void quant_wide_sweep_gif(std::string file, bool dither, int frameDuration){

    std::string makeCleanINFIX = "Output";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string frameFiles = "";
    std::string gifFiles;
        test->read(file +".ppm");
        //test->PPMtoPGM_average();
        //test->PGMtoPPM();
        test->save( file + makeCleanINFIX);
        for(int i = 2; i < 50 ; i++){
        PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(),"quant_" +file + makeCleanINFIX + std::to_string(i) + test->getExtention(), i, dither);
        PNM::ppmtogif( "quant_" + file + makeCleanINFIX + std::to_string(i) +  ".ppm", file + makeCleanINFIX + std::to_string(i) +  ".gif");
        frameFiles = frameFiles +file + makeCleanINFIX + std::to_string(i) + ".gif ";
        }
    PNM::giftoanimatedgif(frameFiles,file +"_quant_wide_sweep_result.gif",frameDuration);
}

void quant_png(std::string file, int nColor, bool dither){

    std::string makeCleanINFIX = "Output";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string gifFiles;
    test->read(file +".ppm");
    test->save( file + makeCleanINFIX);
    PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(),"quant_" +file + makeCleanINFIX +test->getExtention(), nColor, true);
    PNM::pnmtopng( "quant_" + file + makeCleanINFIX + ".ppm", file +"_quant_"+ std::to_string(nColor) + "_" + std::to_string(dither) + ".gif");

}

int main(){
    //quant_png("beans",15,true);
    //quant_wide_sweep_gif("beans",false,20);
    //threshold_sweep_gif("beans", 10);
    return 0;
}
