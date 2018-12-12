# Seam Carver
Seam Carver is an openFrameworks desktop application that performs various seam carving applications. 
It currently supports removing seams, adding seams, generating a GIF of the carving process, and face detection.

See the project [proposal](https://github.com/uiuc-fa18-cs126/finalproject-Bo887/blob/master/PROPOSAL.md) and [documentation](https://github.com/uiuc-fa18-cs126/finalproject-Bo887/blob/master/DEVELOPMENT.md) for more details.

### Dependencies:
  The only dependencies are openFramework addons. See [addons.make](https://github.com/uiuc-fa18-cs126/finalproject-Bo887/blob/master/addons.make) for more detail.
  - [ofxGui](https://openframeworks.cc/documentation/ofxGui/) was used to create most of the graphical components in the windows.
  - [ofxCv](https://github.com/kylemcdonald/ofxCv) was used to enable face detection.
      - Note: I had an issue initially with building ofxCV, and applied [this](https://github.com/openframeworks/openFrameworks/issues/6012) fix.
      - Note: [ofxOpenCv](https://openframeworks.cc/documentation/ofxOpenCv/) was not actually used in any way, but for whatever reason, I needed to add it to my [addons.make](https://github.com/uiuc-fa18-cs126/finalproject-Bo887/blob/master/addons.make) for ofxCv to compile properly.
  - [ofxGif](https://github.com/Geistyp/ofxGif) was used to create, save, and load gifs.
  - [ofxProgressBar](https://github.com/atduskgreg/ofxProgressBar) was used to create the loading bar in the main winow.

### Steps to run:
  1. [Install openFrameworks](https://openframeworks.cc/download/)
  2. [Install dependencies]()

#### Contributors:
  - Eric Zhang
