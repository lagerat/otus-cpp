#include "Document.h"

//----------------------------------------------------------------
void Document::ImportDocument(const std::string &filename) {}
//----------------------------------------------------------------
void Document::ExportDocument(const std::string &filename) {}
//----------------------------------------------------------------
void Document::AddPrimitive(std::unique_ptr<GraphicPrimitive>) {}
//----------------------------------------------------------------
void Document::RemovePrimitive(std::unique_ptr<GraphicPrimitive>) {}
//----------------------------------------------------------------
void Document::ClearDocument() {}
//----------------------------------------------------------------
int Document::GetNumPrimitives() { return 0; }
//----------------------------------------------------------------
GraphicPrimitive *Document::GetPrimitiveAt(size_t index) { return nullptr; }
//----------------------------------------------------------------
bool Document::isValidDocument() { return false; }
//----------------------------------------------------------------

