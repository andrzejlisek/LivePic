# General description and purpose

LivePic captures screen fragment and displays it in separate window\. The image can be transformed before displaying like brightness, convolution, resizing\. The mouse cursor can be displayed on the processed image, but the actual mouse pointer cannot be captured, so the mouse cursor is always displayed as crosshair\. The transform operations can be combined sequentially\.

## Example usage scenarios

There are example scenarios, in which you can use LivePic application\.

### Zoom screen fragment

This is one of the simplest scenario\. Set relatively small size of grabbed image and set display window larger than grabbed image size\. You can follow mouse cursor\. Display image can be stretched proportionally\.

### Transforming screen image

For this scenario there is needed two monitors configured as extended desktop\. Both monitor should be set at the same image resolution \(matching monitor native resolution is not mandatory\)\. The grab position and size takes whole first monitor screen and the display window takes whole second monitor screen\. The image display should not be stretched\. It can be transformed without resizing, like brightness and contrast changing or image flipping\. At this configuration, you can work watching only the second monitor, which displays whole desktop from first monitor\.

### Previewing the second monitor/projector

If system is configured as extended desktop, but you cannot watch the second monitor directly, it is possible to watch whole image in small window displayed on the first monitor\. The grabbing positions and size takes whole second screen and the images is displayed in small window placed on the first screen\. The image can be stretched or the mouse cursor can be followed\.

### Improvement/enhancing old games display

The old games has limited graphics palette and commonly uses pixel\-art and ordered dithering\. This scenarios requires two monitors configured as extended desktop\. Run game or computer emulator on the second monitor in window, size of the window have to match original game size \(1x, 100% etc\.\)\. Set grab size exactly the same as game screen size and set grab position at the game picture window\. The display window should occupy the whole first monitor screen and image can be stretched\. It is possible to use enlarging algorithms as Scale2x, HQ2x to simulate larger picture\. If the game uses ordered dithering like pixel checkerboard, it is possible to replace dithered area with color, which is simulated by dithering, but details are preserved\. Image is not blurred, dedithering uses pattern matching\. Because dedithering is resource\-demanding process, it is recommended to use with images up to 320x240 to retain high frame rate an use as fewest patterns as possible\. Of course, apart from scaling and dedithering, it is possible to use other transform operations\.

### Real\-time enhance photographs and movies

This scenario is similar to one above\. In transformation it is possible to make convolution filters, brightness, contrast for channels separately\. It is possible to transform luminance and chrominance \(like YUV\)\. To do this, it is possible to convert RGB to L/C, where on channel carries luminance and the other carries chrominance and treat this channel the same way as RGB\. After transforming channels, it should be converted from L/C to RGB using the same parameters\. In most cases, enhancing movies is limited to SD\-resolution movies due to frame rate, especially screen capturing and displaying, which cannot be multithreaded\. The resolution of photographs is not limited, because there are static pictures and processing frame rate is not matter\.

### Displaying tiled image

If you can test tiled display of any image, the grab size have to match image size and position have to be the same as tested image position\. The display can be configured to tiled display and display window must be larger at least two times than tested image\. You can watch, how tiled image looks and if the image is seamless \(designed to tile display\)\.

### Sending video to distant computer

You can use LivePic to send video to another computer via wireless network instead of special video senders\. The only requirement is having another computer, on which you can also run LivePic application\. The one computer will act as server and the other computer will act as client, there is not difference, which computer \(sending or receiving\) acts as a server\. After you set connection, you can send picture in both ways \(by one way at a time\)\. The sending computer captures picture and sends into network, and the receiving computer displays picture based on data from network\. The audio can not be sent, you can use wireless sender to send it\. The keyboard and mouse input are not relayed bedcause such thing is platform\-specified, Qt library does not have API required to do this and you can achieve this using any wireless keyboard/mouse\. Both, for autio transmission and keyboard/mouse input you can use appropriate Bluetooth device instead of specialized wireless device\.

### Capturing and translating text from screen

Using Google Cloud API with valid key, you can recognize \(using OCR technique\) and save text existing on the screen\. If the text is in language, which is not understandable for you, you can enable translation into selected language, which is understandable for you\. The original text will be covered and the translated text will be superimposed\. By the such way, you can lively translate applications, web pages, movies with subtitles and more, which contains the text\. You can save the text into file if you need to get the text from image\.

### Recording and slow motion

In some amateur or documentary movies, some scenes seems be displayed too fast to take a look at them\. You can record the movie display and you can watch the captured image frame by frame or play it slower or faster in forward or backward direction\.

# Picture and display settings

After program running you are set the picture grabbing and display settings, which are meaning for:


* **Grab position** \- Position of grabbed image\.
* **Grab size** \- Size of grabbed image\.
* **View position** \- Position of viewing window\.
* **View size** \- Size of viewing window\.
* **Fullscreen** \- Switch viewing window between normal display and fullscreen display\. In some cases after switching wiewing window may display picture impropertly, in such case drag mouse cursor in the viewing window or click **Restart** button\.
* **Mouse type** \- Mouse cursor draw type:
  * **None** \- no mouse cursor\.
  * **High contrast** \- draw mouse cursor using only minimum and maximum values of channels\.
  * **Negative** \- draw mouse cursor using color negative\.
