#ifndef IMAGE_H
#define IMAGE_H

struct Image 
{
    int width;
    int height;
    int pitch;
    void* pixels;
    
    static Image load_bmp(const char* filepath);
    static void save_bmp(Image image, const char* filepath);
    static void free(Image image);
};

#endif //IMAGE_H
