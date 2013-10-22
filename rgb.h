#ifndef RGB_H
#define RGB_H

class RGB
{
public:
    float r;
    float g;
    float b;

    RGB();
    RGB(float _rgb);
    RGB(float _r, float _g, float _b);
    RGB(const RGB& rgb);
    virtual ~RGB();

    RGB operator* (const float _a) const;
    RGB operator+ (const RGB& _rgb) const;
    RGB operator* (const RGB& _rgb) const;
    RGB operator/ (const float _a) const;
    RGB& operator= (const RGB& _rgb);
    RGB& operator+= (const RGB& _rgb);
    RGB& operator/= (const float _a);
    RGB& operator*= (const float _a);
    bool operator== (const RGB& _rgb) const;

};

inline RGB RGB::operator *(const float _a) const
{
    return RGB(r * _a, g * _a, b * _a);
}

inline RGB RGB::operator +(const RGB& _rgb) const
{
    return RGB(r + _rgb.r, g + _rgb.g, b + _rgb.b);
}

inline RGB RGB::operator *(const RGB& _rgb) const
{
    return RGB(r * _rgb.r, g * _rgb.g, b * _rgb.b);
}

inline RGB RGB::operator /(const float _a) const
{
    return RGB(r / _a, g / _a, b / _a);
}

inline RGB& RGB::operator +=(const RGB& _rgb)
{
    r += _rgb.r;
    g += _rgb.g;
    b += _rgb.b;
    return (*this);
}

inline RGB& RGB::operator /=(const float _a)
{
    r /= _a;
    g /= _a;
    b /= _a;
    return (*this);
}

inline RGB& RGB::operator *=(const float _a)
{
    r *= _a;
    g *= _a;
    b *= _a;
    return (*this);
}

inline bool RGB::operator ==(const RGB& _rgb) const
{
    return (r == _rgb.r && g == _rgb.g && b == _rgb.b);
}

RGB operator* (const float _a, const RGB& _rgb);

inline RGB operator* (const float _a, const RGB& _rgb)
{
    return RGB(_a * _rgb.r, _a * _rgb.g, _a * _rgb.b);
}


#endif // RGB_H