* **Folow mouse** \- Move grab position according mouse cursor movement\.
* **Mouse size** \- Size of mouse cursor crosshair legs \(length and thickness\)\.
* **Margin left, top, right, bottom** \- The distance between window edge and viewing picture edge, the negative value allow cropping picture\.
* **View mode** \- Sets view stretch mode:
  * **Center** \- View picture in original size\.
  * **Margin**/**Margin smooth** \- Stretch proportionally with margins \(whole picture is visible\)\.
  * **Fill**/**Fill smooth** \- Stretch proportionally to fill whole window \(picture is cropped\)\.
  * **Stretch**/**Stretch smooth** \- Stretch picture disproportionally to fill whole window without interpolation\.
  * **Tile center** \- Display tiled picture, tile center in window center\.
  * **Tile corner** \- Display tiled picture, tile corner in window center\.
* **Offset X, Y** \- The viewing picture offset, work only in **Center**, **Tile center** and **Tile corner** modes\.
* **Background color** \- Change color of viewing window\.

The other settings are:


* **Pipes** \- Number of pipes used in multithreading picture transforming:
  * **0** \- No pipes\.
  * **Positive values** \- Display picture before capturing\.
  * **Negative values** \- Display picture after capturing\.
* **Threads** \- Number of threads used in one picture transform step, except from some special case\.
* **Throttle** \- Additional sleep time before \(positive value\) or after \(negative value\) picture capture\.
* **Delay line length** \- Length of delay line in frames and delay line position in image processing line:
  * **Auto** \- Use this position, which handles the less amount of temporaty data\.
  * **Before** \- Place delay line before transform\.
  * **After** \- Place delay line after transform\.
* **Delay line temp file** \- Name of temporary file to store temporary delay line memory, when blank, the delay line will be stored in memory\.
* **Mouse margin** \- Distance from viewing window edge, which is sensitive to mouse, placing cursor within this margin it is possible to resize window \(indicated as double arrow cursor\) or display **Settings** window if you click in the corner or viewing window \(indicated as hand cursor\)\. You can move the window if you place the cursor beyond the margins, \(the cursor on this area is invisible\) followed by drag and drop\.
* **Gamma x1000** \- Set display gamma correction used in some transform types to operate on perceived color value instread of real color value\.

# Transform setting

On the **Transform** tab, you can define picture transform sequence\. Below sequence list, there are following buttons:


* **Add list** \- Add transform list to the item on the drop\-down list above the transform list\.
* **Remove list** \- Remove selected transform list on the drop\-down list above the transform list\.
* **Add item** \- Add transform item\.
* **Remove item** \- Remove transform item\.
* **Move up**, **Move down** \- Move transform item on the list\.
* **Enable/disable** \- Enable or disable selected item\.

The tab box below buttons is used to define transform item\. If transform list is empty or there is not selected item, the settings does not matter in picture transform\.

Transform kind is selected by selecting tab in transform definition tab box\. Every tab has settings specified to certain transform kind\. The current transform parameters are showed in transform list\.

Transform list is applied every time in starting or restarting working, so if you change any transform setting during working, you have to click **Restart** button in **Main control** box\.

# Transform: Triple 256\-item Look Up Table

There is defined three 256\-item arrays, one per color channel\. Every item is a number from 0 to 255, which defines, for which value is replaced every value number\. The look\-up table can be generated by following ways:


* **From file** \- Load table from textual or binary file which is generated manually or from other software
* **Brightness** \- Picture brightness
* **Contrast** \- Picture contrast
* **Negative** \- Partially or fully inverting change value to acquire negative color or solarize effect
* **Gamma** \- Gamma transform

The **Save** button allows to save current LUT into textual or binary file in specified resolution\. The saved file can be used as LUT from file\. If resolution is lower than 8, the file will be smaller, but the posterization effect can be observed when using this file\. The **Gamma correction** field allows to include display gamma in **Brightness**/**Contrast**/**Negative**/**Gamma** transform\.

## Textual file structure

The first line contains LUT resolution value \(between 1 and 8\)\. The next lines \(between 2 and 256 according resolution\) contains three number sequence according to color channel, in order Red\-Green\-Blue\. The number of item equals 2 powered to resolution number

## Binary file structure

The first byte has value between 1 and 8, and means LUT resolution\. The next following bytes represents table values sequentally in order Red\-Green\-Blue\. The whole file size is between 7 and 769, is equals formula: `(3*(2^Resolution)+1)`\.

# Transform: Single 16777216\-item Look Up Table

This transform uses look\-up table, which defines replacement of each color from 24\-bit palette, so this LUT consists of 16777216 item, each item consist of 3 values, which represents color channels\.

The look\-up\-table can be generated by following ways:


* **From file** \- Load table from textual or binary file which is generated manually or from other software
* **Saturation** \- Change color saturation, it uses RGB weight values to calculate luminance
* **RGB \-> L/C** \- Convert from RGB to luminance/chrominance color representation, where luminance is in one channel and two chrominance channels are the other channels\. There also is possible to create chroma\-only channels, but this conversion cannot be inverted due to lack of luminance information\. The RGB weight field defines weight of color channels weight in luminance calculation\. In this conversion, the Luma only field value is not used\. After conversion the chrominance values are between 0 and 255, but 127 means neutral value\.
* **L/C \-> RGB** \- Convert from luminance/chrominance to RGB color representation\. This conversion should have the same parameters as previous **RGB \-> L/C** conversion\. If Chroma only conversion is selected, the luminance will be got from Luma field and uniform for whole picture\.
* **Channels** \- Swap and copy color channels\. It can be used for example to convert between RGB and BGR representation or display on color channel as grayscale picture\.
* The **Save** button allows to save current LUT into textual or binary file in specified resolution\. The saved file can be used as LUT from file\. If resolution is lower than 8, the file will be smaller, but the posterization effect can be observed when using this file\. The **Gamma correction** allows to include display gamma in **Saturation** or **RGB<\->LC conversion**\.

