#pragma once

#include "VertexArray.h"

namespace GameEngine {

	class Mesh
	{
	/*
		A mesh is basically an abstraction that allows us to pass in
		geometry, without having to specifically create vertex arrays
		and index buffers to hold that geometry.
	*/

	public:
		/*
			The mesh needs to know:
				- the layout of the vertex attributes
				- the vertex data
				- the index data
		*/
		Mesh(const BufferLayout& layout, float* vertexData, unsigned int vertexDataSize, unsigned int* indexData, unsigned int indexCount)
		{
			// gen vertex array
			m_VertexArray = VertexArray::Create();

			std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertexData, vertexDataSize);

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indexData, indexCount);
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}
		virtual ~Mesh() {}

		inline const std::shared_ptr<VertexArray>& GetVerterxArray() { return m_VertexArray; }

	private:
		// all information required by the renderer is stored inside the vertex array
		std::shared_ptr<VertexArray> m_VertexArray;
	};

}
