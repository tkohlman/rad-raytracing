/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "scene.h"
#include "json.h"
#include "shapefactory.h"

namespace RadRt
{

const int DEFAULT_WIDTH = 500;
const int DEFAULT_HEIGHT = 500;

Scene::Scene():
    m_width(DEFAULT_WIDTH),
    m_height(DEFAULT_WIDTH),
    m_background(Color::BLACK)
{
    s_shapes = new ShapeVector();
    m_lights = new LightVector();
}

Scene::~Scene()
{
    ShapeIterator shape_iter = s_shapes->begin();
    while(shape_iter != s_shapes->end())
    {
        delete *shape_iter;
        ++shape_iter;
    }

    LightIterator light_iter = m_lights->begin();
    while(light_iter != m_lights->end())
    {
        delete *light_iter;
        ++light_iter;
    }

    s_shapes->clear();
    m_lights->clear();

    delete s_shapes;
    delete m_lights;

    s_shapes = nullptr;
    m_lights = nullptr;
}

Json::Value Scene::serialize() const
{
    Json::Value scene;

    scene["dimensions"]["width"] = m_width;
    scene["dimensions"]["height"] = m_height;

    scene["camera"] = m_camera.serialize();

    scene["background_color"] = m_background.serialize();

    Json::Value json_shapes;
    ShapeConstIterator shape_iter = s_shapes->begin();
    while(shape_iter != s_shapes->end())
    {
        json_shapes.append((*shape_iter)->serialize());
        ++shape_iter;
    }
    scene["shapes"] = json_shapes;

    Json::Value json_lights;
    LightConstIterator light_iter = m_lights->begin();
    while(light_iter != m_lights->end())
    {
        json_lights.append((*light_iter)->serialize());
        ++light_iter;
    }
    scene["lights"] = json_lights;

    return scene;
}

void Scene::deserialize(const Json::Value &root)
{
    m_width = root["dimensions"]["width"].asInt();
    m_height = root["dimensions"]["height"].asInt();

    m_camera.deserialize(root["camera"]);

    m_background.deserialize(root["background_color"]);

    Json::Value json_shapes = root["shapes"];
    ShapeFactory factory;
    for (unsigned int index = 0; index < json_shapes.size(); ++index)
    {
        Shape *shape = factory.create(json_shapes[index]["type"].asString());
        shape->deserialize(json_shapes[index]);
        s_shapes->push_back(shape);
    }

    Json::Value json_lights = root["lights"];
    for (unsigned int index = 0; index < json_lights.size(); ++index)
    {
        Light *light = new Light();
        light->deserialize(json_lights[index]);
        m_lights->push_back(light);
    }
}

}   // namespace RadRt
