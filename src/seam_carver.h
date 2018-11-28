#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include <vector>

using std::vector;

struct Color{
    int r;
    int g;
    int b;

    Color(int _r, int _g, int _b){
        r = _r;
        g = _g;
        b = _b;
    }
};

class SeamCarver{
    
    private:
        bool transposed;
        int width;
        int height;
        //2d array representation of the image
        vector<vector<Color>> image;
        //2d array representation of the image's energy values
        //the energy of each pixel is the distance between the RBG values of the pixel and it's neighbors
        vector<vector<double>> energy;

        vector<vector<double>> calculate_energy();
        double pixel_energy(int row, int col);
        int distance(Color a, Color b);

        //returns a list of indexes of the current minimum energy seams
        vector<int> find_h_seam();
        vector<int> find_v_seam();

        void remove_h_seam(vector<int> seam);
        void remove_v_seam(vector<int> seam);

        void transpose();

    public:
        SeamCarver(vector<vector<Color>> image);

        vector<vector<Color>> getCarved(int v_seams, int h_seams);

};

#endif
