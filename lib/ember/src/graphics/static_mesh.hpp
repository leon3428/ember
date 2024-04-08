#ifndef STATIC_MESH_HPP
#define STATIC_MESH_HPP

#include "base_mesh.hpp"

namespace ember {

    class StaticMesh : public BaseMesh {
        public:

            template<Vertex T> 
            StaticMesh(std::span<T> vertices, std::span<uint32_t> indices)
                : BaseMesh(vertices, indices, GL_STATIC_DRAW)
            {}

            // TODO: remove this
            inline auto bind() const {
                glBindVertexArray(m_VAO);
            }

            // TODO: remove this
            inline auto unbind() const {
                glBindVertexArray(0);
            }

        private:
    };
    
}

#endif // STATIC_MESH_HPP