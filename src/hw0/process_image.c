#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
     if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (c < 0)
        c = 0;
    if(x >= im.w)
        x = im.w - 1;
    if(y >= im.h)
        y = im.h - 1;
    if (c >= im.c)
        c = im.c - 1;

    float pixel = im.data[c*im.h*im.w + y*im.w + x] ;
    
    return pixel;
    // TODO Fill this in
    return 0;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    im.data[c*im.h*im.w + y*im.w + x] = v;
    
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for(int i=0; i<im.c*im.h*im.w; i++)
        copy.data[i] = im.data[i];
    return copy;
}

image rgb_to_grayscale(image im)
{
     assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in

     int next_channel = gray.w * gray.h;
    for(int y=0; y<gray.h; y++)
        for(int x=0; x<gray.w; x++)
            gray.data[y * gray.w + x] = 0.299 * im.data[y * gray.w + x] + 0.587 * im.data[y * gray.w + x + next_channel] + 0.114 * im.data[y * gray.w + x + next_channel * 2];
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
     int start = c * im.h * im.w;
    
    for(int i=start; i<start + im.h*im.w; i++)
        im.data[i] += v;
}

void clamp_image(image im)
{
    // TODO Fill this in
     for (int i=0; i<im.c*im.h*im.w; i++)
        if(im.data[i] < 0.)
            im.data[i] = 0.;
        else if(im.data[i] > 1.)
            im.data[i] = 1.;
}

// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    float H,V,S;
    float R,G,B;
    float C,H_=0;
    for(int y=0; y<im.h; y++)
        for(int x=0; x<im.w; x++){
            R = get_pixel(im, x, y, 0);
            G = get_pixel(im, x, y, 1);
            B = get_pixel(im, x, y, 2);
            
            V = three_way_max(R,G,B);
            C = V -three_way_min(R,G,B);
            if (V == 0)
                S = 0;
            else
                S = C / V;

            if (C == 0.)
                H_ = 0;
            else if(V==R)
                H_ = (G-B)/C;
            else if(V==G)
                H_ = (B-R)/C+2;
            else if(V==B)
                H_ = (R-G)/C+4;
            
            if (H_<0)
                H = H_/6+1;
            else
                H = H_/6;            

            set_pixel(im, x, y, 0, H);
            set_pixel(im, x, y, 1, S);
            set_pixel(im, x, y, 2, V);
        }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    float R,G,B;
    float H,V,S;
    float C,min,max,H_;
    for(int y=0; y<im.h; y++)
        for(int x=0; x<im.w; x++){
            H = get_pixel(im, x, y, 0);
            S = get_pixel(im, x, y, 1);
            V = get_pixel(im, x, y, 2);
            
            C = V * S;
            max = V;
            min = V-C;

            H_ = H * 6 ;

            if(C == 0.){
                R = V;
                G = V;
                B = V;
            }else if(H_ > 5 && H_ <6){
                R = max;
                G = min;
                B = ((((H_ /  6) - 1) * 6 * C) - G) * -1;
            }else if (H_ == 5) {
                R = max;
                G = min;
                B = max;
            }else if (H_ < 5 && H_ > 4) {
                G = min;
                R = (H_ - 4) * C + G;
                B = max;
            }else if (H_ == 4) {
                R = min;
                G = min;
                B = max;
            }else if (H_ < 4 && H_ > 3) {
                R = min;
                G = (((H_ - 4) * C) - R) * -1;
                B = max;
            }else if (H_ == 3) {
                R = min;
                G = max;
                B = max;
            }else if (H_ < 3 && H_ > 2) {
                R = min;
                G = max;
                B = ((H_ - 2) * C) + R;
            }else if (H_ == 2) {
                R = min;
                G = max;
                B = min;
            }else if (H_ < 2 && H_ > 1) {
                G = max;
                B = min;
                R = (((H_ - 2) * C) - B) * -1;
            }else if (H_ == 1) {
                R = max;
                G = max;
                B = min;
            }else if (H_ < 1 && H_ > 0) {
                R = max;
                B = min;
                G = (H_ * C) + B;
            }else {
                R = max;
                G = min;
                B = min;
            }

            set_pixel(im, x, y, 0, R);
            set_pixel(im, x, y, 1, G);
            set_pixel(im, x, y, 2, B);
        }
}
