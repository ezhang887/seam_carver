# Project Proposal
## Project:
My project idea is to create a tool for seam carving, also known as content-aware image resizing. Seam carving is an algorithm that resizies images in such a way to preserve the content of the image, while cropping the image down or scaling the image up.
Basically, when seam carving, the algorithm finds the seam with minimum difference in pixel color to it's neighbors, removes that seam, and repeats the process until the image is now the correct dimension. The process is basically reversed for upsizing and adding seams. 
At a minimum, I plan to have an application where the user can input an image, specify what dimensions to resize do, and save the processed image.
## Libraries:
OpenFrameworks will be used to read/save images and to create a GUI for this application.  
## Resources:
[Wikipedia Article](https://en.wikipedia.org/wiki/Seam_carving)  
[Article from Brown University](http://cs.brown.edu/courses/cs129/results/proj3/taox/)  
[Research Article](http://www.faculty.idc.ac.il/arik/SCWeb/imret/index.html)
