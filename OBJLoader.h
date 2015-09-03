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
					const std::string& filename, PTriangles& triangles, bool calcNorms = false) {
					std::ifstream file(filename);
					if (!file) return false;

					std::vector<std::string> face_str;

					std::vector<Vec4> positions;
					std::vector<Vec4> normals;
					std::vector<Vec4> tangents;
					std::vector<Vec4> colors;
					std::vector<Vec2> uvs;

					// For each line in file...
					for (std::string line; std::getline(file, line);) {
						// Create an input stream for the line
						std::istringstream line_stream(line);

						// String to hold the prefix
						std::string prefix;
						// Get the prefix...
						line_stream >> prefix;

						/** 
						 * Now we check through all the different 
						 * prefixes and act accordingly.
						 */

						float x, y, z, w;

						if (prefix == "v") {
							if (line_stream >> x >> y >> z >> w)
								positions.push_back(Vec4(x, y, z, w));
							else {
								line_stream >> x >> y >> z;
								positions.push_back(Vec4(x, y, z, 1.0f));
							}
						} else if (prefix == "vn") {
							if (line_stream >> x >> y >> z >> w)
								normals.push_back(Vec4(x, y, z, w));
							else {
								line_stream >> x >> y >> z;
								normals.push_back(Vec4(x, y, z, 1.0f));
							}
						} else if (prefix == "vt") {
							line_stream >> x >> y;
							uvs.push_back(Vec2(x, y));
						}
						else if (prefix == "f") {
							// Push the face line to a vector
							face_str.push_back(line_stream.str()); 
						}

						// Get smoothing info etc..?
					}

					// Construct regular expressions to check against
					std::regex v("^f\\s(\\d+\\s?){3}");				// f v ..x3
					std::regex vt("^f\\s(\\d+/\\d+\\s?){3}");		// f v/vt ..x3
					std::regex vtn("^f\\s((\\d+/){2}\\d+\\s?){3}"); // f v/vt/vn ..x3
					std::regex vn("^f\\s(\\d+/{2}\\d+\\s?){3}");	// f v//vn ..x3

					// Now go through the vector of face strings and construct the faces
					for (auto s : face_str) {
						// Indices for the vertices, normals and UV's
						int vi1, vi2, vi3,
							ni1, ni2, ni3,
							ti1, ti2, ti3;

						// Get a copy of the string and replace the '/' with spaces
						std::string _s = s;
						std::replace_if(_s.begin(), _s.end(),
							[](const char& c)-> bool { return c == '/'; }, ' ');

						// Get our modified string as a stream
						std::istringstream face_stream(_s);
						std::string f;

						Vertex tri[3];
						Triangle triangle;

						// Check against all the regular expresssions
						if (std::regex_match(s, v)) {
							if (face_stream >> f >> vi1 >> vi2 >> vi3) {
								tri[0].position = positions[vi1 - 1];
								tri[1].position = positions[vi2 - 1];
								tri[2].position = positions[vi3 - 1];

								for (unsigned i = 0; i < 3; ++i) {
									tri[i].tangent = Vec4();
									tri[i].color = V_COL;
									tri[i].uv = Vec2();

									triangle[i] = tri[i];
								}
								
								if (calcNorms)
									calculateFaceNormal(triangle);

								triangles.push_back(Triangle_sptr(&triangle));
							}
						} else if (std::regex_match(s, vt)) {
							if (face_stream >> f >> vi1 >> ti1 >> vi2 >> ti2 >> vi3 >> ti3) {
								tri[0].position = positions[vi1 - 1];
								tri[1].position = positions[vi2 - 1];
								tri[2].position = positions[vi3 - 1];
								tri[0].uv = uvs[ti1 - 1];
								tri[1].uv = uvs[ti2 - 1];
								tri[2].uv = uvs[ti3 - 1];

								for (unsigned i = 0; i < 3; ++i) {
									tri[i].color = V_COL;

									triangle[i] = tri[i];
								}

								if (calcNorms)
									calculateFaceNormal(triangle);

								calculateTangent(triangle);
								triangles.push_back(Triangle_sptr(&triangle));
							}
						} else if (std::regex_match(s, vtn)) {
							if (face_stream >> f >> vi1 >> ti1 >> ni1 >>
								vi2 >> ti2 >> ni2 >> vi3 >> ti3 >> ni3) {
								tri[0].position = positions[vi1 - 1];
								tri[1].position = positions[vi2 - 1];
								tri[2].position = positions[vi3 - 1];
								tri[0].normal = normals[ni1 - 1];
								tri[1].normal = normals[ni2 - 1];
								tri[2].normal = normals[ni3 - 1];
								tri[0].uv = uvs[ti1 - 1];
								tri[1].uv = uvs[ti2 - 1];
								tri[2].uv = uvs[ti3 - 1];

								for (unsigned i = 0; i < 3; ++i) {
									tri[i].color = V_COL;

									triangle[i] = tri[i];
								}

								calculateTangent(triangle);
								triangles.push_back(Triangle_sptr(&triangle));
							}
						} else if (std::regex_match(s, vn)) {
							if (face_stream >> f >> vi1 >> ni1 >> vi2 >> ni2 >> vi3 >> ni3) {
								tri[0].position = positions[vi1 - 1];
								tri[1].position = positions[vi2 - 1];
								tri[2].position = positions[vi3 - 1];
								tri[0].normal = normals[ni1 - 1];
								tri[1].normal = normals[ni2 - 1];
								tri[2].normal = normals[ni3 - 1];

								for (unsigned i = 0; i < 3; ++i) {
									tri[i].tangent = Vec4();
									tri[i].color = V_COL;
									tri[i].uv = Vec2();

									triangle[i] = tri[i];
								}

								triangles.push_back(Triangle_sptr(&triangle));
							}
						}
					}

					return true;
				}

				inline static void calculateTangent(Triangle& triangle) {
					// Calculate position & uv deltas
					Vec4 dv1 = triangle[1].position - triangle[0].position;
					Vec4 dv2 = triangle[2].position - triangle[0].position;
					Vec2 du1 = triangle[1].uv - triangle[0].uv;
					Vec2 du2 = triangle[2].uv - triangle[0].uv;

					// Calulate the tangent
					float t = 1.0f / (du1.x * du2.y - du1.y * du2.x);
					Vec4 tangent = (dv1 * du2.y - dv2 * du1.y) * t;

					// Apply the tangent to each of the triangle's points
					for (unsigned i = 0; i < 3; ++i)
						triangle[i].tangent = tangent;
				}

				// Use face normals for a flat shaded mesh
				inline static void calculateFaceNormal(Triangle& triangle) {
					// Get two edges of the triangle
					Vec4 U = triangle[1].position - triangle[0].position;
					Vec4 V = triangle[2].position - triangle[0].position;

					// Convert the edges to Vector 3
					Vec3 u3 = Vec3(U.x, U.y, U.z);
					Vec3 v3 = Vec3(V.x, V.y, V.z);

					// Calculate the normal (cross product of the two edges)
					Vec3 N = glm::cross(u3, v3);

					// Apply the normal to each of the triangle's points
					for (unsigned i = 0; i < 3; ++i)
						triangle[i].normal = Vec4(N, 1.0f);
				}
		};
	}
}

#pragma endregion

#endif /* !__OBJ_LOADER_H__ */

// END OF FILE