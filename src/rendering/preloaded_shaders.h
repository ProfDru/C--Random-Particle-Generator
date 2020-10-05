#pragma once
#include <rendering\shader.h>

#include <vector>
#include <string>

namespace rpg::rendering {

static Shader ParticleShader(
    "shaders/particle",
    std::vector<ShaderUniform>{ShaderUniform("MVP", ShaderUniform::type::MVP)},
    std::vector<ShaderAttribute>{
        ShaderAttribute("vcolor", ShaderAttribute::type::color),
        ShaderAttribute("vpos", ShaderAttribute::type::vertex)});

}  // namespace rpg::rendering
