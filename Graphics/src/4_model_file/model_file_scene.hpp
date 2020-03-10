#ifndef MODEL_FILE_SCENE_HPP
#define MODEL_FILE_SCENE_HPP

#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <../common/framebuffer.hpp>
#include <scene.hpp>
#include <shader.hpp>
#include <mesh/mesh.hpp>
#include <textures/texture2d.hpp>
#include <textures/texture_cube.hpp>
#include <camera/camera.hpp>
#include <camera/controllers/fly_camera_controller.hpp>



class ModelFileScene : public Scene {
private:
    Shader* shader,*waterShader,*skyShader;
    Mesh* plane, *boatMesh,*cube , *port, *lighthouse;
    Camera* camera;
	glm::vec3 lightPosition;
	float lightYaw, lightPitch;
    FlyCameraController* controller;
	bool speed=false ;
	int speedvalue = 1;
	bool clr = false;
    Texture2D* checkers, *moonTex, *boatTex,*watertex,*dudvTex, *portTex, *lighthouseTex;
	FrameBuffer* fbo;
	TextureCube* env;
	glm::vec3 ObjectLocation;
	glm::vec3 ObjectRotation;
	glm::mat4 Color;
	glm::mat4 frameVPMatrix;
	float moveFactor = 0; //for the water movement
    GLuint mLoc,mitLoc,camPosLoc,vpLoc, texLoc, dudvLoc, texLocofWater, mvpLocofWater, moveFactorofWater;

public:
    ModelFileScene(Application* app): Scene(app) {}

    void Initialize() override;
    void Update(double delta_time) override;
    void Draw() override;
    void Finalize() override;
};

#endif