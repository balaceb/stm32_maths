#include <math.h>

// Polynomial approximation for arctan(z) where |z| <= 1
float arctan_approx(float z) {
    float z_sq = z * z;
    return z * (1.0f + 0.28125f * z_sq) / (1.0f + z_sq * (0.75f + 0.09375f * z_sq));
}

float arctan2_approx(float y, float x) {
    if (x == 0.0f) {
        if (y > 0.0f) return M_PI_2;
        else if (y < 0.0f) return -M_PI_2;
        else return 0.0f; // Handle (0,0) as needed
    }

    float x_abs = fabsf(x);
    float y_abs = fabsf(y);
    float z, angle;

    if (x_abs > y_abs) {
        z = y_abs / x_abs;
        angle = arctan_approx(z);
    } else {
        z = x_abs / y_abs;
        angle = M_PI_2 - arctan_approx(z);
    }

    // Adjust angle based on quadrant
    if (x < 0.0f) {
        angle = M_PI - angle;
    }
    if (y < 0.0f) {
        angle = -angle;
    }

    return angle;
}

// Example usage with accelerometer data
float calculate_tilt_angle(float accel_x, float accel_y) {
    return arctan2_approx(accel_y, accel_x); // Note: order is y, x for arctan2
}
