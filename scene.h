#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <camera.h>
#include <ijsonserializable.h>
#include <Light.h>
#include <Shape.h>
#include <vector>

namespace RadRt
{

typedef std::vector<Shape*> ShapeVector;
typedef std::vector<Shape*>::iterator ShapeIterator;
typedef std::vector<Shape*>::const_iterator ShapeConstIterator;
typedef std::vector<Light*> LightVector;
typedef std::vector<Light*>::iterator LightIterator;
typedef std::vector<Light*>::const_iterator LightConstIterator;

class Scene : public IJsonSerializable
{

public:

    Scene();
    ~Scene();

    // Accessors
    int getWidth() const { return width; };
    int getHeight() const { return height; };
    Camera getCamera() const { return camera; };
    Color getBackground() const { return background; };
    ShapeVector *getShapes() const { return shapes; };
    LightVector *getLights() const { return lights; };

    // Mutators
    void setWidth( int width ) { this->width = width; };
    void setHeight( int height ) { this->height = height; };
    void setCamera(const Camera &camera) { this->camera = camera; };
    void setBackground(const Color &color) { this->background = color; };
    void addShape(Shape *shape) { shapes->push_back(shape); };
    void addLight(Light *light) { lights->push_back(light); };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    int width;
    int height;

    Camera camera;

    Color background;

    ShapeVector *shapes;
    LightVector *lights;

};

}   // namespace RadRt

#endif // SCENE_H
