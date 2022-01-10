#include "Component.h"

class Spawner : public Component
{
public:
    ~Spawner();
    void draw() const {}
    void tick();
    void collisionHandler(int other) {}
    bool collsionAftermath(int other) { return false; }
    virtual void spawnFunc() = 0;

protected:
    Spawner() : Component(0, 0, 0, 0, 0) {
    }
};