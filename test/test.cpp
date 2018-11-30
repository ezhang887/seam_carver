#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "../src/seam_carver.h"

using std::cout;
using std::endl;

class TestCarver : public SeamCarver{
    public:
        TestCarver(vector<vector<Color>> image) : SeamCarver(image){}
        bool tp(){
            return SeamCarver::transposed;
        }
        int w(){
            return SeamCarver::width;
        }
        int h(){
            return SeamCarver::height;
        }
        vector<vector<Color>> img(){
            return SeamCarver::image;
        }
        vector<vector<double>> energy(){
            return SeamCarver::energy;
        }
        double distance(Color a, Color b){
            return SeamCarver::distance(a,b);
        }
        void transpose(){
            return SeamCarver::transpose();
        }
        vector<int> h_seam(){
            return SeamCarver::find_h_seam();
        }
        vector<int> v_seam(){
            return SeamCarver::find_v_seam();
        }
        void r_h_seam(vector<int> seam){
            return SeamCarver::remove_h_seam(seam);
        }
        void r_v_seam(vector<int> seam){
            return SeamCarver::remove_v_seam(seam);
        }
};

TEST_CASE("TEST"){
    vector<vector<Color>> image;
    const int rows = 3;
    const int cols = 4;

    /*
     * (0,0,0), (0,1,1), (0,2,2), (0,3,3)
     * (1,0,1), (1,1,2), (1,2,3), (1,3,4)
     * (2,0,2), (2,1,3), (2,2,4), (2,3,5)
     */
    for(int i=0; i<rows; i++){
        vector<Color> temp;
        for(int j=0; j<cols; j++){
            temp.push_back(Color(i,j,i+j));
        }
        image.push_back(temp);
    }
    TestCarver t(image);

    SECTION("Member Variables"){
        REQUIRE(t.tp() == false);
        REQUIRE(t.w() == cols);
        REQUIRE(t.h() == rows);
    }

    SECTION("distance()"){
        Color a(255, 255, 255);
        Color b(0,0,0);
        REQUIRE(t.distance(a,b) == sqrt(3*255*255));
        a = Color(1,1,1);
        b = Color(2,3,4);
        REQUIRE(t.distance(a,b) == sqrt(1+2*2+3*3));
    }

    SECTION("transpose()"){
        t.transpose();
        REQUIRE(t.tp() == true);
        REQUIRE(t.w() == rows);
        REQUIRE(t.h() == cols);
    }

    SECTION("energy (and calculate_energy() + pixel_energy()"){
        vector<vector<double>> energy = t.energy();
        vector<vector<double>> expected = {{2*sqrt(2), 3*sqrt(2), 3*sqrt(2), 2*sqrt(2)},{3*sqrt(2),4*sqrt(2),4*sqrt(2),3*sqrt(2)},{2*sqrt(2),3*sqrt(2),3*sqrt(2),2*sqrt(2)}};
        REQUIRE(energy == expected);

        for(int i=0; i<energy.size(); i++){
            for(int j=0; j<energy[i].size(); j++){
                cout << energy[i][j] << " ";
            }
            cout << endl;
        }
    }

    SECTION("check horizontal seam"){
        vector<int> h_seam = t.h_seam();
        vector<int> expected = {0,0,0,0};
        REQUIRE(h_seam == expected);
    }

    SECTION("check vertical seam"){
        vector<int> v_seam = t.v_seam();
        vector<int> expected = {0,0,0};
        REQUIRE(v_seam == expected);
    }

    SECTION("remove horizontal seam"){
        t.r_h_seam(t.h_seam());
        REQUIRE(t.h() == rows-1);
        REQUIRE(t.w() == cols);
    }

    SECTION("remove vertical seam"){
        t.r_v_seam(t.v_seam());
        REQUIRE(t.h() == rows);
        REQUIRE(t.w() == cols-1);
    }
}
