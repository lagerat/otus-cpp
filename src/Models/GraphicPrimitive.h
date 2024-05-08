#ifndef GRAPHICSEDITOR_GRAPHICPRIMITIVE_H
#define GRAPHICSEDITOR_GRAPHICPRIMITIVE_H
#include "../math/MathHelper.h"

/**
* @brief GraphicPrimitive
*/
class GraphicPrimitive {
public:
    GraphicPrimitive() = default;
    virtual ~GraphicPrimitive() {};

    virtual void Draw() = 0;

    virtual void Translate(double dx, double dy);
    virtual void Rotate(double angle);
    virtual void Scale(double sx, double sy);

    void SetColor(myMath::Color newColor);
    void SetPosition(myMath::Position newPosition);
    void SetSize(myMath::Size newSize);
private:
    myMath::Color       m_color;
    myMath::Position    m_position;
    myMath::Size        m_size;
};


#endif //GRAPHICSEDITOR_GRAPHICPRIMITIVE_H
