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

#ifdef U_TEST
    friend class TestCarver;
#endif

    public:
        bool transposed;
        int width;
        int height;
        //2d array representation of the image
        vector<vector<Color>> image;

        double energy(int row, int col);
        double distance(Color a, Color b);

        //returns a list of indexes of the current minimum energy seams
        vector<int> find_h_seam();
        vector<int> find_v_seam();

        void remove_h_seam(vector<int> seam);
        void remove_v_seam(vector<int> seam);
        void add_h_seam(vector<int> seam);
        void add_v_seam(vector<int> seam);

        void transpose();

    public:
        SeamCarver(vector<vector<Color>> image);

        vector<vector<int>> carve_h_seams(int num_seams);
        vector<vector<int>> carve_v_seams(int num_seams);
        vector<vector<int>> add_h_seams(int num_seams);
        vector<vector<int>> add_v_seams(int num_seams);

        vector<vector<Color>> getImage();

};

#endif
