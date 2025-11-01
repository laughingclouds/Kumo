#include <iostream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include <ranges>
#include <print>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

#include <kumo/StreamWrapper.hpp>

namespace fs = std::filesystem;

const fs::path ASSETS_DIR = "/home/laughingclouds/projects/Kumo/assets/";

/**Read metadata values and save into a stringstream object */
template <kumo::StreamLike T>
void extract_metadata(const poppler::document *doc, std::string DOCUMENT_NAME, T &ss)
{
    time_t doc_creation_date = doc->get_creation_date_t();
    char *dt = ctime(&doc_creation_date);

    ss << "File: " << DOCUMENT_NAME << " found\n";
    ss << "Created: " << dt;
    ss << "Number of pages: " << doc->pages();
}

/**Write metadata to stdout then prompt user to continue printing per page */
void read_pdf(std::string DOCUMENT_NAME)
{
    fs::path file_path = ASSETS_DIR / DOCUMENT_NAME;
    std::println("{}", file_path);
    std::unique_ptr<poppler::document> doc(poppler::document::load_from_file(file_path.string()));

    if (doc == NULL)
        std::cerr << "Error: Could not find file" << std::endl;

    kumo::PrintOnceStringStream ss;

    extract_metadata(doc.get(), DOCUMENT_NAME, ss);
    ss.println();
    std::println("----------------------------------");

    bool isReadNextPage = true;
    int page_index = 0;

    // read first page and then prompt user to continue
    while(true) {
        // return once all pages have been read
        if (page_index >= doc->pages())
            return;
        if (isReadNextPage)
        {            
            std::unique_ptr<poppler::page> pg(doc->create_page(page_index));
            ss << pg->text().to_latin1();
            ss.println();

            std::println("page: {}", page_index + 1);

            isReadNextPage = false;
            page_index++;
        }

        char continue_read;
        std::print("Next page(y/n): ");
        std::cin >> continue_read;

        if (continue_read == 'y')
            isReadNextPage = true;
        else if (continue_read == 'n')
            return;
    }
    
}

int main()
{
    std::string options[3] = {
        "2June2025_HemantBhandari_Resume.pdf",
        "virtual_id.pdf",
        "combinatorics.pdf",
    };
    int choice;

    std::stringstream ss;
    ss << "Select one option:\n";

    for (auto const [index, filename] : std::views::enumerate(options))
        ss << index << ": " << filename << "\n";

    ss << "Your choice: ";
    std::print("{}", ss.str());

    std::cin >> choice;

    std::println("----------------------------------");

    std::string DOCUMENT_NAME = options[choice];
    read_pdf(DOCUMENT_NAME);

    return 0;
}