#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // for std::setw
#include "tinyxml2.h"
#include "nlohmann/json.hpp"
#include <cstdlib> // for system
#include <string>

// For file dialog
#include <gtk/gtk.h>
#include <gtk/gtkdialog.h>

using namespace tinyxml2;
using json = nlohmann::json;

std::string selectXmlFile() {
    // Initialize GTK
    gtk_init(0, NULL);

    // Create a file chooser dialog
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Select XML File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         "Open", GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Add XML filter to only allow XML files
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "XML files");
    gtk_file_filter_add_pattern(filter, "*.xml");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Run the dialog and get the response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    std::string selectedFile;

    // If the user selects a file
    if (response == GTK_RESPONSE_ACCEPT) {
        // Get the selected file path
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        selectedFile = std::string(filename);
        g_free(filename);

        // Check if the selected file has the .xml extension
        size_t dotPos = selectedFile.find_last_of('.');
        if (dotPos == std::string::npos || selectedFile.substr(dotPos) != ".xml") {
            std::cerr << "Error: File must be an XML file." << std::endl;
            selectedFile.clear(); // Clear the selected file path
        }
    }

    // Destroy the dialog
    gtk_widget_destroy(dialog);

    // Return the selected file path
    return selectedFile;
}

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
    // Select XML file using file dialog
    std::string xmlFilePath = selectXmlFile();
    if (xmlFilePath.empty()) {
        std::cerr << "No file selected. Exiting program." << std::endl;
        return -1;
    }

    XMLDocument doc;
    std::vector<std::vector<std::string>> songs; // To store all songs' info

    if (doc.LoadFile(xmlFilePath.c_str()) == XML_SUCCESS) {
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