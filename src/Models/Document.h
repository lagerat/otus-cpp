#ifndef GRAPHICSEDITOR_DOCUMENT_H
#define GRAPHICSEDITOR_DOCUMENT_H

#include <string>
#include <memory>
#include <vector>

#include "GraphicPrimitive.h"

/**
* @brief Document model
*/
class Document {
public:
    Document() = default;
    ~Document() = default;

    void ImportDocument(const std::string &filename);
    void ExportDocument(const std::string &filename);

    void AddPrimitive(std::unique_ptr<GraphicPrimitive>);
    void RemovePrimitive(std::unique_ptr<GraphicPrimitive>);
    void ClearDocument();

    int GetNumPrimitives();
    GraphicPrimitive* GetPrimitiveAt(size_t index);

private:
    bool isValidDocument();

    struct DocumentData{
        std::string documentName;
        std::string creationDate;
    } m_documentData;

    std::vector<std::unique_ptr<GraphicPrimitive>> m_primitives;

    bool m_isModified = false;
};


#endif //GRAPHICSEDITOR_DOCUMENT_H
