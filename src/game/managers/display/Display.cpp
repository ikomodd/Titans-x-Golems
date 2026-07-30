#include "Display.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

 void GAME_DisplayManager::SetWindowSize() {

    baseplate::Vector2i WindowSizeInt = 0;
    SDL_GetWindowSize(m_Window, &WindowSizeInt.X, &WindowSizeInt.Y);
    m_WindowSize = WindowSizeInt.ToVector2();
}

//

void GAME_DisplayManager::_Init() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    m_Window = SDL_CreateWindow("game", m_WindowSize.X, m_WindowSize.Y, SDL_WINDOW_OPENGL);
    m_Context = SDL_GL_CreateContext(m_Window);

    SetWindowSize();

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cerr << "[GAME_DisplayManager] Erro ao iniciar o GLAD\n";

    glViewport(0, 0, m_WindowSize.X, m_WindowSize.Y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    m_Projection = glm::ortho(0.0f, m_WindowSize.X, m_WindowSize.Y, 0.0f, -1.0f, 1.0f);
}

void GAME_DisplayManager::_Event(SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED)
        SetWindowSize();
}

void GAME_DisplayManager::_Process() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    
    GAME_StateManager& StateManager = baseplate::Manager<GAME_StateManager>::Get();
    auto LinearStateChildren = StateManager.GetCurrentState()->GetLinearChildren();

    for (baseplate::iNode* inode : LinearStateChildren) {

        inode->_Draw();
    }

    SDL_GL_SwapWindow(m_Window);
}

void GAME_DisplayManager::_Close() {

    SDL_DestroyWindow(m_Window);
}