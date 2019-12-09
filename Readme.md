# General description and purpose
LivePic captures screen fragment and displays it in separate window. The image can be transformed before displaying like brightness, convolution, resizing. The mouse cursor can be displayed on the processed image, but the actual mouse pointer cannot be captured, so the mouse cursor is always displayed as crosshair. The transform operations can be combined sequentially.

## Example usage scenarios
There are example scenarios, in which you can use LivePic application.

### Zoom screen fragment
This is one of the simplest scenario. Set relatively small size of grabbed image and set display window larger than grabbed image size. You can follow mouse cursor. Display image can be stretched proportionally.

### Transforming screen image
For this scenario there is needed two monitors configured as extended desktop. Both monitor should be set at the same image resolution (matching monitor native resolution is not mandatory). The grab position and size takes whole first monitor screen and the display window takes whole second monitor screen. The image display should not be stretched. It can be transformed without resizing, like brightness and contrast changing or image flipping. At this configuration, you can work watching only the second monitor, which displays whole desktop from first monitor.

### Previewing the second monitor/projector
If system is configured as extended desktop, but you cannot watch the second monitor directly, it is possible to watch whole image in small window displayed on the first monitor. The grabbing positions and size takes whole second screen and the images is displayed in small window placed on the first screen. The image can be stretched or the mouse cursor can be followed.

### Improvement/enhancing old games display
The old games has limited graphics palette and commonly uses pixel-art and ordered dithering. This scenarios requires two monitors configured as extended desktop. Run game or computer emulator on the second monitor in window, size of the window have to match original game size (1x, 100% etc.). Set grab size exactly the same as game screen size and set grab position at the game picture window. The display window should occupy the whole first monitor screen and image can be stretched. It is possible to use enlarging algorithms as Scale2x, HQ2x to simulate larger picture. If the game uses ordered dithering like pixel checkerboard, it is possible to replace dithered area with color, which is simulated by dithering, but details are preserved. Image is not blurred, dedithering uses pattern matching. Because dedithering is resource-demanding process, it is recommended to use with images up to 320x240 to retain high frame rate an use as fewest patterns as possible. Of course, apart from scaling and dedithering, it is possible to use other transform operations.

### Real-time enhance photograph and movies
This scenario is similar to one above. In transformation it is possible to make convolution filters, brightness, contrast for channels separately. It is possible to transform luminance and chrominance (like YUV). To do this, it is possible to convert RGB to L/C, where on channel carries luminance and the other carries chrominance and treat this channel the same way as RGB. After transforming channels, it should be converted from L/C to RGB using the same parameters. In most cases, enhancing movies is limited to SD-resolution movies due to frame rate, especially screen capturing and displaying, which cannot be multithreaded. The resolution of photograph is not limited, because there are static pictures and processing frame rate is not matter.

### Displaying tiled image
If you can test tiled display of any image, the grab size have to match image size and position have to be the same as tested image position. The display can be configured to tiled display and display window must be larger at least two times than tested image. You can watch, how tiled image looks and if the image is seamless (designed to tile display).

# Picture and display settings
After program running you are set the picture grabbing and display settings, which are meaning for:
* __Grab position__ – Position of grabbed image
* __Grab size__ – Size of grabbed image
* __View position__ – Position of viewing window
* __View size__ – Size of viewing window
* __Folow mouse__ – Move grab position according mouse cursor movement
* __Mouse type__ – Mouse cursor draw type:
  * __None__ – no mouse cursor
  * __High contrast__ – draw mouse cursor using only minimum and maximum values of channels
  * __Negative__ – draw mouse cursor using color negative

