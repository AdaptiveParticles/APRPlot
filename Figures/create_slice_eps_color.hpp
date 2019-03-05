//
// Created by Joel Jonsson on 05.03.19.
//

#ifndef PARTPLAY_CREATE_SLICE_EPS_COLOR_HPP
#define PARTPLAY_CREATE_SLICE_EPS_COLOR_HPP

#include <algorithm>
#include <iostream>

#include "src/data_structures/Mesh/PixelData.hpp"
#include "src/io/TiffUtils.hpp"

#include "src/data_structures/APR/APR.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
#include "include/Board.h"
#include <sstream>
#include <string>

#include "create_eps/get_part_eps.hpp"

struct cmdLineOptions{
    std::string output = "output";
    std::string stats = "";
    std::string directory = "";
    std::string input = "";
    std::string color_image = "";
    unsigned int slice = 0;
    bool stats_file = false;
    std::string name = "name";
    float min = 100;
    float max = 2000;
    std::string input_slice = "";
};


#endif //PARTPLAY_CREATE_SLICE_EPS_COLOR_HPP