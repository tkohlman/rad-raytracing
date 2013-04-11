/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "camera.h"
#include "ijsonserializable.h"
#include "light.h"
#include "shape.h"
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
    int width() const { return m_width; };
    int height() const { return m_height; };
    Camera camera() const { return m_camera; };
    Color background() const { return m_background; };
    ShapeVector *shapes() const { return s_shapes; };
    LightVector *lights() const { return m_lights; };

    // Mutators
    void set_width( int width ) { this->m_width = width; };
    void set_height( int height ) { this->m_height = height; };
    void set_camera(const Camera &camera) { this->m_camera = camera; };
    void set_background(const Color &color) { this->m_background = color; };
    void add_shape(Shape *shape) { s_shapes->push_back(shape); };
    void add_light(Light *light) { m_lights->push_back(light); };

    Json::Value serialize() const;
    void deserialize(const Json::Value &root);

private:

    int m_width;
    int m_height;

    Camera m_camera;

    Color m_background;

    ShapeVector *s_shapes;
    LightVector *m_lights;
};

}   // namespace RadRt

#endif // SCENE_H
