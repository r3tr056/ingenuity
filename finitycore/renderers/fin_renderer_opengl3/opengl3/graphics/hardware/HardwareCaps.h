#pragma once

#ifndef FINITY_GL_RENDERER_HARDWARECAPS_H
#define FINITY_GL_RENDERER_HARDWARECAPS_H

#include <ostream>

struct HardwareCaps {
	float MaxAnisotropy;
	int MaxArrayTextureLayers;
	int MaxTextureSamples;
	int MaxTextureSamplers;
	int MaxVertexUniformBlocks;
	int MaxGeometryUniformBlocks;
	int MaxFragmentUniformBlocks;
	int MaxComputeWorkGroupSize;
	int MaxComputeWorkGroupCount;
	int TotalVideoMemoryKB;
};

inline std::ostream& operator<<(std::ostream& out, const HardwareCaps& c) {
	return out << c.TotalVideoMemoryKB;
}

#endif