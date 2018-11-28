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
    for(int i=0; i<3; i++){
        vector<Color> temp;
        for(int j=0; j<3; j++){
            temp.push_back(Color(i,j,i+j));
        }
        image.push_back(temp);
    }
    TestCarver t(image);
    REQUIRE(t.tp() == false);
    REQUIRE(t.w() == 3);
    REQUIRE(t.h() == 3);
}