## Textual file structure

The first line consists of two number\. The first number is the resolution and the second number means number of color columns\. The one color consists of three value, so if there is 256 columns defined, the one row consists of 768 numbers\. The number of column must be divisor of 16777216\.

The next following rows consists of color values in Red\-Green\-Blue order\. The most significiant color channel is blue and the least significiant value is red\. The file is read line by line\. For example, if resolution is 2 \(four levels of each channel\), there are 64 colors replacement defined by following order \(value are RGB\): `(0, 0, 0); (1, 0, 0); (2, 0, 0); (3, 0, 0); (0, 1, 0); (1, 1, 0); (2, 1, 0); (3, 1, 0); (0, 0, 0); (1, 2, 0); (2, 2, 0); (3, 2, 0); (0, 3, 0); (1, 3, 0); (2, 3, 0); (3, 3, 0); (0, 0, 1); (1, 0, 1); (2, 0, 1); (3, 0, 1); (0, 1, 1); (1, 1, 1); (2, 1, 1); (3, 1, 1); (0, 0, 1); (1, 2, 1); (2, 2, 1); (3, 2, 1); (0, 3, 1); (1, 3, 1); (2, 3, 1); (3, 3, 1); (0, 0, 2); (1, 0, 2); (2, 0, 2); (3, 0, 2); (0, 1, 2); (1, 1, 2); (2, 1, 2); (3, 1, 2); (0, 0, 2); (1, 2, 2); (2, 2, 2); (3, 2, 2); (0, 3, 2); (1, 3, 2); (2, 3, 2); (3, 3, 2); (0, 0, 3); (1, 0, 3); (2, 0, 3); (3, 0, 3); (0, 1, 3); (1, 1, 3); (2, 1, 3); (3, 1, 3); (0, 0, 3); (1, 2, 3); (2, 2, 3); (3, 2, 3); (0, 3, 3); (1, 3, 3); (2, 3, 3); (3, 3, 3)`\.

## Binary structure file

The first byte has value between 1 and 8, and means LUT resolution\. The next following bytes represents table values sequentally in order Red\-Green\-Blue\. The color value order are the same as described in textual file structure\. The file size equals formula: `(3*(2^Resolution)*(2^Resolution)*(2^Resolution)+1)`, so the file size is between 25 and 50331649\.

# Transform: Convolution

The convolution transform uses three 5x5 matrices, one for each color channel \(red, green, blue\)\. It is possible to use one matrix and other parameter definition to two or all channel\. The Gamma correction field indicates, that output color are calculated using perceived intensity \(including display gamma\) instead of intensity values\. The Common field provides this ability, for example, you have to define matrix and parameters for red color channel only to use this for all channels\.

For each pixel in picture, the pixel is represented by center matrix field, the other fields represents adjacent pixels\. The pixels beyond picture border repeats values from border pixels\. For channel separately, for each pixel, result color value is calculated as follows:


1. Get color of 25 pixels \(the current and 24 adjacent pixels\)\.
2. Multiply pixel value by matrix cell value\.
3. Sum calculated values to get one value\.
4. Add In offset value\.
5. Divide by divider\.
6. Add out offset value\.
7. Limit pixel value in range between 0 and 255\.

The transform kind is also called as convolution, kernel, mask, filter etc\.

# Transform: Dedithering

This transform replaces simulated color by real color, but it can preserve details, because does not blur picture\. The color can be simulated by ordered dithering, which uses regular patterns\. This technique was frequently used in old games and graphics software, where color palette was limited to 16 colors\. Color simulated by random\-based or diffused dithering algorithm cannot be replaced to real color through dedithering\.

Each template can create from one to four patterns \(it is possible to set 0 patterns, so this template will not be used\), all patters in one template are rotated the same pattern\. The pattern is 5x5 matrix, which can define up to 4 colors layout\. The 0 value indicates that color of the pixel is not important\. The numbers from 1 to 4 defines color, which must be the same in all pixels with the same number to match pattern\. If the pattern define dithering for two colors \(the most frequently case\), it must contain the 1 and 2 number and not contain 3 and 4 number\. Of course, the pattern can contain the 0 number for neutral pixels\. The **Color 1**, **Color 2**, **Color 3** and **Color 4** fields defines color factor\. If pattern defines dithering of two colors and the used color intensity proportions is equal \(for example, the checkerboard pattern\), the value of **Color 1** and **Color 2** must be greater than **0** and equal each other, and the values of **Color 3** and **Color 4** must be equal **0**\. If dithering pattern has 4 times more pixels of **Color 1** than **Color 2**, the **Color 1** value must be 4 times greater than **Color 2** value\.

The drop\-down lists defines the pattern flipping or rotation variants, which are used to transform picture\. It is possible to set up to 4 pattern variants within one template, ordering from left to right\. The following variants are following:


* **None** \- Do not use
* **Straight** \- Use without flipping or rotatin
* **U/D** \- Upside down \(flip both horizontal and vertical\)
* **Hori** \- Flip horizontal
* **Vert** \- Flip vertical
* **Main D** \- Flip by main diagonal
* **Other D** \- Flip by other than main diagonal
* **Clk** \- Rotate clockwise
* **Cnt clk** \- Rotate counter clockwise

## Dedither processing

For each picture pixel, there is read 24 adjacent pixels and it is searched for matching pattern \(the dedither pattern list order is very important\)\. If found matching pattern, the pixel color are replaced by color calculated using adjacent pixels and color factors of the first matching pattern\. If matching patterns not found, the pixel color will not be changed\.

Because the dedithering requires relatively high computing power, it is recommended to use the fewest patterns as possible\.

