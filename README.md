# CS155-Final-Project

Introduction:

This is a final project for CS-155: Assembly Language. The main focus of the project was to create a linker program for the LC-3 processor so that multiple programs can be loaded into the machine at one time. By accepting numerous .OBJ files, the program will determine the origination of the code in the LC-3's memory and sort them in ascending order by their origin values. Once this processing of the files is completed, it will then take these files and write them to a new linked file, providing additional padding with NOP so that every program is located at the appropriate memory address.

Limitations:

This program was written in an Ubunutu 20.04 environment with C++, using a g++ compiler. As such, the variables used were of appropriate size for reading the binary from the .OBJ files. However, depending upon the system that is being used, there could be problems with reading the origins if the variable sizes used differ from the ones in an Ubuntu environment. Variables that were used that can cause issues are:
    - Unsigned short
    - Unsigned int
    - Unsigned char

Author:
  Luke Foster - lgfoster@nic.edu
