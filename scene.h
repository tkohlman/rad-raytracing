#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class Scene
{

public:

    Scene( int width, int height );

    void setWidth( int width );
    void setHeight( int height );

    int getWidth() const;
    int getHeight() const;

private:

    int width;
    int height;

};

inline void Scene::setWidth( int width )
{
    this->width = width;
}

inline void Scene::setHeight( int height )
{
    this->height = height;
}

inline int Scene::getWidth() const
{
    return width;
}

inline int Scene::getHeight() const
{
    return height;
}



#endif // SCENE_H
