#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Algorithms.h"


class CircleCMY: public sf::Drawable{
public:
    CircleCMY(int rad, int x, int y, float percent){
        radius = rad;
        sf::Uint8  *colors_pixels = new sf::Uint8[2* radius * 2* radius *4];
        for(int i = -radius; i<radius; i++){
            for(int j = -radius; j<radius; j++){
                currRad = sqrt(i*i + j*j);
                if(j>=0) deegre = asin(i/currRad);
                if(j<0) deegre = -asin(i/currRad)+ M_PI;
                if(deegre<0) deegre = deegre+2*M_PI;
                if(currRad<radius){
                    colors_pixels[4 * ((j+radius) * radius*2 + (i+radius)) + 0] = 255 - (255 * currRad/radius);
                    colors_pixels[4 * ((j+radius) * radius*2 + (i+radius)) + 1] = 255 - (255- 255 * deegre/(M_PI*2));
                    colors_pixels[4 * ((j+radius) * radius*2 + (i+radius)) + 2] = 255 - 255*percent;
                    colors_pixels[4 * ((j+radius) * radius*2 + (i+radius)) + 3] = 255;
                }
            }
        }
        texture.create(radius*2,radius*2);
        texture.update(colors_pixels);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    ~CircleCMY(){
        delete[] colors_pixels;
    }

    void setColor(float blue){
        for(int i = -radius; i<radius; i++){
            for(int j = -radius; j<radius; j++){
                currRad = sqrt(i*i + j*j);
                if(currRad<radius){
                    colors_pixels[4 * ((j+radius) * radius*2 + (i+radius)) + 2] = 255 - 255*blue;
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


