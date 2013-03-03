
#include "scene.h"

#include <json.h>

const int DEFAULT_WIDTH = 500;
const int DEFAULT_HEIGHT = 500;


Scene::Scene()
{
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    background = Color::BLACK;
    shapes = new std::vector<Shape*>();
    lights = new std::vector<Light*>();
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

    Json::Value json_shapes;

    vector<Shape*>::const_iterator shape_iter = shapes->begin();
    while(shape_iter != shapes->end())
    {
        json_shapes.append((*shape_iter)->serialize());
        ++shape_iter;
    }
    scene["shapes"] = json_shapes;

    Json::Value json_lights;

    vector<Light*>::const_iterator light_iter = lights->begin();
    while(light_iter != lights->end())
    {
        json_lights.append((*light_iter)->serialize());
        ++light_iter;
    }
    scene["lights"] = json_lights;

    return scene;
}
