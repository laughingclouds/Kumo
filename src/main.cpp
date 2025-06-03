#include <iostream>
#include <sstream>
#include <ctime>
#include <memory>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>


std::string ASSETS_DIR = "/home/laughingclouds/projects/Kumo/assets/";

int main()
{
    std::string DOCUMENT_NAME = "2June2025_HemantBhandari_Resume.pdf";
    std::unique_ptr<poppler::document> doc(poppler::document::load_from_file(ASSETS_DIR + DOCUMENT_NAME));

    if (doc == NULL)
    {
        std::cerr << "Error: Could not find file" << std::endl;
        return -1;
    }

    time_t doc_creation_date = doc->get_creation_date_t();
    char *dt = ctime(&doc_creation_date);

    std::stringstream ss;
    ss << "File: " << DOCUMENT_NAME << " found\n";
    ss << "Created: " << dt;
    ss << "Number of pages: " << doc->pages();

    std::cout << ss.str() << std::endl;
    ss.clear();

    std::unique_ptr<poppler::page> pg(doc->create_page(0));
    
    ss << "Content:\n";
    ss << pg->text().to_latin1();
    std::cout << ss.str() << std::endl;
}