#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // for std::setw
#include "tinyxml2.h"
#include "nlohmann/json.hpp"

using namespace tinyxml2;
using json = nlohmann::json;

// Function to write data to JSON file
void writeToJson(const std::vector<std::vector<std::string>>& songs, const std::string& outputFileName) {
    json jsonObject;

    for (const auto& songInfo : songs) {
        if (songInfo.size() >= 3) {
            json songObject;
            songObject["Name"] = songInfo[0];
            songObject["Artist"] = songInfo[1];
            songObject["Album"] = songInfo[2];
            jsonObject.push_back(songObject);
        }
    }

    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << std::setw(4) << jsonObject << std::endl;
        std::cout << "JSON file '" << outputFileName << "' created successfully." << std::endl;
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }
}

int main() {
    XMLDocument doc;
    std::vector<std::vector<std::string>> songs; // To store all songs' info

    if (doc.LoadFile("Music.xml") == XML_SUCCESS) {
        XMLElement* root = doc.RootElement();

        for (XMLElement* dict = root->FirstChildElement("dict"); dict != nullptr; dict = dict->NextSiblingElement("dict")) {
            std::vector<std::string> songInfo; // To store individual song info

            for (XMLElement* element = dict->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()) {
                // Assuming 'key' tags are followed by 'string' tags with actual data
                if (std::string(element->Value()) == "key" && element->NextSiblingElement() != nullptr) {
                    songInfo.push_back(element->NextSiblingElement()->GetText() ? element->NextSiblingElement()->GetText() : "N/A");
                }
            }

            if (songInfo.size() >= 3) {
                songs.push_back(songInfo);
            }
        }
    } else {
        std::cerr << "Error loading XML file." << std::endl;
        return -1;
    }

    // Write all song information to JSON file
    writeToJson(songs, "Music.json");

    return 0;
}

