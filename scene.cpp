
#include "scene.h"

#include <json.h>

Scene::Scene( int width, int height ) :
    width( width ), height( height )
{
}

void Scene::serialize(std::ostream &os)
{
    Json::Value scene;

    scene["dimensions"]["width"] = width;
    scene["dimensions"]["height"] = height;

    os << scene << std::endl;
}