* __Mouse size__ – Size of mouse cursor crosshair legs
* __Margin left, top, right, bottom__ – The distance between window edge and viewing picture edge, the negative value allow cropping picture
* __View mode__ – Sets view stretch mode:
  * __Center__ – View picture in original size
  * __Margin/Margin smooth__ – Stretch proportionally with margins (whole picture is visible)
  * __Fill/Fill smooth__ – Stretch proportionally to fill whole window (picture is cropped)
  * __Stretch/Stretch smooth__ – Stretch picture disproportionally to fill whole window without interpolation
  * __Tile center__ – Display tiled picture, tile center in window center
  * __Tile corner__ – Display tiled picture, tile corner in window center
* __Offset X, Y__ – The viewing picture offset, work only in „Center”, „Tile center” and „Tile corner modes”
* __Background color__ – Change color of viewing window

The other settings are:
* __Pipes__ – Number of pipes used in multithreading picture transforming:
  * __0__ – No pipes
  * __Positive values__ – Display picture before capturing
  * __Negative values__ – Display picture after capturing

* __Threads__ – Number of threads used in one picture transform step, except from some special case
* __Delay line length__ – Length of delay line in frames
* __Delay line temp file__ – Name of temporary file to store temporary delay line memory, when blank, the delay line will be stored in memory
* __Mouse margin__ – Distance from window edge, which is sensitive to mouse, placing cursor within this margin it is possible to resize window
* __Gamma x1000__ – Set display gamma correction used in some transform types to operate on perceived color value instread of real color value

# Transform setting
On the __Transform__ tab, you can define picture transform sequence. Below sequence list,  there are following buttons:
* __Load list__ – Load transform list from file
* __Save list__ – Save transform list to file
* __Add item__ – Add transform item
* __Remove item__ – Remove transform item
* __Move up, move down__ – Move transform item on the list
* __Enable/disable__ – Enable or disable selected item
The tab box below buttons is used to define transform item. If transform list is empty or there is not selected item, the settings does not matter in picture transform.
Transform kind is selected by selecting tab in transform definition tab box. Every tab has settings specified to certain transform kind. The current transform parameters are showed in transform list.
Transform list is applied every time in starting or restarting working, so if you change any transform setting during working, you have to click __Restart__ button in __Main control__ box.

# Transform: Triple 256-item Look Up Table
There is defined three 256-item arrays, one per color channel. Every item is a number from 0 to 255, which defines, for which value is replaced every value number. The look-up table can be generated by following ways:
* __From file__ – Load table from textual or binary file which is generated manually or from other software
* __Brightness__ – Picture brightness
* __Contrast__ – Picture contrast
* __Negative__ – Partially or fully inverting change value to acquire negative color or solarize effect
* __Gamma__ – Gamma transform
The __Save__ button allows to save current LUT into textual or binary file in specified resolution. The saved file can be used as LUT from file. If resolution is lower than 8, the file will be smaller, but the posterization effect can be observed when using this file. The  __Gamma correction__ field allows to include display gamma in Brightness/Contrast/Negative/Gamma transform

## Textual file structure
The first line contains LUT resolution value (between 1 and 8). The next lines (between 2 and 256 according resolution) contains three number sequence according to color channel, in order Red-Green-Blue. The number of item equals 2 powered to resolution number

## Binary file structure
The first byte has value between 1 and 8, and means LUT resolution. The next following bytes represents table values sequentally in order Red-Green-Blue. The whole file size is between 7 and 769, is equals formula: (3*(2^Resolution)+1)

