#include "./pnm.h"
#include "./ColorSphere.h"
#include <ostream>
#include <iostream>
#include <memory>
#include <math.h>

void threshold_sweep_gif(std::string file, int frameDuration)
{
    PNM *test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string gifFiles;
    for (float i = 0; i <= 1; i += 0.01)
    {
        test->read(file + ".ppm");
        // std::cout << *test;
        test->PPMtoPGM_luminosity();
        test->PGMtoPBM_threshold(i);
        test->PBMtoPPM();
        test->save(file + "Output");
        PNM::ppmtogif(file + "Output.ppm", file + std::to_string(i) + "Output.gif");
        gifFiles = gifFiles + file + std::to_string(i) + "Output.gif ";
        // PNM::pnmtopng( file +"Output.ppm", file + std::to_string(i) + "Output" + ".png");
    }
    PNM::giftoanimatedgif(gifFiles, file + "_threshold_sweep_result.gif", frameDuration);
}
void quant_sweep_gif()
{

    std::string file = "beans";
    // std::string file = "rainbow";
    std::string makeCleanINFIX = "Output";

    PNM *test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string frameFiles = "";
    std::string gifFiles;
    test->read(file + ".ppm");
    // test->PPMtoPGM_average();
    // test->PGMtoPPM();
    test->save(file + makeCleanINFIX);
    int nColor[] = {2, 3, 4, 5, 6, 8, 10, 12, 15, 18, 23, 28, 34, 40, 48};
    for (int i = 0; i < 15; i++)
    {
        PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(), "quant_" + file + makeCleanINFIX + std::to_string(nColor[i]) + test->getExtention(), nColor[i], true);
        PNM::ppmtogif("quant_" + file + makeCleanINFIX + std::to_string(nColor[i]) + ".ppm", file + makeCleanINFIX + std::to_string(nColor[i]) + ".gif");
        frameFiles = frameFiles + file + makeCleanINFIX + std::to_string(nColor[i]) + ".gif ";
    }
    PNM::giftoanimatedgif(frameFiles, file + "_quant_sweep_result.gif", 25);
}
void quant_wide_sweep_gif(std::string file, bool dither, int frameDuration)
{

    std::string makeCleanINFIX = "Output";

    PNM *test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string frameFiles = "";
    std::string gifFiles;
    test->read(file + ".ppm");
    // test->PPMtoPGM_average();
    // test->PGMtoPPM();
    test->save(file + makeCleanINFIX);
    for (int i = 2; i < 50; i++)
    {
        PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(), "quant_" + file + makeCleanINFIX + std::to_string(i) + test->getExtention(), i, dither);
        PNM::ppmtogif("quant_" + file + makeCleanINFIX + std::to_string(i) + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".gif");
        frameFiles = frameFiles + file + makeCleanINFIX + std::to_string(i) + ".gif ";
    }
    PNM::giftoanimatedgif(frameFiles, file + "_quant_wide_sweep_result.gif", frameDuration);
}

void quant_png(std::string file, int nColor, bool dither)
{

    std::string makeCleanINFIX = "Output";

    PNM *test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    std::string gifFiles;
    test->read(file + ".ppm");
    test->save(file + makeCleanINFIX);
    PNM::pnm_quantisize(file + makeCleanINFIX + test->getExtention(), "quant_" + file + makeCleanINFIX + test->getExtention(), nColor, true);
    PNM::pnmtopng("quant_" + file + makeCleanINFIX + ".ppm", file + "_quant_" + std::to_string(nColor) + "_" + std::to_string(dither) + ".png");
}

void custom_palette(std::string file)
{
    std::string makeCleanINFIX = "Output";

    PNM *palette = PNM::createPalette();
    palette->addColorToPalette(247, 220, 129);
    palette->addColorToPalette(78, 28, 128);
    palette->addColorToPalette(0, 0, 0);
    palette->addColorToPalette(255, 255, 255);
    palette->removeColorFromPalette(255, 255, 255);
    palette->save("palette_" + makeCleanINFIX);

    PNM *test = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    test->reMap(file + ".ppm", file + makeCleanINFIX + ".ppm", "palette_" + makeCleanINFIX + ".ppm", true);
    PNM::pnmtopng(file + makeCleanINFIX + ".ppm", file + "_customPalette.png");
}

void palette_Test()
{
    PNM *palette = PNM::createPalette();
    std::cout << *palette << std::endl;
    palette->addColorToPalette(247, 220, 129);
    palette->addColorToPalette(78, 28, 128);
    std::cout << *palette;
    palette->save("palette");
    PNM::pnmtopng("palette.ppm", "palette.png");
}

void gradient_palette(std::string file, int frameDuration)
{
    std::string makeCleanINFIX = "Output";

    int startingColor1[3] = {247, 220, 129};
    int startingColor2[3] = {78, 28, 128};
    PNM *palette = PNM::createPalette();
    palette->addColorToPalette(startingColor1[0], startingColor1[1], startingColor1[2]);
    palette->addColorToPalette(startingColor2[0], startingColor2[1], startingColor2[2]);

    PNM::pngtopnm(file + ".png", file + ".ppm");

    std::string frameFiles;
    for (int i = 0; i < 25; i++)
    {
        palette->removeColorFromPalette(startingColor1[0], startingColor1[1], startingColor1[2] + (i - 1) * 5);
        palette->addColorToPalette(startingColor1[0], startingColor1[1], startingColor1[2] + i * 5);
        palette->removeColorFromPalette(startingColor2[0], startingColor2[1], startingColor2[2] - (i - 1) * 5);
        palette->addColorToPalette(startingColor2[0], startingColor2[1], startingColor2[2] - i * 5);
        palette->save("palette_" + makeCleanINFIX, true);

        PNM::reMap(file + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".ppm", "palette_" + makeCleanINFIX + ".ppm", true);
        PNM::ppmtogif(file + makeCleanINFIX + std::to_string(i) + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".gif");
        frameFiles = frameFiles + file + makeCleanINFIX + std::to_string(i) + ".gif ";
    }
    for (int i = 23; i > 1; i--)
    {
        frameFiles = frameFiles + file + makeCleanINFIX + std::to_string(i) + ".gif ";
    }
    std::cout << frameFiles << std::endl;
    PNM::giftoanimatedgif(frameFiles, file + "_palette_sweep_result.gif", frameDuration);
}

