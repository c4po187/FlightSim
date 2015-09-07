/**
 * OBJLoader.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#pragma once

#pragma region Prerequisites

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include "Triangle.h"

using namespace EUMD_FlightSimulator::Core::Graphics;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Utilities {
		
		#define V_COL Vec4(.7f, .7f, .7f, 1.0f)

		class OBJLoader {

			public:

				/* Functions */

				inline static bool loadOBJtoMesh(
					const std::string& filename, Vertices& vertices, bool calcNorms = false) {
					// Get the file
					std::ifstream file(filename);
					if (!file) return false;

					// Vector to hold the face strings
					std::vector<std::string> face_str;

					//  Vectors for the Vertex attributes
					std::vector<Vec4> positions;
					std::vector<Vec4> normals;
					std::vector<Vec4> tangents;
					std::vector<Vec4> colors;
					std::vector<Vec2> uvs;

					// Read each line in the file & act accordingly
					for (std::string line; std::getline(file, line);) {
						std::istringstream line_stream(line);

						// Dump the prefix
						std::string prefix;
						line_stream >> prefix;

						float x, y, z, w;

						// Check the prefix and fill the attribute vectors 
						if (prefix == "v") {
							if (line_stream >> x >> y >> z)
								positions.push_back(Vec4(x, y, z, 1.0f));
						} else if (prefix == "vn") {
							if (line_stream >> x >> y >> z)
								normals.push_back(Vec4(x, y, z, .0f));
						} else if (prefix == "vt") {
							if (line_stream >> x >> y)
								uvs.push_back(Vec2(x, y));
						} else if (prefix == "f") {
							face_str.push_back(line_stream.str());
						}
					}

					// Construct regular expressions to check the face strings against
					std::regex v("^f\\s(\\d+\\s?){3}");				// f v ..x3
					std::regex vt("^f\\s(\\d+/\\d+\\s?){3}");		// f v/vt ..x3
					std::regex vtn("^f\\s((\\d+/){2}\\d+\\s?){3}"); // f v/vt/vn ..x3
					std::regex vn("^f\\s(\\d+/{2}\\d+\\s?){3}");	// f v//vn ..x3

					// Create the vertices from the face strings & stored attributes
					for (auto s : face_str) {
						int v1, v2, v3, n1, n2, n3, u1, u2, u3;

						// Replace all '/' characters with spaces
						std::string _s = s, f;
						std::replace_if(_s.begin(), _s.end(),
							[](const char& c)-> bool { return c == '/'; }, ' ');

						std::istringstream face_stream(_s);

						Vertex p1, p2, p3;

						// Match up the regular expressions
						if (std::regex_match(s, v)) {
							if (face_stream >> f >> v1 >> v2 >> v3) {
								p1.position = positions[v1 - 1];
								p2.position = positions[v2 - 1];
								p3.position = positions[v3 - 1];
							}
						}
						else if (std::regex_match(s, vt)) {
							if (face_stream >> f >> v1 >> u1 >> v2 >> u2 >> v3 >> u3) {
								p1.position = positions[v1 - 1];
								p2.position = positions[v2 - 1];
								p3.position = positions[v3 - 1];

								p1.uv = uvs[u1 - 1];
								p2.uv = uvs[u2 - 1];
								p3.uv = uvs[u3 - 1];
							}
						} else if (std::regex_match(s, vtn)) {
							if (face_stream >> f >> v1 >> u1 >> n1 >> v2 >> u2 >> n2 >> v3 >> u3 >> n3) {
								p1.position = positions[v1 - 1];
								p2.position = positions[v2 - 1];
								p3.position = positions[v3 - 1];

								p1.uv = uvs[u1 - 1];
								p2.uv = uvs[u2 - 1];
								p3.uv = uvs[u3 - 1];

								p1.normal = normals[n1 - 1];
								p2.normal = normals[n2 - 1];
								p3.normal = normals[n3 - 1];

								calculateTangent(p1, p2, p3);
							}
						} else if (std::regex_match(s, vn)) {
							if (face_stream >> f >> v1 >> n1 >> v2 >> n2 >> v3 >> n3) {
								p1.position = positions[v1 - 1];
								p2.position = positions[v2 - 1];
								p3.position = positions[v3 - 1];

								p1.normal = normals[n1 - 1];
								p2.normal = normals[n2 - 1];
								p3.normal = normals[n3 - 1];
							}
						}

						// Singular colour for now
						p1.color = V_COL;
						p2.color = V_COL;
						p3.color = V_COL;

						// Push the Vertices onto the vector
						vertices.push_back(p1);
						vertices.push_back(p2);
						vertices.push_back(p3);
					}

					return true;
				}

				inline static void calculateTangent(Vertex& p1, Vertex& p2, Vertex& p3) {
					// Calculate deltas
					Vec4 dv1 = p2.position - p1.position;
					Vec4 dv2 = p3.position - p1.position;
					Vec2 du1 = p2.uv - p1.uv;
					Vec2 du2 = p3.uv - p1.uv;

					// Calculate the tangent
					float t = 1.0f / (du1.x * du2.y - du1.y * du2.x);
					Vec4 tangent = (dv1 * du2.y - dv2 * du1.y) * t;

					// Apply the tangent to each of the vertices
					p1.tangent = tangent;
					p2.tangent = tangent;
					p3.tangent = tangent;
				}
		};
	}
}

#pragma endregion

#endif /* !__OBJ_LOADER_H__ */

// END OF FILE