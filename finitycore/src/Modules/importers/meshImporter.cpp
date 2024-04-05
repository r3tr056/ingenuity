
#include <vector>
#include "graphics/components/Mesh.h"
#include "meshImporter.h"
#include <glm/glm.hpp>
#include <sstream>


bool MeshImporter::fromFile(const std::string &filepath, Mesh *pMesh) {
    std::ifstream in(filepath, std::ios::in);
    if (!in)
        return false;
    std::vector<glm::vec3> t_vert;
    std::string s_line;

    while (std::getline(in, s_line)) {
        std::istringstream ss_line(s_line);
        std::string id;
        ss_line >> id;

        // when the line contains vertices
        if (id=="v") {
            // Create a vector to store vertex
            glm::vec3 v;
            // Read the vertex
            ss_line >> v.x >> v.y >> v.z;
            // Add to temporary vertices before indexing
            t_vert.push_back(v);
        }

        // When the line contains faces
        else if (id=="f") {
            std::string v1, v2, v3;
            ss_line >> v1 >> v2 >> v3;

            GLuint vert_idx[3];
            vert_idx[0] = tokenize(v1, '/').at(0);
            vert_idx[1] = tokenize(v2, '/').at(0);
            vert_idx[2] = tokenize(v3, '/').at(0);

            pMesh->addVertexIndex(vert_idx[0]-1);
            pMesh->addVertexIndex(vert_idx[1]-1);
            pMesh->addVertexIndex(vert_idx[2]-1);
        }
    }

    for (auto v_idx : pMesh->getVertexIndices()) {
        glm::vec3 vert = t_vert[v_idx];
    }

    return true;
}