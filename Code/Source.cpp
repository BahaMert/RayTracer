#include "camera.h"
#include "rtweekend.h"
#include "aarect.h"
#include "material.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include "aarect.h"
#include "box.h"
#include <iostream>
#include <fstream>

using namespace std;


color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

hittable_list simple_light() {
    hittable_list objects;


    //.\RayTracerNew.exe>image.ppm

    auto difflight = make_shared<diffuse_light>(color(4, 4, 4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
    objects.add(make_shared<sphere>(point3(0,2,2), 0.5, difflight));
    //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

    auto materialAir = make_shared<dielectric>(1.0);
    auto materialWater = make_shared<dielectric>(1.4);
    auto materialDiamond = make_shared<dielectric>(2.4);
    auto materialHarderThanDiamond = make_shared<dielectric>(5.8);

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

    objects.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));
    objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    objects.add(make_shared<sphere>(point3(0.0, -1000, 0), 1000, material_reflectiveMetal3));
    objects.add(make_shared<sphere>(point3(1, 2, -1.0), 0.5, material_opaque));
    objects.add(make_shared<sphere>(point3(0, 2, -1), 0.5, material_reflectiveMetal));
    objects.add(make_shared<sphere>(point3(-1.0, 2, -1), 0.5, materialWater));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));



    return objects;
}

hittable_list myScene1(){
    hittable_list objects;


    //.\RayTracerNew.exe>image.ppm

    auto difflightGreen = make_shared<diffuse_light>(color(0, 7, 0));
    auto difflightBlue = make_shared<diffuse_light>(color(0, 0, 7));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflightGreen));
    objects.add(make_shared<sphere>(point3(0, 2, 2), 0.5, difflightBlue));
    //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

    auto materialAir = make_shared<dielectric>(1.0);
    auto materialWater = make_shared<dielectric>(1.4);
    auto materialDiamond = make_shared<dielectric>(2.4);
    auto materialHarderThanDiamond = make_shared<dielectric>(5.8);

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

    objects.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));
    //objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    objects.add(make_shared<sphere>(point3(0.0, -1000, 0), 1000, material_reflectiveMetal3));
    objects.add(make_shared<sphere>(point3(1, 2, -1.0), 0.5, material_opaque));
    objects.add(make_shared<sphere>(point3(0, 2, -1), 0.5, material_reflectiveMetal));
    objects.add(make_shared<sphere>(point3(-1.0, 2, -1), 0.5, materialWater));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}


hittable_list sceneTask1() {
    hittable_list scene;


    //.\RayTracerNew.exe>image.ppm

   /* auto difflightGreen = make_shared<diffuse_light>(color(0, 7, 0));
    auto difflightBlue = make_shared<diffuse_light>(color(0, 0, 7));*/
    //scene.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflightGreen));
    //scene.add(make_shared<sphere>(point3(0, 2, 2), 0.5, difflightBlue));
    //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

 /*   auto materialAir = make_shared<dielectric>(1.0);
    auto materialWater = make_shared<dielectric>(1.4);
    auto materialDiamond = make_shared<dielectric>(2.4);
    auto materialHarderThanDiamond = make_shared<dielectric>(5.8);*/

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

   /* scene.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));*/
    //objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    
    scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    scene.add(make_shared<sphere>(point3(0, 1, -1.5), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(0, 2, -2), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(-1, 1.5, -2), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(1, 1.5, -2), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(-1, 0.5, -1.5), 0.5, material_opaque));
    scene.add(make_shared<sphere>(point3(1, 0.5, -1.5), 0.5, material_opaque));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return scene;
}

