#include <SDL3/SDL.h>
#include "DriveQuest.h"
#include <iostream>
#include <algorithm> // Required for std::clamp

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return 1;

    SDL_Window* window = SDL_CreateWindow("DriveQuest", 600, 900, 0);
    if (!window) return 1;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) return 1;

    // --- LOAD BACKGROUND TEXTURE ---
    SDL_Surface* roadSurface = SDL_LoadBMP("assets/RoadTexture.bmp");
    if (roadSurface == nullptr) {
        std::cerr << "Failed to load background: " << SDL_GetError() << std::endl;
    }

    SDL_Texture* backgroundTexture = nullptr;
    if (roadSurface != nullptr) {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, roadSurface);
        SDL_DestroySurface(roadSurface);
    }

    // --- LOAD CAR TEXTURE ---
    SDL_Surface* carSurface = SDL_LoadBMP("assets/CarSprite.bmp");

    // Check if it actually loaded
    if (carSurface == nullptr) {
        std::cerr << "Failed to load car: " << SDL_GetError() << std::endl;
    }

    SDL_Texture* carTexture = nullptr;
    if (carSurface != nullptr) {
        // Force SDL to use Magenta as transparent background
        SDL_SetSurfaceColorKey(carSurface, true, SDL_MapSurfaceRGB(carSurface, 0xFF, 0x00, 0xFF));

        carTexture = SDL_CreateTextureFromSurface(renderer, carSurface);
        SDL_DestroySurface(carSurface);
    }

    // --- MOVEMENT SETUP ---
    SDL_FRect carRect = { 165.0f, 600.0f, 100.0f, 150.0f };
    float carSpeed = 400.0f; // Pixels per second
    Uint64 lastTime = SDL_GetPerformanceCounter();

    // SCROLLING BACKGROUND SETUP
    float backgroundY = 0.0f;
    float backgroundSpeed = 200.0f; // Pixels per second

    // WRONG SIDE SETUP
    bool isOnWrongSide = false;
    float maxWrongSideTime = 5.0f; // Maximum time allowed on wrong side in seconds
    float activeTimer = maxWrongSideTime; // Timer that counts down when on wrong side

    // TEXT SETUP
    SDL_Surface* warningSurface = SDL_LoadBMP("assets/WarningText.bmp");
    SDL_Texture* warningTexture = nullptr;
    if (warningSurface != nullptr) {
        SDL_SetSurfaceColorKey(warningSurface, true, SDL_MapSurfaceRGB(warningSurface, 0xFF, 0x00, 0xFF));
        warningTexture = SDL_CreateTextureFromSurface(renderer, warningSurface);
        SDL_DestroySurface(warningSurface);
    }

    SDL_FRect warningRect = { 150.0f, 100.0f, 300.0f, 120.0f };

    // --- QUIZ STATE SETUP ---
    bool isQuizActive = false;
    float timeUntilNextQuiz = 15.0f; // seconds until first pop-up

    // Load sign
    SDL_Surface* signSurface = SDL_LoadBMP("assets/30Sign.bmp");
    SDL_Texture* signTexture = nullptr;
    if (signSurface != nullptr) {
        SDL_SetSurfaceColorKey(signSurface, true, SDL_MapSurfaceRGB(signSurface, 0xFF, 0x00, 0xFF));
        signTexture = SDL_CreateTextureFromSurface(renderer, signSurface);
        SDL_DestroySurface(signSurface);
    }
    SDL_FRect signRect = { 225.0f, 150.0f, 150.0f, 150.0f }; // Centered near top

    // Load Question Text
    SDL_Surface* questionSurface = SDL_LoadBMP("assets/Quiz1.bmp");
    SDL_Texture* questionTexture = nullptr;
    if (questionSurface != nullptr) {
        SDL_SetSurfaceColorKey(questionSurface, true, SDL_MapSurfaceRGB(questionSurface, 0xFF, 0x00, 0xFF));
        questionTexture = SDL_CreateTextureFromSurface(renderer, questionSurface);
        SDL_DestroySurface(questionSurface);
    }
    SDL_FRect questionRect = { 100.0f, 320.0f, 400.0f, 120.0f }; // Centered below sign

    // Load first button
    SDL_Surface* btnASurface = SDL_LoadBMP("assets/AnswerA30.bmp");
    SDL_Texture* btnATexture = nullptr;
    if (btnASurface != nullptr) {
        SDL_SetSurfaceColorKey(btnASurface, true, SDL_MapSurfaceRGB(btnASurface, 0xFF, 0x00, 0xFF));
        btnATexture = SDL_CreateTextureFromSurface(renderer, btnASurface);
        SDL_DestroySurface(btnASurface);
    }
    SDL_FRect btnARect = { 50.0f, 450.0f, 225.0f, 80.0f }; // Positioned on left

    // Load second button
    SDL_Surface* btnBSurface = SDL_LoadBMP("assets/AnswerB30.bmp");
    SDL_Texture* btnBTexture = nullptr;
    if (btnBSurface != nullptr) {
        SDL_SetSurfaceColorKey(btnBSurface, true, SDL_MapSurfaceRGB(btnBSurface, 0xFF, 0x00, 0xFF));
        btnBTexture = SDL_CreateTextureFromSurface(renderer, btnBSurface);
        SDL_DestroySurface(btnBSurface);
    }
    SDL_FRect btnBRect = { 325.0f, 450.0f, 225.0f, 80.0f }; // Positioned on right

    // --- GAME LOOP ---
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Delta Time Calculation
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (float)(currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        // Event Polling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }

            // --- MOUSE CLICK GRADING ---
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && isQuizActive) {
                // Only register Left Clicks
                if (event.button.button == SDL_BUTTON_LEFT) {
                    float mouseX = event.button.x;
                    float mouseY = event.button.y;

                    // Did mouse click inside first button rectangle? (Correct)
                    if (mouseX >= btnARect.x && mouseX <= btnARect.x + btnARect.w &&
                        mouseY >= btnARect.y && mouseY <= btnARect.y + btnARect.h) {

                        isQuizActive = false;
                        timeUntilNextQuiz = 15.0f;
                    }
                    // Did mouse click inside second button rectangle? (Wrong)
                    else if (mouseX >= btnBRect.x && mouseX <= btnBRect.x + btnBRect.w &&
                        mouseY >= btnBRect.y && mouseY <= btnBRect.y + btnBRect.h) {

                        std::cout << "Wrong Answer! Game Over!" << std::endl;
                        isRunning = false;
                    }
                }
            }
        }

        // --- STATE MACHINE ---
        if (!isQuizActive) {
            // --- DRIVING STATE ---
            const bool* keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_LEFT]) {
                carRect.x -= carSpeed * deltaTime;
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                carRect.x += carSpeed * deltaTime;
            }

            // Boundary Clamping
            carRect.x = std::clamp(carRect.x, 120.0f, 380.0f);

            // Update Background Position
            backgroundY += backgroundSpeed * deltaTime;
            if (backgroundY >= 900.0f) {
                backgroundY -= 900.0f;
            }

            // Check for wrong side
            if (carRect.x > 300.0f) {
                isOnWrongSide = true;
            }
            else {
                isOnWrongSide = false;
                activeTimer = maxWrongSideTime;
            }

            // Update timer if on wrong side
            if (isOnWrongSide) {
                activeTimer -= deltaTime;
                if (activeTimer <= 0.0f) {
                    std::cout << "Game Over! You stayed on wrong side for too long." << std::endl;
                    isRunning = false;
                }
            }

            // Quiz Trigger Countdown
            timeUntilNextQuiz -= deltaTime;
            if (timeUntilNextQuiz <= 0.0f) {
                isQuizActive = true; // Timer hit zero, pause game and show quiz
            }
        }

        // --- RENDERING ---
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer); // Clear canvas

        // Draw scrolling background
        if (backgroundTexture != nullptr) {
            SDL_FRect bgRect1 = { 0.0f, backgroundY - 900.0f, 600.0f, 900.0f };
            SDL_FRect bgRect2 = { 0.0f, backgroundY, 600.0f, 900.0f };
            SDL_RenderTexture(renderer, backgroundTexture, nullptr, &bgRect1);
            SDL_RenderTexture(renderer, backgroundTexture, nullptr, &bgRect2);
        }

        // Draw car on top of background
        if (carTexture != nullptr) {
            SDL_RenderTexture(renderer, carTexture, nullptr, &carRect);
        }

        // Draw warning text if on wrong side
        if (isOnWrongSide && warningTexture != nullptr) {
            SDL_RenderTexture(renderer, warningTexture, nullptr, &warningRect);
        }

        // --- RENDER QUIZ UI ---
        if (isQuizActive) {
            if (signTexture != nullptr) SDL_RenderTexture(renderer, signTexture, nullptr, &signRect);
            if (questionTexture != nullptr) SDL_RenderTexture(renderer, questionTexture, nullptr, &questionRect);
            if (btnATexture != nullptr) SDL_RenderTexture(renderer, btnATexture, nullptr, &btnARect);
            if (btnBTexture != nullptr) SDL_RenderTexture(renderer, btnBTexture, nullptr, &btnBRect);
        }

        // Swap back buffer to screen
        SDL_RenderPresent(renderer);
    }

    // --- CLEANUP ---
    if (carTexture != nullptr) {
        SDL_DestroyTexture(carTexture);
    }

    if (backgroundTexture != nullptr) {
        SDL_DestroyTexture(backgroundTexture);
    }

    // --- QUIZ CLEANUP ---
    if (signTexture != nullptr) SDL_DestroyTexture(signTexture);
    if (questionTexture != nullptr) SDL_DestroyTexture(questionTexture);
    if (btnATexture != nullptr) SDL_DestroyTexture(btnATexture);
    if (btnBTexture != nullptr) SDL_DestroyTexture(btnBTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}