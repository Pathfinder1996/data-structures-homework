#include "ChainNode.h"
#include "Polynomial.h"
#include "av_list.h"
#include "gui.h"
#include <locale>
#include <codecvt>  // for wstring <-> string conversion
#include <fstream>

int debug = 0;
int N;
extern void LOGO();
void system_init(std::ifstream&);

// New function: handle file dialog + open file
std::ifstream openInputFile();

int main() {
    int cont = 1;
    char ch;
   

    while (cont) {
        // Use the new function to open the input file
        std::ifstream inFile = openInputFile();
        if (!inFile) {
            std::cerr << "Program terminated due to file opening failure." << std::endl;
            return 0;
        }
        Polynomial a, b, c, d;
        LOGO();
        system_init(inFile);
        
        // Read two polynomials
        inFile >> a;
        inFile >> b;

        // Polynomial addition and multiplication
        c = (a + b);
        std::cout << "a = " << a << "\nb = " << b << "\nc = a + b =\n"
            << a << " + " << b << " =\n " << c << "\n";

        d = a * b;
        d = c + d;
        std::cout << "\n(a+b) + (a*b) =\n" << c << " + " << a << " * " << b << " =\n" << d << "\n";

        cont = 0;

        // Trigger Polynomial destructors and free all nodes
        std::cout << "Press any key to trigger Polynomial destructors and release memory...\n";
        ch = getchar();
    }

    std::cout << "Press any key to exit the program...\n";
    getchar();
    return 0;
}

void system_init(std::ifstream& is) {
    is >> debug;    is.clear();     is.ignore(100, '\n');
    is >> N;        is.clear();     is.ignore(100, '\n');
}

// === Implementation of the new helper function ===
std::ifstream openInputFile() {
    std::wstring wfilepath = openFileDialog();
    if (wfilepath.empty()) {
        std::wcerr << L"No file selected or operation canceled." << std::endl;
        return std::ifstream();  // Return empty
    }

    // Convert wstring to UTF-8 string
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string filepath = converter.to_bytes(wfilepath);

    // Open the file
    std::ifstream inFile(filepath, std::ios::in);
    if (!inFile)   std::cerr << "Failed to open the input file: " << filepath << std::endl;
    
    return inFile;
}