# Transform: Single 16777216-item Look Up Table
This transform uses look-up table, which defines replacement of each color from 24-bit palette, so this LUT consists of 16777216 item, each item consist of 3 values, which represents color channels.
The look-table can be generated by following ways:
* __From file__ – Load table from textual or binary file which is generated manually or from other software
Saturation – Change color saturation, it uses RGB weight values to calculate luminance
* __RGB -> L/C__ – Convert from RGB to luminance/chrominance color representation, where luminance is in one channel and two chrominance channels are the other channels. There also is possible to create chroma-only channels, but this conversion cannot be inverted due to lack of luminance information. The RGB weight field defines weight of color channels weight in luminance calculation. In this conversion, the Luma only field value is not used. After conversion the chrominance values are between 0 and 255, but 127 means neutral value.
* __L/C -> RGB__ – Convert from luminance/chrominance to RGB color representation. This conversion should have the same parameters as previous RGB -> L/C conversion. If Chroma only conversion is selected, the luminance will be got from Luma field and uniform for whole picture.
* __Channels__ – Swap and copy color channels. It can be used for example to convert between RGB and BGR representation or display on color channel as grayscale picture.
The __Save__ button allows to save current LUT into textual or binary file in specified resolution. The saved file can be used as LUT from file. If resolution is lower than 8, the file will be smaller, but the posterization effect can be observed when using this file. The __Gamma correction__ allows to include display gamma in Saturation or RGB<->LC conversion.

## Textual file structure
The first line consists of two number. The first number is the resolution and the second number means number of color columns. The one color consists of three value, so if there is 256 columns defined, the one row consists of 768 numbers. The number of column must be divisor of 16777216.
The next following rows consists of color values in Red-Green-Blue order. The most significiant color channel is blue and the least significiant value is red. The file is read line by line. For example, if resolution is 2 (four levels of each channel), there are 64 colors replacement defined by following order (value are RGB): (0, 0, 0); (1, 0, 0); (2, 0, 0); (3, 0, 0); (0, 1, 0); (1, 1, 0); (2, 1, 0); (3, 1, 0); (0, 0, 0); (1, 2, 0); (2, 2, 0); (3, 2, 0); (0, 3, 0); (1, 3, 0); (2, 3, 0); (3, 3, 0); (0, 0, 1); (1, 0, 1); (2, 0, 1); (3, 0, 1); (0, 1, 1); (1, 1, 1); (2, 1, 1); (3, 1, 1); (0, 0, 1); (1, 2, 1); (2, 2, 1); (3, 2, 1); (0, 3, 1); (1, 3, 1); (2, 3, 1); (3, 3, 1); (0, 0, 2); (1, 0, 2); (2, 0, 2); (3, 0, 2); (0, 1, 2); (1, 1, 2); (2, 1, 2); (3, 1, 2); (0, 0, 2); (1, 2, 2); (2, 2, 2); (3, 2, 2); (0, 3, 2); (1, 3, 2); (2, 3, 2); (3, 3, 2); (0, 0, 3); (1, 0, 3); (2, 0, 3); (3, 0, 3); (0, 1, 3); (1, 1, 3); (2, 1, 3); (3, 1, 3); (0, 0, 3); (1, 2, 3); (2, 2, 3); (3, 2, 3); (0, 3, 3); (1, 3, 3); (2, 3, 3); (3, 3, 3)

## Binary structure file
The first byte has value between 1 and 8, and means LUT resolution. The next following bytes represents table values sequentally in order Red-Green-Blue. The color value order are the same as described in textual file structure. The file size equals formula: (3*(2^Resolution)*(2^Resolution)*(2^Resolution)+1), so the file size is between 25 and 50331649.

# Transform: Convolution
The convolution transform uses three 5x5 matrices, one for each color channel (red, green, blue). It is possible to use one matrix and other parameter definition to two or all channel. The Gamma correction field indicates, that output color are calculated using perceived intensity (including display gamma) instead of intensity values. The Common field provides this ability, for example, you have to define matrix and parameters for red color channel only to use this for all channels.
For each pixel in picture, the pixel is represented by center matrix field, the other fields represents adjacent pixels. The pixels beyond picture border repeats values from border pixels. For channel separately, for each pixel, result color value is calculated as follows:
1. Get color of 25 pixels (the current and 24 adjacent pixels).
2. Multiply pixel value by matrix cell value.
3. Sum calculated values to get one value.
4. Add In offset value.
5. Divide by divider.
6. Add out offset value.
7. Limit pixel value in range between 0 and 255.

The transform kind is also called as convolution, kernel, mask, filter etc.

