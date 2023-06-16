#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono> // Added for time-related functions
#include <thread> // Added for sleep_for function

using namespace std;

const int WINDOW_WIDTH = 80;
const int WINDOW_HEIGHT = 50;
const int NUM_PARTICLES = 30;

float distance(float x1, float y1, float x2, float y2) {
    const float xDist = x2 - x1;
    const float yDist = y2 - y1;
    return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

class Particle {
public:
    Particle(float x, float y, float directionX, float directionY)
        : x(x), y(y), directionX(directionX), directionY(directionY) {}

    void draw() {
        
        cout << "C++";  // Particle represented as a string
    }

    void update(vector<Particle>& particles) {
        x += directionX;
        y += directionY;

        if (x + 2 > WINDOW_WIDTH || x - 2 < 0)
            directionX = -directionX;
        if (y + 2 > WINDOW_HEIGHT || y - 2 < 0)
            directionY = -directionY;

        for (const Particle& particle : particles) {
            if (distance(x, y, particle.x, particle.y) <= 10) {
                cout << "\033[" << static_cast<int>(y) << ";" << static_cast<int>(x) << "H";  // Move cursor to (x, y)
                
            }
        }
    }

    float x, y;
    float directionX, directionY;
};

int main() {
    vector<Particle> particleArray;
    default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
    uniform_real_distribution<float> directionDistribution(-2.0f, 2.0f);
    uniform_real_distribution<float> positionDistribution(2.0f, 18.0f);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        float x = positionDistribution(engine);
        float y = positionDistribution(engine);
        float directionX = directionDistribution(engine);
        float directionY = directionDistribution(engine);
        particleArray.emplace_back(x, y, directionX, directionY);
    }

    while (true) {
        // Clear console
        cout << "\033[2J";
        cout << "\033[1;1H";  // Move cursor to (1, 1)

        for (Particle& particle : particleArray) { // Removed 'const' qualifier
            particle.update(particleArray);
            particle.draw();
        }

        cout.flush();

        // Delay to control animation speed
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
