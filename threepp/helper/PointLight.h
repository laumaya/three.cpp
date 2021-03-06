//
// Created by byter on 2/16/18.
//

#ifndef THREE_PP_POINTLIGHT_H
#define THREE_PP_POINTLIGHT_H

#include <threepp/objects/Mesh.h>
#include <threepp/light/PointLight.h>
#include <threepp/geometry/Sphere.h>
#include <threepp/material/MeshBasicMaterial.h>

namespace three {
namespace helper {

class PointLight : public MeshT<geometry::buffer::Sphere, MeshBasicMaterial>
{
  three::PointLight::Ptr _light;
  Color _color;

protected:
  PointLight(three::PointLight::Ptr light, float sphereSize, const Color &color)
     : MeshT(geometry::buffer::Sphere::make(sphereSize, 4, 2), MeshBasicMaterial::make()),
       _light(light), _color(color)
  {
    material()->wireframe = true;
    matrixAutoUpdate = false;

    update();
  }

  void update()
  {
    if (_color) {
      material<0>()->color() = _color;
    }
    else {
      material<0>().color() = _light->color();
    }
  }
};

}
}

#endif //THREE_PP_POINTLIGHT_H
