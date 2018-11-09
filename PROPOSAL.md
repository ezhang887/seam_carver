# Project Proposal
## Project:
My project idea is to create a tool for seam carving, also known as content-aware image resizing. Seam carving is an algorithm that resizies images in such a way to preserve the content of the image, while cropping the image down or scaling the image up.
Basically, when seam carving, the algorithm finds the seam with minimum difference in pixel color to it's neighbors, removes that seam, and repeats the process until the image is now the correct dimension. The process is basically reversed for upsizing and adding seams. This is (in general) a better way of resizing than scaling/cropping, because it preserves the original scale of the image and also preserves the main content of the image.  
I plan on having a single window, where users can upload and display an image, specifiy the new dimensions, and can view/save the resized image. I also plan on having an option for users to view the image with the seams on top of it.

Some extra features that may or may not be worked on:  
* Face detection 
* Object removal  
## Libraries:
[OpenFrameworks](https://openframeworks.cc/) will be used create a windows application for this project. Specifically, I will be using the [graphics library](https://openframeworks.cc/documentation/graphics/) to load/display/save images. The algorithm/processing will not use any outside libraries. I will also be using [OpenCV](https://openframeworks.cc/documentation/ofxOpenCv/) to draw the seams.
## Resources:
[Wikipedia Article](https://en.wikipedia.org/wiki/Seam_carving)  
[Article from Brown University](http://cs.brown.edu/courses/cs129/results/proj3/taox/)  
[Research Article](http://www.faculty.idc.ac.il/arik/SCWeb/imret/index.html)  
[CMU Article](http://graphics.cs.cmu.edu/courses/15-463/2012_fall/hw/proj3-seamcarving/imret.pdf)
