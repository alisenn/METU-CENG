#ifndef __HW2__PARSER__
#define __HW2__PARSER__

#include <string>
#include <vector>

namespace parser
{
    //Notice that all the structures are as simple as possible
    //so that you are not enforced to adopt any style or design.
    struct Vec2f
    {
        float x, y;
    };

    struct Vec3f
    {
        float x, y, z;
    };

    struct Vec3i
    {
        int x, y, z;
    };

    struct Vec4f
    {
        float x, y, z, w;
    };

    struct Camera
    {
        Vec3f position;
        Vec3f gaze;
        Vec3f up;
        Vec4f near_plane;
        float near_distance;
        int image_width, image_height;
        std::string image_name;
    };

    struct PointLight
    {
        Vec3f position;
        Vec3f intensity;
    };

    struct Material
    {
        Vec3f ambient;
        Vec3f diffuse;
        Vec3f specular;
        Vec3f mirror;
        float phong_exponent;
    };

    struct Face
    {
        int v0_id;
        int v1_id;
        int v2_id;
    };

    struct Mesh
    {
        int texture_id;
        int material_id;
        std::vector<Face> faces;
        std::string transformations;
    };

    struct Triangle
    {
        int texture_id;
        int material_id;
        Face indices;
        std::string transformations;
    };

    struct Sphere
    {
        int texture_id;
        int material_id;
        int center_vertex_id;
        float radius;
        std::string transformations;
    };

    struct Rotation
    {
        float angle, x, y, z;
    };

    struct Texture
    {
        std::string imageName;
        std::string interpolation;
        std::string decalMode;
        std::string appearance;
    };

    struct Scene
    {
        //Data
        Vec3i background_color;
        float shadow_ray_epsilon;
        int max_recursion_depth;
        std::vector<Camera> cameras;
        Vec3f ambient_light;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<Vec3f> vertex_data;
        std::vector<Vec2f> tex_coord_data;
        std::vector<Mesh> meshes;
        std::vector<Triangle> triangles;
        std::vector<Sphere> spheres;
        std::vector<Vec3f> translations;
        std::vector<Vec3f> scalings;
        std::vector<Rotation> rotations;
        std::vector<Texture> textures;

        //Functions
        void loadFromXml(const std::string& filepath);
    };
}

#endif