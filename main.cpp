//GRAVITY
#include <map>
#include <cmath>
#include <string>
#include <sstream>   
#include <fstream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Effect.hpp"

namespace sf{
	bool operator< (const sf::Color& c1, const sf::Color& c2){
		if(c1.r < c2.r) return true; else if(c1.r > c2.r) return false;
		else if(c1.g < c2.g) return true; else if(c1.g > c2.g) return false;
		else if(c1.b < c2.b) return true; else if(c1.b > c2.b) return false;
		else if(c1.a < c2.a) return true; else if(c1.a > c2.a) return false;
		else return false;
	}
}

sf::Color getColisionColor(float posx, float posy, sf::Image& img, sf::Sprite& bSprite){
	return img.getPixel( posx/bSprite.getScale().x, posy/bSprite.getScale().y);
}

int main(int argc, const char* argv[]){
    
    sf::Vector2f v = sf::Vector2f(0,0);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Gravity");
       sf::Vector2f screenSize = sf::Vector2f(window.getSize().x,window.getSize().y);
    float g = (int)screenSize.y*2 ;

    sf::RectangleShape r(sf::Vector2f(screenSize.x/10, screenSize.y/10));
    r.setPosition(0,0); r.setFillColor(sf::Color::White);
    
	float ground = screenSize.y-4; //  float ground = screenSize.y*6/7;
	
	sf::Text text; sf::Font font; 
	if(! font.loadFromFile("res/font.ttf")) std::cerr << "fail on font load" << std::endl;
	text.setFont(font); text.setPosition(0,0); text.setString("penguin <3");
	text.setColor(sf::Color(255,255,255));
	
	sf::Image bimg;
	sf::Texture bTex;
	sf::Sprite bSprite;
	
	std::map<sf::Color, sf::Time> colorsColiding;

	int pantalla = 0;
    float boardTime = 0;
	if(argc > 1) pantalla = atoi(argv[1]);
	bool reboot = false;
	bool needshiet = true;
	
    sf::Clock timer;
    Effect effect;
   //effect.loadAnimation("res/explosion", 5); //works
    effect.loadSpriteSheet("res/penguin.png", 4, 4); //works
    effect.setOrigin(effect.getGlobalBounds().width/2, effect.getGlobalBounds().height/2);
    
    float deltatime = 0;
    
    //GAME LOOP
    while(window.isOpen()){
		
        deltatime = timer.restart().asSeconds();
        boardTime += deltatime;
        effect.updateAnimation(deltatime);
        
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); 
		}
				
		if(r.getPosition().y > 0){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up   ))  v.y = (float)screenSize.y/2 * -1;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W   ))  v.y = (float)screenSize.y/2 * -1;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  v.y = (float)screenSize.y/1.5 * -1;
		}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left ))  v.x = (float)screenSize.x/20 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A ))  v.x = (float)screenSize.x/20 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  v.x = (float)screenSize.x/20;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))  v.x = (float)screenSize.x/20;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        
		if(pantalla < 2) r.move(v*3.0f * deltatime);
        else r.move(v * deltatime);
        
		if(r.getPosition().y < 0) {v.y += g*deltatime;}
        if( (r.getPosition().y + r.getSize().y) < ground || v.y < 0) v.y += g *deltatime;
        else {
            r.setPosition(r.getPosition().x, ground - r.getSize().y);
            v.y = 0;
        }
        r.setOutlineColor(sf::Color::White);
		r.setOutlineThickness(1);
        
		if(r.getPosition().x < 1) r.setPosition(1, r.getPosition().y);
        if(r.getPosition().x + r.getSize().x+3 > screenSize.x){
			r.setPosition(screenSize.x-r.getSize().x-3, r.getPosition().y);
		}
        
        sf::VertexArray pj(sf::Quads, 4);
        sf::FloatRect fr = r.getGlobalBounds();
        pj[0].position = sf::Vector2<float>(r.getPosition().x, r.getPosition().y);
        pj[1].position = sf::Vector2<float>(r.getPosition().x + fr.width-2, r.getPosition().y);
        pj[3].position = sf::Vector2<float>(r.getPosition().x, r.getPosition().y + fr.height-2);
        pj[2].position = sf::Vector2<float>(r.getPosition().x + fr.width-2, r.getPosition().y + fr.height-2);

        effect.rotate(100*deltatime);
        effect.setOrigin(effect.getLocalBounds().width/2, effect.getLocalBounds().height/2);
        effect.setPosition(r.getPosition());
        effect.setTimeBetweenAnimations(0.1);
    
        window.clear();
        window.draw(bSprite);
        window.draw(r);
        window.draw(pj, sf::BlendAlpha);
        window.draw(effect);
        window.display();
    }
}
