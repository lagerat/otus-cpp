#ifndef GRAPHICSEDITOR_RECTANGLE_H
#define GRAPHICSEDITOR_RECTANGLE_H

#include "GraphicPrimitive.h"

class Rectangle : public GraphicPrimitive{
public:
    Rectangle() = default;
    ~Rectangle() override = default;

    void Draw() override;

    void Translate(double dx, double dy) override;
    void Rotate(double angle) override;
    void Scale(double sx, double sy) override;

    void SetHeight(double height);
    void SetWidth(double width);
private:

    double m_width;
    double m_height;
    myMath::Position m_topLeftCorner;
};


#endif //GRAPHICSEDITOR_RECTANGLE_H
