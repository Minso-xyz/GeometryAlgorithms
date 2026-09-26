# Geometry Algorithms
An interactive C++ and OpenGL playground for implementing fundamental
computational geometry and mesh processing algorithms from scratch.
 
The project explores geometry operations commonly encountered in
CAD, geometry processing, and computational geometry systems.
 
## Current Features

### Mesh Processing
- OBJ Loader
- Triangle Mesh Rendering
- Orbit Camera
- Bounding Box Fitting
- Stanford Bunny Rendering
- Face Normal Visualization
- Vertex Normal Visualization

### Computational Geometry
- 2D Polygon Representation
- Polygon Rendering
- Polygon View Fitting
- Polygon Area (Shoelace Formula)
- Polygon Orientation (CW/CCW)
- Point-in-Polygon Test (Ray Casting)
- 2D Cross Product and Orientation Test
- Line Segment Intersection Test
- Line Segment Intersection Point Calculation

 
## OBJ Mesh Rendering
The Stanford Bunny (Vertices: 35947, Faces: 69451)
| Source Mesh | Geometry Algorithms |
|------------|------------|
| ![GeometryAlgorithms](Bunny.png)  | ![GeometryAlgorithms](Bunny_Wireframe.png) |

 
## Face Normals vs Vertex Normals
| Face Normals | Vertex Normals |
|------------|------------|
| ![GeometryAlgorithms](FaceNormals.png)  | ![GeometryAlgorithms](VertexNormals.png) |

 
## Roadmap
### Computational Geometry
- [x] Polygon Rendering
- [x] Polygon Area Calculation
- [x] Point In Polygon (PIP)
- [x] Line Segment Intersection
- [x] Line Segment Intersection Point Calculation
- [ ] Convex Polygon Clipping (Sutherland-Hodgman)
- [ ] Polygon Triangulation
- [ ] Polygon Boolean Operations
- [ ] Polygon Offset
- [ ] SVG Export
 
### Mesh Processing
- [x] OBJ Loader
- [x] Wireframe Mesh Rendering
- [x] Face Normal Visualization
- [x] Vertex Normal Visualization
- [ ] Half-Edge Data Structure
- [ ] Laplacian Smoothing
- [ ] Mesh Simplification
- [ ] Subdivision
- [ ] Curvature Visualization
 
### Research
- [ ] Geometry Processing Pipeline
- [ ] Gaussian Splatting Experiments
