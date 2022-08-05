#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

int main(){
    std::string file = "beans";
    //std::string file = "rainbow";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    for(float i = 0; i <=1 ; i+=0.1){
    test->read(file +".ppm");
    //std::cout << *test;
    test->PPMtoPGM_singleChannel(0,1,0);
    test->PGMtoPBM_threshold(i);
    test->save( file +"Output");
    PNM::pnmtopng( file +"Output.pbm", file + std::to_string(i) + "Output" + ".png");
    }
    return 0;
}