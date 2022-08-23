# Image_Manipulator (WIP)

 Image Manipulation software. I will write a more detailed description one day. 
 You may look at the gifs and pngs to see the results. beans.png and rainbow.png are the samples I am using as input.

## For this to run properly you will need to:
 - be on Linux
 - have NETPBM installed
 - have GIFSICLE installed (for GIF related operations)

## Results
<p align="center">
   <img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans.png" width="65%" />
<div align="center">
  ⬆ Input Image (beans.png -> Bowl of Jelly Beans by Patrick Fore - https://unsplash.com/photos/0u_vbeOkMpk)
  </div>
</p>
  
<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_threshold_sweep_result.gif" width="65%" />
<div align="center">
  ⬆ Image gets read as PPM, PPM is converted to PGM via grayscale, PGM is converted into PBM (whether the Gray value is larger or less than the threshold value). Threshold starts from 0 and gets incremented until reaches range. For each step a gif is created and at the end all gifs are put together to form an animated gif.
  </div>
</p>
  
<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_quant_10_1.gif" width="65%"/>
<div align="center">
  ⬆ Quantisation example with 10 colors. Image gets quantisized using NETPBM's pnmcolormap and pnmremap functions, in this case with 10 colors.
  </div>
</p>
  
<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_quant_15_1.gif" width="65%" />
<div align="center">
  ⬆ Quantisation example with 15 colors. Image gets quantisized using NETPBM's pnmcolormap and pnmremap functions, in this case with 15 colors.
  </div>
</p>  
  
<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_quant_wide_sweep_result.gif" width="65%" />
<div align="center">
  ⬆ Image gets quantisized using NETPBM's pnmcolormap and pnmremap functions. Starting with just 2 color, for each frame one more color is used until 256 colors (color   limit of gif format) is reached. At the end all gifs are put together to form an animated gif.
  </div>
</p>

<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_customPalette.png" width="65%" />
<div align="center">
  ⬆ Color remapping using custom palette (in this case khaki and purple). Netpbm remap choses the closest color from given palette.
  </div>
</p>
  
<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_palette_sweep_result.gif" width="65%" />
<div align="center">
  ⬆ Color remapping using linear changing custom palette (in this case khaki's blue value gets increased and purple's blue value decreased gradualy). Netpbm remap choses the closest color from given palette for each frame. At the end all gifs are put together to form an animated gif.
  </div>
</p>

<p align="center" >
<img src="https://github.com/MisterNimbus/Image_Manipulator/blob/master/beans_rainbow_palette_result.gif" width="65%" />
<div align="center">
  ⬆ Color remapping using rotating color phasors palette and base image invertion. Color phasors can be thought as a sphere placed inside a cube, where ea ch axis represents a color channel. A point on the surface of the sphere keeps moving which results in a gradual color change that is not linear. The position of the point is expressed in spherical coordinates, which makes it easy to move the point by just theta and phi velocities. To prevent repetition velocities are randomized after every period. The colors' distance from the (0,0,0) point (which is black) is measured and compared and depending on the result the inverted or the original base image is remapped. This prevents the colors from switching places and ensures a gradual change for both fields. At the end all gifs are put together to form an animated gif.
  </div>
</p>


