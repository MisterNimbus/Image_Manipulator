#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

int main(){
    
    int pbmTestArrayWidth = 5;
    int pbmTestArrayHeight = 5;
    bool pbmTestArray[5][5] = { { false,  true, false,  true, false },
                                {  true, false,  true, false,  true },
                                {  true, false, false, false,  true },
                                { false,  true, false,  true, false },
                                { false, false,  true, false, false }};
    int pgmTestArrayWidth = 5;
    int pgmTestArrayHeight = 5;
    int pgmTestArray[5][5] ={ {0,1,2,3,4},{1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{0,0,0,0,0}};
    int ppmTestArrayWidth = 2;
    int ppmTestArrayHeight = 2;
    int ppmTestArray[2][2][3] = {{{1,0,0},{0,1,0}},{{0,0,0},{1,1,1}}};
    
    
    auto pbmTest = std::make_unique<pbm>(5,5);
    for ( int y = 0; y < pbmTestArrayHeight; y++){
        for ( int x = 0; x < pbmTestArrayWidth; x++){
            pbmTest->pushToRow(y, pbmTestArray[y][x]);
        }
    }
    auto pgmTest = std::make_unique<pgm>(5,5,7);
    for ( int y = 0; y < pgmTestArrayHeight; y++){
        for ( int x = 0; x < pgmTestArrayWidth; x++){
            pgmTest->pushToRow(y, pgmTestArray[y][x]);
        }
    }
    auto ppmTest = std::make_unique<ppm>(2,2,1);
    for ( int y = 0; y < ppmTestArrayHeight; y++){
        for ( int x = 0; x < ppmTestArrayWidth; x++){
            ppmTest->pushToRow(y, ppmTestArray[y][x][0], ppmTestArray[y][x][1], ppmTestArray[y][x][2]);
        }
    }
    
    std::cout  << std::endl <<"pbm:" << std::endl << *pbmTest;
    std::cout  << std::endl <<"pgm:" <<  std::endl << *pgmTest;
    std::cout  << std::endl <<"ppm:" << std::endl << *ppmTest;
    return 0;
}