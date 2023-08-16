#pragma once
#include <vector>
#include "Camera.h"
#include "Object.h"

class SceneManager {

private:
    static SceneManager* instance;

    std::vector<Object*> objects;
    std::vector<Camera*> cameras;

    SceneManager() {}

public:

    static SceneManager* GetInstance() {
        if (!instance)
            instance = new SceneManager();

        return instance;
    }

    void LoadScene(std::string sceneFile) {
        // Load objects, cameras, lights from scene file

        // Create each object


        // Create each camera
       

    }

    void UpdateScene(float deltaTime) {
        // Call update on each object
        for (Object* obj : objects) {
            obj->Update(deltaTime);
        }
    }

    // Other methods (Init, Key, Cleanup, etc)
};