hittable_list sceneTask2() {
    hittable_list objects;


    //.\RayTracerNew.exe>image.ppm

   auto difflightGreen = make_shared<diffuse_light>(color(0, 7, 0));
   auto difflightBlue = make_shared<diffuse_light>(color(0, 0, 7));
   auto difflightWhite = make_shared<diffuse_light>(color(4, 4, 4));
   //objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflightGreen));
   //objects.add(make_shared<sphere>(point3(0, 2, 2), 0.5, difflightBlue));
   //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

 /*   auto materialAir = make_shared<dielectric>(1.0);
    auto materialWater = make_shared<dielectric>(1.4);
    auto materialDiamond = make_shared<dielectric>(2.4);
    auto materialHarderThanDiamond = make_shared<dielectric>(5.8);*/

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

   /* scene.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));*/
    //objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    objects.add(make_shared<sphere>(point3(0, 3, -5), 0.5, difflightWhite));
    objects.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    //objects.add(make_shared<box>(point3(-1, 0, 1), point3(1, 2, 3), material_opaqueBox));
    objects.add(make_shared<xy_rect>(-1, 2, 0, 3, 2, material_opaqueBox));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

hittable_list sceneTaskLight() {
    hittable_list objects;


    //.\RayTracerNew.exe>image.ppm

    auto difflightGreen = make_shared<diffuse_light>(color(0, 10, 0));
    auto difflightBlue = make_shared<diffuse_light>(color(0, 0, 10));
    auto difflightRed = make_shared<diffuse_light>(color(10, 0, 0));
    auto difflightWhite = make_shared<diffuse_light>(color(4, 4, 4));
    //objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflightGreen));
    //objects.add(make_shared<sphere>(point3(0, 2, 2), 0.5, difflightBlue));
    //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

  /*   auto materialAir = make_shared<dielectric>(1.0);
     auto materialWater = make_shared<dielectric>(1.4);
     auto materialDiamond = make_shared<dielectric>(2.4);
     auto materialHarderThanDiamond = make_shared<dielectric>(5.8);*/

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

   /* scene.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));*/
    //objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    //objects.add(make_shared<sphere>(point3(0, 3, -5), 0.5, difflightWhite));
    objects.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    objects.add(make_shared<box>(point3(-6, 0, 1), point3(-5, 1, 2), difflightBlue));
    objects.add(make_shared<sphere>(point3(-1.5, 0, 0), 0.5, difflightGreen));
    objects.add(make_shared<sphere>(point3(-4, 2.5, -1.5), 0.5, difflightRed));
    //objects.add(make_shared<xy_rect>(-1, 2, 0, 3, 2, difflightGreen));

    objects.add(make_shared<sphere>(point3(-3, 1.5, 0), 0.5, material_opaque));
    objects.add(make_shared<sphere>(point3(-5, 1.5, 0), 0.5, material_reflectiveMetal2));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

hittable_list sceneCreative() {
    hittable_list objects;


    //.\RayTracerNew.exe>image.ppm

    auto difflightGreen = make_shared<diffuse_light>(color(0, 10, 0));
    auto difflightBlue = make_shared<diffuse_light>(color(0, 0, 10));
    auto difflightRed = make_shared<diffuse_light>(color(10, 3, 1));
    auto difflightWhite = make_shared<diffuse_light>(color(4, 4, 4));
    //objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflightGreen));
    //objects.add(make_shared<sphere>(point3(0, 2, 2), 0.5, difflightBlue));
    //objects.add(make_shared<xy_rect>(-3, -5, 1, 3, 2, difflight));

  /*   auto materialAir = make_shared<dielectric>(1.0);
     auto materialWater = make_shared<dielectric>(1.4);
     auto materialDiamond = make_shared<dielectric>(2.4);
     auto materialHarderThanDiamond = make_shared<dielectric>(5.8);*/

    auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.5));
    auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    auto material_opaqueBox = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);
    auto material_reflectiveMetal3 = make_shared<metal>(color(0.6, 0.3, 0.3), 0.9);

    //objects.add(make_shared<xy_rect>(2, 5, 2, 5, -2, material_opaque));

   /* scene.add(make_shared<box>(point3(2, 0, 1), point3(3, 1.5, 2), material_opaqueBox));*/
    //objects.add(make_shared<box>(point3(2, 0, 2.4), point3(4, 3.3, 4.6), material_opaqueBox));

    
    //objects.add(make_shared<sphere>(point3(-50.5, 5, -400), 0.5, difflightWhite));
    //starry sky

    for(int i = 0; i < 150; i++){
        objects.add(make_shared<sphere>(point3(random_double(-150.5,150.5), random_double(-50,150.5), -400), 0.2, difflightWhite));
    }
    //ground
    objects.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));

    //streetlight
    //objects.add(make_shared<box>(point3(-6, 0, 1), point3(-5.5, 5, 2), material_opaqueBox));
    //objects.add(make_shared<sphere>(point3(-5.75, 5.5, 1.5), 0.5, difflightWhite));
    double boxx1 = 1;
    double boxx2 = 2;
    double shperex = 1.5;
    objects.add(make_shared<box>(point3(-8, -1, boxx1), point3(-7.5, 4, boxx2), material_opaqueBox));
    objects.add(make_shared<sphere>(point3(-7.75, 4.5, shperex), 0.5, difflightWhite));
    for(int i = 0; i < 10; i++){
        boxx1+=10;
        boxx2+=10;
        shperex+=10;
        objects.add(make_shared<box>(point3(-8, 0, boxx1), point3(-7.5, 5, boxx2), material_opaqueBox));
        objects.add(make_shared<sphere>(point3(-7.75, 5.5, shperex), 0.5, difflightWhite));
    }
     boxx1 = 1;
     boxx2 = 2;
     shperex = 1.5;
    objects.add(make_shared<box>(point3(7.5, -1, boxx1), point3(8, 4, boxx2), material_opaqueBox));
    objects.add(make_shared<sphere>(point3(7.75, 4.5, shperex), 0.5, difflightWhite));
    for (int i = 0; i < 10; i++) {
        boxx1 += 10;
        boxx2 += 10;
        shperex += 10;
        objects.add(make_shared<box>(point3(7.5, 0, boxx1), point3(8, 5, boxx2), material_opaqueBox));
        objects.add(make_shared<sphere>(point3(7.75, 5.5, shperex), 0.5, difflightWhite));
    }

    //house
    auto material_house = make_shared<lambertian>(color(1.65, 0.42, 0.42));
    
    objects.add(make_shared<box>(point3(-9, -1, 1.5), point3(9, 15, -4.5), material_house));
    auto material_roof = make_shared<lambertian>(color(1.65, 1.3, 1.4));
    auto material_rooflight = make_shared<diffuse_light>(color(2, 2, 4));
    objects.add(make_shared<box>(point3(-12, 15, 2.5), point3(12, 16, -5.5), material_rooflight));
    
    //objects.add(make_shared<sphere>(point3(-11.5, 14.5, 2.5), 0.5, material_rooflight));
    //objects.add(make_shared<sphere>(point3(11.5, 14.5, 2.5), 0.5, material_rooflight));
    //objects.add(make_shared<sphere>(point3(20, 14.5, -5), 5, material_rooflight));

    //door
    auto material_door = make_shared<metal>(color(0.6, 0.8, 0.6), 0.8);
    objects.add(make_shared<xy_rect>(-2, 2, -1, 6, 1.55, material_door));

    //doorbell
    auto material_window = make_shared<diffuse_light>(color(0,4,0));
    objects.add(make_shared<xy_rect>(-4, -3, 2, 3, 1.55, material_window));
    //objects.add(make_shared<xy_rect>(3, 4, 2, 3, 1.5, material_window));
    //objects.add(make_shared<xy_rect>(-3, 3, -1, 6, 1.5, material_window));

    


    //objects.add(make_shared<box>(point3(-6, 0, 1), point3(-5, 1, 2), difflightBlue));
    //objects.add(make_shared<sphere>(point3(-1.5, 0, 0), 0.5, difflightGreen));
    //objects.add(make_shared<sphere>(point3(-4, 2.5, -1.5), 0.5, difflightRed));
    //objects.add(make_shared<xy_rect>(-1, 2, 0, 3, 2, difflightGreen));

    //objects.add(make_shared<sphere>(point3(-3, 1.5, 0), 0.5, material_opaque));
    //objects.add(make_shared<sphere>(point3(-5, 1.5, 0), 0.5, material_reflectiveMetal2));

    //auto pertext = make_shared<noise_texture>(4);
    //objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    //objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return objects;
}