# Transform: Dedithering
This transform replaces simulated color by real color, but it can preserve details, because does not blur picture. The color can be simulated by ordered dithering, which uses regular patterns. This technique was frequently used in old games and graphics software, where color palette was limited to 16 colors. Color simulated by random-based or diffused dithering algorithm cannot be replaced to real color through dedithering.
Each template can create from one to four patterns (it is possible to set 0 patterns, so this template will not be used), all patters in one template are rotated the same pattern. The pattern is 5x5 matrix, which can define up to 4 colors layout. The 0 value indicates that color of the pixel is not important. The numbers from 1 to 4 defines color, which must be the same in all pixels with the same number to match pattern. If the pattern define dithering for two colors (the most frequently case), it must contain the 1 and 2 number and not contain 3 and 4 number. Of course, the pattern can contain the 0 number for neutral pixels. The Color 1, Color 2, Color 3 and Color 4 fields defines color factor. If pattern defines dithering of two colors and the used color intensity proportions is equal (for example, the checkerboard pattern), the value of Color 1 and Color 2 must be greater than 0 and equal each other, and the values of Color 3 and Color 4 must be equal 0. If dithering pattern has 4 times more pixels of Color 1 than Color 2, the Color 1 value must be 4 times greater than Color 2 value.
The drop-down lists defines the pattern flipping or rotation variants, which are used to transform picture. It is possible to set up to 4 pattern variants within one template, ordering from left to right. The following variants are following:
* __None__ – Do not use
* __Straight__ – Use without flipping or rotatin
* __U/D__ – Upside down (flip both horizontal and vertical)
* __Hori__ – Flip horizontal
* __Vert__ – Flip vertical
* __Main D__ – Flip by main diagonal
* __Other D__ – Flip by other than main diagonal
* __Clk__ – Rotate clockwise
* __Cnt clk__ – Rotate counter clockwise

## Dedither processing
For each picture pixel, there is read 24 adjacent pixels and it is searched for matching pattern (the dedither pattern list order is very important). If found matching pattern, the pixel color are replaced by color calculated using adjacent pixels and color factors of the first matching pattern. If matching patterns not found, the pixel color will not be changed.
Because the dedithering requires relatively high computing power, it is recommended to use the fewest patterns as possible.

# Transform: Resize/scale
This transform is user to change image size in three ways.

## Resize
Resize is the simple resize, which can be with smoothing or without it. The high quality smoothing requires more computing power than fast smoothing, but it has better quality. The new size is defined by ratio of original size. The width and height ratios are defined by numerator and denominator for width and height. For example, to enlarge image 4 times, the size numerator for both width and height can be 4, while the denominator for both dimensions are 1. To shrink image 3 times, the size numerator can be 1 and denominator can be 3.

## Scale
The scale way offers enlarging 2 times, 3 times or four times and id dedicated to pixel-art similar pictures. It uses Scale or HQ algorithm. If Separate channels are checked, each color channel will be treated as separate grayscale image.

## Subpixels
This offers subpixel composition or decomposition. This operations supports RGB stripes layout only, which are in the most LCD and plasma screens. The monitor can be rotated, so there is possible to select one of four subpixels layout. Each composition and decomposition transforming, which uses luminance, user RGB weight to calculate luminance. The following composition and decomposition is described for horizontal RGB layout, the transforms for other layouts are analogous.

