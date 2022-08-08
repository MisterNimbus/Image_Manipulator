#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <bitset>

enum PNMtype{PPM, PGM, PBM};

class PNM{
public:
    PNM(int width = 0, int height = 0, PNMtype type = PNMtype::PPM, int range = 1);
    ~PNM();

    PNMtype getType();
    int getWidth();
    int getHeight();
    int getRange();
    std::string getMagicNumber();
    std::string getExtention();

    int getPixelValueR(int row, int col);
    int getPixelValueG(int row, int col);
    int getPixelValueB(int row, int col);
    int getPixelValueGRAY(int row, int col);
    bool getPixelValueBINARY(int row, int col);

    void setType(PNMtype newType);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setRange(int newRange);

    void setPixelValueR(int row, int col, int newR);
    void setPixelValueG(int row, int col, int newG);
    void setPixelValueB(int row, int col, int newB);
    void setPixelValueRGB(int row, int col, int newR, int newG, int newB);
    
    void setPixelValueGRAY(int row, int col, int newGray);
    void setPixelValueBINARY(int row, int col, bool newBit);

    static void pnmtopng(std::string sourceFile, std::string targetFile); //sourceFile and targetFile with extention
    static void pngtopnm(std::string sourceFile, std::string targetFile); //sourceFile and targetFile with extention
    static void pnm_quantisize(std::string sourceFile, std::string targetFile, int nColors, bool dithering = false);
    static void ppmtogif(std::string sourceFile, std::string targetFile); //sourceFile and targetFile with extention
    static void giftoanimatedgif(std::string sourceFiles, std::string targetFile, int delay = 50);

    int read(std::string sourceFile); //sourceFile with extention
    int save(std::string targetFile); //targetFile without extention
    
    friend std::ostream& operator<<(std::ostream& os, PNM& PNM);

    void invert();

    void PPMtoPGM_average();
    void PPMtoPGM_luminosity();
    void PPMtoPGM_singleChannel(bool R, bool G, bool B);
    
    void PGMtoPPM();
    void PBMtoPPM();
    void PBMtoPGM();

    void PGMtoPBM_threshold(float percentage);


private:
    int width;
    int height;
    PNMtype type;
    int range;
    std::vector<std::vector<std::vector<int>>> map;
};

#endif