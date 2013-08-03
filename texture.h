#ifndef TEXTURE_H
#define TEXTURE_H

class SkCanvas;
class Texture
{
public:
    void Draw();
protected:
    virtual void Draw(SkCanvas* canvas) = 0; 

};

#endif