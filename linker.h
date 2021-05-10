/**
 * @file linker.h
 * @author Luke Foster
 * @brief Header file for the linker. Contains the declaration of the fileData struct and the function declarations for 
 *        manipulating the files during the linking
 * 
 * @date 2021-05-09
 */

#ifndef LINKER_H
#define LINKER_H

#include <fstream>
#include <string>
#include <vector>

// Structure that holds the file names and their respective orig values
struct fileData
{
    std::string fileName;
    unsigned short orig;
};

// Function declarations
void prepareFiles(std::vector <fileData> &files);

void writeFile(const std::vector <fileData> &files);

#endif