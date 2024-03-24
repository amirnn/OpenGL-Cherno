#include "Shader.hpp"
#include "glad/gl.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

#include "../../Utils/GLCall.hpp"

namespace cherno {

    auto Shader::CreateShaderFromSourceFile(const std::string &path) ->  std::optional<Shader>
    {
        std::ifstream file {path};
        std::string line;
        std::stringstream source;
        Shader::Type type{Type::None};
        while (std::getline(file, line)) 
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos) 
                {
                    type = Type::Vertex;
                }
                else if( line.find("fragment") != std::string::npos)
                {
                    type = Type::Fragment;
                }
                else
                {
                    type = Type::None;
                }
            }
            else
            {
                source << line << std::endl;
            }
        }

        std::string str = source.str();
        
        assert(source.str().size() != 0);

        Shader shader {type, source.str()};
        
        if (shader.IsValid()) 
        {
            return shader;
        }

        return {};
    }

Shader::Shader(Type type, std::string const& src)
{
    uint enum_type;
    switch (type)
    {
        case Type::Vertex:
        {
            m_type = type;
            enum_type = GL_VERTEX_SHADER;
            break;
        }
        case Type::Fragment:
        {
            m_type = type;
            enum_type = GL_FRAGMENT_SHADER;
            break;
        }
        default:
        {
            enum_type = 0;
            m_type = Type::None;
            break;
        }
    }
    if (enum_type != 0)
    {
        GLCall(m_id = glCreateShader(enum_type));
        m_source = src;
        m_source_ptr = m_source.c_str();

        GLCall(glShaderSource(m_id, 1, &m_source_ptr, nullptr));
        GLCall(glCompileShader(m_id));

        m_isValid = true;
    }
    else 
    {
        m_id = 0;
        m_source.clear();
        m_source_ptr = nullptr;
        m_isValid = false;
    }
}

Shader::~Shader() {GLCall(glDeleteShader(m_id));}

}