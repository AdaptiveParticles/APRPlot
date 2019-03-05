//
// Created by Joel Jonsson on 05.03.19.
//

//
// Created by cheesema on 21/02/17.
//
//
//  Creates eps files of particular image slices from APR
//
//
//
//

#include "create_slice_eps_color.hpp"





bool command_option_exists(char **begin, char **end, const std::string &option)
{
    return std::find(begin, end, option) != end;
}

char* get_command_option(char **begin, char **end, const std::string &option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

cmdLineOptions read_command_line_options(int argc, char **argv){

    cmdLineOptions result;

    if(argc == 1) {
        std::cerr << "Usage: \"pipeline -i inputfile -d directory -img imagefile [-t] [-o outputfile]\"" << std::endl;
        exit(1);
    }

    if(command_option_exists(argv, argv + argc, "-i"))
    {
        result.input = std::string(get_command_option(argv, argv + argc, "-i"));
    } else {
        std::cout << "Input file required" << std::endl;
        exit(2);
    }

    if(command_option_exists(argv, argv + argc, "-d"))
    {
        result.directory = std::string(get_command_option(argv, argv + argc, "-d"));
    }

    if(command_option_exists(argv, argv + argc, "-img"))
    {
        result.color_image = std::string(get_command_option(argv, argv + argc, "-img"));
    }

    if(command_option_exists(argv, argv + argc, "-o"))
    {
        result.output = std::string(get_command_option(argv, argv + argc, "-o"));
    }

    if(command_option_exists(argv, argv + argc, "-name"))
    {
        result.name = std::string(get_command_option(argv, argv + argc, "-name"));
    }


    if(command_option_exists(argv, argv + argc, "-slice"))
    {
        result.slice = std::stoi(std::string(get_command_option(argv, argv + argc, "-slice")));
    }

    if(command_option_exists(argv, argv + argc, "-min"))
    {
        result.min = std::stof(std::string(get_command_option(argv, argv + argc, "-min")));
    }

    if(command_option_exists(argv, argv + argc, "-max"))
    {
        result.max = std::stof(std::string(get_command_option(argv, argv + argc, "-max")));
    }

    if(command_option_exists(argv, argv + argc, "-input_slice_file"))
    {
        result.input_slice = (std::string(get_command_option(argv, argv + argc, "-input_slice_file")));
    }


    return result;

}

int main(int argc, char **argv) {



    // INPUT PARSING

    cmdLineOptions options = read_command_line_options(argc, argv);

    std::string file_name = options.directory + options.input;

    // Read the apr file into the part cell structure
    APRTimer timer;

    timer.verbose_flag = true;

    // APR datastructure
    APR<uint16_t> apr;

    timer.start_timer("read apr");
    //read file
    apr.read_apr(file_name);
    timer.stop_timer();

    create_apr_eps_color(apr,apr.particles_intensities,options.directory,options.output,options.color_image);

}