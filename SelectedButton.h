#ifndef SELECTEDBUTTON_H
#define SELECTEDBUTTON_H

#include "Button.h"
class SelectedButton :public Button {
public:
	SelectedButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& text, sf::Font& font,int& value);

	// Draw the button on the window
	void draw(std::shared_ptr<sf::RenderWindow> window) override;
	void update();

	// Check if the button is clicked
	bool isClicked(const sf::Vector2f& mousePosition) const;
	const bool getSelected();
	void setSelected(bool value);
private:
	bool isSelected;
	int value;

};

#endif // !SELECTEDBUTTON_H
