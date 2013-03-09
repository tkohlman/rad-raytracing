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

Scene::Scene()
{
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    background = Color::BLACK;
    shapes = new ShapeVector();
    lights = new LightVector();
}

Scene::~Scene()
{
    delete shapes;
    delete lights;
}

Json::Value Scene::serialize() const
{
    Json::Value scene;

    scene["dimensions"]["width"] = width;
    scene["dimensions"]["height"] = height;

    scene["camera"] = camera.serialize();

    scene["background_color"] = background.serialize();

    Json::Value json_shapes;
    ShapeConstIterator shape_iter = shapes->begin();
    while(shape_iter != shapes->end())
    {
        json_shapes.append((*shape_iter)->serialize());
        ++shape_iter;
    }
    scene["shapes"] = json_shapes;

    Json::Value json_lights;
    LightConstIterator light_iter = lights->begin();
    while(light_iter != lights->end())
    {
        json_lights.append((*light_iter)->serialize());
        ++light_iter;
    }
    scene["lights"] = json_lights;

    return scene;
}

void Scene::deserialize(const Json::Value &root)
{
    width = root["dimensions"]["width"].asInt();
    height = root["dimensions"]["height"].asInt();

    camera.deserialize(root["camera"]);

    background.deserialize(root["background_color"]);

    Json::Value json_shapes = root["shapes"];
    ShapeFactory factory;
    for (unsigned int index = 0; index < json_shapes.size(); ++index)
    {
        Shape *shape = factory.create(json_shapes[index]["type"].asString());
        shape->deserialize(json_shapes[index]);
        shapes->push_back(shape);
    }

    Json::Value json_lights = root["lights"];
    for (unsigned int index = 0; index < json_lights.size(); ++index)
    {
        Light *light = new Light();
        light->deserialize(json_lights[index]);
        lights->push_back(light);
    }
}

}   // namespace RadRt
