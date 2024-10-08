#include "Pulsar.hpp"

#include "glad.h" //Temporary, when everything will be encapsulated - then delete.

int main(){

    PX_LOG::Init();
    PX_TIMER::Init();
    
    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();

    ShaderSource src;
    std::string file_path = "/home/marek/Dev/Projects/pulsarEngine/res/shader_prog.txt";

    src = ReadGLSLFromFile(file_path);

    const char *vertexShaderSource = src.s_vertexSource.c_str();
    // PX_CORE_INFO("Vertex Shader");
    // PX_CORE_INFO(vertexShaderSource);
    const char *fragmentShaderSource = src.s_fragmentSource.c_str();
    // PX_CORE_INFO("Fragment Shader");
    // PX_CORE_INFO(fragmentShaderSource);
   

    //Create shader program
    unsigned int shaderProgram = glCreateProgram();
    if (shaderProgram == 0)
        PX_CORE_ERROR("Shader program cretion failed!\n");
    
    //Create shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(vertexShader == 0 || fragmentShader == 0)
        PX_CORE_ERROR("Shader objects cretion failed!\n");

    //Compile shaders
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Check if compilation complete
    int compilationFlag; 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationFlag);
    if(compilationFlag != GL_TRUE){
        PX_CORE_ERROR("Vertex shader compilation failed!\n");
        return -1;
    }
    
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Check if compilation complete
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compilationFlag);
    if(compilationFlag != GL_TRUE){
        PX_CORE_ERROR("Vertex shader compilation failed!\n");
        return -1;
    }

    //Attach shaders to program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    //Link program
    glLinkProgram(shaderProgram);

    //Use shader program
    glUseProgram(shaderProgram);

    //Delete uncessesary shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //TODO

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Unbind VAO
    glBindVertexArray(0); 

    while (!window->ShouldWindowClose())
    {
        //Event handler - in the future

        // PX_CORE_TIMER_START();

        renderer->BeginRender();
        // PX_CORE_TIMER_STOP_MILI("Rendering");


        
        //Calculation...

        //Rendering staff...

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

        //GUI adjustment
        
        gui->OnBegin();
        /*
            Customizing gui...
        */
        gui->OnEnd();
        
        window->onUpdate();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);


    PX::ShutDown();


    return 0;
}