# Transform: Resize/scale

This transform is user to change image size in three ways\.

## Resize

Resize is the simple resize, which can be with smoothing or without it\. The high quality smoothing requires more computing power than fast smoothing, but it has better quality\. The new size is defined by ratio of original size\. The width and height ratios are defined by numerator and denominator for width and height\. For example, to enlarge image 4 times, the size numerator for both width and height can be 4, while the denominator for both dimensions are 1\. To shrink image 3 times, the size numerator can be 1 and denominator can be 3\.

## Scale

The scale way offers enlarging 2 times, 3 times or 4 times and is dedicated to pixel\-arts, pictures from emulated old computer or game console or other similar pictures\. It uses **Scale** or **HQ** algorithm\. If **Separate channels** are checked, each color channel will be treated as separate grayscale image\.

## Subpixels

This offers subpixel composition or decomposition\. This operations supports RGB stripes layout only, which are in the most LCD and plasma screens\. The monitor can be rotated, so there is possible to select one of four subpixels layout\. Each composition and decomposition transforming, which uses luminance, user RGB weight to calculate luminance\. The following composition and decomposition is described for horizontal RGB layout, the transforms for other layouts are analogous\.

### Subpixel composition

The composition means shrinking image three times with subpixel rendering\. The vertical shrinking is simple shrink three times, for each pixels there is calculated average color of vertically placet three pixels\. The horizontal shrinking uses five horizontally placed pixels using following formulas, where `L(R,G,B) = ((R\*RWeight+G\*GWeight+B\*BWeight)/(RWeight+GWeight+BWeight))`\.

The five source pixels in the formulas are:

`{RLL,GLL,BLL}{RL,GL,BL}{R,G,B}{RR,GR,BR}{RRR,GRR,BRR}`

Composite color without smoothing \- `{RL,G,BR}`

Composite color with smoothing \- `{(RLL+RL+R)/3,(GL+G+GR)/3,(B+BR+BRR)/3}`

Composite luminance without smoothing \- `{L(RL,GL,BL), L(R,G,B), L(RR,GR,BR)}`

Composite luminance with smoothing \- `{(L(RLL,GLL,BLL)+L(RL,GL,BL)+L(R,G,B))/3, (L(RL,GL,BL)+L(R,G,B)+L(RR,GR,BR))/3, (L(R,G,B)+L(RR,GR,BR)+L(RRR,GRR,BRR))/3}`

### Subpixel decomposition

In theory, the subpixel decomposition is inverse of subpixel composition and it can be used to zoom subpixel\-rendered text and pictures\. The decomposition means three time picture enlarging both horizontally and vertically\. In practice, the horizontally enlarging is not simple zoom in due to layout of subpixels\.

The vertically enlarging is simple three times zoom in with smoothing or without it, depending on Smoothing field checking\. The "Color subpixels" and "Gray subpixels" are the simple simulation, how image is actually displayed on screen \(the only difference between this models is displaying color or gray simulated subpixels\)\. The color areas will be rendered with vertical stripes due to varying subpixel intensity\.

The third decomposite modes uses luminance \(luma\) and may use chrominance \(chroma\) and there is most recommended decomposite mode\. The luminance is calculated using channel weights from RGB weight fields\. The decomposite of one pixel really uses three pixels of source image \(the current and two adjacent\)\. The chrominance calculation may use adjacent pixels and pixels above and below current pixels\. This uses the fact, that every subpixel with two adjacent subpixels creates whole RGB color\.

The **Decomposite chroma** field allows to set, how many horizontally placed subpixels are used to calculate average chrominance, by following:


* **Base** \- The number of sumbixels in current line\.
* **Line 1** \- The number of sumbixels in the first lines above and below current line\.
* **Line 2** \- The number of sumbixels in the second lines above and below current line\.

The number indicates, how many subpixels in this lines are used horizontally\. The higher number causes more chrominance blur and less chrominance artifacts\. The **0** value indicates, that chrominance will not be used\.

The luminance is `L(R,G,B) = ((R\*RWeight+G\*GWeight+B\*BWeight)/(RWeight+GWeight+BWeight))`\.

The one pixel of source image creates three pixels, where luminance will be calculated from values:


`{R,G,BL1}`
`{R,G,B}`
`{RR1,G,B}`

In the one line, there can be used three or five adjacent pixels for chrominance, which will be signed as: `{RL2,GL2,BL2}{RL1,GL1,BL1}{R,G,B}{RR1,GR1,BR1}{RR2,GR2,BR2}`

The chrominance for 11 subpixels \(the most widest variant\) will be calculated using following pixel values:


`{RL2,GL2,BL2}`
`{RL1,GL2,BL2}`
`{RL1,GL1,BL2}`
`{RL1,GL1,BL1}`
`{R,GL1,BL1}`
`{R,G,BL1}`
`{R,G,B}`
`{RR1,G,B}`
`{RR1,GR1,B}`
`{RR1,GR1,BR1}`
`{RR2,GR1,BR1}`
`{RR2,GR2,BR1}`
`{RR2,GR2,BR2}`

There are 13 chrominance values, for final pixel there will be used as follows:


* For red subpixel: The first 11 values\.
* For gree subpixel: The 11 values without the first and the last value\.
* For blue subpixel: The last 11 values\.

The chrominance of one channel is the difference between luminance value and color channel value, so, it can be positive or negative value\.

# Transform: Flip/rotate

This is a simple transform, which flips or rotates image depending on selection in **Flip or rotate** field\. The rotation or flipping by diagonal are executed in one thread regardless number of threads in settings due to complexity of this operation when is splitted into threads\.

