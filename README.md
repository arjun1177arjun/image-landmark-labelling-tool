# Image-landmark-labelling-tool

A simple c++ tool for manual labelling of landmark points on images as is commonly needed in machine learning research. I have used OpenCv library for implementation. The program takes in the video as input and then landmark points can be labelled for each frame one by one. For each image a text file is generated which stores the marked datapoints with each landmark's x and y location separated by a space (advantage of this is it can be direclty read as a matrix variable in Matlab using dlmread function).

## How to use

### Implementation

There are 3 modifications you need to make to run Source.cpp

1) Give the address of the video to cap.open as arguments:
> cap.open("F:\\\inputVids\\\a1.mpg");

here "F:\\\inputVids\\\a1.mpg" is specifying the location of the video a1.mpg on my system.
Be careful to use double backslash in the address.

2) Specify the number of landmark points you have to label:
> const int points = 68;

3) Specify the output folder location of the text files
> myfile.open("F:\\\landmark-points\\\landmarks-img"+to_string(frame)+".txt");

Here the text files will be stored in "F:\\landmark-points\\" folder.

### Output

![Image](image-landmark-labelling-tool/Screenshot (275).png?raw=true "Output Text file")