### Subpixel composition
The composition means shrinking image three times with subpixel rendering. The vertical shrinking is simple shrink three times, for each pixels there is calculated average color of vertically placet three pixels. The horizontal shrinking uses five horizontally placed pixels using following formulas, where L(R,G,B) = ((R\*RWeight+G\*GWeight+B\*BWeight)/(RWeight+GWeight+BWeight)).
The five source pixels in the formulas are:
{RLL,GLL,BLL}{RL,GL,BL}{R,G,B}{RR,GR,BR}{RRR,GRR,BRR}
Composite color without smoothing – {RL,G,BR}
Composite color with smoothing – {(RLL+RL+R)/3,(GL+G+GR)/3,(B+BR+BRR)/3}
Composite luminance without smoothing – {L(RL,GL,BL), L(R,G,B), L(RR,GR,BR)}
Composite luminance with smoothing – {(L(RLL,GLL,BLL)+L(RL,GL,BL)+L(R,G,B))/3, (L(RL,GL,BL)+L(R,G,B)+L(RR,GR,BR))/3, (L(R,G,B)+L(RR,GR,BR)+L(RRR,GRR,BRR))/3}

### Subpixel decomposition
In theory, the subpixel decomposition is inverse of subpixel composition and it can be used to zoom subpixel-rendered text and pictures. The decomposition means three time picture enlarging both horizontally and vertically. In practice, the horizontally enlarging is not simple zoom in due to layout of subpixels.
The vertically enlarging is simple three times zoom in with smoothing or without it, depending on Smoothing field checking. The "Color subpixels" and "Gray subpixels" are the simple simulation, how image is actually displayed on screen (the only difference between this models is displaying color or gray simulated subpixels). The color areas will be rendered with vertical stripes due to varying subpixel intensity.
The third decomposite modes uses luminance (luma) and may use chrominance (chroma) and there is most recommended decomposite mode. The luminance is calculated using channel weights from RGB weight fields. The decomposite of one pixel really uses three pixels of source image (the current and two adjacent). The chrominance calculation may use adjacent pixels and pixels above and below current pixels. This uses the fact, that every subpixel with two adjacent subpixels creates whole RGB color.
The _Decomposite chroma_ field allows to set, how many horizontally placed subpixels are used to calculate average chrominance, by following:
* _Base_ - The number of sumbixels in current line.
* _Line 1_ - The number of sumbixels in the first lines above and below current line.
* _Line 2_ - The number of sumbixels in the second lines above and below current line.
The number indicates, how many subpixels in this lines are used horizontally. The higher number causes more chrominance blur and less chrominance artifacts. The _0_ value indicates, that chrominance will not be used.
The luminance is L(R,G,B) = ((R\*RWeight+G\*GWeight+B\*BWeight)/(RWeight+GWeight+BWeight)).
The one pixel of source image creates three pixels, where luminance will be calculated from values::
* {R,G,BL1}
* {R,G,B}
* {RR1,G,B}
In the one line, there can be used three or five adjacent pixels for chrominance, which will be signed as: {RL2,GL2,BL2}{RL1,GL1,BL1}{R,G,B}{RR1,GR1,BR1}{RR2,GR2,BR2}
The chrominance for 11 subpixels (the most widest variant) will be calculated using following pixel values:
* {RL2,GL2,BL2}
* {RL1,GL2,BL2}
* {RL1,GL1,BL2}
* {RL1,GL1,BL1}
* {R,GL1,BL1}
* {R,G,BL1}
* {R,G,B}
* {RR1,G,B}
* {RR1,GR1,B}
* {RR1,GR1,BR1}
* {RR2,GR1,BR1}
* {RR2,GR2,BR1}
* {RR2,GR2,BR2}
There are 13 chrominance values, for final pixel there will be used as follows:
* For red subpixel: The first 11 values.
* For gree subpixel: The 11 values without the first and the last value.
* For blue subpixel: The last 11 values.
The chrominance of one channel is the difference between luminance value and color channel value, so, it can be positive or negative value.

# Transform: Flip/rotate
This is a simple transform, which flips or rotates image depending on selection in __Flip or rotate__ field. The rotation or flipping by diagonal are executed in one thread regardless number of threads in settings due to complexity of this operation when is splitted into threads.

# Performance settings and recommendations
In the __Settings__ window, there is FPS display during working. The maximum FPS is throttled by grabbing screen and displaying picture by operating system, usually there is ca. 30 FPS. This speed can decrease if you set high resolution of grabbing picture or if you use a lot of transform operations.