# Input, output, network and other settings

Using settings on the **Input/Output** tab, you can achieve transmitting picture via network ans access to ther settings\.

## Other settings

On this tab there are following settings, which are not related to network transmitting:


* **Picture window on top** \- Show Picture window on the top of other windows \(requires application restart\)\.
* **Settings window on top** \- Show Settings window on the top of other windows \(requires application restart\)\.
* **Recorder window on top** \- Show Recorder window on the top of other windows \(requires application restart\)\.
* **Close application by closing Settings window** \- If checked, when you close Settings window using system X button, the whole application will be closed\.
* **Screen bounds \(Left, Top, Right, Bottom\)** \- Coordinates of bounds, within which grabbing area will be kept while mouse ursor following is turned on\. This is usable to avoid messy image when you grab area outside screen area or limit grabbing to one screen or part of the screen\. You can press the **Auto** button to switch between bounds, which covers all displays \(if you have more than one\), one display and not bounded \(bounds from \-999999 to 999999 in both axis\)\. If you changed bounds manually, the **Auto** button \(if pressed once\) will switch to default bounds, which covers all screens\.

## Transmitting picture via network

LivePic has ability to transmit picture via network using TCP or UDP protocol\. To transmit picture via network, at first, you have to create connection between two instances of LivePic application\. The one instance is on the sending computer and the other instances is on the receiving computer\.

You can transmit pictures if your network configuration meets one of three following scenarios:


1. Both computers are in the same network\. The transmitting computer is directly accessible from the receiving computer and the receiving computer is directly accessible from the transmiting computer\.
2. The receiving computer is in subnet behind NAT related to the transmitting computer\. The transmitting computer is directly accessible from the receiving computer and the receiving computer is not directly accessible from the transmiting computer\.
3. The transmiting computer is in subnet behind NAT related to the receiving computer\. The transmitting computer is not directly accessible from the receiving computer and the receiving computer is directly accessible from the transmiting computer\.

### Establishing TCP connection

In the TCP connection, one instance is the server and the other instance is the client\. There is not difference, if the sending or receiving computer is server\. You have set as server thic computer, which is accessible via network from the other computer\. If both computers are visible from each other computer \(scenario 1\), you may choose, which computer will be server and which computer will be client\. In other cases \(scenario 2 or 3\), set as server this computer, which is directly accessible from the other computer, regardless picture transmission direction\.

On the computer applied as server, input address and port for listening in the **Address** and the **Port** fields\. To listen for any connection regardless the address of client computer, set **Address** to **0\.0\.0\.0**\. To sart server, click the **Start TCP server** button\.

On the other computer, which is applied as client, int the **Address** field input the address of server and in the **Port** field, input the same port, on which server listens\. To start client, click **Start TCP client** button and connection will be established\.

The **Disconnect** button closes the connection\. On the other computer, the connection will be closed automatically after this\.

### Establishing UDP connection

Actually, in the UDP protocol, there is not an logical connection and computers are not distinguished by server and client\. The communication is achieved by binding instance with address and port\. Similarly to TCP connection, at least one computer must be visible from the other computer to establich the connection\.

On the both computer set the address in the **Address** field to **0\.0\.0\.0** and set port number in the **Port** field to any number, but port number on both computers must be different\. Instead of **0\.0\.0\.0** you can set the real computer IP address\. Then, click the **Bind UDP** on both computers\.

After binding with address and port on both computers, futher proceeding depends on your network configuration, especially relation between computers\.


* Both computers are directly accessible from each other \(scenario 1\):
  1. On the transmitting computer input the IP address of the receiving computer into **Address** field\.
  2. On the transmitting computer input the same port number into **Port** field, which was choosen on the receiving computer\.
  3. On the receiving computer input the IP address of the transmitting computer into **Address** field\.
  4. On the receiving computer input the same port number into **Port** field, which was choosen on the transmitting computer\.
  5. Perform the two\-way communication test by clicking the **Two\-way test** button on one of the computers\.
* One computer is directly inaccesible brom the other computer \(scenario 2 or scenario 3\):
  1. On the inaccessible computer input the IP address of the accessible computer into **Address** field\.
  2. On the inaccessible computer input the same port number into **Port** field, which was choosen on the accessible computer\.
  3. Perform the one\-way communication test by clicking the **One\-way test** button on the inaccessible computer\. During the test, the router, which hides the inaccessible computer from the accessible computer will allow to sending the messages in opposite direction\.
  4. On the accessible computer input the IP address displayed in the received message into **Address** field \(there will be probably the address of router\)\.
  5. On the accessible computer input the port number displayed in the received message into **Port** field \(there will be probably the same port number, which was choosen on the inaccessible computer\)\.
  6. Perform the two\-way communication test by clicking the **Two\-way test** button on one of the computers\.
* If your configuration meets the scenario 3, there is not necessary to get two\-way communication working\. You can treat the UDP connection as established directly after successfully performed one\-way communication test \(the step 3\)\. In this case, the **Refresh** button on the receiving computer will not work\.

The **Disconnect** button unbounds address and port\. You have to do it on both computers\.

### Testing the communication

You can test the one\-way or two\-way connection using one of two apropriate buttons:


* One\-way connection test: Click the **One\-way test** button\. If addresses and ports was input correctly, on the computer there will be displayed **message n sent** messages \(where **n** is randomly choosen number\) and on the other computer tere will be displayed **message n received**\. The **n** number must be the same in all two messages on both computers per once test\.
* Two\-way connection test: Click the **Two\-way test** button\. If addresses and ports was input correctly, on the computer there will be displayed **request n sent** and **response n received** messages \(where **n** is randomly choosen number\) and on the other computer tere will be displayed **request n received** and **response n sent** messages\. The **n** number must be the same in all four messages on both computers per once test\.

