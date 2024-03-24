#pragma once

#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../ChernoGL//Program/Program.hpp"

#include "../ProgramInterface/ProgramInterface.hpp"

namespace cherno
{
    class GLProgram final: public cherno::ProgramInterface
    {
        public:
        ~GLProgram() override;

        void Start(int argc, char const * argv[]) override;

        struct SharedState
        {
            GLFWwindow *window{nullptr};
            std::shared_ptr<Program> programPtr;
            uint vertexArray{};
            uint mvpLocation{};
        };

        private:
        void Init() override;
        void MainLoop() override;
        void CleanUp() override;

        SharedState m_state;
    };
}

