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
    test->save( file +"Output");
    PNM::pnmtopng( file +"Output.ppm", file +"Output.png");
    std::cout << std::endl;
    return 0;
}