#include "./pnm.h"
#include <ostream>
#include <iostream>
#include <memory>

void testObjectCreation(){
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
    std::cout  << std::endl <<"pgm:" <<  std::endl <<*pgmTest;
    std::cout  << std::endl <<"ppm:" << std::endl << *ppmTest;

    std::string targetFile1 = "pbmTest.pbm";
    std::cout << pbmTest->save(&targetFile1);
    std::string targetFile2 = "pgmTest.pgm";
    std::cout << pgmTest->save(&targetFile2);
    std::string targetFile3 = "ppmTest.ppm";
    std::cout << ppmTest->save(&targetFile3);

    system("pnmtopng pbmTest.pbm>pbmTest.png");
    system("pnmtopng pgmTest.pgm>pgmTest.png");
    system("pnmtopng ppmTest.ppm>ppmTest.png");
}

void testRead(){
    std::string targetFile1 = "pbmTest.pbm";
    pnm * readPBM = pnm::read(&targetFile1);

    std::string targetFile2 = "pgmTest.pgm";
    pnm * readPGM = pnm::read(&targetFile2);

    std::string targetFile3 = "ppmTest.ppm";
    pnm * readPPM = pnm::read(&targetFile3);

    
    std::cout  << std::endl <<"pbm:" << std::endl << readPBM;
    std::cout << readPBM->print();
    std::cout  << std::endl <<"pgm:" <<  std::endl << readPGM;
    std::cout << readPGM->print();
    std::cout  << std::endl <<"ppm:" << std::endl << readPPM;
    std::cout << readPPM->print();

    
    std::cout << readPBM->save(&targetFile1);
    std::cout << readPGM->save(&targetFile2);
    std::cout << readPPM->save(&targetFile3);

    system("pnmtopng pbmTest.pbm>pbmTest2.png");
    system("pnmtopng pgmTest.pgm>pgmTest2.png");
    system("pnmtopng ppmTest.ppm>ppmTest2.png");
    
}

void testPixel(){
    pixel * p = new pixel(1,2,3);
    std::cout << "outputRGB(): " << p->outputRGB() << std::endl;
    std::cout << "getR(): " << p->getR() << std::endl;
    std::cout << "getG(): " << p->getG() << std::endl;
    std::cout << "getB(): " << p->getB() << std::endl;

    std::cout << "getGRAY(): " << p->getGRAY() << std::endl;
    std::cout << "getBit(): " << p->getBit() << std::endl;
    p->setRGB(4,5,6);
    std::cout << "outputRGB(): " << p->outputRGB() << std::endl;
    std::cout << "getR(): " << p->getR() << std::endl;
    std::cout << "getG(): " << p->getG() << std::endl;
    std::cout << "getB(): " << p->getB() << std::endl;


    std::cout << "outputGRAY(): " << p->outputGRAY() << std::endl;
    std::cout << "outputBINARY(): " << p->outputBINARY() << std::endl;
    std::cout << "getGRAY(): " << p->getGRAY() << std::endl;
    std::cout << "getBit(): " << p->getBit() << std::endl;
}

void testPNM(){
    pnm * PBMptr = new pbm(2,2);
    PBMptr->pushToRow(0,0);
    PBMptr->pushToRow(0,1);
    PBMptr->pushToRow(1,1);
    PBMptr->pushToRow(1,0);
    std::cout << PBMptr->print() << PBMptr;


}

int main(){
    //testObjectCreation();
    //system("pngtopnm pbmTest.png>pbmTest.pbm");
    //testRead();
    //testPixel();
    testPNM();
    return 0;
}
