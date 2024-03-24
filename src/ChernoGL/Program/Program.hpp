#pragma once

#include "../Shader/Shader.hpp"
#include <vector>

namespace cherno
{
class Program
{
public:
    explicit Program(std::vector<Shader>&& shadersVec);
    explicit Program(std::vector<Shader> const& shadersVec);

    auto GetId() const noexcept -> uint { return m_id;}
    auto IsValid() const noexcept -> bool {return m_isValid;}
    
private:
  Shader m_vertexShader;
  Shader m_fragmentShader;
  uint m_id{};
  bool m_isValid{};

  void CompileProgram();

};
} // namespace cherno
