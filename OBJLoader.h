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
		
		class OBJLoader {

			public:

				/* Functions */

				inline static bool loadOBJtoMesh(const std::string& filename,
												 PTriangles& triangles) {
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
					std::regex vt("^f\\s(\d+/\\d+\\s?){3}");		// f v/vt ..x3
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

						// Check against all the regular expresssions
						if (std::regex_match(s, v)) {
							if (face_stream >> f >> vi1 >> vi2 >> vi3) {
								triangles.push_back(Triangle_sptr(
									new Triangle {
										Vertex {
											positions[vi1 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											Vec2()
										},
										Vertex {
											positions[vi2 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											Vec2()
										},
										Vertex {
											positions[vi3 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											Vec2()
										}
									})
								);
							}
						} else if (std::regex_match(s, vt)) {
							if (face_stream >> f >> vi1 >> ti1 >> vi2 >> ti2 >> vi3 >> ti3) {
								triangles.push_back(Triangle_sptr(
									new Triangle {
										Vertex {
											positions[vi1 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											uvs[ti1 - 1]
										},
										Vertex {
											positions[vi2 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											uvs[ti2 - 1]
										},
										Vertex {
											positions[vi3 - 1],
											Vec4(),
											Vec4(),
											Vec4(),
											uvs[ti3 - 1]
										}
									})
								);
							}
						} else if (std::regex_match(s, vtn)) {
							if (face_stream >> f >> vi1 >> ti1 >> ni1 >>
								vi2 >> ti2 >> ni2 >> vi3 >> ti3 >> ni3) {
								triangles.push_back(Triangle_sptr(
									new Triangle {
										Vertex {
											positions[vi1 - 1],
											normals[ni1 - 1],
											Vec4(),
											Vec4(),
											uvs[ti1 - 1]
										},
										Vertex {
											positions[vi2 - 1],
											normals[ni2 - 1],
											Vec4(),
											Vec4(),
											uvs[ti2 - 1]
										},
										Vertex {
											positions[vi3 - 1],
											normals[ni3 - 1],
											Vec4(),
											Vec4(),
											uvs[ti3 - 1]
										}
									})
								);

								// Get current index
								unsigned int i = (triangles.size() - 1);

								// Calculate position and UV deltas
								Vec4 dv1 = triangles[i]->p1.position - triangles[i]->p0.position;
								Vec4 dv2 = triangles[i]->p2.position - triangles[i]->p0.position;
								Vec2 du1 = triangles[i]->p1.uv - triangles[i]->p0.uv;
								Vec2 du2 = triangles[i]->p2.uv - triangles[i]->p0.uv;

								// Calculate the tangent
								float t = 1.0f / (du1.x * du2.y - du1.y * du2.x);
								Vec4 tangent = (dv1 * du2.y - dv2 * du1.y) * t;

								// Apply the tangent to each point on the triangle
								triangles[i]->p0.tangent = tangent;
								triangles[i]->p1.tangent = tangent;
								triangles[i]->p2.tangent = tangent;
							}
						} else if (std::regex_match(s, vn)) {
							if (face_stream >> f >> vi1 >> ni1 >> vi2 >> ni2 >> vi3 >> ni3) {
								triangles.push_back(Triangle_sptr(
									new Triangle {
										Vertex {
											positions[vi1 - 1],
											normals[ni1 - 1],
											Vec4(),
											Vec4(),
											Vec2()
										},
										Vertex {
											positions[vi2 - 1],
											normals[ni2 - 1],
											Vec4(),
											Vec4(),
											Vec2()
										},
										Vertex {
											positions[vi3 - 1],
											normals[ni3 - 1],
											Vec4(),
											Vec4(),
											Vec2()
										}
									})
								);
							}
						}
					}

					return true;
				}
		};
	}
}

#pragma endregion

#endif /* !__OBJ_LOADER_H__ */

// END OF FILE