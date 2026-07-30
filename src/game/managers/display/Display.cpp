#include "Display.hpp"

#include "game/managers/state/State.hpp"
#include "game/states/state/State.hpp"

 void game::DisplayManager::SetWindowSize() {

    baseplate::Vector2i WindowSizeInt = 0;
    SDL_GetWindowSize(mWindow, &WindowSizeInt.X, &WindowSizeInt.Y);
    mWindowSize = WindowSizeInt.ToVector2();
}

//

void game::DisplayManager::_Init() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    mWindow = SDL_CreateWindow("game", mWindowSize.X, mWindowSize.Y, SDL_WINDOW_OPENGL);
    mContext = SDL_GL_CreateContext(mWindow);

    SetWindowSize();

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cerr << "[game::DisplayManager] Erro ao iniciar o GLAD\n";

    glViewport(0, 0, mWindowSize.X, mWindowSize.Y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    mProjection = glm::ortho(0.0f, mWindowSize.X, mWindowSize.Y, 0.0f, -1.0f, 1.0f);

    mStateManager = &baseplate::Manager<StateManager>::Get();
}

void game::DisplayManager::_Event(SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED)
        SetWindowSize();
}

void game::DisplayManager::_Process() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(mVAO);
    
    auto LinearStateChildren = mStateManager->GetCurrentState()->GetLinearChildren();

    for (baseplate::iNode* inode : LinearStateChildren) {

        inode->_Draw(mVAO, mProjection);
    }

    SDL_GL_SwapWindow(mWindow);
}

void game::DisplayManager::_Close() {

    SDL_DestroyWindow(mWindow);
}