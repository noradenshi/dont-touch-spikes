#include "bird.h"
#include "spike.h"
#include <raylib.h>
#include <raymath.h>
#include <string.h>

const int width = 600;
const int height = 800;

const Color color = {200, 250, 50, 255};
const float radius = 16.f;
const float gravity = 1500.f;
const float horizontalSpeed = 400.f;
const float flapForce = 400.f;
const float maxFallVelocity = 600.f;
const Vector2 startPos = {width / 2.f, height / 4.f};

Vector2 pos = startPos;
float fallVelocity = 0.f;
bool directionRight = true;
int score = -1;
char scoreText[16] = "score: ";
Texture birdTexture;
bool gameOver = false;

void strrev(char *str) {
    const int length = strlen(str);
    char t;
    for (int i = 0; i < length / 2; i++) {
        t = str[0];
        str[0] = str[length - 1 - i];
        str[length - 1 - i] = t;
    }
}

void strnumber(char *str, unsigned int n) {
    int i = 0;
    do {
        str[i] = n % 10 + '0';
        n /= 10;
        i++;
    } while (n > 0);
    strrev(str);
    str[i] = 0;
}

void bird_init() { birdTexture = LoadTexture("resources/bird.png"); }

void bird_reset() {
    gameOver = false;
    pos = startPos;
    score = -1;
}

void bird_update(const float deltaTime) {
    if (pos.y > height + radius)
        return;

    fallVelocity += gravity * deltaTime;
    if (fallVelocity > maxFallVelocity)
        fallVelocity = maxFallVelocity;

    pos.y += fallVelocity * deltaTime;
    if (gameOver)
        return;

    if ((pos.y > height - radius) || (pos.y < radius))
        gameOver = true;

    pos.x += horizontalSpeed * deltaTime * (directionRight ? 1 : -1);

    if ((pos.x + radius > width) || (pos.x < radius)) {
        if (spike_checkCollision(pos.y)) {
            gameOver = true;
            return;
        }
        directionRight = !directionRight;
        score++;
        spike_next(directionRight ? width : 0, score / 10 + 3);
    }

    if (IsKeyPressed(KEY_UP) || IsMouseButtonPressed(0)) {
        fallVelocity = -flapForce;
    }

    strnumber(&scoreText[7], score);
}

void bird_draw() {
    if (score >= 0)
        DrawText(scoreText, width / 2 - 100, 100, 40, GRAY);

    DrawTexturePro(birdTexture,
                   (Rectangle){0, 0, directionRight ? 16 : -16, 16},
                   (Rectangle){pos.x, pos.y, radius * 2, radius * 2},
                   (Vector2){radius, radius}, 0.f, WHITE);
}
