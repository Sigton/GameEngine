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
		{
			// cube with normals
			float cubeVertices[4 * 6 * (3 + 3)] = { // num vertices per side * num sides * (components of position + components of normal)
				// front side
				-1.0f,  1.0f,  1.0f,		 0.0f,  0.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,		 0.0f,  0.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,		 0.0f,  0.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,		 0.0f,  0.0f,  1.0f,
				 // back side	 		 	   
				  1.0f,  1.0f, -1.0f,		 0.0f,  0.0f, -1.0f,
				 -1.0f,  1.0f, -1.0f,		 0.0f,  0.0f, -1.0f,
				  1.0f, -1.0f, -1.0f,		 0.0f,  0.0f, -1.0f,
				 -1.0f, -1.0f, -1.0f,		 0.0f,  0.0f, -1.0f,
				 // top side		 		 	   
				 -1.0f,  1.0f, -1.0f,		 0.0f,  1.0f,  0.0f,
				  1.0f,  1.0f, -1.0f,		 0.0f,  1.0f,  0.0f,
				 -1.0f,  1.0f,  1.0f,		 0.0f,  1.0f,  0.0f,
				  1.0f,  1.0f,  1.0f,		 0.0f,  1.0f,  0.0f,
				  // bottom side 			 		 		   
				  -1.0f, -1.0f,  1.0f,		 0.0f, -1.0f,  0.0f,
				   1.0f, -1.0f,  1.0f,		 0.0f, -1.0f,  0.0f,
				  -1.0f, -1.0f, -1.0f,		 0.0f, -1.0f,  0.0f,
				   1.0f, -1.0f, -1.0f,		 0.0f, -1.0f,  0.0f,
				   // left side	 		 		 	 	   
				   -1.0f,  1.0f, -1.0f,		-1.0f,  0.0f,  0.0f,
				   -1.0f,  1.0f,  1.0f,		-1.0f,  0.0f,  0.0f,
				   -1.0f, -1.0f, -1.0f,		-1.0f,  0.0f,  0.0f,
				   -1.0f, -1.0f,  1.0f,		-1.0f,  0.0f,  0.0f,
				   // right side 			 	 	 	   
					1.0f,  1.0f,  1.0f,		 1.0f,  0.0f,  0.0f,
					1.0f,  1.0f, -1.0f,		 1.0f,  0.0f,  0.0f,
					1.0f, -1.0f,  1.0f,		 1.0f,  0.0f,  0.0f,
					1.0f, -1.0f, -1.0f,		 1.0f,  0.0f,  0.0f,
			};

			unsigned int cubeIndices[6 * 6] = {
				// front
				0, 2, 3,
				0, 3, 1,
				// back
				4, 6, 7,
				4, 7, 5,
				// top
				8, 10, 11,
				8, 11, 9,
				// bottom
				12, 14, 15,
				12, 15, 13,
				// left
				16, 18, 19,
				16, 19, 17,
				// right
				20, 22, 23,
				20, 23, 21
			};

			// gen vertex array
			m_VertexArray = GameEngine::VertexArray::Create();

			std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer = GameEngine::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));

			GameEngine::BufferLayout layout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
				{ GameEngine::ShaderDataType::Float3, "a_Normal"}
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			std::shared_ptr<GameEngine::IndexBuffer> indexBuffer = GameEngine::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}

		{
			// quad with normals
			float quadVertices[4 * 1 * (3 + 3)] = { // num vertices per side * num sides * (components of position + components of normal)
				// top side
				-1.0f,  0.0f,  1.0f,		 0.0f,  1.0f,  0.0f,
				 1.0f,  0.0f,  1.0f,		 0.0f,  1.0f,  0.0f,
				-1.0f,  0.0f, -1.0f,		 0.0f,  1.0f,  0.0f,
				 1.0f,  0.0f, -1.0f,		 0.0f,  1.0f,  0.0f
			};

			unsigned int quadIndices[1 * 6] = {
				// top
				0, 2, 3,
				0, 3, 1
			};

			// gen vertex array
			m_PlaneVertexArray = GameEngine::VertexArray::Create();

			std::shared_ptr<GameEngine::VertexBuffer> vertexBuffer = GameEngine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));

			GameEngine::BufferLayout layout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
				{ GameEngine::ShaderDataType::Float3, "a_Normal"}
			};
			vertexBuffer->SetLayout(layout);
			m_PlaneVertexArray->AddVertexBuffer(vertexBuffer);

			std::shared_ptr<GameEngine::IndexBuffer> indexBuffer = GameEngine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(unsigned int));
			m_PlaneVertexArray->SetIndexBuffer(indexBuffer);
		}

		m_Shader = GameEngine::Shader::Create("assets/shaders/BasicDiffuse.glsl");

		//m_Texture = GameEngine::Texture2D::Create("assets/textures/smile.png");
		//m_Shader->Bind();
		//m_Shader->SetInt("u_Texture", 0);

		m_Camera = std::make_shared<GameEngine::PerspectiveCamera>();
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 5.0f);
		m_CameraSmoothVector = glm::vec2(0);

		m_Transform = std::make_shared<GameEngine::Transform>();
		m_SquareScale = glm::vec3(1.0f);

		m_LightPos = glm::vec3(0.0f, 3.0f, 0.0f);
		
		m_PlaneTransform = std::make_shared<GameEngine::Transform>();
		m_PlaneTransform->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
		m_PlaneTransform->SetScale(glm::vec3(10));
	}

	virtual void OnAttach() override
	{
	}

	virtual void OnUpdate(GameEngine::Timestep ts) override
	{

		// camera controlled by the mouse
		glm::vec2 md = GameEngine::Input::GetMouseDelta();
		md *= m_CameraSensitivity * m_CameraSmoothing;
		m_CameraSmoothVector = glm::mix(m_CameraSmoothVector, md, 1.0f / m_CameraSmoothing);
		m_MouseLook += m_CameraSmoothVector;

		m_CameraRotation = glm::vec3(-glm::radians(m_MouseLook.y), -glm::radians(m_MouseLook.x), 0);


		m_SquareRotation += (float)ts * glm::vec3(1, 2, 3);


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
		// m_Texture->Bind();
		m_Shader->SetFloat3("u_LightPos", m_LightPos);
		GameEngine::Renderer::Submit(m_Shader, m_VertexArray, m_Transform);
		GameEngine::Renderer::Submit(m_Shader, m_PlaneVertexArray, m_PlaneTransform);


		// END RENDERING SCENE
		GameEngine::Renderer::EndScene();
	}

	virtual void OnEvent(GameEngine::Event& event)
	{
		GameEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(OnKey));
	}

	bool OnKey(GameEngine::KeyPressedEvent& KeyEvent)
	{
		return false;
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Camera Controls");
		ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_CameraPosition), -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(m_CameraRotation), -3.14f,3.14f);
		//ImGui::SliderFloat("Camera Sensitivity", &m_CameraSensitivity, 0.1f, 10.0f); 
		//ImGui::SliderFloat("Camera Smoothing", &m_CameraSmoothing, 0.1f, 10.0f);

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


		ImGui::Begin("Light Controls");
		ImGui::SliderFloat3("Light Position", glm::value_ptr(m_LightPos), -8.0f, 8.0f);

		if (ImGui::Button("Reset"))
		{
			m_LightPos = glm::vec3(0.0f, 3.0f, 0.0f);
		}

		ImGui::End();
	}

private:
	std::shared_ptr<GameEngine::VertexArray> m_VertexArray;
	std::shared_ptr<GameEngine::Shader> m_Shader;

	std::shared_ptr<GameEngine::VertexArray> m_PlaneVertexArray;

	std::shared_ptr<GameEngine::Texture2D> m_Texture;

	std::shared_ptr<GameEngine::PerspectiveCamera> m_Camera;
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraRotation;

	std::shared_ptr<GameEngine::Transform> m_Transform;
	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareRotation;
	glm::vec3 m_SquareScale;

	std::shared_ptr<GameEngine::Transform> m_PlaneTransform;

	glm::vec3 m_LightPos;

	float m_CameraSensitivity = 0.5f;
	float m_CameraSmoothing = 1;
	glm::vec2 m_CameraSmoothVector;
	glm::vec2 m_MouseLook;
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
