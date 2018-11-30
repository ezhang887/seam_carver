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
        vector<vector<double>> energy(){
            return SeamCarver::energy;
        }
        double distance(Color a, Color b){
            return SeamCarver::distance(a,b);
        }
        void transpose(){
            return SeamCarver::transpose();
        }
};

TEST_CASE("TEST"){
    vector<vector<Color>> image;
    const int dim = 3;

    /*
     * (0,0,0), (0,1,1), (0,2,2)
     * (1,0,1), (1,1,2), (1,2,3)
     * (2,0,2), (2,1,3), (2,2,4)
     */
    for(int i=0; i<dim; i++){
        vector<Color> temp;
        for(int j=0; j<dim; j++){
            temp.push_back(Color(i,j,i+j));
        }
        image.push_back(temp);
    }
    TestCarver t(image);

    SECTION("Member Variables"){
        REQUIRE(t.tp() == false);
        REQUIRE(t.w() == dim);
        REQUIRE(t.h() == dim);
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

    }

    SECTION("energy (and calculate_energy() + pixel_energy()"){
        vector<vector<double>> energy = t.energy();
        vector<vector<double>> expected = {{2*sqrt(2), 3*sqrt(2),2*sqrt(2)},{3*sqrt(2),4*sqrt(2),3*sqrt(2)},{2*sqrt(2),3*sqrt(2),2*sqrt(2)}};
        REQUIRE(energy == expected);

        for(int i=0; i<energy.size(); i++){
            for(int j=0; j<energy.size(); j++){
                cout << energy[i][j] << " ";
            }
            cout << endl;
        }
    }
}
