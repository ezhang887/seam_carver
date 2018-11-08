# Project Proposal
## Project:
My project idea is to create a tool for seam carving, also known as content-aware image resizing. Seam carving is an algorithm that resizies images in such a way to preserve the content of the image, while cropping the image down or scaling the image up.
Basically, when seam carving, the algorithm finds the seam with minimum difference in pixel color to it's neighbors, removes that seam, and repeats the process until the image is now the correct dimension. The process is basically reversed for upsizing and adding seams.  
I plan on having a single window, where users can upload and display an image, specifiy the new dimensions, and can view/save the resized image. I also plan on having an option for users to view image with the seams on top of it.
## Libraries:
OpenFrameworks will be used to read/save images and to create a GUI for this application. Specifically, I will be using the graphics library to load/display/save images. 
## Resources:
[Wikipedia Article](https://en.wikipedia.org/wiki/Seam_carving)  
[Article from Brown University](http://cs.brown.edu/courses/cs129/results/proj3/taox/)  
[Research Article](http://www.faculty.idc.ac.il/arik/SCWeb/imret/index.html)
