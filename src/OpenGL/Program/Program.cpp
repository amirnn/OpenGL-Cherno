#include "Program.hpp"
#include "glad/gl.h"
#include <utility>

namespace cherno {

Program::Program(std::vector<Shader> &&shadersVec)
{
  std::vector<Shader> shaders = shadersVec;
  for (auto &shader : shaders) 
  {
    if (shader.IsValid())
    {
      switch (shader.GetType())
      {
        case Shader::Type::Vertex: 
        {
            // Should initialized only once.
            if (not m_vertexShader.IsValid())
            {
                m_vertexShader = std::move(shader);
            }
            break;
        }
        case Shader::Type::Fragment:
        {
            if (not m_fragmentShader.IsValid())
            {
                m_fragmentShader = std::move(shader);
            }
            break;
        }
        default:
        {
            continue;
        }
      }
    }
  }
  m_isValid = m_vertexShader.IsValid() && m_fragmentShader.IsValid();

  if (m_isValid)
  {
    CompileProgram();
  }
}

Program::Program(std::vector<Shader> const& shadersVec): 
m_id{},
m_fragmentShader{},
m_vertexShader{}
{
    for (Shader const& shader : shadersVec)
    {
        if (shader.IsValid())
        {
            switch (shader.GetType())
            {
                case Shader::Type::Vertex: 
                {
                    // Should initialized only once.
                    if (not m_vertexShader.IsValid())
                    {
                        m_vertexShader = shader;
                    }
                    break;
                }
                case Shader::Type::Fragment:
                {
                    if (not m_fragmentShader.IsValid())
                    {
                        m_fragmentShader = shader;
                    }
                    break;
                }
                default:
                {
                    continue;
                }
            }
        }
    }
    m_isValid = m_vertexShader.IsValid() && m_fragmentShader.IsValid();

    if (m_isValid)
    {
        CompileProgram();
    }
}

void Program::CompileProgram()
{
    glAttachShader(m_id, m_vertexShader.GetId());
    glAttachShader(m_id, m_fragmentShader.GetId());
    glLinkProgram(m_id);
}

} // namespace cherno