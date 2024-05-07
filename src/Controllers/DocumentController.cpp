#include "DocumentController.h"

//----------------------------------------------------------------
void DocumentController::CreateNewDocument() {}
//----------------------------------------------------------------
void DocumentController::ImportDocument(const std::string &filename) {}
//----------------------------------------------------------------
void DocumentController::ExportDocument(const std::string &filename) {}
//----------------------------------------------------------------
void DocumentController::Undo() {}
//----------------------------------------------------------------
void DocumentController::Redo() {}

std::unique_ptr<Document> DocumentController::GetCurrentDocument() {
    return std::unique_ptr<Document>();
}
//----------------------------------------------------------------