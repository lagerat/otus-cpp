#include <iostream>
#include "src/Views/DocumentView.h"

int main (int, char **) {
    try{
        DocumentView documentView;
        while (documentView.IsOpen())
        {
            documentView.HandleEvents();
            documentView.UpdateUI();
            documentView.Render();
        }
    }catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