color gridAverage(color& rgb, double detail) {
    double denominator = detail; 
    return (rgb / denominator); //returning the average of the colors

}

int main() {
    
    ofstream output("output.ppm");


    // Image

    /*const auto aspect_ratio = 16.0 / 12.0;*/
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    /*const int image_width = 640;*/
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    /*const int samples_per_pixel = 1000;*/ //const olacak!!! sirf rand yaparken int yap
    const int samples_per_pixel = 1000;
    const int max_depth = 50;
    //color background = color(0.2, 0.2, 0.2);
    //color background = color(0.05, 0.05, 0.1);
    color background = color(0.004, 0.005, 0.008);
    //color background = color(0.04, 0.05, 0.08);
    //color background = color(0.4, 0.5, 0.8);

    // World
    // 
    // -----------Benimki Asagidaki -----------
    // 
    
    
    
    //auto world = random_scene();

    hittable_list world;
    world = sceneCreative();
    //auto materialAir = make_shared<dielectric>(1.0);
    //auto materialWater = make_shared<dielectric>(1.4);
    //auto materialDiamond = make_shared<dielectric>(2.4);
    //auto materialHarderThanDiamond = make_shared<dielectric>(5.8);

    //auto material_ground = make_shared<lambertian>(color(0.8, 0.9, 0.3));
    //auto material_opaque = make_shared<lambertian>(color(0.4, 0.3, 0.6));
    //auto material_reflectiveMetal = make_shared<metal>(color(0.2, 0.8, 0.6), 0.1);
    //auto material_reflectiveMetal2 = make_shared<metal>(color(0.8, 0.6, 0.6), 0.01);

    //world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    //world.add(make_shared<sphere>(point3(1, 0.0, -1.0), 0.5, material_opaque));
    //world.add(make_shared<sphere>(point3(0, 0.0, -1), 0.5, material_reflectiveMetal));
    //world.add(make_shared<sphere>(point3(-1.0, 0.0, -1), 0.5, material_reflectiveMetal2));


    // Camera

    //look from, look at, vup, fow degrees, aspect_ratio
    point3 lookfrom(0, 8, 100);
    point3 lookat(0, 2, -2.5);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 0.0; //for no blur keep it at 0

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus); 

    // Render

    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, background, world, max_depth);
			}
			write_color(output, pixel_color, samples_per_pixel);
		}
	}

    //grid algorithm is the one below
    //change samples per pixel to what you want, for instance
    // double gridValue=10.0; //random equivalent would be 900 samples per pixel
    //for (int j = image_height - 1; j >= 0; --j) {
    //    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //    for (int i = 0; i < image_width; ++i) {
    //        color pixel_color(0, 0, 0);
    //        for (double s = 0; s < gridValue; ++s) {
    //            for (double s2 = 0; s2 < gridValue; ++s2) {
    //                auto u = (i + s/gridValue) / (image_width - 1);
    //                auto v = (j + s2/gridValue) / (image_height - 1);
    //                ray r = cam.get_ray(u, v);
    //                pixel_color += ray_color(r, background, world, max_depth);
    //            }
    //        }
    //        pixel_color = gridAverage(pixel_color, gridValue);
    //        write_color(output, pixel_color, gridValue);
    //    }
    //}


    output.close();

    std::cerr << "\nDone.\n";
}