void NETPBMtest(std::string file)
{
    std::string makeCleanINFIX = "Output";
    PNM::pngtopnm(file + ".png", file + "_unchanged_" + makeCleanINFIX + ".ppm");
    PNM::pnmtopng(file + "_unchanged_" + makeCleanINFIX + ".ppm", file + "_unchanged_" + makeCleanINFIX + ".png");
}

void color_sphere_test(int sphere_center_X,
                                    int sphere_center_Y,
                                    int sphere_center_Z,
                                    int sphere_radius,
                                    int sphere_theta_start,
                                    int sphere_phi_start,
                                    int iteration,
                                    std::string paletteName)
{
    PNM *palette = PNM::createPalette();

    ColorSphere * sphere = new ColorSphere( sphere_center_X,
                                            sphere_center_Y,
                                            sphere_center_Z,
                                            sphere_radius,
                                            sphere_theta_start,
                                            sphere_phi_start);

    for (int i = 0; i < iteration; i++)
    {

        palette->addColorToPalette(sphere->getR(), sphere->getG(), sphere->getB());
        sphere->update();
    }
    palette->save(paletteName, true);
    PNM::pnmtopng( paletteName + ".ppm","sphere_test.png");
}

void rainbow_palette_gif(   std::string file, 
                            float threshold_percentage,
                            int frameDuration,
                            int frameCount)
{

    std::string makeCleanINFIX = "Output";
    std::string frameFiles;
    PNM *input = new PNM();
    PNM::pngtopnm(file + ".png", file + ".ppm");
    input->read(file + ".ppm");
    input->PPMtoPGM_luminosity();
    input->PGMtoPBM_threshold(threshold_percentage);
    input->PBMtoPPM();
    input->save(file + makeCleanINFIX + "_beforeRemap",true);

    input->read(file + ".ppm");
    input->PPMtoPGM_luminosity();
    input->PGMtoPBM_threshold(threshold_percentage);
    input->invert();
    input->PBMtoPPM();
    input->save(file + makeCleanINFIX + "_beforeRemap_inverted",true);

    input->~PNM();

    ColorSphere * sphere1 = new ColorSphere(120,
                                            120,
                                            120,
                                            120,
                                            0,
                                            0);
    ColorSphere * sphere2 = new ColorSphere(125,
                                            125,
                                            125,
                                            125,
                                            M_PI,
                                            M_PI);
    PNM * palette = PNM::createPalette();
    palette->addColorToPalette(sphere1->getR(), sphere1->getG(), sphere1->getB());
    palette->addColorToPalette(sphere2->getR(), sphere2->getG(), sphere2->getB());
    for (int i = 0; i < frameCount; i++)
    {
        palette->save( "palette_" + makeCleanINFIX,true);

        if(sphere1->getDistanceToBlack()>sphere2->getDistanceToBlack()){
        PNM::reMap(file+ makeCleanINFIX + "_beforeRemap" + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".ppm", "palette_" + makeCleanINFIX + ".ppm", true);
        }else{
        PNM::reMap(file+ makeCleanINFIX + "_beforeRemap" + "_inverted" + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".ppm", "palette_" + makeCleanINFIX + ".ppm", true);
        }
        
        PNM::ppmtogif(file + makeCleanINFIX + std::to_string(i) + ".ppm", file + makeCleanINFIX + std::to_string(i) + ".gif");
        frameFiles = frameFiles + file + makeCleanINFIX + std::to_string(i) + ".gif ";

        palette->removeColorFromPalette(sphere1->getR(), sphere1->getG(), sphere1->getB());
        palette->removeColorFromPalette(sphere2->getR(), sphere2->getG(), sphere2->getB());
        
        sphere1->update();
        sphere2->update();
        
        palette->addColorToPalette(sphere1->getR(), sphere1->getG(), sphere1->getB());
        palette->addColorToPalette(sphere2->getR(), sphere2->getG(), sphere2->getB());

    }
    std::cout << frameFiles;
    PNM::giftoanimatedgif(frameFiles, file + "_rainbow_palette_result.gif", frameDuration);
}

int main()
{

    // NETPBMtest("beans");
    // palette_Test();
    // quant_png("beans",2,true);
    // quant_sweep_gif();
    // quant_wide_sweep_gif("beans",true, 20);
    // threshold_sweep_gif("beans", 10);
    // custom_palette("beans");
    // gradient_palette("beans", 10);
    // rainbow_palette_sphere_in_cube( 120,120,120,120,0,0,200,"sphere");
    // color_sphere_test(120,120,120,120,0,0,200,"sphere");
     rainbow_palette_gif("beans", 0.54, 5, 400);

    return 0;
}
