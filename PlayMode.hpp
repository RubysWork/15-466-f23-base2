#include "Mode.hpp"

#include "Scene.hpp"

#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <deque>

struct PlayMode : Mode
{
	PlayMode();
	virtual ~PlayMode();

	// functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;
	virtual float distance(glm::uvec3 a, glm::uvec3 b);
	//----- game state -----

	// input tracking:
	struct Button
	{
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, forward, back, down, up, F;

	// local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	/*
	// hexapod leg to wobble:
	Scene::Transform *hip = nullptr;
	Scene::Transform *upper_leg = nullptr;
	Scene::Transform *lower_leg = nullptr;
	glm::quat hip_base_rotation;
	glm::quat upper_leg_base_rotation;
	glm::quat lower_leg_base_rotation;
	float wobble = 0.0f;
	*/

	// object
	Scene::Transform *dolphin = nullptr;
	Scene::Transform *ground = nullptr;

	typedef struct Fish
	{
		int index = 0;
		Scene::Transform *transform = nullptr;
		glm::quat fish_rotation_base;
	} Fish;
	std::array<Fish, 10> fishes;

	typedef struct Coral
	{
		int index = 0;
		Scene::Transform *transform = nullptr;
	} Coral;
	std::array<Coral, 5> corals;

	typedef struct CleanCoral
	{
		int index = 0;
		Scene::Transform *transform = nullptr;
	} CleanCoral;
	std::array<CleanCoral, 5> clean_corals;

	//  camera:
	Scene::Camera *camera = nullptr;
	// variables
	bool F_once = true;
	int energy = 0;
	int clean_coral_num = 0;
	bool show_warning = false;
	bool show_win = false;
	int timer = 0;
	bool starttimer = false;
	float wobble = 0.0f;
	glm::quat dolphin_rotation_base;
};
