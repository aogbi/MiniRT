/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:58:38 by aogbi             #+#    #+#             */
/*   Updated: 2024/10/25 14:15:52 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

Vector3 vector_create(double x, double y, double z) {
    Vector3 v = {x, y, z};
    return v;
}

Vector3 vector_subtract(Vector3 v1, Vector3 v2) {
    return vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

double vector_dot(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 vector_normalize(Vector3 v) {
    double length = sqrt(vector_dot(v, v));
    return vector_create(v.x/length, v.y/length, v.z/length);
}

double ray_sphere_intersect(Ray ray, Sphere sphere) {
    Vector3 oc = vector_subtract(ray.origin, sphere.center);
    
    double a = vector_dot(ray.direction, ray.direction);
    double b = 2.0 * vector_dot(oc, ray.direction);
    double c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0;
    }
    
    double t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t > 0)
        return (t);
    return (-1.0);
}

double calculate_lighting(Vector3 point, Vector3 normal) {
    Vector3 light_dir = vector_normalize(vector_create(-1.0, -1.0, -1.0));
    double intensity = -vector_dot(normal, light_dir);
    if (intensity > 0) 
        return intensity;
    return 0;
}
