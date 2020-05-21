#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Algorithms.h"
#define M_PI 3.14


class CircleHSV: public sf::Drawable{
public:
    CircleHSV(int rad, int x, int y, float percent){
        radius = rad;
        sf::Uint8  *colors_pixels = new sf::Uint8[2* radius * 2* radius *4];
        HSV data(0,0,0);
        RGB value(0,0,0);
        for(int i = -radius; i<radius; i++){
            for(int j = -radius; j<radius; j++){
                currRad = sqrt(i*i + j*j);
                if(j>=0) deegre = asin(i/currRad);
                if(j<0) deegre = -asin(i/currRad)+ M_PI;
                if(deegre<0) deegre = deegre+2*M_PI;
                if(currRad<radius){
                    data = HSV((deegre/(2*M_PI))*360, (currRad/radius), percent);
                    value = HSVToRGB(data);
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 0] = value.R;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 1] = value.G;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 2] = value.B;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 3] = 255;

                }
            }
        }
        texture.create(radius*2,radius*2);
        texture.update(colors_pixels);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    ~CircleHSV(){
        delete[] colors_pixels;
    }

    void setColor(float percent){
        HSV data(0,0,0);
        RGB value(0,0,0);
        for(int i = -radius; i<radius; i++){
            for(int j = -radius; j<radius; j++){
                currRad = sqrt(i*i + j*j);
                if(currRad<radius){
                    data = HSV((deegre/(2*M_PI))*360, (currRad/radius), percent);
                    value = HSVToRGB(data);
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 0] = value.R;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 1] = value.G;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 2] = value.B;
                    colors_pixels[4 * ((i+radius) * radius*2 + (j+radius)) + 3] = 255;
                }
            }
        }
        texture.update(colors_pixels);
        sprite.setTexture(texture);
    }

    void setPosition(int x, int y){
        sprite.setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    int radius;
    sf::Uint8  *colors_pixels;
    float currRad;
    float deegre;
};


