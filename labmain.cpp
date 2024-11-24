//
// Created by Flavia Rivero on 24/11/24.
//
#include <iostream>
#include <cstdio>
#include <string>
#include "Labmain.h"

using namespace std;

struct ColorConsole {
    static const char* fg_blue;
    static const char* bg_white;
};

const char* ColorConsole::fg_blue = "\033[34m";
const char* ColorConsole::bg_white = "\033[47m";

struct ConsoleBox {
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox;

void load_script(const char* filename, bool show_script) {
    string script;
    FILE* f = nullptr;

    try {
        f = fopen(filename, "r");
        if (!f) {
            perror("Error al abrir el archivo");
            return;
        }

        char buf[4001];
        size_t bytesRead;
        while ((bytesRead = fread(buf, 1, 4000, f)) > 0) {
            buf[bytesRead] = '\0'; // Terminar correctamente la cadena
            script.append(buf);
        }

        if (ferror(f)) {
            cerr << "Error durante la lectura del archivo" << endl;
            fclose(f);
            return;
        }

        fclose(f);

        if (show_script) {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    } catch (const exception &e) {
        cerr << "Excepción: " << e.what() << endl;
        if (f) {
            fclose(f);
        }
    }
}

void load_script() {
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}

