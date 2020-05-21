#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CircleHSV.h"
#include "CircleHSL.h"
#include "CircleCMY.h"
#include "CircleRBG.h"
#include "Scrollbar.h"

class Burrito: public sf::Drawable{
public:
    Burrito(){
        circleHSL = new CircleHSL(100, 20, 20, 0.50);
        circleHSV = new CircleHSV(100, 300, 20, 0.50);
        circleCMY = new CircleCMY(100, 20, 300, 0.50);
        circleRGB = new CircleRGB(100, 300, 300);
        scrollbar = new Scrollbar(30,200,600,50);
        sf::Font font;
    }

    void changeColors(int x, int y){
        float percent = scrollbar->getPercent(x, y);
        if(percent!=-1){
            circleRGB->setColor(percent);
            circleCMY = new CircleCMY(100, 20, 300, percent);
            circleHSL = new CircleHSL(100, 20, 20, percent);
            circleHSV = new CircleHSV(100, 300, 20,percent);
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*circleHSV);
        target.draw(*circleHSL);
        target.draw(*circleRGB);
        target.draw(*circleCMY);
        target.draw(*scrollbar);
    }

private:
    CircleHSV *circleHSV;
    CircleHSL *circleHSL;
    CircleRGB *circleRGB;
    CircleCMY *circleCMY;
    Scrollbar *scrollbar;
};


