#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include <vector>
#include "structs.h"

using std::vector;
    
class SeamCarver{

#ifdef U_TEST
    //Used for unit testing private members, see test/test.cpp
    friend class TestCarver;
#endif

    private:
        bool transposed;
        int width;
        int height;
        //2d array representation of the image
        vector<vector<Color>> image;
        vector<vector<Color>> drawn_image;

        Color average(Color a, Color b);
        double energy(int row, int col, FaceBounds& face_bounds);
        double distance(Color a, Color b);

        void transpose();

    public:
        SeamCarver();
        SeamCarver(vector<vector<Color>> image);

        vector<int> find_h_seam(FaceBounds& face_bounds);
        vector<int> find_v_seam(FaceBounds& face_bounds);

        void load_image(vector<vector<Color>> image);

        void remove_h_seam(vector<int> seam);
        void remove_v_seam(vector<int> seam);
        void add_h_seam(vector<int> seam);
        void add_v_seam(vector<int> seam);

        vector<vector<Color>> getCarved();
        vector<vector<Color>> getDrawn();

};

#endif
