#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include "./pixel.h"
#include <memory>

class pnm
{
public:
    enum pnmType{ pbm, pgm, ppm };
    pnm(enum pnm::pnmType type);
    virtual ~pnm();
    virtual std::string getMagicNumber() = 0;
    int save(std::string targetFolder);
    static std::unique_ptr<pnm> read(std::string sourceFolder);
    virtual int format() = 0;
    virtual std::string print() = 0;
private:
    pnmType pnmType;
};

class pbm : pnm{
public:
    pbm(int width, int height);
    ~pbm();
    int format() override;
    std::string getMagicNumber() override;
    void pushToRow(int targetRow, bool value);
    friend std::ostream& operator<<(std::ostream& os, pbm& pbm);
    std::string print() override;
private:
    int width, height;
    std::vector<std::vector<std::unique_ptr<BINARYpixel>>> map = {};
};

class pgm : pnm{
public:
    pgm(int width, int height, int range);
    ~pgm();
    int format() override;
    std::string print();
    friend std::ostream& operator<<(std::ostream& os, pgm& pgm);
    std::string getMagicNumber() override;
    void pushToRow(int targetRow, int grayValue);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr<GRAYpixel>>> map;
};

class ppm : pnm{
public:
    ppm(int width, int height, int range);
    ~ppm();
    int format() override;
    std::string print();
    friend std::ostream& operator<<(std::ostream& os, ppm& ppm);
    std::string getMagicNumber() override;
    void pushToRow(int targetRow,int valueR, int valueG, int valueB);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr< RGBpixel>>> map;
};

#endif