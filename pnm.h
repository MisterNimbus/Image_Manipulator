#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <ostream>
#include "./pixel.h"
#include <memory>

class pnm
{
public:
    enum pnmType{ pbm, pgm, ppm };
    pnm(enum pnm::pnmType type);
    virtual ~pnm();
    virtual int getMagicNumber() = 0;
    int save(std::string targetFolder);
    static std::unique_ptr<pnm> read(std::string sourceFolder);
    virtual int format() = 0;
private:
    pnmType pnmType;
};

class pbm : pnm{
public:
    pbm(int width, int height);
    ~pbm();
    int format() override;
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, bool value);
private:
    int width, height;
    std::vector< std::vector< std::unique_ptr<BINARYpixel>>> map;
};

class pgm : pnm{
public:
    pgm(int width, int height, int range);
    ~pgm();
    int format() override;
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, std::unique_ptr<GRAYpixel> pixel);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr<GRAYpixel>>> map;
};

class ppm : pnm{
public:
    ppm(int width, int height, int range);
    ~ppm();
    int format() override;
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, std::unique_ptr<RGBpixel> pixel);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr< RGBpixel>>> map;
};

#endif