#include <application.hpp>
#include "model_file_scene.hpp"
#include <iostream>
#include <mesh/mesh_utils.hpp>
#include <textures/texture_utils.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;
const int WIDTH = 400;
const int HEIGHT = 600;
/*
*
* The goal of this scene is just to showcase simple static model loading
* Also to show Anisotropic filtering
*
*/

void ModelFileScene::Initialize() {
	
	Color = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	
	
	ObjectLocation = { 0,0,0};
	ObjectRotation = { 0,0,0 };
	//Defining our shaders

	//main shader (used for ship textyring)
    shader = new Shader();
    shader->attach("assets/shaders/texture.vert", GL_VERTEX_SHADER);
    shader->attach("assets/shaders/texture.frag", GL_FRAGMENT_SHADER);
    shader->link();
	//Used for water effects
	waterShader = new Shader();
	waterShader->attach("assets/shaders/water.vert", GL_VERTEX_SHADER);
	waterShader->attach("assets/shaders/water.frag", GL_FRAGMENT_SHADER);
	waterShader->link();
	////3dTexture effects and loading
	//skyShader = new Shader();
	//skyShader->attach("assets/shaders/sky.vert", GL_VERTEX_SHADER);
	//skyShader->attach("assets/shaders/sky.frag", GL_FRAGMENT_SHADER);
	//skyShader->link();

	//unifroms locations
	//You dont have to store its value, you can just call the function "glGetUniformLocation" inside "glUniform3f" msln, zay ma m3mol f SkyShader
	mLoc = glGetUniformLocation(shader->getID(), "M");
	mitLoc = glGetUniformLocation(shader->getID(), "M_it");
	vpLoc = glGetUniformLocation(shader->getID(), "VP");
	camPosLoc = glGetUniformLocation(shader->getID(), "cam_pos");

    texLoc = glGetUniformLocation(shader->getID(), "tex");
	moveFactorofWater = glGetUniformLocation(waterShader->getID(), "moveFactor");
	mvpLocofWater = glGetUniformLocation(waterShader->getID(), "MVP");
	texLocofWater = glGetUniformLocation(waterShader->getID(), "reflect");
	dudvLoc = glGetUniformLocation(waterShader->getID(), "dudvMap");

	//defining meshUtilitis
    plane = MeshUtils::Plane({0,0}, {10,10});
    boatMesh = MeshUtils::LoadObj("assets/models/Boat/12219_boat_v2_L2.obj");
	port = MeshUtils::LoadObj("assets/models/port/port.obj");
	lighthouse = MeshUtils::LoadObj("assets/models/lighthouse/lighthouse.obj");
	//cube = MeshUtils::Box();


	//defining our Textures
	watertex = TextureUtils::Load2DTextureFromFile("assets/textures/reflection.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	dudvTex = TextureUtils::Load2DTextureFromFile("assets/textures/waterDUDV.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    boatTex = TextureUtils::Load2DTextureFromFile("assets/models/Boat/boat_roof_accessory_diffuse.jpg");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	portTex = TextureUtils::Load2DTextureFromFile("assets/models/port/port01.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	lighthouseTex = TextureUtils::Load2DTextureFromFile("assets/models/lighthouse/lighthouse.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	shader->use();
	shader->set("ambient", 1.0f);
	shader->set("light.diffuse", { 0.8f, 0.8f, 0.8f });
	shader->set("light.ambient", { 0.1f, 0.1f, 0.1f });
	shader->set("light.specular", { 1.0f, 1.0f, 1.0f });
	shader->set("light.attenuation", 0.001f);
	shader->set("light.inner_cone", glm::pi<float>() / 1.0f);
	shader->set("light.outer_cone", glm::pi<float>() / 5.0f);
	shader->set("light.position", { 36, -2, -25 });
	shader->set("colortransform", Color);

	/*const char* files[6] = {
		"assets/textures/Sky/posx.png",
		"assets/textures/Sky/negx.png",
		"assets/textures/Sky/posy.png",
		"assets/textures/Sky/negy.png",
		"assets/textures/Sky/posz.png",
		"assets/textures/Sky/negz.png"
	};*/
	//env = TextureUtils::LoadCubTextureFromFiles(files);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////Enable Seamless cubemap filtering so that no seams appear at the cube edges
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);



	//camera xD
    camera = new Camera();
    glm::ivec2 windowSize = getApplication()->getWindowSize();
    camera->setupPerspective(glm::pi<float>()/2, (float)windowSize.x / windowSize.y, 0.1f, 1000.0f);
    camera->setUp({0, 1, 0});

    controller = new FlyCameraController(this, camera);
    controller->setYaw(0);
    controller->setPitch(0);
    controller->setPosition({-10, 15, 0});

	lightYaw = lightPitch = glm::quarter_pi<float>();

	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//this line for testing changes
	glClearColor(0,0,0,0.0f);
}
inline glm::vec3 getTimeOfDayMix(float sunPitch) {
	sunPitch /= glm::half_pi<float>();
	if (sunPitch > 0) {
		float noon = glm::smoothstep(0.0f, 0.5f, sunPitch);
		return{ noon, 1.0f - noon, 0 };
	}
	else {
		float dusk = glm::smoothstep(0.0f, 0.25f, -sunPitch);
		return{ 0, 1.0f - dusk, dusk };
	}
}
void ModelFileScene::Update(double delta_time) {
    controller->update(delta_time);
	controller->setPosition({ ObjectLocation.x-10,ObjectLocation.y+10,ObjectLocation.z });
	Keyboard* kb = getKeyboard();
	float temp = ObjectLocation.x;

	float yaw_speed = 0.5f;
	if (kb->isPressed(GLFW_KEY_K)) lightYaw += (float)delta_time * yaw_speed;
	if (kb->isPressed(GLFW_KEY_J)) lightYaw -= (float)delta_time * yaw_speed;
	if (lightYaw < -glm::half_pi<float>()) lightYaw = -glm::half_pi<float>();
	if (lightYaw > glm::half_pi<float>()) lightYaw = glm::half_pi<float>();
	lightYaw = glm::wrapAngle(lightYaw);

	/////////////////////////////////////////SPEED CONTROL ///////////////////////////////////////////////////////////
	if (kb->isPressed(GLFW_KEY_LEFT_SHIFT))
	{
		speedvalue = 3;
	}
	else
	{
		speedvalue = 1;
	}
	
	//--------------------------------------------------------------------------------------------//

	///////////////////////////////////////////////////////////BASIC CONTROLS ////////////////////////////////
	if (kb->isPressed(GLFW_KEY_UP))
	{
		temp += (float)delta_time * 4 * speedvalue;
		if (85 - temp > 15.5)
		{
			ObjectLocation.x = temp;
		}
	}
	if (kb->isPressed(GLFW_KEY_DOWN))
	{
		ObjectLocation.x -= (float)delta_time * 4* speedvalue;
	}

	if (kb->isPressed(GLFW_KEY_RIGHT))
	{
		ObjectLocation.z += (float)delta_time * 4* speedvalue;
	}

	if (kb->isPressed(GLFW_KEY_LEFT))
	{
		ObjectLocation.z -= (float)delta_time * 4* speedvalue;
	}
	//----------------------------------------------------------------------------------------//

	///////////////////////////////////////////////// ROTATIONAL CONTROL///////////////////////////////////////
	if (kb->isPressed(GLFW_KEY_RIGHT) && kb->isPressed(GLFW_KEY_UP))
	{
		if (ObjectRotation.z < 0.5)
			ObjectRotation.z += 0.01;
	}

	else if (kb->isPressed(GLFW_KEY_LEFT) && kb->isPressed(GLFW_KEY_UP))
	{
		if (ObjectRotation.z > -0.5)
			ObjectRotation.z -= 0.01;
	}
	else if (kb->isPressed(GLFW_KEY_RIGHT) && kb->isPressed(GLFW_KEY_DOWN))
	{
		if (ObjectRotation.z > -0.5)
			ObjectRotation.z -= 0.01;

	}

	else if (kb->isPressed(GLFW_KEY_LEFT) && kb->isPressed(GLFW_KEY_DOWN))
	{
		if (ObjectRotation.z < 0.5)
			ObjectRotation.z += 0.01;

	}
	else
	{
		
		if (ObjectRotation.z < 0.00)
			ObjectRotation.z += 0.01;
		else if (ObjectRotation.z > 0.00&&ObjectRotation.z > 0.01)
			ObjectRotation -= 0.01;
		
	}
	controller->setYaw(ObjectRotation.z);
	//-------------------------------------------------------------------------------------//

	////////////////////////////////////// COLOR TRANSFORMATION EFFECT ////////////////////////////////////
	if (kb->justPressed(GLFW_KEY_C))
	{
		clr = !clr;
		
		if (clr)
		{
			Color = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
		}
		else
		{
			Color = { {0.393, 0.349, 0.272,0},{0.769, 0.686, 0.534,0},{0.189, 0.168, 0.131,0},{0,0,0,1} };
		
		}
		shader->use();
		shader->set("colortransform", Color);
	}


}

void ModelFileScene::Draw() {
	
	//No frame buffers objects are rendered Yet

	//main frameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glm::vec3 cam_pos = camera->getPosition();
	glm::mat4 VP = camera->getVPMatrix();
	glm::mat4 V = camera->getViewMatrix();
	glm::vec3 lightdir = glm::vec3(glm::cos(lightYaw), 0, glm::sin(lightYaw));

	shader->use();
	shader->set("VP", VP);
	shader->set("V", V);
	shader->set("cam_pos", cam_pos);
	shader->set("light.direction", -lightdir);

	//this line is almost useless
	//glClearColor(0.96f, 0.1f, 0.99f, 0.0f);
	glClearColor(0.16015625f, 0.05859375f, 0.3515625, 0.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear colors and depth
	
	//first rendering the sky cube texture
	//glActiveTexture(GL_TEXTURE0);
	//env->bind();

	//skyShader->use();
	//glUniformMatrix4fv(glGetUniformLocation(skyShader->getID(), "VP"), 1, GL_FALSE, glm::value_ptr(VP));
	//glUniform3f(glGetUniformLocation(skyShader->getID(), "cam_pos"), cam_pos.x, cam_pos.y, cam_pos.z);
	//glUniform1i(glGetUniformLocation(skyShader->getID(), "tex"), 0);

	//glDepthFunc(GL_LEQUAL);//Since sky shader always draws at maximum depth (1) we need to use less-than-or-equal
	//glDepthMask(GL_FALSE);//Disable writing to depth buffer
	//glCullFace(GL_FRONT);//Draw cube from the inside

	//glm::mat4 sky_mat = glm::translate(glm::mat4(), cam_pos); //Note that the sky move with the camera
	//glUniformMatrix4fv(glGetUniformLocation(skyShader->getID(), "M"), 1, GL_FALSE, glm::value_ptr(sky_mat));
	//cube->draw();

	//Return depth test and culling to usual state
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);



	//some Transformation Matrices
	glm::mat4 tree_mat = glm::translate(glm::mat4(), { 5 + ObjectLocation.x, 0 + ObjectLocation.y, 0 + ObjectLocation.z })
		* glm::scale(glm::mat4(), { 0.01, 0.01,0.01 })
		*glm::rotate(glm::mat4(), (float)(-90 * 3.14 / 180), { 1,0,0 })
		*glm::rotate(glm::mat4(), (float)(-180 * 3.14 / 180)+ObjectRotation.z, { 0,0,-1 });

	glm::mat4 ground_mat = glm::scale(glm::mat4(), glm::vec3(100, 1, 100));

	//rendering Water Plane
	//notice we've rendered two textures
	//dudvTex for distortion
	waterShader->use();
	glUniform1i(texLocofWater, 0);
	glUniform1i(dudvLoc, 1);
	//you can change the movefactor value, I think this one is the best, so far
	moveFactor += 0.00001f *(float)glfwGetTime();
	if (moveFactor > 1) moveFactor = 0;
	glUniform1f(moveFactorofWater, moveFactor);

	//rendering the water scene
	glActiveTexture(GL_TEXTURE0);
	watertex->bind();
	glActiveTexture(GL_TEXTURE1);
	dudvTex->bind();
	glUniformMatrix4fv(mvpLocofWater, 1, GL_FALSE, glm::value_ptr(VP * ground_mat));
	plane->draw();


	//rendering the Ship scene 
	shader->use();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texLoc, 0);
	boatTex->bind();
	glm::mat4 boat_mat = tree_mat;
	shader->set("M", boat_mat);

	cam_pos = camera->getPosition();
	shader->set("cam_pos", cam_pos);
	V = camera->getViewMatrix();
	shader->set("V", VP);

	shader->set("M_it", glm::transpose(glm::inverse(boat_mat)));
	shader->set("material.diffuse", { 0.9f,0.9f,0.9f });
	shader->set("material.specular", { 1.0f,1.0f,1.0f });
	shader->set("material.ambient", { 0.5f,0.6f,0.5f });
	shader->set("material.shininess", 32);
	boatMesh->draw();

	shader->use();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texLoc, 0);
	portTex->bind();
	glm::mat4 port_mat = glm::translate(glm::mat4(), { 90 ,3, 8 })*
		glm::rotate(glm::mat4(), glm::half_pi<float>() ,{ 0 , -1 , 0 } ) *
		glm::scale(glm::mat4(), { 1.55 , 1 , 1 });
	shader->set("M", port_mat);

	cam_pos = camera->getPosition();
	shader->set("cam_pos", cam_pos);
	V = camera->getViewMatrix();
	shader->set("V", V);

	shader->set("M_it", glm::transpose(glm::inverse(port_mat)));
	shader->set("material.diffuse", { 0.8f,0.8f,0.8f });
	shader->set("material.specular", { 1.0f,1.0f,1.0f });
	shader->set("material.ambient", { 0.5f,0.6f,0.5f });
	shader->set("material.shininess", 32);
	port->draw();

	shader->use();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texLoc, 0);
	lighthouseTex->bind();

	glm::mat4 lighthouse_mat = translate(glm::mat4(), { 36, -2, -25 }) * glm::scale(glm::mat4(), { 0.01,0.014,0.01 });
	shader->set("M", lighthouse_mat);

	cam_pos = camera->getPosition();
	shader->set("cam_pos", cam_pos);
	V = camera->getViewMatrix();
	shader->set("V", V);

	shader->set("M_it", glm::transpose(glm::inverse(lighthouse_mat)));
	shader->set("material.diffuse", { 0.8f,0.8f,0.8f });
	shader->set("material.specular", { 1.0f,1.0f,1.0f });
	shader->set("material.ambient", { 0.5f,0.6f,0.5f });
	shader->set("material.shininess", 32);
	lighthouse->draw();

}

void ModelFileScene::Finalize() {
	delete controller;
    delete camera;
    delete boatTex;
	delete watertex;
	delete boatMesh;
    delete plane;
    delete shader;
	delete dudvTex;
	delete port;
	delete portTex;
}