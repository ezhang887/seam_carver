#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include <vector>

using std::vector;

struct Color{
    int r;
    int g;
    int b;
};

class SeamCarver{
    
    private:
        int width;
        int height;
        //2d array representation of the image
        vector<vector<Color>> image;
        //2d array representation of the image's energy values
        //the energy of each pixel is the distance between the RBG values of the pixel and it's neighbors
        vector<vector<int>> energy;

        vector<vector<int>> calculate_energy();
        int pixel_energy(int row, int col);
        int distance(Color a, Color b);

    public:
        SeamCarver(vector<vector<Color>> image);

        vector<vector<Color>> getCarved(int v_seams, int h_seams);

};

#endif
