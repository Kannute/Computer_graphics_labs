#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Scrollbar: public sf::Drawable{
public:
    Scrollbar(int h, int w, int x, int y): height(h), width(w){
        sf::Uint8 * colors_pixels = new sf::Uint8[4*h*w];
        int i, j;
        for(i =0; i<height; i++){
            for(j = 0; j<width; j++){
                    colors_pixels[4*(i*width + j) + 0] = 255 * float(i)/height;
                    colors_pixels[4*(i*width + j) + 1] = 255 * float(i)/height;
                    colors_pixels[4*(i*width + j) + 2] = 255 * float(i)/height;
                    colors_pixels[4*(i*width + j) + 3] = 255;
            }
        }

        texture.create(height, width);
        texture.update(colors_pixels);
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }

    float getPercent(int x,int y){
        const sf::Vector2f vector = sprite.getPosition();
        if((x>=vector.x && x<=vector.x + height) && (y>=vector.y && y<=vector.y+width)){
            int sectionY = 200 - (y - vector.y);
            percent = float(sectionY)/width;
            return percent;
        }
        return -1;
    }


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }

private:
    float percent;
    int height;
    int width;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Uint8  *colors_pixels;

};
