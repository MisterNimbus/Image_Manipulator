#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

int main(){
    std::string file = "beans";
    //std::string file = "rainbow";

    PNM * test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    test->read(file +".ppm");
    //std::cout << *test;
    test->PPMtoPGM_singleChannel(0,1,0);
    test->save( file +"Output");
    PNM::pnmtopng( file +"Output.pgm", file +"Output.png");
    std::cout << std::endl;
    return 0;
}
