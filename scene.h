#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

class Scene
{

public:

    Scene( int width, int height );

    void setWidth( int width );
    void setHeight( int height );

    const int getWidth() const;
    const int getHeight() const;

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

inline const int Scene::getWidth() const
{
    return width;
}

inline const int Scene::getHeight() const
{
    return height;
}



#endif // SCENE_H
