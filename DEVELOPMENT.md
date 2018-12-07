# Development Documentation
## Week 1
During week 1, most of my work was on the GUI and setting up my libraries/testing features. I got openFrameworks (and openFramework plugins for OpenCV to build successfully. I also created a basic outline of how my application would look, with buttons/features for an user to load/save images, and specify what dimensions to carve the image to.
## Week 2
During week 2, most of my work was developing the algorithm. I created a class for the seam carving algorithm that was completely abstracted away from all libraries (except for the STL), so it would be easy to debug/unit test. I finished the algorithm, and created some basic tests for it. I also updated my GUI template a bit, adding features for a user to display the carved image and the seams on the original image in a pop-up window.
## Week 3
During week 3, my main goal is to integrated the GUI + the algorithm together, and get a functional seam carving application. I also added a feature to the algorithm to add seams instead of only removing seams. I also added face detection, but did not fully integrate it with the algorithm. I also updated the GUI a bit, added some more labels to display the image width and height, and also cleaned up some of the algorithm code. I still need to fix a few bugs with displaying the seams.
## Week 4
During week 4, my main goal is to add special features such as face detection, object removal, and clean/optimize up the GUI/algorithm.
