#include <Resource/LoadModel.h>

#include <FC/Map.h>

#include <cstring>

struct PackedVertexInfo {
    Vec3 vert;
    Vec2 uv;
    Vec3 normal;
    
    bool operator<(const PackedVertexInfo that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertexInfo))>0;
	};
};

Mesh* LoadOBJ(const String& path) {
    std::vector<u32> vertex_indices, uv_indices, normal_indices;

    std::vector<Vec3> tmp_vert;
    std::vector<Vec2> tmp_uv;
    std::vector<Vec3> tmp_norm;
    
    FILE* fp = fopen(path.c_str(), "r");
    if (!fp)
		throw RuntimeException("Failed to open '" + path + "'");
    
    Mesh* model = new Mesh();
    
    while (true) {
        static char line_header[128];

        int res = fscanf(fp, "%s", line_header);

        if (res == EOF)
            break;

        if (!strcmp(line_header, "v")) {
            Vec3 vertex;
            fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmp_vert.push_back(vertex);
        }
        else if (!strcmp(line_header, "vt")) {
            Vec2 uv;
            fscanf(fp, "%f %f\n", &uv.x, &uv.y);
            tmp_uv.push_back(uv);
        }
        else if (!strcmp(line_header, "vn")) {
            Vec3 normal;
            fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tmp_norm.push_back(normal);
        }
        else if (!strcmp(line_header, "f")) {
            u32 vert_index[3], uv_index[3], norm_index[3];
            int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vert_index[0], &uv_index[0], &norm_index[0],
                                 &vert_index[1], &uv_index[1], &norm_index[1],
                                 &vert_index[2], &uv_index[2], &norm_index[2]);

            if (matches != 9)
                throw RuntimeException("Failed to parse '" + path + "'");

            vertex_indices.push_back(vert_index[0] - 1);
            vertex_indices.push_back(vert_index[1] - 1);
            vertex_indices.push_back(vert_index[2] - 1);
            uv_indices.push_back(uv_index[0] - 1);
            uv_indices.push_back(uv_index[1] - 1);
            uv_indices.push_back(uv_index[2] - 1);
            normal_indices.push_back(norm_index[0] - 1);
            normal_indices.push_back(norm_index[1] - 1);
            normal_indices.push_back(norm_index[2] - 1);
        }
//        else
//			throw RuntimeException("Unknown or unsupported entry '" + String(line_header) + "'");
    }
    
    {
        std::map<PackedVertexInfo, u32> vbo;
        
        int len = vertex_indices.size();
        for (int i = 0; i < len; i++) {
            PackedVertexInfo vertexInfo = { tmp_vert[vertex_indices[i]], tmp_uv[uv_indices[i]], tmp_norm[normal_indices[i]] };
            
            auto it = vbo.find(vertexInfo);
            
            if (it != vbo.end())
                model->elements.push_back(it->second);
            else {
                int newIndex = model->vertices.size();
                model->elements.push_back(newIndex);
                
                model->vertices.push_back(vertexInfo.vert);
                model->uvs.push_back(vertexInfo.uv);
                model->normals.push_back(vertexInfo.normal);
                
                vbo[vertexInfo] = newIndex;
            }
        }
    }
    
    fclose(fp);
    return model;
}
