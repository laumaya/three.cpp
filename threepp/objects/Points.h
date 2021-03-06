//
// Created by byter on 27.09.17.
//

#ifndef THREEPP_POINTS_H
#define THREEPP_POINTS_H

#include <threepp/core/Object3D.h>
#include <threepp/material/PointsMaterial.h>

namespace three {

class Points : public Object3D_GM<BufferGeometry, PointsMaterial>
{
protected:
  Points(const BufferGeometry::Ptr geometry, const PointsMaterial::Ptr material)
     : Object3D_GM(geometry, object::ResolverT<Points>::make(*this), material),
       Object3D(object::ResolverT<Points>::make(*this))
  {}

public:
  using Ptr = std::shared_ptr<Points>;

  static Ptr make(const BufferGeometry::Ptr geometry=BufferGeometry::make(),
                  const PointsMaterial::Ptr material=PointsMaterial::make(Color(0xffffff * 1.0f / rand())))
  {
    return Ptr(new Points(geometry, material));
  }

  bool isShadowRenderable() const override {return true;}
};

}
#endif //THREEPP_POINTS_H
