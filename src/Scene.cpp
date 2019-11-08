#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 1, 1), "/Users/edwinagbakpe/eyden-tracer-04/data/cb.bmp");
		std::vector<Vec3f> vVertexes;
		std::vector<Vec3f> vnVertices;
		std::vector<Vec2f> vtVertices;
		std::string line;

		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertexes.emplace_back(v);
			}
			else if (line == "f") {
				Vec3i f;
                Vec3i n;
				Vec3i t;
                std::string s;
                for (int i = 0; i < 3; i++) {
                    ss >> s;
                    std::replace(s.begin(), s.end(), '/', ' ');
                    std::stringstream iss(s);
                    iss >> f.val[i];
                    iss >> t.val[i];
                    iss >> n.val[i];
                }
				Add(std::make_shared<CPrimTriangleSmoothTextured>
                    (vVertexes[f.val[0] - 1], vVertexes[f.val[1] - 1], vVertexes[f.val[2] - 1],
                     vnVertices[n.val[0] - 1],vnVertices[n.val[1] - 1], vnVertices[n.val[2] - 1],
					 vtVertices[t.val[0] - 1], vtVertices[t.val[1] - 1], vtVertices[t.val[2 - 1]],
                     pShader));
			}
			else if ( line == "vn"){
				Vec3f vn;
				for (int i = 0; i < 3; i++) ss >> vn.val[i];
				//std::cout<< "Normal: "<<vn<<std::endl;
				vnVertices.emplace_back(vn);
			}
			else if (line == "vt"){
				Vec2f vt;
				for (int i = 0; i < 2; i++) ss >> vt.val[i];
				//std::cout<< "Normal: "<<vn<<std::endl;
				vtVertices.emplace_back(vt);
			}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
