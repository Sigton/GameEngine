#include <GameEngine.h>
#include <GameEngine/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public GameEngine::Layer
{
public:
	GameLayer()
		: Layer("Game Layer")
	{
		// define geometry and indices
		float cubeVertices[8 * (3 + 2)] = {
			-1.0f,	 1.0f,	 -1.0f,		0.0f, 1.0f,
			 1.0f,	 1.0f,	 -1.0f,		1.0f, 1.0f,
			-1.0f,	-1.0f,	 -1.0f,		0.0f, 0.0f,
			 1.0f,	-1.0f,	 -1.0f,		1.0f, 0.0f,
			-1.0f,	 1.0f,	  1.0f,		1.0f, 0.0f,
			 1.0f,	 1.0f,	  1.0f,		0.0f, 0.0f,
			-1.0f,	-1.0f,	  1.0f,		1.0f, 1.0f,
			 1.0f,	-1.0f,	  1.0f,		0.0f, 1.0f
		};

		unsigned int cubeIndices[6 * 6] = {
			0, 3, 1, 0, 2, 3,
			5, 6, 4, 5, 7, 6,
			4, 2, 0, 4, 6, 2,
			1, 7, 5, 1, 3, 7,
			4, 1, 5, 4, 0, 1,
			2, 7, 3, 2, 6, 7
		};


		float squareVertices[4 * (3 + 4)] = {
			-1.0f,	 1.0f,	 0.0f,		0.0f, 1.0f,
			 1.0f,	 1.0f,	 0.0f,		1.0f, 1.0f,
			-1.0f,	-1.0f,	 0.0f,		0.0f, 0.0f,
			 1.0f,	-1.0f,	 0.0f,		1.0f, 0.0f
		};

		unsigned int squareIndices[6] =
		{
			0, 3, 1, 0, 2, 3
		};

		// gen vertex array
		m_VertexArray = GameEngine::VertexArray::Create();

		std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer = GameEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float2, "a_TextureCoords"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<GameEngine::IndexBuffer> indexBuffer = GameEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader = GameEngine::Shader::Create("assets/shaders/Texture.glsl");

		m_Texture = GameEngine::Texture2D::Create("assets/textures/smile.png");

		m_Shader->Bind();
		m_Shader->SetInt("u_Texture", 0);

		m_Camera = std::make_shared<GameEngine::PerspectiveCamera>();
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);

		m_Transform = std::make_shared<GameEngine::Transform>();
		m_SquareScale = glm::vec3(1.0f);
		
	}

	virtual void OnAttach() override
	{
	}

	virtual void OnUpdate() override
	{
		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);

		m_Transform->SetPosition(m_SquarePosition);
		m_Transform->SetRotation(m_SquareRotation);
		m_Transform->SetScale(m_SquareScale);

		// CLEAR FROM LAST FRAME
		GameEngine::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1));
		GameEngine::RenderCommand::Clear();


		// BEGIN RENDERING SCENE
		GameEngine::Renderer::BeginScene(*m_Camera);


		// SUBMIT TO RENDERER
		m_Texture->Bind();
		GameEngine::Renderer::Submit(m_Shader, m_VertexArray, m_Transform);


		// END RENDERING SCENE
		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Camera Controls");
		ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_CameraPosition), -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(m_CameraRotation), -3.14f, 3.14f);

		if (ImGui::Button("Reset"))
		{
			m_CameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
			m_CameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		ImGui::End();

		ImGui::Begin("Square Controls");
		ImGui::SliderFloat3("Square Position", glm::value_ptr(m_SquarePosition), -5.0f, 5.0f);
		ImGui::SliderFloat3("Square Rotation", glm::value_ptr(m_SquareRotation), -5.0f, 5.0f);
		ImGui::SliderFloat3("Square Scale", glm::value_ptr(m_SquareScale), -5.0f, 5.0f);

		if (ImGui::Button("Reset"))
		{
			m_SquarePosition = glm::vec3(0);
			m_SquareRotation = glm::vec3(0);
			m_SquareScale = glm::vec3(1);
		}

		ImGui::End();
	}

private:
	std::shared_ptr<GameEngine::VertexArray> m_VertexArray;
	std::shared_ptr<GameEngine::Shader> m_Shader;

	std::shared_ptr<GameEngine::Texture2D> m_Texture;

	std::shared_ptr<GameEngine::PerspectiveCamera> m_Camera;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraRotation;

	std::shared_ptr<GameEngine::Transform> m_Transform;
	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareRotation;
	glm::vec3 m_SquareScale;
};


class SandboxApp : public GameEngine::Application
{
public:
	SandboxApp()
	{
		PushLayer(new GameLayer());
	}
};


GameEngine::Application* GameEngine::CreateApplication()
{
	return new SandboxApp();
}
