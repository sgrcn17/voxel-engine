#include "chunk.hpp"
#include "engine.hpp"

Chunk::Chunk(int x, int z, int data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]) : x(x), z(z) {
    std::cout << "Creating chunk at (" << x << ", " << z << ")" << std::endl;

    for(int i = 0; i < CHUNK_SIZE; i++) {
        for(int j = 0; j < CHUNK_HEIGHT; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                blockIds[i][j][k] = data[i][j][k];
            }
        }
    }

    vao = new VAO();
    vbo = new VBO();
    ebo = new EBO();

    vao->bind();
    vao->linkAttrib(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    vao->linkAttrib(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    vao->linkAttrib(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    std::cout << "Updating mesh..." << std::endl;
    UpdateMesh();
    std::cout << "Updating buffers..." << std::endl;
    UpdateBuffers();
    std::cout << "Chunk created successfully." << std::endl;
}

void Chunk::EmplaceBlockRenderData(int i, int j, int k, std::vector<GLfloat>& _vertices, std::vector<GLuint>& _indices) {
    auto addVertex = [&](GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat tex_x, GLfloat tex_y) {
        _vertices.emplace_back(x);
        _vertices.emplace_back(y);
        _vertices.emplace_back(z);
        _vertices.emplace_back(r);
        _vertices.emplace_back(g);
        _vertices.emplace_back(b);
        _vertices.emplace_back(tex_x);
        _vertices.emplace_back(tex_y);
    };

    auto addIndices = [&]() {
        _indices.emplace_back(vertices.size()/8 - 4);
        _indices.emplace_back(vertices.size()/8 - 3);
        _indices.emplace_back(vertices.size()/8 - 2);
        _indices.emplace_back(vertices.size()/8 - 2);
        _indices.emplace_back(vertices.size()/8 - 1);
        _indices.emplace_back(vertices.size()/8 - 4);
    };
    
    if(blockIds[i][j][k] == 0) return;

    try {
        Model model = (*Engine::GetBlockModels())[blockIds[i][j][k]];

        //left face
        if(i == 0 || blockIds[i - 1][j][k] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::WEST]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::WEST]].yPos;
            addVertex(x+i-0.5f, j-0.5f, z+k-0.5f, 1.0f, 0.0f, 0.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i-0.5f, j-0.5f, z+k+0.5f, 1.0f, 0.0f, 0.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i-0.5f, j+0.5f, z+k+0.5f, 1.0f, 0.0f, 0.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addVertex(x+i-0.5f, j+0.5f, z+k-0.5f, 1.0f, 0.0f, 0.0f, tex_x*0.03125f, tex_y*0.03125f);
            addIndices();
        }
        
        //right face
        if(i == CHUNK_SIZE - 1 || blockIds[i + 1][j][k] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::EAST]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::EAST]].yPos;
            addVertex(x+i+0.5f, j-0.5f, z+k-0.5f, 0.0f, 1.0f, 0.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j-0.5f, z+k+0.5f, 0.0f, 1.0f, 0.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k+0.5f, 0.0f, 1.0f, 0.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k-0.5f, 0.0f, 1.0f, 0.0f, tex_x*0.03125f, tex_y*0.03125f);
            addIndices();
        }

        //bottom face
        if(j == 0 || blockIds[i][j - 1][k] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::BOTTOM]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::BOTTOM]].yPos;
            addVertex(x+i-0.5f, j-0.5f, z+k-0.5f, 0.0f, 0.0f, 1.0f, tex_x*0.03125f, tex_y*0.03125f);
            addVertex(x+i+0.5f, j-0.5f, z+k-0.5f, 0.0f, 0.0f, 1.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j-0.5f, z+k+0.5f, 0.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i-0.5f, j-0.5f, z+k+0.5f, 0.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addIndices();
        }

        //top face
        if(j == CHUNK_HEIGHT - 1 || blockIds[i][j + 1][k] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::TOP]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::TOP]].yPos;
            addVertex(x+i-0.5f, j+0.5f, z+k-0.5f, 0.0f, 0.0f, 1.0f, tex_x*0.03125f, tex_y*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k-0.5f, 0.0f, 0.0f, 1.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k+0.5f, 0.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i-0.5f, j+0.5f, z+k+0.5f, 0.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addIndices();
        }

        //back face
        if(k == 0 || blockIds[i][j][k - 1] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::SOUTH]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::SOUTH]].yPos;
            addVertex(x+i-0.5f, j-0.5f, z+k-0.5f, 1.0f, 0.0f, 1.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j-0.5f, z+k-0.5f, 1.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k-0.5f, 1.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addVertex(x+i-0.5f, j+0.5f, z+k-0.5f, 1.0f, 0.0f, 1.0f, tex_x*0.03125f, tex_y*0.03125f);
            addIndices();
        }

        //front face
        if(k == CHUNK_SIZE - 1 || blockIds[i][j][k + 1] == 0) {
            GLfloat tex_x = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::NORTH]].xPos;
            GLfloat tex_y = (*Engine::GetTextureAtlas())[model.textureId[SETTINGS::NORTH]].yPos;
            addVertex(x+i-0.5f, j-0.5f, z+k+0.5f, 1.0f, 0.0f, 1.0f, tex_x*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j-0.5f, z+k+0.5f, 1.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, (tex_y+1)*0.03125f);
            addVertex(x+i+0.5f, j+0.5f, z+k+0.5f, 1.0f, 0.0f, 1.0f, (tex_x+1)*0.03125f, tex_y*0.03125f);
            addVertex(x+i-0.5f, j+0.5f, z+k+0.5f, 1.0f, 0.0f, 1.0f, tex_x*0.03125f, tex_y*0.03125f);
            addIndices();
        }
    } catch(...) {
        std::cout << "ERROR block at " << i << " " << j << " " << k << " not found" << std::endl;
    }
}

void Chunk::UpdateMesh() {
    vertices.clear();
    indices.clear();

    for(int i = 0; i < CHUNK_SIZE; i++) {
        for(int j = 0; j < CHUNK_HEIGHT; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                if(blockIds[i][j][k] == 0) continue;
                EmplaceBlockRenderData(i, j, k, vertices, indices);
            }
        }
    }

    //size_t totalSize = vertices.size() * sizeof(GLfloat) + indices.size() * sizeof(GLuint) + sizeof(blockIds);
    //std::cout << "Total size of chunk: " << totalSize << " bytes" << std::endl;

    UpdateBuffers();
}

void Chunk::UpdateBuffers() {
    vao->bind();
    vbo->bind();
    vbo->setData(vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    ebo->bind();
    ebo->setData(indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    vao->unbind();
}

void Chunk::AddBlock(int i, int j, int k, int id) {
    
}

void Chunk::RemoveBlock(int i, int j, int k) {
    
}

void Chunk::Render() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao->unbind();
}