
#include "checkedshader.h"

namespace RadRt
{

CheckedShader::CheckedShader( Point a, Point b, Point c, Point d ):
    a(a), b(b), c(c), d(d)
{
}

Color CheckedShader::shade( const Point &p )
{
    Vector AP = displacementVector(p, a);
    Vector AD = displacementVector(d, a);
    Vector AB = displacementVector(b, a);

    float AdistanceP = length(AP);
    AP = normalize(AP);
    AD = normalize(AD);
    AB = normalize(AB);

    float u = AdistanceP * dotProduct(AP, AD);
    float v = AdistanceP * dotProduct(AP, AB);

    int U = int(u / 3);
    int V = int(v / 3);

    bool oddU = U & 0x01;
    bool oddV = V & 0x01;

    if ((oddU && oddV) || (!oddU && !oddV))
    {
        return Color(1,0,0);
    }
    else
    {
        return Color(1,1,0);
    }
}

Json::Value CheckedShader::serialize() const
{
    Json::Value root;
    root["type"] = "checked_shader";
    root["a"] = a.serialize();
    root["b"] = b.serialize();
    root["c"] = c.serialize();
    root["d"] = d.serialize();
    return root;
}

void CheckedShader::deserialize(const Json::Value &root)
{
    a.deserialize(root["a"]);
    b.deserialize(root["b"]);
    c.deserialize(root["c"]);
    d.deserialize(root["d"]);
}

}   // namespace RadRt

