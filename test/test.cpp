#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/seam_carver.h"

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
};

TEST_CASE("TEST"){
    vector<vector<Color>> image;
    /*
     * (0,0,0), (0,1,1), (0,2,2), (0,3,3)
     * (1,0,1), (1,1,2), (1,2,3), (1,3,4)
     * (2,0,2), (2,1,3), (2,2,4), (2,3,5)
     * (3,0,3), (3,1,4), (3,2,5), (3,3,6)
     */
    for(int i=0; i<4; i++){
        vector<Color> temp;
        for(int j=0; j<4; j++){
            temp.push_back(Color(i,j,i+j));
        }
        image.push_back(temp);
    }
    TestCarver t(image);
    REQUIRE(t.tp() == false);
    REQUIRE(t.w() == 4);
    REQUIRE(t.h() == 4);
    vector<vector<double>> energy = {{1},{1},{1}};
}
