#include <iostream>
#include <string>

void PrintHelp() {
    static const std::string HELP =
        "Использование: archiver [ПАРАМЕТР] [ФАЙЛЫ (если потребуются)]\n"
        "\n"
        "-c создать архив\n"
        "-d разархивировать архив и положить файлы в текущую директорию\n"
        "-h вызов справки\n"
        "\n"
        "ФОРМАТ\n"
        "archiver -c archive_name file1 [file2 ...]\n"
        "archiver -d archive_name\n"
        "archiver -h\n"
        "\n"
        "ПРИМЕРЫ\n"
        "archiver -c myarchive.arc homework.txt tasks.docx music.mp3\n"
        "archiver -d myarchive.arc (положит файлы homework.txt tasks.docx music.mp3 в текущую директорию)\n"
        "\n"
        "archiver -c newarchive.wow master_i_margarita.txt\n"
        "archiver -d newarchive.wow (положит файл master_i_margarita.txt в текущую директорию)\n";

    std::cout << HELP;
}