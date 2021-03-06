//
// Created by byter on 12/14/17.
//

#ifndef THREEPPQ_MATERIAL_H
#define THREEPPQ_MATERIAL_H

#include <threepp/quick/ThreeQObjectRoot.h>
#include <threepp/quick/qutil/MeshCreator.h>
#include <threepp/quick/textures/Texture.h>

namespace three {
namespace quick {

class Material : public ThreeQObjectRoot
{
Q_OBJECT
  Q_PROPERTY(bool wireframe READ wireframe WRITE setWireframe NOTIFY wireframeChanged)
  Q_PROPERTY(bool flatShading READ flatShading WRITE setFlatShading NOTIFY flatShadingChanged)
  Q_PROPERTY(bool needsUpdate READ needsUpdate WRITE setNeedsUpdate NOTIFY needsUpdateChanged)
  Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
  Q_PROPERTY(QByteArray name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(Texture *map READ map WRITE setMap NOTIFY mapChanged)

protected:
  bool _wireframe = false;
  bool _flatShading = false;
  bool _visible = true;
  Texture *_map = nullptr;
  QByteArray _name;

  Material(QObject *parent = nullptr) : ThreeQObjectRoot(parent) {}

  virtual three::Material::Ptr material() const = 0;

  bool needsUpdate() const {return material() ? material()->needsUpdate : true;}

  void setNeedsUpdate(bool value) {
    three::Material::Ptr mat = material();
    if(mat && mat->needsUpdate != value) {
      mat->needsUpdate = value;
      emit needsUpdateChanged();
    }
  }

  void setBaseProperties(three::Material::Ptr material) const;

public:
  bool visible() const {return _visible;}

  void setVisible(bool visible) {
    if(_visible != visible) {
      _visible = visible;
      if(material()) {
        material()->visible = _visible;
      }
      emit visibleChanged();
    }
  }

  bool wireframe() const {return _wireframe;}

  void setWireframe(bool wireframe) {
    if(_wireframe != wireframe) {
      _wireframe = wireframe;
      emit wireframeChanged();
    }
  }

  bool flatShading() const {return _flatShading;}

  void setFlatShading(bool flatShading) {
    if(_flatShading != flatShading) {
      _flatShading = flatShading;
      emit flatShadingChanged();
    }
  }

  const QByteArray &name() const {return _name;}

  void setName(const QByteArray &name) {
    if(_name != name) {
      _name = name;
      emit nameChanged();
    }
  }

  Texture *map() const {return _map;}

  void setMap(Texture *map);

  virtual void identify(MeshCreator &creator) {}

signals:
  void wireframeChanged();
  void flatShadingChanged();
  void needsUpdateChanged();
  void mapChanged();
  void visibleChanged();
  void nameChanged();
};

}
}

#endif //THREEPPQ_MATERIAL_H
