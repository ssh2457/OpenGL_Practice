#include "Model.h"

Model::~Model() {
	ClearModel();
}


void Model::LoadModel(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene) {
		printf("Model (%s) failed to load: %s\n", fileName.c_str(), importer.GetErrorString());
		return;
	}

	LoadMode(scene->mRootNode, scene);
	LoadMaterials(scene);
}

void Model::RenderModel() {
	for (size_t i = 0; i < MeshList.size(); ++i) {
		unsigned int materialIdx = MeshToTex[i];

		if (materialIdx < TextureList.size() && TextureList[materialIdx]) {
			TextureList[materialIdx]->UseTexture();
		}

		MeshList[i]->RenderMesh();
	}
}

void Model::ClearModel() {
	for (size_t i = 0; i < MeshList.size(); ++i) {
		if (MeshList[i]) {
			delete MeshList[i];
			MeshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < TextureList.size(); ++i) {
		if (TextureList[i]) {
			delete TextureList[i];
			TextureList[i] = nullptr;
		}
	}
}

void Model::LoadMode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; ++i) {
		LoadMode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<GLfloat> vertices;
	vertices.reserve(8 * mesh->mNumVertices);

	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {

		// Input vertex position(x, y, z)
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		// Input texture position(UV position)
		if (mesh->mTextureCoords[0]) {
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}
		else {
			vertices.push_back(0);
			vertices.push_back(0);
		}

		// Input normal vector (nx, ny, nz)
		vertices.push_back(-mesh->mNormals[i].x);
		vertices.push_back(-mesh->mNormals[i].y);
		vertices.push_back(-mesh->mNormals[i].z);
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	MeshList.push_back(newMesh);
	MeshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene* scene) {
	TextureList.resize(scene->mNumMaterials);
	for (size_t i = 0; i < scene->mNumMaterials; ++i) {

		aiMaterial* material = scene->mMaterials[i];
		TextureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				int idx = std::string(path.data).rfind("\\");
				std::string fileName = std::string(path.data).substr(idx + 1);
				std::string texPath = std::string("../../Textures/") + fileName;

				TextureList[i] = new Texture(texPath.c_str());

				if (!TextureList[i]->LoadTexture()) {
					printf("Failed to load texture at %s\n", texPath.c_str());
					delete TextureList[i];
					TextureList[i] = nullptr;
				}
			}

		}

		if (!TextureList[i]) {
			TextureList[i] = new Texture("../../Textures/plain.png");
			TextureList[i]->LoadTextureA();
		}
	}


}
