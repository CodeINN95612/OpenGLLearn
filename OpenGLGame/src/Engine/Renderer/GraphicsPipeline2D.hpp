#pragma once

#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/BufferLayout.hpp"
#include "Engine/Renderer/Texture2D.hpp"

namespace GL
{
	class GraphicsPipeline2D
	{
	public:
		GraphicsPipeline2D(std::shared_ptr<BufferLayout> layout, std::shared_ptr<Shader> shader);
		virtual ~GraphicsPipeline2D() = default;

		GraphicsPipeline2D(const GraphicsPipeline2D& other) = delete;
		GraphicsPipeline2D& operator==(const GraphicsPipeline2D& other) = delete;

		inline void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; };

		inline const std::shared_ptr<BufferLayout>& GetLayout() const { return m_Layout; }
		inline const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }
		inline const std::shared_ptr<Texture2D>& GetTexture() const { return m_Texture; }
		
		void Bind();
		void Bind(uint32_t textureUnit);
	private:
		std::shared_ptr<BufferLayout> m_Layout;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
