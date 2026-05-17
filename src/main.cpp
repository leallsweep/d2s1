#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        return 1;
    }
    
    std::vector<std::pair<std::string, std::string>> dialogues;
    std::string line;
    
    while (std::getline(file, line)) {
        size_t space = line.find(' ');
        if (space != std::string::npos && line[space + 1] == '"') {
            std::string name = line.substr(0, space);
            std::string text = line.substr(space + 2);
            if (!text.empty() && text.back() == '"') {
                text.pop_back();
            }
            dialogues.push_back({name, text});
        }
    }
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "d2s1", sf::Style::Close);
    sf::Font font;
    
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
            return 1;
        }
    }
    
    sf::Text nameText;
    sf::Text dialogueText;
    sf::Text continueText;
    
    nameText.setFont(font);
    dialogueText.setFont(font);
    continueText.setFont(font);
    
    nameText.setCharacterSize(24);
    dialogueText.setCharacterSize(20);
    continueText.setCharacterSize(16);
    
    nameText.setFillColor(sf::Color::Yellow);
    dialogueText.setFillColor(sf::Color::White);
    continueText.setFillColor(sf::Color::Green);
    
    nameText.setPosition(20, 500);
    dialogueText.setPosition(20, 540);
    continueText.setPosition(600, 570);
    continueText.setString("[Enter]");
    
    size_t currentIndex = 0;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                currentIndex++;
                if (currentIndex >= dialogues.size()) {
                    window.close();
                }
            }
        }
        
        if (currentIndex < dialogues.size()) {
            nameText.setString(dialogues[currentIndex].first);
            dialogueText.setString(dialogues[currentIndex].second);
        }
        
        window.clear(sf::Color(30, 30, 60));
        window.draw(nameText);
        window.draw(dialogueText);
        window.draw(continueText);
        window.display();
    }
    
    return 0;
}
