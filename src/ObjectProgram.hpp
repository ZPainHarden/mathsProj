#pragma once
#include "p6/p6.h"

struct ObjectProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTreeTexture;

    GLint uLightPos_vs;
    GLint uLightPosPoint_vs;
    GLint uLightPos02_vs;
    GLint uLightPos03_vs;
    GLint uLightIntensity;
    GLint uKd;
    GLint uKs;
    GLint uShininess;

    ObjectProgram()
        : m_Program{p6::load_shader("src/shaders/3D.vs.glsl", "src/shaders/directionalLight.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uTreeTexture  = glGetUniformLocation(m_Program.id(), "uTexture");

        uLightPosPoint_vs = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightPos_vs      = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightPos02_vs    = glGetUniformLocation(m_Program.id(), "uLightDir02_vs");
        uLightPos03_vs    = glGetUniformLocation(m_Program.id(), "uLightDir03_vs");
        uLightIntensity   = glGetUniformLocation(m_Program.id(), "uLightIntensity");
        uKd               = glGetUniformLocation(m_Program.id(), "uKd");
        uKs               = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess        = glGetUniformLocation(m_Program.id(), "uShininess");
    }
};
