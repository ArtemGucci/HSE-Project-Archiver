#include "archivate.h"
#include "dearchivate.h"
#include "helper.h"

#include <iostream>

int main(int argc, char** argv) {
    try {
        CommandLineParser parser(argc, argv);
        if (!parser.Correct()) {
            std::cout << "Некорректные параметры командной строки, см. справку" << std::endl;
            PrintHelp();
            return 0;
        }
        if (parser.IsArchivate()) {
            Archivate(parser);
        } else if (parser.IsDearchivate()) {
            DeArchivate(parser);
        } else {
            PrintHelp();
            return 0;
        }
    } catch (...) {
        std::cout << "Ошибка выполнения программы" << std::endl;
        exit(111);
    }
    return 0;
}
