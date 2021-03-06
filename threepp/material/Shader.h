//
// Created by byter on 11/17/17.
//

#ifndef THREEPP_SHADER_H
#define THREEPP_SHADER_H

#include <string>
#include <threepp/renderers/gl/shader/ShaderLib.h>

namespace three {

/**
 * represents a OpenGL shader program. This class is only defined outside the renderer-specific realm to
 * accomodate the needs of ShaderMaterial
 */
class Shader
{
protected:
  const char * _name;
  gl::UniformValues _uniforms;

  std::string _vertexShader;
  std::string _fragmentShader;

public:
  Shader() : _name(nullptr) {}

  Shader(const char *name, const gl::UniformValues &uniforms, const std::string &vertexShader, const std::string &fragmentShader)
     : _name(name), _uniforms(uniforms), _vertexShader(vertexShader), _fragmentShader(fragmentShader) {}

  Shader(const char *name, const gl::ShaderInfo &shaderInfo)
     : _name(name), _uniforms(shaderInfo.uniforms), _vertexShader(shaderInfo.vertexShader), _fragmentShader(shaderInfo.fragmentShader) {}

  gl::UniformValues &uniforms() {return _uniforms;}

  const char *vertexShader() {return _vertexShader.data();}
  const char *fragmentShader() {return _fragmentShader.data();}

  const char *name() const {return _name;}
};

}

#endif //THREEPP_SHADER_H
