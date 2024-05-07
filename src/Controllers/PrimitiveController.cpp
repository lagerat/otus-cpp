#include "PrimitiveController.h"

//----------------------------------------------------------------
void PrimitiveController::AddPrimitiveToDocument(std::unique_ptr<GraphicPrimitive>, std::unique_ptr<Document>) {}
//----------------------------------------------------------------
void PrimitiveController::RemovePrimitiveFromDocument(std::unique_ptr<GraphicPrimitive>, std::unique_ptr<Document>) {}
//----------------------------------------------------------------
void PrimitiveController::CreateLine(myMath::Position startPoint, myMath::Position endPoint, myMath::Color color) {}
//----------------------------------------------------------------
void PrimitiveController::CreateRectangle(myMath::Position position, myMath::Size size, myMath::Color color) {}
//----------------------------------------------------------------