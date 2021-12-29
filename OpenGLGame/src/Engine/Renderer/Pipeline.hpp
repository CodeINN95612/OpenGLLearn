#pragma once

#include "Engine/Shader.hpp"
#include "Engine/BufferLayout.hpp"

namespace GL
{
	class Pipeline
	{
	public:
		Pipeline(std::shared_ptr<BufferLayout> layout, std::shared_ptr<Shader> shader);
		virtual ~Pipeline() = default;

		Pipeline(const Pipeline& other) = delete;
		Pipeline& operator==(const Pipeline& other) = delete;

		const std::shared_ptr<BufferLayout>& GetLayout() const { return m_Layout; }
		const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }
		
		void Bind();
	private:
		std::shared_ptr<BufferLayout> m_Layout;
		std::shared_ptr<Shader> m_Shader;
	};
}