### Picture input and output modes

You have to set input and output by setting one of the **Picture input and output** modes:


* **From screen to screen** \- Grab and display picture on this computer\. Use this mode if transmission via the network is not used\.
* **From screen to network \- normal** \- Grab picture from this computer and send to network as normal pictures, which presents the grabbed frames\. Use this mode on the transmitting computer\. This is recommended when you use UDP connection, because UDP protocol not guarantees delivery all sent data and send data may be received in different order\.
* **From screen to network \- differential** \- Works same as **From screen to network \- normal**, but sender creates differential pictures, which has smaller size than normal pictures, when transmitted picture is rather statical, like photograph, slideshow, text editor application\. On the other hand, this value requires slighty more computational power on the sending computer, because for every picture it creates two sets of picture data \(normal and differential\), sends this set, which is smaller and finnaly decodes the sent data to create local buffer, which is used to create next differential picture\.
* **From network to screen** \- Grab picture from network buffer instead of screen\. Use this value on receiving computer to receive network transmission\.

If you use **From screen to network \- differential** mode, especially if you use UDP connection, the received picture may be going incorrect or unreadable\. If received picture is incorrect, click the **Refresh** button on transmitting or on the receiving instance\. If you click the **Refresh** button on the transmitting instance \(in **From screen to network** mode\), the next picture will be sent as normal regardless picture data size\. If you clich the **Refresh** button on the receiving instance \(in **From network to screen** mode\), the refresh request will be sent to other computer\.

### Preparing picture transmission

After connection establishing, you have to propoertly set the **Picture input and output** value on both computer\. On the sending computer use one of the two **From screen to network** values and on the receiving computer use **From network to screen** value\. You can transform picture using **Transform** tab on both computers\.

LivePic uses JPEG or PNG format in transmission\. The fields **Picture quality** allowes to set the quality of normal \(the first value\) and differential \(the second value\) picture\. If value is set between **0** and **100**, the JPEG format of this quality will be used\. If you set the **\-1** value, the PNG will be used\. You can change this values during transmission\.

To avoid hanging up of LivePic during transmission, on both computers set the **Throttle** value to about 100 ms or greater, after this, click **Start** button on both computers\. If you want, after transmisjon started, you may decrease **Throttling** value on both computers to get more fluenty transmission, but keep the transmission stable\. Finally, on the receiving computer **Throttling** may be shorter than **Throttling** on the sending computer\. If you fitted **Throttling** values, later you do not have to increase **Throttling** values, when you want to perform transmission later at the same parameters on the same computers\.

During transmission via network, on the bottom of Settings window you can watch the FPS, which must be more explained in this case:


* On the transmitting computer, the FPS are frames per second, which are actually grabbed, transformed and sent into network\.
* On the receiving computer, the FPS are speed of taking picture from internal buffer to transform and display, so the FPS can differ from FPS on the transmitting computer\. It is recommended to fit **Throttling** value to get a FPS slightly greater than FPS on the sending computer\.

At the bottom of the **Input/Output** tab, there are three values related to network:


* **Status** \- Network mode and status\.
* **Size** \- Minimum, average and maximum size of one received or transmitted picture between two last readings\.
* **Transfer** \- Total picture data size per one second\.

If transmission is not stable or LivePic hangs up during transmission, you may:


* Decrease **Picture quality** values\.
* Increase the **Throttling** value on the transmitting computer\.
* Reduce size of transmitted image by reducing grab size or applying appropriate resize transform on transmitting computer\.

# Google Cloud settings

If you have access to the the Google Cloud Platform with valid API key, you can capture or translate displayed capture text\. Settings related to the Google Cloud are on the Google Cloud tab\.

There are the following settings relatet to the Google Cloud:


* **Enable Google Cloud text capture and translation** \- Enable and use optical character recognition and translation\. It requites and uses delay line\.
* **Google API access key** \- Input valid Google Cloud Platform API key\. LivePic requires **Vision API** and **Translation API** to be aenabled\.
* **Connection slots** \- Number of simultaneous connection slots, changing the setting requires application restart\. There is number of all simultaneous connection with Google\. The connections are asynchronous, each text recognition and translation uses new connection, which is performed on the first free slot\. If the number of connections are exceeded, the text will not be captured\. In most cases, recommended number is **1000**\.
* **Image quality** \- JPEG quality used to send image to Google server\. You can set value from **0** to **100** to use **JPEG** or set **\-1** to use **PNG**, which is the largest and most accurate image format\.
* **Mask overlay** \- Additional border size around detected text field on the image to use more smooth overpainting original text in the image\.
* **Frame decimate** \- Number of frames in the row per once text capture and translation\. If you set small throttle in **Picture and display** tab appropiate to watch movie, you can set decimation between **10** and **20** to process text once or twice per second\. The higher text capturing frequency usually is not needed, but generates significially more network traffic and spends more money for Google services\.
* **Language \(from / to\)** \- Source and destination language used to translate captured text\.
* **Font name and size** \- Font name and size for captured and translated text\.
* **Text alignment** \- The text alignment in each detected text block\.
* **Automatic font size** \- If set, the font size will be adjusted to match the tekst inside text block\. In this case, the font size set in **Font name and size** field is used as minimum font size\.
* **Automatic vertical text** \- Google does not give information about text orientation, it gives only the coordinates of the field points, so the Google does not give any information if the text is written horizontally or vertically \(rotated by right angle\)\. The text orientation will be guessed by better font size matching\.
* **Preserve line breaks** \- Google Translate API does not preserve line breaks, but uses some tricks to force line breaks preservation\.
* **HTML percentage text size** \- Percentage text size in HTML capture file\. It is recommendedn to use value between **80** and **90** to avoid HTML field distortion in certain cases\.

