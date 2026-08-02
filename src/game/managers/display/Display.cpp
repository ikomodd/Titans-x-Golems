#include "Display.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

 void game::DisplayManager::SetWindowSize() {

    baseplate::Vector2i windowSizeInt = 0;
    SDL_GetWindowSize(m_window, &windowSizeInt.X, &windowSizeInt.Y);
    m_windowSize = windowSizeInt.ToVector2();
}

//

void game::DisplayManager::Init() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    m_window = SDL_CreateWindow("game", m_windowSize.X, m_windowSize.Y, SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);

    SetWindowSize();

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cerr << "[game::DisplayManager] Erro ao iniciar o GLAD\n";

    glViewport(0, 0, m_windowSize.X, m_windowSize.Y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    m_projection = glm::ortho(0.0f, m_windowSize.X, m_windowSize.Y, 0.0f, -1.0f, 1.0f);

    m_stateManager = &baseplate::Manager<StateManager>::Get();
}

void game::DisplayManager::Event(const SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED)
        SetWindowSize();
}

void game::DisplayManager::Process() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);
    
    auto linearStateChildren = m_stateManager->GetCurrentState()->GetLinearChildren();

    for (baseplate::iNode* inode : linearStateChildren) {

        inode->Draw(m_vao, m_projection);
    }

    SDL_GL_SwapWindow(m_window);
}

void game::DisplayManager::Close() {

    SDL_DestroyWindow(m_window);
}