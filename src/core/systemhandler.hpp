#pragma once


//Forward dec.
class Logger;
class Window;

//typical singleton
class SystemHandler {
    public:

        //Copy constr.
        SystemHandler(const SystemHandler&) = delete;
        SystemHandler& operator=(const SystemHandler&) = delete;

        //Move constr.
        SystemHandler(SystemHandler&&) = delete;
        SystemHandler& operator=(SystemHandler&&) = delete;

        //Access
        static SystemHandler& getSystem() {
            static SystemHandler system;
            return system;
        }

        //Utilities
        bool Init();
        void Run();
        void Clean();

    private:
        //Constr. & Destr.
        SystemHandler();
        ~SystemHandler();

    private:
        //what's system manages
        Logger *m_Logger = nullptr;
        Window *m_Window = nullptr;

};