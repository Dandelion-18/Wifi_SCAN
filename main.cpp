#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <limits> // Додаємо цей заголовочний файл

void clearScreen() {
    if (system("clear")) {} // Виконує команду очищення екрану для Linux
}

void printWithDelay(const std::string& text, int delay_ms = 100) {
    for (char c : text) {
        std::cout << c;
        std::cout.flush();
        usleep(delay_ms * 1000);
    }
    std::cout << std::endl;
}

void logo() {
    std::string logo_text = R"(
    __        __ _____ _____ _____     _____  _______  _____   _______ _    _
    \ \      / // ____/ ____|  __ \   |  __ \|__   __|/ ____| |__   __| |  | |
     \ \    / /| |   | |    | |__) |  | |__) |  | |  | (___      | |  | |__| |
      \ \  / / | |   | |    |  _  /   |  ___/   | |   \___ \     | |  |  __  |
       \ \/ /  | |___| |____| | \ \   | |       | |   ____) |    | |  | |  | |
        \__/    \_____\_____|_|  \_\  |_|       |_|  |_____/     |_|  |_|  |_|)";

    clearScreen();
    printWithDelay(logo_text);
    std::cout << "\033[1m  by Dandelion        v0.1    Made in Ukraine :)\033[0m" << std::endl;
    sleep(2);
}

void wifiScan() {
    std::string os_system = "Linux"; // Ми припускаємо, що цей код працюватиме на Linux
    std::string command = "sudo iwlist scan";

    std::cout << "Running command: " << command << std::endl;

    try {
        std::string result;
        char buffer[128];
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);
        std::cout << "Command output:\n" << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError running command: " << e.what() << "\033[0m" << std::endl;
    }
}

void menu() {
    while (true) {
        clearScreen();
        std::cout << R"(
 __  __ ______ _   _ _    _
|  \/  |  ____| \ | | |  | |
| \  / | |__  |  \| | |  | |
| |\/| |  __| | . ` | |  | |
| |  | | |____| |\  | |__| |
|_|  |_|______|_| \_|\____/
        )" << std::endl;
        std::cout << "I think, if you download this util, you are ready)\n 1) Wifi Scan\n";
        std::cout << "0) ! EXIT !" << std::endl;

        int choice;
        std::cout << "\n [+] Choose your choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[31mPrint real point of menu!\033[0m" << std::endl;
            sleep(2);
            continue;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            wifiScan();
        } else {
            std::cout << "\033[31mPrint real point of menu!\033[0m" << std::endl;
            sleep(2);
        }
    }
}

int main() {
    logo();
    menu();
    return 0;
}
