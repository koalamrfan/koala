#ifndef TEXTURE_POOL
#define TEXTURE_POOL

class TexturePool
{
public:
    static TexturePool* GetInstance();
    void Init(HWND hwnd);
    HWND GetHwnd() const {
        return hwnd_;
    }
protected:
    TexturePool() {}
    HWND hwnd_;
};

#endif