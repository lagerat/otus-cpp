#ifndef GRAPHICSEDITOR_LINE_H
#define GRAPHICSEDITOR_LINE_H

#include "GraphicPrimitive.h"

/**
* @brief Line
*/
class Line : public GraphicPrimitive{
public:
    Line() = default;
    ~Line() override {};

    void Draw() override;

    void Translate(double dx, double dy) override;
    void Rotate(double angle) override;
    void Scale(double sx, double sy) override;

private:
    myMath::Position m_startPoint;
    myMath::Position m_endPoint;
};


#endif //GRAPHICSEDITOR_LINE_H
