#pragma once

#include <glad/gl.h>

#include <string>
#include <optional>
#include <sys/types.h>

namespace cherno {

class Shader {

public:
  enum class Type : signed char { None = -1, Vertex = 0, Fragment = 1 };

  [[nodiscard]] static auto CreateShaderFromSourceFile(std::string const& path) -> std::optional<Shader> ;
  
  Shader() = default;

  Shader(Type type, std::string const& src);

  auto GetId() const -> unsigned int {return m_id;};

  auto GetType() const noexcept -> Type { return m_type;}

  auto IsValid() const noexcept -> bool { return m_isValid;}

  void DeleteShaderProgram();

private:
  std::string m_source;
  char const * m_source_ptr;

  Type m_type {Type::None};
  uint m_id;
  bool m_isValid{};

};

} // namespace cherno
