/**
 * @file linker.cpp
 * @author Luke Foster
 * @brief Linker cpp file that contains the function definitions of the program. All of the functions are used to 
 *        manipulate the old files so that a new linked file can be created
 * 
 * @date 2021-05-09
 */

#include "linker.h"
#include <iostream>

using std::fstream;
using std::string;
using std::ios;

/**
 * @brief Function that prepares the files for being linked by opening them and assessing the first 2 bytes to ascertain the position
 *        that they should be in the newly linked file
 * 
 * @param files Vector of fileData structs that contain the file names and the orig values of those files
 */
void prepareFiles(std::vector <fileData> &files)
{
    char first8, last8;
    unsigned short word;
    
    // Evaluate each .ORIG of each file and then store them in the appropriate struct
    for(size_t index = 0; index < files.size(); index++)
    {
        fstream file(files[index].fileName, ios::binary | ios::in);

        file.read(reinterpret_cast <char *> (&first8), sizeof(char));
        file.read(reinterpret_cast <char *> (&last8), sizeof(char));

        // Store the contents of the first 8 bits and last 8 bits into a 16 bit word
        word = ((unsigned int)first8 << 8) + (unsigned int) last8;
        
        // Push word into struct vector
        files[index].orig = word;
        
        file.close();
    }

    bool madeAswap = true;
    
    // Bubble sort
    while (madeAswap)
    {
        madeAswap = false;
    
        for (size_t index = 0; index < files.size() - 1; ++index)
        {
            if (files[index].orig > files[index + 1].orig)
            {
                fileData temp;
                temp = files[index];
                files[index] = files[index + 1];
                files[index + 1] = temp;
            
                madeAswap = true;
            }
        }
    }
}

/**
 * @brief This function accepts a vector of fileData structs and then reads the file contents of each element. Afterwards
 *        it writes the read contents to the newly linked obj file
 * 
 * @param files Vector of fileData structs to be opened and read from
 */
void writeFile(const std::vector <fileData> &files)
{
    char *fileInput;
    int size;

    // Open both the new file and the first old file
    fstream oldFile(files[0].fileName, ios::binary | ios::in | ios::ate);
    fstream newFile("newLinkedFile.obj", ios::binary | ios::out | ios::trunc);

    // Check if the files opened successfully
    if(!oldFile || !newFile)
    {
        std::cout << "Couldn't open file! Closing program!\n";
        exit(1);
    }

    // Determine size of file so that it can be stored in a char array
    size = oldFile.tellg();
    oldFile.seekg(0, ios::beg);
    fileInput = new char [size];

    // Read contents from the file and then write them to the new file
    oldFile.read(fileInput, size);
    newFile.write(fileInput, size);

    oldFile.close();

    // Free dynamically allocated memory
    delete [] fileInput;

    // Padding variable
    unsigned int empty = 0x0000;
    int adjust = (size / 2) - 1;
    int target = files[1].orig;

    // Create x0000 spaces below the first file to force next file to correct location
    for(unsigned short num = files[0].orig; num < target - adjust; num++)
    {
        newFile.write(reinterpret_cast <char *> (&empty), sizeof(unsigned short));
    }

    // Open each old file and write them to the new file, after which we add x0000 to pad for the next file
    for(size_t index = 1; index < files.size(); index++)
    {
        // Open next file
        oldFile.open(files[index].fileName, ios::binary | ios::in | ios::ate);

        // Check if file opened
        if(!oldFile)
        {
            std::cout << "Couldn't open file! Closing program!\n";
            exit(1);
        }

        // Get size of file and allocate memory for the char *
        size = oldFile.tellg();
        fileInput = new char [size];

        // Move forward 2 bytes in file to skip the .ORIG bytes and then start reading
        oldFile.seekg(2, ios::beg);
        oldFile.read(fileInput, size);
        newFile.write(fileInput, size);

        // Free memory of file inputs and close the file
        delete [] fileInput;    
        oldFile.close();

        // Evaluate if last file opened is not the last one
        if((index + 1) != files.size())
        {
            adjust = (size / 2);
            target = files[index + 1].orig;
            
            // Create additional padding for the next file in line
            for(unsigned short num = files[index].orig; num < target - adjust; num++)
            {
                newFile.write(reinterpret_cast <char *> (&empty), sizeof(unsigned short));
            } 
        }
    }
}