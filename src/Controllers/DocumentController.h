#ifndef GRAPHICSEDITOR_DOCUMENTCONTROLLER_H
#define GRAPHICSEDITOR_DOCUMENTCONTROLLER_H

#include "../Models/Document.h"

class DocumentController {
public:
    DocumentController() = default;
    ~DocumentController() = default;

    void CreateNewDocument();
    void ImportDocument(const std::string& filename);
    void ExportDocument(const std::string& filename);

    std::unique_ptr<Document> GetCurrentDocument();

    void Undo();
    void Redo();
private:

    std::unique_ptr<Document> m_currentDocument;
    std::vector<std::unique_ptr<Document>> m_documents;
};


#endif //GRAPHICSEDITOR_DOCUMENTCONTROLLER_H
