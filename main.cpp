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
    auto pbmTest = std::make_unique<pbm>(5,5);
    for ( int y = 0; y < pbmTestArrayHeight; y++){
        for ( int x = 0; x < pbmTestArrayWidth; x++){
            pbmTest->pushToRow(y, pbmTestArray[x][y]);
        }
    }
    return 0;
}