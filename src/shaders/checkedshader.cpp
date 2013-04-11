/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "checkedshader.h"

namespace RadRt
{

CheckedShader::CheckedShader(Point a, Point b, Point c, Point d):
    m_a(a),
    m_b(b),
    m_c(c),
    m_d(d)
{
}

Color CheckedShader::shade( const Point &p )
{
    Vector AP = displacement_vector(p, m_a);
    Vector AD = displacement_vector(m_d, m_a);
    Vector AB = displacement_vector(m_b, m_a);

    float AdistanceP = length(AP);
    AP = normalize(AP);
    AD = normalize(AD);
    AB = normalize(AB);

    float u = AdistanceP * dot_product(AP, AD);
    float v = AdistanceP * dot_product(AP, AB);

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
    root["a"] = m_a.serialize();
    root["b"] = m_b.serialize();
    root["c"] = m_c.serialize();
    root["d"] = m_d.serialize();
    return root;
}

void CheckedShader::deserialize(const Json::Value &root)
{
    m_a.deserialize(root["a"]);
    m_b.deserialize(root["b"]);
    m_c.deserialize(root["c"]);
    m_d.deserialize(root["d"]);
}

}   // namespace RadRt