Changing settings other than **Connection slots** and **Frame decimate** are visible immediately during capturing and displaying picture \(you do not have to restart capturing to get efeect of settings change\)\.

# Translating text from screen

The main purpose of text capture is translating all visible text on the fly\. To do this, enable Google Cloud text capture and adjust delay line length to about between 3 and 5 seconds\. the text is captured and translated asynchronously within delay line\. While you are usng the feature, there is difference, if the delay line is before or after image processing, this affects the OCR quality and superimposed text looking\.

During processing, the original text is overpainted and there is superimposed translated captured text\.

If captured and translated text is not displayed or flickers, you can do:


* Increase frame decimate\.
* Increase delay line length\.
* Increate throttle\.
* Check if API access key is valid and the Google services are turned on\.

You can also display original text, if you select **\(no translation\)** as destination language in the **Google Cloud** tab\. In such case, the translation service will not be used\.

Because the Google services is called asynchronously, you can achieve fluently text translating regardless time required from sending image to get translated text\.

# Recording image and text

You can record captured image into memory or disk using recorder available by clicking the **Recorder** button\. You can also watch recording in slow motion, fast motion or manually frame by frame\. You can also capture text to text files\.

Recorder can work only while the picture capture and display works \(after clicking the **Start** button in the **Settings** window\)\.

## Recorder mode

The recorder works as pipeline element, which can be placed in one of the four places\. The place can be sed using **Recoder mode** field\. If you set **None**, the recorder will not be used\. After changing recoder mode, you have to click the **Restart** button\.

If the delay line is placed after transform, there is not difference between **Before transform, before delay line** and **Before transform, after delay line**\. Analogically, if the delay line is placed before transform, there is not difference between **After transform, before delay line** and **After transform, after delay line**\.

The recorder mode affects the following things:


* If translation is enabled, recoded images can be original or with superimposed translated text\.
* Image size if transform changes the image size\.
* Possibility of text translation on the fly during playing\.

## Recording settings

Before recording, you have to set the following fields:


* **Directory** \- To this directory pictures will be saved if you not set the **Memory** mode\. You can select the directory using **Browse** button or manually input path\.\.
* **Picture format** \- The format and quality, which will be used to save pictures:
  * **RAW** \- Raw format, without additional processing\.
  * **BMP** \- BMP format
  * **PNG** \- PNG format
  * **JPEG** \- JPEG format, set quality between **0** and **100** using the field on the right\.
* **Memory** \- Memory mode, the pictures will not be saved on the disk\.

After set above fields, you have to click the **Apply** button\. The existing recording will be cleared, but generated files will remain\. If you selected **JPEG** format, during live view, there will be shown decompressed **JPEG** picture to check the picture quality\.

After clicking the **Apply** button, you can change settings in **Directory** and **Picture format** fields to manually capture single frame\.

## Record and playback

To start the recording click the **Rec start** button, after recording, click the **Rec stop** button\. You can record sequence several times, the newly recorded images will be appended to the end of sequence regardless the playback position\.

The progress bar shows two values\. The first is the playback position, the second is the sequence length\. You can record picture during playback\.

There are the following playback controls:


* **\[ \]** \- Stop playback and display live picture\.
* **\[X\]** \- Stop playback and display freezed frame\.
* **\[<\]** and **\[>\]** \- Move position by one frame and display freezed frame\.
* **<&#124;** and **&#124;>** \- Play slow motion one frame per several live frames\. The playback speed is determined by first value in **Speed factors** field\.
* **<** and **>** \- Play in natural tempo
* **<<** and **>>** \- Play fast motion several frames per one live frame\. The playback speed is determined by second value in **Speed factors** field\.

## Capture one frame and text

If recorder is activated by setting **Recorder mode** to other than **None**, you can save one frame with captured text\. To do this, select directory and picture format in the **Directory** and **Picture format** fields\. Next, set the value in **Capture frame** field\. There is number of frames, which will be waited before capturing, so you have hide the **Recorder** windowand prepare data to capture within the time\. To start capture process, click the **Capture** button\. The time to capture will be presented in progress bar\. You can break the waiting by clicking the **Capture** button one more before filling the time bar\.

There will be saved the picture file in the directory\. The file name consists of current date and time\. The picture will be based on displayed picture, so you can save any recorded frame\.

If the delay line and capturing text are enabled, there will be saved two additional files:


* **HTML** \- File containing the image and text fields looking similarly to picture view\. The background image is embedded into HTML file in JPEG or PNG format\. If you use RAW or BMP format, the empedded image will be in PNG format\.
* **CSV** \- File containing the list of detected text fields\. It is recommended to open this file in spreadsheed application\.

## Save sequence

If you capture sequence into memory, you can save the sequence to serie of files by clicking the save sequence\. You can adjust, how many pictures will be saved per one live frame by adjusting the **Capture frame** value:


* If the value is too low, the sequence saving process will unnecessary take long time\.
* If the value is too high, the application can be freezed or crashed during saving the sequence\.

You have to adjust the value experimentally\. The file name of each picture will consist of date and time, when the picture was recorded\.

# Performance settings and recommendations

