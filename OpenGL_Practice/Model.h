#pragma once

#include "Mesh.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

class Model {
public:
	Model() = default;
	virtual ~Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();

private:
	void LoadMode(aiNode* node, const aiScene* scene);
	void LoadMesh(aiMesh* mesh, const aiScene* scene);
	void LoadMaterials(const aiScene* scene);

	std::vector<Mesh*> MeshList;
	std::vector<Texture*> TextureList;
	std::vector<unsigned int> MeshToTex;
};
