//
// Created by byter on 29.07.17.
//

#ifndef THREEQT_WEBGLRENDERER
#define THREEQT_WEBGLRENDERER

#include <QOpenGLContext>
#include <Constants.h>
#include <scene/Scene.h>
#include <camera/Camera.h>

namespace three {

struct OpenGLRendererData
{
  bool alpha = false;
  bool depth = true;
  bool stencil = true;
  bool antialias = false;
  bool premultipliedAlpha = true;
  bool preserveDrawingBuffer = false;
};

class OpenGLRenderer : private OpenGLRendererData
{
protected:
  QOpenGLContext *_context;

  // clearing
  bool _autoClear = true;
  bool _autoClearColor = true;
  bool _autoClearDepth = true;
  bool _autoClearStencil = true;

  // scene graph
  bool _sortObjects = true;

  // user-defined clipping
  //this.clippingPlanes = [];
  bool _localClippingEnabled = false;

  // physically based shading
  float _gammaFactor = 2.0;	// for backwards compatibility
  bool _gammaInput = false;
  bool _gammaOutput = false;

  // physical lights
  bool _physicallyCorrectLights = false;

  // tone mapping
  ToneMapping _toneMapping = ToneMapping::Linear;
  float _toneMappingExposure = 1.0;
  float _toneMappingWhitePoint = 1.0;

  // morphs
  unsigned _maxMorphTargets = 8;
  unsigned _maxMorphNormals = 4;

  OpenGLRenderer(QOpenGLContext *context, OpenGLRendererData data=OpenGLRendererData())
  {

  }
  OpenGLRenderer(float width, float height)
  {

  }
public:
  using Ptr = std::shared_ptr<OpenGLRenderer>;
  static Ptr make(QOpenGLContext *context, float width, float height);

  OpenGLRenderer &setClearColor(const Color &color) {
    //_backg
  }

  OpenGLRenderer &setSize(unsigned width, unsigned height) {

  }

  void render(const Scene &scene, const Camera::Ptr &camera) {

  }
};

}


#endif //THREEQT_WEBGLRENDERER
