#ifndef GRAPHICSEDITOR_PRIMITIVECONTROLLER_H
#define GRAPHICSEDITOR_PRIMITIVECONTROLLER_H

#include "../Models/Line.h"
#include "../Models/Rectangle.h"
#include "../Models/Document.h"

#include <vector>
#include <memory>

/**
* @brief A controller for graphics objects
*/
class PrimitiveController {
public:
    PrimitiveController() = default;
    ~PrimitiveController() = default;

    void AddPrimitiveToDocument(std::unique_ptr<GraphicPrimitive>, std::unique_ptr<Document>);
    void RemovePrimitiveFromDocument(std::unique_ptr<GraphicPrimitive>, std::unique_ptr<Document>);

    void CreateLine(myMath::Position startPoint, myMath::Position endPoint, myMath::Color color);
    void CreateRectangle(myMath::Position position, myMath::Size size, myMath::Color color);

};


#endif //GRAPHICSEDITOR_PRIMITIVECONTROLLER_H
