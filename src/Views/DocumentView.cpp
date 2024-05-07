#include "DocumentView.h"

//----------------------------------------------------------------
void DocumentView::renderDocument(std::unique_ptr<Document> document) {}
//----------------------------------------------------------------
void DocumentView::UpdateUI() {}
//----------------------------------------------------------------
void DocumentView::HandleEvents() {}
//----------------------------------------------------------------
void DocumentView::renderLine(const Line &) {}
//----------------------------------------------------------------
void DocumentView::renderRectangle(const Rectangle &) {}
//----------------------------------------------------------------
bool DocumentView::IsOpen() { return true; }
//----------------------------------------------------------------
void DocumentView::Render() {
    renderDocument(m_documentController.GetCurrentDocument());
}
//----------------------------------------------------------------
void DocumentView::exportDocument(const std::string &filename) {
    m_documentController.ExportDocument(filename);
}
//----------------------------------------------------------------
void DocumentView::importDocument(const std::string &filename) {
    m_documentController.ImportDocument(filename);
}
//----------------------------------------------------------------
void DocumentView::createDocument() {
    m_documentController.CreateNewDocument();
}
//----------------------------------------------------------------
void DocumentView::addPrimitive(std::unique_ptr<GraphicPrimitive>) {
    m_primitiveController.AddPrimitiveToDocument(std::unique_ptr<GraphicPrimitive>(), m_documentController.GetCurrentDocument());
}
//----------------------------------------------------------------
void DocumentView::deletePrimitive(std::unique_ptr<GraphicPrimitive>) {
    m_primitiveController.RemovePrimitiveFromDocument(std::unique_ptr<GraphicPrimitive>(),std::unique_ptr<Document>());
}
//----------------------------------------------------------------
void DocumentView::createLine() {}
//----------------------------------------------------------------
void DocumentView::createRectangle() {}
//----------------------------------------------------------------