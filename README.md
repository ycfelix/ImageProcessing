# ImageProcessing
testing using different image processing algorithm<br/>
update: 2019/1/3<br/>
Slope finding algorithm for image with a lot of noise<br/>
<img src="https://github.com/ycfelix/ImageProcessing/blob/master/perfect.jpg" width="100" height="100" /><br/>
The returned value is y=-1.56757x+58, which is very close to the actual result<br/>
In `logic.h` contains the binary image, In `main.cpp` contains the demo code to print slope and intercept<br/>


update: 2018/12/27<br/>
prototype slope finding algorithm, brute force calculation<br/>
Detectable range: 0(horizontal) ~ 45 degrees<br/>
`SlopeFinder.h` and `SlopeFinder.cpp` contains the method to get slope of a given image which is a int[][]


update: 2018/12/27<br/>
edge finding algorithm, re-implementation in C/C++<br/>
`palivis.h` and `palivis.cpp` contains the method to process image, example is shown in `main.cpp`<br/>

Input: 1D array with size 36x36, can be modified, with 0-255 grayscale image<br/>
<img src="https://github.com/ycfelix/ImageProcessing/blob/master/36.png" width="100" height="100" />



output:binary 0/255 edge image of the source<br/>
<img src="https://github.com/ycfelix/ImageProcessing/blob/master/finished%20img.jpg" width="100" height="100" />


