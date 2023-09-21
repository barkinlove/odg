#include <GL/glew.h>

#include "Config.hxx"
#include "Game.hxx"
#include "Loader.hxx"
#include "Object.hxx"
#include "Renderer.hxx"
#include "Shader.hxx"
#include "ShaderFactory.hxx"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_opengl.h>
#include <SDL_events.h>
#include <SDL_timer.h>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <ranges>
#include <set>
#include <spdlog/spdlog.h>

#include <iostream>

Renderer::Renderer(Game& game)
  : m_game(game)
{
  spdlog::info("Started initializing renderer");
}

static const auto defaultShaderPath =
  std::filesystem::current_path() / "shaders/";

void Renderer::init_shaders()
{
  m_shaderProgram = glCreateProgram();
  auto path = Config::has("shaderPath") ? Config::get<std::string>("shaderPath")
                                        : defaultShaderPath.string();
  size_t count = load_shaders(path);

  if (count > 0) {
    build_shaders();
  }
}

static uint32_t s_lastFrameTime = 0;

void Renderer::render()
{
  static float g_scale = 0.f;
  g_scale += 0.01f;

  auto model = glm::scale(glm::identity<glm::mat4x4>(), { 0.5f, 0.5f, 0.5f });
  model = glm::rotate(model, std::sin(g_scale), { 0.f, 0.f, 1.f });
  model = glm::rotate(model, std::sin(g_scale), { 1.f, 0.f, 0.f });

  Camera& cam = m_game.get_camera();

  uint32_t timeDelta = SDL_GetTicks() - s_lastFrameTime;
  s_lastFrameTime = SDL_GetTicks();
  cam.set_acceleration(timeDelta);

  glm::mat4x4 view = cam.get_view();

  glm::mat4x4 projection =
    glm::perspective(glm::radians(45.f),
                     static_cast<float>(m_game.get_window().get_width()) /
                       m_game.get_window().get_height(),
                     0.1f,
                     100.f);

  GLuint modelLocation = glGetUniformLocation(m_shaderProgram, "model");
  GLuint viewLocation = glGetUniformLocation(m_shaderProgram, "view");
  GLuint projectionLocation =
    glGetUniformLocation(m_shaderProgram, "projection");
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(
    projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

  const Model& renderModel = m_models[0];

  for (const auto& mesh : renderModel.meshes) {
    glBindVertexArray(mesh.get_vao());
    glDrawElements(GL_TRIANGLES, mesh.get_indices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}

void handleInput(Game& game, const SDL_KeyboardEvent& event)
{
  std::string_view key = SDL_GetKeyName(event.keysym.sym);
  Camera& cam = game.get_camera();
  if (key == "W") {
    cam.move_forward();
  }

  if (key == "A") {
    cam.move_left();
  }

  if (key == "D") {
    cam.move_right();
  }

  if (key == "S") {
    cam.move_backward();
  }

  if (key == "Up") {
    cam.increase_pitch();
  }

  if (key == "Down") {
    cam.decrease_pitch();
  }

  if (key == "Left") {
    cam.decrease_yaw();
  }

  if (key == "Right") {
    cam.incraese_yaw();
  }
}

void Renderer::main_loop()
{
  // wanna keep init here in order to be able to obtain window instance
  init();

  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        handleInput(m_game, e.key);
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render();
    SDL_GL_SwapWindow(m_game.get_window().get_underlying());
  }
}

void Renderer::init()
{
  m_glContext = SDL_GL_CreateContext(m_game.get_window().get_underlying());
  if (!m_glContext) {
    spdlog::critical("wasnt able to intialize opengl context");
    return;
  }
  GLenum error = glewInit();
  if (error != GLEW_OK) {
    spdlog::critical("failed to initialize glew");
    return;
  }

  // Vsync why so?
  if (SDL_GL_SetSwapInterval(1) < 0) {
    spdlog::warn("unable to enable vsync. reason: {}", SDL_GetError());
  }
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glEnable(GL_DEPTH_TEST);

  init_shaders();
  std::string_view modelPath = "path/to/monkey";
  m_models.push_back(Loader::load_model(modelPath));
}

static constexpr std::array<std::string_view, 2> s_allowedShaderExtensions = {
  ".vs",
  ".fs"
};

static constexpr std::array<GLenum, 2> s_shaderTypes = { GL_VERTEX_SHADER,
                                                         GL_FRAGMENT_SHADER };

size_t Renderer::load_shaders(std::filesystem::path path)
{
  std::vector<std::filesystem::directory_entry> filenames;
  std::filesystem::directory_iterator dirs{ path };

  for (const auto& entry : dirs) {
    const bool isExtensionAllowed = std::any_of(
      s_allowedShaderExtensions.begin(),
      s_allowedShaderExtensions.end(),
      [extension = entry.path().extension()](auto allowedExtension) {
        return allowedExtension == extension;
      });

    if (isExtensionAllowed) {
      filenames.push_back(entry);
    }
  }

  m_shaders.reserve(filenames.size());

  for (const auto& file : filenames) {
    std::ifstream openedFile{ file.path() };
    std::string filename = file.path().filename().string();

    if (!openedFile.is_open()) {
      spdlog::error("Unable to open shader file {}. Skipping it.", filename);
      continue;
    }

    std::stringstream ss;
    ss << openedFile.rdbuf();

    if (ss.fail()) {
      spdlog::error("Unable to read shader source: {}. Skipping it.", filename);
      continue;
    }

    auto it =
      std::ranges::find(s_allowedShaderExtensions, file.path().extension());
    auto idx = std::ranges::distance(s_allowedShaderExtensions.begin(), it);

    m_shaders.push_back(
      ShaderFactory::Create(s_shaderTypes[idx], filename, ss.str()));
  }
  spdlog::info("{} shaders have been loaded in total.", m_shaders.size());
  return m_shaders.size();
}

void Renderer::build_shaders()
{
  compile_shaders();
  glLinkProgram(m_shaderProgram);
  GLint success;
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    std::string log;
    log.reserve(1024);
    glGetProgramInfoLog(m_shaderProgram, log.capacity(), nullptr, log.data());
    throw std::runtime_error(fmt::format("Error linking program. {}", log));
  }
  glValidateProgram(m_shaderProgram);
  glUseProgram(m_shaderProgram);
}

void Renderer::compile_shaders()
{
  for (const auto& shader : m_shaders) {
    compile_shader(shader);
  }
}

void Renderer::compile_shader(const Shader& shader)
{
  glCompileShader(shader.get_object());
  GLint success;
  glGetShaderiv(shader.get_object(), GL_COMPILE_STATUS, &success);
  if (!success) {
    std::string log;
    log.reserve(1024);
    glGetShaderInfoLog(
      shader.get_object(), log.capacity(), nullptr, log.data());
    spdlog::error("Unable to compile shader {}. Shader info log: {}",
                  shader.get_name(),
                  log);
  }
  glAttachShader(m_shaderProgram, shader.get_object());
}

Renderer::~Renderer()
{
  destroy_shaders();
}

void Renderer::destroy_shaders()
{
  for (const auto& shader : m_shaders) {
    destroy_shader(shader);
  }
}

void Renderer::destroy_shader(const Shader& shader)
{
  glDetachShader(m_shaderProgram, shader.get_object());
  glDeleteShader(shader.get_object());
}
