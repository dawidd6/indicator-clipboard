#include "../src/indicator-clipboard.h"

int main(int argc, char **argv) {
    QString string = "0123456789cut_here";
    int stop = 10;

    Tray::trim(string, stop);
    qDebug("result: %s", qPrintable(string));
    if(string.length() == stop + 3)
        return 0;
    else
        return 1;
}