In the **Settings** window, there is FPS display during working\. In some cases, the maximum FPS can be is throttled by grabbing screen and displaying picture by operating system, usually there is ca\. 30 FPS\. This speed can decrease if you set high resolution of grabbing picture or if you use a lot of transform operations\. In other operating systems, the grabbing screen operation does not throttle FPS and it is recommended to increase **Throttle \(ms\)** value \(or decrease to get negative value\), when FPS significantly exceedes the display refresh rate\.

## Threads

Every transform opereration \(except of rotating or flipping by diagonal\) are splitted in threads\. If you set 4 in the **Threads** field, every operation will run 4 threads, which one thread will process one quarter of picture, and application will wait for end of all threads before performing next operation\. If you have computer with multi\-core processor, increasing number of threads may shorten time needed for each picture transform operation\.

## Pipes

The pipe can give more processor time for process one picture without decreasing FPS\. If you increase number of pipes, there will be more time to process one picture, but picture will be displayed with small delay\.

The pipe number can be negative or positive value, in both cases, the absolute value is the number of pipes, which will be created\. If you set 0, the piping mechanism will not be used\.

### Positive value of pipes

For example, if you set **Pipes** field for 4, application will work as follows:


1. Create dummy picture and assign it as input picture for all pipes\.
2. Run picture transform in separated thread for pipe 0, 1, 2 and 3 \(all pipes\)\.
3. Wait for finish picture transform thread for pipe 0\.
4. Display picture from pipe 0\.
5. Grab new picture into pipe 0\.
6. Run picture transform in separated thread for pipe 0\.
7. Wait for finish picture transform thread for pipe 1\.
8. Display picture from pipe 1\.
9. Grab new picture into pipe 1\.
10. Run picture transform in separated thread for pipe 1\.
11. Wait for finish picture transform thread for pipe 2\.
12. Display picture from pipe 2\.
13. Grab new picture into pipe 2\.
14. Run picture transform in separated thread for pipe 2\.
15. Wait for finish picture transform thread for pipe 3\.
16. Display picture from pipe 3\.
17. Grab new picture into pipe 3\.
18. Run picture transform for pipe 3\.
19. Go to operation 3\.

### Negative value of pipes

For example, if you set **Pipes** field for \-4, application will work as follows:


1. Create dummy picture and assign it as input picture for all pipes\.
2. Run picture transform for pipe 1, 2 and 3 \(all pipes except of pipe 0\)\.
3. Grab new picture into pipe 0\.
4. Run picture transform in separated thread for pipe 0\.
5. Wait for finish picture transform thread for pipe 1\.
6. Display picture from pipe 1\.
7. Grab new picture into pipe 1\.
8. Run picture transform in separated thread for pipe 1\.
9. Wait for finish picture transform thread for pipe 2\.
10. Display picture from pipe 2\.
11. Grab new picture into pipe 2\.
12. Run picture transform in separated thread for pipe 2\.
13. Wait for finish picture transform thread for pipe 3\.
14. Display picture from pipe 3\.
15. Grab new picture into pipe 3\.
16. Run picture transform in separated thread for pipe 3\.
17. Wait for finish picture transform thread for pipe 0\.
18. Display picture from pipe 0\.
19. Go to operation 3\.

## Throttling

In case, when, high FPS is not necessary or FPS exceedes display abilities, you can throttle capturing image speed by setting **Throttling \(ms\)** value, which is time in milliseconds an can be positive or negative\. The values means additional thread sleeping before \(positive value\) or after \(negative value\) capture picture\.

## Performance recommendations

To achieve optimal picture transforming, create transform list according rules:


* All LUT\-based operations should be directly followed one by other\. The following LUT\-based operations will be internally merged into one operation\.
* Dedither operation causes internally creates 2 operations, the first directly before and the second directly after dedithering\. This operations convert picture between RGB representation and color number representation with 2\-pixel margins to increase dedither performance\. If you want to use several dedither operations, you should define them one after other directly\.
* If you want to get rotated of flipped picture, define the flip/rotate operation once\. The all operations can by applyed regardless of picture orientation \(after slighty modification in some cases\)\.
* As far as possible, use display resizing mode instead of picture resize transform\.
* In most cases, two convolution operations with 3x3 kernel or smaller kernel can be replaced with one convolution operation with 5x5 kernel, which gives the same effect\. Use as few convolution operations as possible\.
* In dedithering, use as fewest patterns as possible\.
* Generally, use as few transform operations as possible\.

Apart from transform optimization, you may increase performance and fluenty by following:


* Set as small grabbing picture size as necessary\.
* As far as possible, use computer with multi\-core processor\.
* Close all not necessary software, especially software, which taking a lot of computing power\.
* Increase number of threads or pipes, you have to experimentally choose optimal values with FPS and usage of processor cores checking\.
* Otherwise, if high FPS is not required, set throttle time value as high as acceptable\.
* If you want to send picture via network, attempt to achieve as small picture as possible, use the lowest quality as acceptable\.

## Google cloud

If you use capturing text with Google Cloud services, usu the following settings:


* **Throttling \(ms\)** \- About 20\-50 for dynamic images \(like movies\) or above 200ms for static images like photos, applications, web pages\.
* **Frame decimation** \- Dependts on **throttling \(ms\)**, optimally is to achieve capture speed at most 2 or 3 times per one second\.
* **Delay line length** \- You can set as short as possible without text flickering\. In most cases, the optimal delay line length is the number of frames, which gives from 2 to 5 seconds depending on picture size\. The time depends on **throttling \(ms\)** value\.
* **Image quality** \- Set between 70 and 90 for smaller images or between 50 and 70 for large images\. Use As low value as possible, but use enough high values to remain text readable\. The size of picture, which will be sent to server depends on the settings\. Use **100** or **\-1** value for small images and for images with text written using very small font size\.




