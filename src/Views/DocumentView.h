#ifndef GRAPHICSEDITOR_DOCUMENTVIEW_H
#define GRAPHICSEDITOR_DOCUMENTVIEW_H

#include "../Models/Document.h"

#include "../Models/Line.h"
#include "../Models/Rectangle.h"

#include "../Controllers/DocumentController.h"
#include "../Controllers/PrimitiveController.h"

class DocumentView {
public:
    DocumentView() = default;
    ~DocumentView() = default;

    void Render();
    void UpdateUI();

    void HandleEvents();
    bool IsOpen();
private:
    void renderLine(const Line&);
    void renderRectangle(const Rectangle&);
    void renderDocument(std::unique_ptr<Document> document);

    void exportDocument(const std::string& filename);
    void importDocument(const std::string& filename);
    void createDocument();

    void addPrimitive(std::unique_ptr<GraphicPrimitive>);
    void deletePrimitive(std::unique_ptr<GraphicPrimitive>);

    void createLine();
    void createRectangle();

    DocumentController      m_documentController;
    PrimitiveController     m_primitiveController;
};


#endif //GRAPHICSEDITOR_DOCUMENTVIEW_H
