/**
 * @file main.cpp
 * @author Luke Foster
 * @brief Main cpp that initializes the fileData vector and writes the file names that were passed
 *        as arguments when the file was executed. Afterwards it then passes the vector so that it can be processed,
 *        creating a newly linked file in the process
 * 
 * @date 2021-05-09
 */

#include <fstream>
#include <vector>
#include <iostream>
#include "linker.h"

int main(int argc, char *argv[])
{
    // Check if either one or zero files were passed and terminate program
    if(argc <= 2)
    {
        std::cerr << "Not enough arguments! Closing program...\n";
        exit(1);
    }

    // fileData vector that will hold all file names and orig data
    std::vector <fileData> fileInput;

    // Store all of the file names passed as an argument during execution
    for(int index = 1; index < argc; ++index)
    {
        fileData temp;
        temp.fileName = argv[index];
        fileInput.push_back(temp);
    }

    // Prepare files for reading by determining their orig and order
    prepareFiles(fileInput);

    // Write contents of all the files into a newly linked file
    writeFile(fileInput);

    return 0;
}