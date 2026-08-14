#include "Display.hpp"

#include "game/managers/scene/Scene.hpp"
#include "game/managers/interface/Interface.hpp"
#include "game/origins/Origin.hpp"

#include "game/instances/frame/Frame2D.hpp"

#include <algorithm>

 void game::DisplayManager::SetWindowSize() {

    baseplate::Vector2i windowSizeInt = 0;
    SDL_GetWindowSize(m_window, &windowSizeInt.X, &windowSizeInt.Y);
    m_windowSize = windowSizeInt.ToVector2() / projectionScale;

    baseplate::Vector2 realySize = windowSizeInt.ToVector2();

    m_projection = glm::ortho(0.0f, m_windowSize.X, m_windowSize.Y, 0.0f, -1.0f, 1.0f);
    glViewport(0, 0, realySize.X, realySize.Y);
}

//

void game::DisplayManager::Init() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    m_window = SDL_CreateWindow("game", m_windowSize.X, m_windowSize.Y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    m_context = SDL_GL_CreateContext(m_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        std::cerr << "[game::DisplayManager] Erro ao iniciar o GLAD\n";

    SetWindowSize();

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

    m_interfaceManager = &baseplate::Manager<InterfaceManager>::Get();
    m_sceneManager = &baseplate::Manager<SceneManager>::Get();
}

void game::DisplayManager::Event(const SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_RESIZED) {

        SetWindowSize();

        auto linearInterfaceChildren = m_interfaceManager->GetCurrentInterface()->GetLinearChildren();

        for (auto* node : linearInterfaceChildren) {

            Frame2D* frame = node->As<Frame2D>();
            if (frame)
                frame->UpdateTransform(m_windowSize);
        }
    }
}

void game::DisplayManager::Process() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);

    //

    auto linearInterfaceChildren = m_interfaceManager->GetCurrentInterface()->GetLinearChildren();
    auto linearSceneChildren = m_sceneManager->GetCurrentScene()->GetLinearChildren();

    std::vector<baseplate::iNode*> allChildrens;
    
    allChildrens.insert(allChildrens.end(), linearSceneChildren.begin(), linearSceneChildren.end());
    allChildrens.insert(allChildrens.end(), linearInterfaceChildren.begin(), linearInterfaceChildren.end());
    
    for (baseplate::iNode* inode : allChildrens) {

        inode->Draw(m_vao, m_projection);
    }

    SDL_GL_SwapWindow(m_window);
}

void game::DisplayManager::Close() {

    SDL_DestroyWindow(m_window);
}