## Threads
Every transform opereration (except of rotating or flipping by diagonal) are splitted in threads. If you set 4 in the __Threads__ field, every operation will run 4 threads, which one thread will process one quarter of picture, and application will wait for end of all threads before performing next operation. If you have computer with multi-core processor, increasing number of threads may shorten time needed for each picture transform operation.

## Pipes
The pipe can give more processor time for process one picture without decreasing FPS. If you increase number of pipes, there will be more time to process one picture, but picture will be displayed with small delay.
The pipe number can be negative or positive value, in both cases, the absolute value is the number of pipes, which will be created. If you set 0, the piping mechanism will not be used.

### Positive value of pipes
For example, if you set __Pipes__ field for 4, application will work as follows:
1. Create dummy picture and assign it as input picture for all pipes.
2. Run picture transform in separated thread for pipe 0, 1, 2 and 3 (all pipes).
3. Wait for finish picture transform thread for pipe 0.
4. Display picture from pipe 0.
5. Grab new picture into pipe 0.
6. Run picture transform in separated thread for pipe 0.
7. Wait for finish picture transform thread for pipe 1.
8. Display picture from pipe 1.
9. Grab new picture into pipe 1.
10. Run picture transform in separated thread for pipe 1.
11. Wait for finish picture transform thread for pipe 2.
12. Display picture from pipe 2.
13. Grab new picture into pipe 2.
14. Run picture transform in separated thread for pipe 2.
15. Wait for finish picture transform thread for pipe 3.
16. Display picture from pipe 3.
17. Grab new picture into pipe 3.
18. Run picture transform for pipe 3.
19. Go to operation 3.

### Negative value of pipes
For example, if you set __Pipes__ field for -4, application will work as follows:
1. Create dummy picture and assign it as input picture for all pipes.
2. Run picture transform for pipe 1, 2 and 3 (all pipes except of pipe 0).
3. Grab new picture into pipe 0.
4. Run picture transform in separated thread for pipe 0.
5. Wait for finish picture transform thread for pipe 1.
6. Display picture from pipe 1.
7. Grab new picture into pipe 1.
8. Run picture transform in separated thread for pipe 1.
9. Wait for finish picture transform thread for pipe 2.
10. Display picture from pipe 2.
11. Grab new picture into pipe 2.
12. Run picture transform in separated thread for pipe 2.
13. Wait for finish picture transform thread for pipe 3.
14. Display picture from pipe 3.
15. Grab new picture into pipe 3.
16. Run picture transform in separated thread for pipe 3.
17. Wait for finish picture transform thread for pipe 0.
18. Display picture from pipe 0.
19. Go to operation 3.

## Performance recommendations
To achieve optimal picture transforming, create transform list according rules:
* All LUT-based operations should be directly followed one by other. The following LUT-based operations will be internally merged into one operation.
* Dedither operation causes internally creates 2 operations, the first directly before and the second directly after dedithering. This operations convert picture between RGB representation and color number representation with 2-pixel margins to increase dedither performance. If you want to use several dedither operations, you should define them one after other directly.
* If you want to get rotated of flipped picture, define the flip/rotate operation once. The all operations can by applyed regardless of picture orientation (after slighty modification in some cases).
* As far as possible, use display resizing mode instead of picture resize transform.
* In most cases, two convolution operations with 3x3 kernel or smaller kernel can be replaced with one convolution operation with 5x5 kernel, which gives the same effect. Use as few convolution operations as possible.
* In dedithering, use as fewest patterns as possible.
* Generally, use as few transform operations as possible.

Apart from transform optimization, you may increase performance and fluenty by following:
* Set as small grabbing picture size as necessary.
* As far as possible, use computer with multi-core processor.
* Close all not necessary software, especially software, which taking a lot of computing power.
* Increase number of threads or pipes, you have to experimentally choose optimal values with FPS and usage of processor cores checking.
