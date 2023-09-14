#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <random>
#include <string>

// define a vao
GLuint hexapod_meshes_for_lit_color_texture_program = 0;
// Load mesh
Load<MeshBuffer> hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const *
								{
	MeshBuffer const *ret = new MeshBuffer(data_path("dolphin.pnct"));
	hexapod_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret; });

// load scene
Load<Scene> hexapod_scene(LoadTagDefault, []() -> Scene const *
						  { return new Scene(data_path("dolphin.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name)
											 {
												 Mesh const &mesh = hexapod_meshes->lookup(mesh_name);

												//put the scene info to drawable
												 scene.drawables.emplace_back(transform);
												 Scene::Drawable &drawable = scene.drawables.back();

												 drawable.pipeline = lit_color_texture_program_pipeline;

												 drawable.pipeline.vao = hexapod_meshes_for_lit_color_texture_program;
												 drawable.pipeline.type = mesh.type;
												 drawable.pipeline.start = mesh.start;
												 drawable.pipeline.count = mesh.count; }); });

// scene's playmode
PlayMode::PlayMode() : scene(*hexapod_scene)
{
	// get pointers to objects
	for (auto &transform : scene.transforms)
	{
		if (transform.name == "Dolphin")
			dolphin = &transform;
		else if (transform.name == "Fish")
		{
			Fish fish0;
			fish0.index = 0;
			fish0.transform = &transform;
			fish0.fish_rotation_base = fish0.transform->rotation;
			fishes[0] = fish0;
		}
		else if (transform.name == "Fish1")
		{
			Fish fish1;
			fish1.index = 1;
			fish1.transform = &transform;
			fish1.fish_rotation_base = fish1.transform->rotation;
			fishes[1] = fish1;
		}
		else if (transform.name == "Fish2")
		{
			Fish fish2;
			fish2.index = 2;
			fish2.transform = &transform;
			fish2.fish_rotation_base = fish2.transform->rotation;
			fishes[2] = fish2;
		}
		else if (transform.name == "Fish3")
		{
			Fish fish3;
			fish3.index = 3;
			fish3.transform = &transform;
			fish3.fish_rotation_base = fish3.transform->rotation;
			fishes[3] = fish3;
		}
		else if (transform.name == "Fish4")
		{
			Fish fish4;
			fish4.index = 4;
			fish4.transform = &transform;
			fish4.fish_rotation_base = fish4.transform->rotation;
			fishes[4] = fish4;
		}
		else if (transform.name == "Fish5")
		{
			Fish fish5;
			fish5.index = 5;
			fish5.transform = &transform;
			fish5.fish_rotation_base = fish5.transform->rotation;
			fishes[5] = fish5;
		}
		else if (transform.name == "Fish6")
		{
			Fish fish6;
			fish6.index = 6;
			fish6.transform = &transform;
			fish6.fish_rotation_base = fish6.transform->rotation;
			fishes[6] = fish6;
		}
		else if (transform.name == "Fish7")
		{
			Fish fish7;
			fish7.index = 7;
			fish7.transform = &transform;
			fish7.fish_rotation_base = fish7.transform->rotation;
			fishes[7] = fish7;
		}
		else if (transform.name == "Fish8")
		{
			Fish fish8;
			fish8.index = 8;
			fish8.transform = &transform;
			fish8.fish_rotation_base = fish8.transform->rotation;
			fishes[8] = fish8;
		}
		else if (transform.name == "Fish9")
		{
			Fish fish9;
			fish9.index = 9;
			fish9.transform = &transform;
			fish9.fish_rotation_base = fish9.transform->rotation;
			fishes[9] = fish9;
		}

		else if (transform.name == "Coral")
		{
			Coral coral0;
			coral0.index = 0;
			coral0.transform = &transform;
			corals[0] = coral0;
		}
		else if (transform.name == "Coral1")
		{
			Coral coral1;
			coral1.index = 1;
			coral1.transform = &transform;
			corals[1] = coral1;
		}
		else if (transform.name == "Coral2")
		{
			Coral coral2;
			coral2.index = 2;
			coral2.transform = &transform;
			corals[2] = coral2;
		}
		else if (transform.name == "Coral3")
		{
			Coral coral3;
			coral3.index = 3;
			coral3.transform = &transform;
			corals[3] = coral3;
		}
		else if (transform.name == "Coral4")
		{
			Coral coral4;
			coral4.index = 4;
			coral4.transform = &transform;
			corals[4] = coral4;
		}
		else if (transform.name == "CleanCoral")
		{
			CleanCoral clean_coral;
			clean_coral.index = 0;
			clean_coral.transform = &transform;
			clean_corals[0] = clean_coral;
		}
		else if (transform.name == "CleanCoral1")
		{
			CleanCoral clean_coral1;
			clean_coral1.index = 1;
			clean_coral1.transform = &transform;
			clean_corals[1] = clean_coral1;
		}
		else if (transform.name == "CleanCoral2")
		{
			CleanCoral clean_coral2;
			clean_coral2.index = 2;
			clean_coral2.transform = &transform;
			clean_corals[2] = clean_coral2;
		}
		else if (transform.name == "CleanCoral3")
		{
			CleanCoral clean_coral3;
			clean_coral3.index = 3;
			clean_coral3.transform = &transform;
			clean_corals[3] = clean_coral3;
		}
		else if (transform.name == "CleanCoral4")
		{
			CleanCoral clean_coral4;
			clean_coral4.index = 4;
			clean_coral4.transform = &transform;
			clean_corals[4] = clean_coral4;
		}
		else if (transform.name == "Ground")
			ground = &transform;
	}

	// get pointer to camera for convenience:
	if (scene.cameras.size() != 1)
		throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();
}

PlayMode::~PlayMode()
{
}
/*
bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size)
{

	if (evt.type == SDL_KEYDOWN)
	{
		if (evt.key.keysym.sym == SDLK_a)
		{
			std::cout << "left!" << std::endl;
			left.downs += 1;
			left.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_d)
		{
			std::cout << "right!" << std::endl;
			right.downs += 1;
			right.pressed = true;
			return true;
		}
	}
	else if (evt.type == SDL_KEYUP)
	{
		if (evt.key.keysym.sym == SDLK_a)
		{
			left.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_d)
		{
			right.pressed = false;
			return true;
		}
	}

	return false;
}
*/

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size)
{

	if (evt.type == SDL_KEYDOWN)
	{

		if (evt.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_a)
		{
			left.downs += 1;
			left.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_d)
		{
			right.downs += 1;
			right.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_e)
		{
			up.downs += 1;
			up.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_q)
		{
			down.downs += 1;
			down.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_w)
		{
			forward.downs += 1;
			forward.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_s)
		{
			back.downs += 1;
			back.pressed = true;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_f)
		{
			F.downs += 1;
			F.pressed = true;
			return true;
		}
	}
	else if (evt.type == SDL_KEYUP)
	{
		if (evt.key.keysym.sym == SDLK_a)
		{
			left.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_d)
		{
			right.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_e)
		{
			up.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_q)
		{
			down.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_w)
		{
			forward.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_s)
		{
			back.pressed = false;
			return true;
		}
		else if (evt.key.keysym.sym == SDLK_f)
		{
			F.pressed = false;
			F.downs = true;
			F_once = true;
			return true;
		}
	}

	else if (evt.type == SDL_MOUSEBUTTONDOWN)
	{
		if (SDL_GetRelativeMouseMode() == SDL_FALSE)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed)
{
	// if clean all coral, win
	if (clean_coral_num < 5)
	{
		float FishSpeed = 10.0f;
		//  fish move
		for (auto fish : fishes)
		{
			fish.transform->position.x -= FishSpeed * elapsed / 10.0f;
			fish.transform->rotation = fish.fish_rotation_base * glm::angleAxis(glm::radians(80.0f * std::sin(wobble * 2.0f * float(M_PI))), glm::vec3(0.0f, 0.0f, 0.1f));
		}
		// fish detect
		for (auto fish : fishes)
		{
			if (distance(dolphin->position, fish.transform->position) < 5)
			{
				fish.transform->position.z = -25;
				energy++;

				show_warning = false;
				starttimer = false;
				timer = 0;
			}
		}
		// coral detect
		for (auto coral : corals)
		{
			if (distance(dolphin->position, coral.transform->position) < 10 && F.pressed && F_once)
			{
				if (energy > 0)
				{
					show_warning = false;
					starttimer = false;
					timer = 0;

					energy--;
					clean_coral_num++;
					clean_corals[coral.index].transform->position.z = -13;
					coral.transform->position.z = -25;
					F_once = false;
				}
				else
				{
					show_warning = true;
					starttimer = true;
				}
			}
		}
		// timer
		if (starttimer)
		{
			if (timer > 300)
			{
				show_warning = false;
				starttimer = false;
				timer = 0;
			}
			else
			{
				timer++;
			}
		}

		// move dolphin:
		{
			// combine inputs into a move:
			constexpr float PlayerSpeed = 30.0f;
			glm::vec3 new_dolphWPos = dolphin->position;
			glm::quat new_dolphWRo = dolphin->rotation;
			glm::vec3 move = glm::vec3(0.0f);
			if (forward.pressed && !back.pressed)
			{
				move.x -= PlayerSpeed * elapsed;
			}
			if (back.pressed && !forward.pressed)
			{
				move.x += PlayerSpeed * elapsed;
			}
			if (left.pressed && !right.pressed)
			{
				new_dolphWRo = glm::quat(1, 0, 0, PlayerSpeed * elapsed / 60.0f) * new_dolphWRo;
			}

			if (!left.pressed && right.pressed)
			{
				new_dolphWRo = glm::quat(1, 0, 0, -PlayerSpeed * elapsed / 60.0f) * new_dolphWRo;
			}

			if (down.pressed && !up.pressed)
			{
				move.z -= PlayerSpeed * elapsed;
			}

			if (!down.pressed && up.pressed)
			{
				move.z += PlayerSpeed * elapsed;
			}

			// make it so that moving diagonally doesn't go faster:
			if (move != glm::vec3(0.0f))
				move = glm::normalize(move) * PlayerSpeed * elapsed;

			glm::mat4x3 frame = dolphin->make_local_to_parent();
			glm::vec3 frame_forward = frame[0];
			glm::vec3 frame_right = -frame[1];
			glm::vec3 frame_up = -frame[2]; // back is +z, so -

			// Set border
			if (new_dolphWPos.x > -300 && new_dolphWPos.x < 220 && new_dolphWPos.y > -200 && new_dolphWPos.y < 220 && new_dolphWPos.z < 44 && new_dolphWPos.z > ground->position.z)
				dolphin->position = dolphin->position + move.x * frame_forward + move.y * frame_right + move.z * frame_up;
			else
			{
				if (new_dolphWPos.x < -300)
					new_dolphWPos.x = -299;
				if (new_dolphWPos.x > 220)
					new_dolphWPos.x = 219;
				if (new_dolphWPos.y < -200)
					new_dolphWPos.y = -219;
				if (new_dolphWPos.y > 220)
					new_dolphWPos.y = 219;
				if (new_dolphWPos.z > 44)
					new_dolphWPos.z = 43;
				if (new_dolphWPos.z < ground->position.z)
					new_dolphWPos.z = ground->position.z + 1;
				dolphin->position = new_dolphWPos;
			}

			dolphin->rotation = new_dolphWRo;
			camera->transform->position = glm::vec3(dolphin->position.x + 45, dolphin->position.y, dolphin->position.z + 25);
		}

		// reset button press counters:
		left.downs = 0;
		right.downs = 0;
		up.downs = 0;
		down.downs = 0;
		F.downs = 0;
	}
	else
	{
		show_win = true;
	}
}

void PlayMode::draw(glm::uvec2 const &drawable_size)
{
	// update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	// set up light type and position for lit_color_texture_program:
	//  TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, -1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); // 1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); // this is the default depth comparison function, but FYI you can change it.

	GL_ERRORS(); // print any errors produced by this setup code

	// just for draw text
	scene.draw(*camera);

	{ // use DrawLines to overlay some text:

		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));

		// draw text
		constexpr float H = 0.09f;
		lines.draw_text("Hold Mose & WASDQE moves; Escape ungrabs mouse; Catch fish to earn energy; F clean coral;",
						glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
						glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
						glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text("Hold Mose & WASDQE moves; Escape ungrabs mouse; Catch fish to earn energy; F clean coral;",
						glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + +0.1f * H + ofs, 0.0),
						glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
						glm::u8vec4(0xff, 0xff, 0xff, 0x00));
		lines.draw_text("Current Energy: " + std::to_string(energy) + "; Cleaned Coral: " + std::to_string(clean_coral_num) + "/5;",
						glm::vec3(-aspect + 0.1f * H + 2800.0f / drawable_size.x, -1.0 + 0.1f * H + 1300.0f / drawable_size.y, 0.0),
						glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
						glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		lines.draw_text("Current Energy: " + std::to_string(energy) + "; Cleaned Coral: " + std::to_string(clean_coral_num) + "/5;",
						glm::vec3(-aspect + 0.1f * H + +2800.0f / drawable_size.x + ofs, -1.0 + +0.1f * H + 1300.0f / drawable_size.y + ofs, 0.0),
						glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
						glm::u8vec4(0xff, 0x80, 0x00, 0x00));

		if (show_warning)
		{
			constexpr float height = 0.09f;
			float offset = 1300.0f / drawable_size.y;
			lines.draw_text("No Energy!",
							glm::vec3(-aspect + 0.1f * height + offset - 302.0f / drawable_size.y, -1.0 + 0.1f * height + offset - 2.0f / drawable_size.y, 0.0),
							glm::vec3(height, 0.0f, 0.0f), glm::vec3(0.0f, height, 0.0f),
							glm::u8vec4(0x00, 0x00, 0x00, 0x00));
			lines.draw_text("No Energy!",
							glm::vec3(-aspect + 0.1f * height + offset - 300.0f / drawable_size.y, -1.0 + +0.1f * height + offset, 0.0),
							glm::vec3(height, 0.0f, 0.0f), glm::vec3(0.0f, height, 0.0f),
							glm::u8vec4(0xff, 0x00, 0x00, 0x00));
		}

		// save the ocean
		if (show_win)
		{
			constexpr float height = 0.3f;
			float offset = 500.0f / drawable_size.y;
			lines.draw_text("You Saved the Ocean!",
							glm::vec3(-aspect + 0.1f * height + 496.0f / drawable_size.y, -1.0 + +0.1f * height + 496.0f / drawable_size.y, 0.0),
							glm::vec3(height, 0.0f, 0.0f), glm::vec3(0.0f, height, 0.0f),
							glm::u8vec4(0xff, 0xff, 0xff, 0x00));
			lines.draw_text("You Saved the Ocean!",
							glm::vec3(-aspect + 0.1f * height + 498.0f / drawable_size.y, -1.0 + 0.1f * height + 498.0f / drawable_size.y, 0.0),
							glm::vec3(height, 0.0f, 0.0f), glm::vec3(0.0f, height, 0.0f),
							glm::u8vec4(0x00, 0x00, 0x00, 0x00));
			lines.draw_text("You Saved the Ocean!",
							glm::vec3(-aspect + 0.1f * height + offset, -1.0 + +0.1f * height + offset, 0.0),
							glm::vec3(height, 0.0f, 0.0f), glm::vec3(0.0f, height, 0.0f),
							glm::u8vec4(0xff, 0x80, 0x00, 0x00));
		}
	}
}

float PlayMode::distance(glm::uvec3 a, glm::uvec3 b)
{
	float dis = (float)sqrt(pow(abs((int)(a.x - b.x)), 2) + pow(abs((int)(a.y - b.y)), 2) + pow(abs((int)(a.z - b.z)), 2));
	return dis;
}