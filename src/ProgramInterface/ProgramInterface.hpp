#pragma once

namespace cherno 
{
    class ProgramInterface
    {
        public:
        virtual void Start(int argc, char const * argv[]) = 0;
        virtual void Init() = 0;
        virtual void MainLoop() = 0;
        virtual void CleanUp() = 0;

        virtual ~ProgramInterface() = default;
    };
}