/*
 * @file
 * @author Thomas Kohlman
 *
 * @section LICENSE
 *
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "color.h"

namespace RadRt
{

const Color Color::BLACK(0,0,0);
const Color Color::BLUE(0,0,1);
const Color Color::GREEN(0,1,0);
const Color Color::CYAN(0,1,1);
const Color Color::RED(1,0,0);
const Color Color::PURPLE(1,0,1);
const Color Color::YELLOW(1,1,0);
const Color Color::WHITE(1,1,1);

Color::Color(float red, float green, float blue):
    m_red(red),
    m_green(green),
    m_blue(blue)
{
}

Color::Color(const Color& other):
    m_red(other.m_red),
    m_green(other.m_green),
    m_blue(other.m_blue)
{
}

Color::Color():
    m_red(0),
    m_green(0),
    m_blue(0)
{
}

Json::Value Color::serialize() const
{
    Json::Value root;
    root["r"] = m_red;
    root["g"] = m_green;
    root["b"] = m_blue;
    return root;
}

void Color::deserialize(const Json::Value &root)
{
    m_red = root["r"].asFloat();
    m_green = root["g"].asFloat();
    m_blue = root["b"].asFloat();
}

}   // namespace RadRt
