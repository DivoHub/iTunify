#include <iostream>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;

int main() {
    XMLDocument doc;
    std::vector<std::string> songInfo; // Array to store Name, Artist, and Album

    // Load the XML file
    if (doc.LoadFile("Music.xml") == XML_SUCCESS) {
        // Get the root element
        XMLElement* root = doc.RootElement();

        // Iterate through each 'dict' element
        for (XMLElement* dict = root->FirstChildElement("dict"); dict; dict = dict->NextSiblingElement("dict")) {
            // Get the 'Name', 'Artist', and 'Album' elements
            XMLElement* nameElement = dict->FirstChildElement("key")->NextSiblingElement("string");
            XMLElement* artistElement = nameElement->NextSiblingElement("key")->NextSiblingElement("string");
            XMLElement* albumElement = artistElement->NextSiblingElement("key")->NextSiblingElement("string");

            // Check if the elements are not null
            if (nameElement && artistElement && albumElement) {
                // Get the text content of 'Name', 'Artist', and 'Album'
                std::string name = nameElement->GetText();
                std::string artist = artistElement->GetText();
                std::string album = albumElement->GetText();

                // Store the information in the array
                songInfo.push_back(name);
                songInfo.push_back(artist);
                songInfo.push_back(album);
            }
        }

        // Print the stored information
        for (const auto& info : songInfo) {
            std::cout << info << std::endl;
        }
    } else {
        std::cerr << "Error loading XML file." << std::endl;
    }

    return 0;
}