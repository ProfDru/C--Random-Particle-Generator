#pragma once
#include <rendering\shader.h>

#include <vector>
#include <string>

namespace rpg::rendering {

static Shader ParticleShader(
    "shaders/particle",
    std::vector<ShaderUniform>{
        ShaderUniform("MVP", ShaderUniform::type::MVP),
        ShaderUniform("g_Resolution", ShaderUniform::type::SCREEN_XY)},
    std::vector<ShaderAttribute>{
        ShaderAttribute("vcolor", ShaderAttribute::type::color),
        ShaderAttribute("vpos", ShaderAttribute::type::vertex)});

static Shader RainbowShader(
    "shaders/RainbowParticle",
    "shaders/particle",
    std::vector<ShaderUniform>{ShaderUniform("MVP", ShaderUniform::type::MVP)},
    std::vector<ShaderAttribute>{
        ShaderAttribute("vpos", ShaderAttribute::type::vertex)});

}  // namespace rpg::rendering
