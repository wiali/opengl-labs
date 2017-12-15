//
//  Header.h
//  lab1
//
//  Created by Roman on 04.12.2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdexcept>
#include <cstdio>

#ifndef Header_h
#define Header_h

//GLuint loadTexture(const char * filename)
//{
//    if (!filename)
//    {
//        throw std::invalid_argument("Empty filename");
//    }
//
//    FILE * image = fopen(filename, "rb");
//    if (!image)
//    {
//        throw std::invalid_argument("Wrong texture filename");
//    }
//
//    unsigned char header[54]; // header of the BMP file
//
//    if (fread(header, 1, 54, image) != 54)
//    {
//        throw std::runtime_error("Wrong header of texture file");
//    }
//
//    if (header[0] != 'B' || header[1] != 'M')
//    {
//        throw std::runtime_error("Incorrect BMP texture file");
//    }
//
//    // Reading header
//
//    int dataPos = *(int *) & (header[0x0A]); // offset for data
//    int imageSize = *(int *) & (header[0x22]); // byte size of image
//    int width = *(int *) & (header[0x12]);
//    int height = *(int *) & (header[0x16]);
//
//    if (imageSize == 0)
//    {
//        imageSize = width * height * 3; // 3 - for RGB
//    }
//    if (dataPos == 0)
//    {
//        dataPos = 54; // straight after header
//    }
//
//    unsigned char * data = new unsigned char[imageSize];
//    fread(data, 1, imageSize, image);
//    fclose(image);
//
//    GLuint texId;
//    glGenTextures(1, &texId);
//    glBindTexture(GL_TEXTURE_2D, texId);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//    return texId;
//}

#endif /* Header_h */
