#pragma once
#ifndef FINITY_GUI_MESHIMPORTER_H
#define FINITY_GUI_MESHIMPORTER_H

#include <fstream>
#include <string>
#include "graphics/util/strUtil.h"

class MeshImporter {
    virtual bool fromFile(const std::string &filepath, Mesh* pMesh) = 0;

public:
    enum MeshImportFlags {
        PROCESS_CALC_TANGENT_SPACE = 0,
        PROCESS_TRIANGULATE,
        PROCESS_SORTBYTYPE,
        PROCESS_GEN_NORMALS,
        PROCESS_GEN_UVCOORDS,
        PROCESS_OPTIMIZE_MESHES,
        PROCESS_VALIDATE_DATA_STRUCT
    };
};

#endif //FINITY_GUI_MESHIMPORTER_H
