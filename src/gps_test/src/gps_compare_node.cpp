#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>

constexpr double a = 6378137.0;
constexpr double f = 1.0 / 298.257223563;
constexpr double e_sq = f * (2 - f);

// Phương pháp 1 - Azimuthal Approximation
void convert_azimuthal(const double& lat, const double& lon, const double& ref_lat, const double ref_lon, double& x, double& y) {
    if ((lat == ref_lat) && (lon == ref_lon)) {
        x = y = 0;
        return;
    }

    double lat_rad = lat * M_PI / 180.0;
    double lon_rad = lon * M_PI / 180.0;
    double ref_lon_rad = ref_lon * M_PI / 180.0;
    double ref_lat_rad = ref_lat * M_PI / 180.0;

    double sin_lat = sin(lat_rad);
    double cos_lat = cos(lat_rad);
    double cos_d_lon = cos(lon_rad - ref_lon_rad);

    double ref_sin_lat = sin(ref_lat_rad);
    double ref_cos_lat = cos(ref_lat_rad);

    double c = acos(ref_sin_lat * sin_lat + ref_cos_lat * cos_lat * cos_d_lon);
    double k = (fabs(c) < std::numeric_limits<double>::epsilon()) ? 1.0 : (c / sin(c));

    x = k * cos_lat * sin(lon_rad - ref_lon_rad) * 6371000; // East
    y = k * (ref_cos_lat * sin_lat - ref_sin_lat * cos_lat * cos_d_lon) * 6371000; // North
}

// Phương pháp 2 - ECEF -> ENU
void convert_ecef_enu(const double& lat, const double& lon, const double& ref_lat, const double ref_lon, double& x, double& y) {
    double alt = 0.0, ref_alt = 0.0;

    double lat_rad = lat * M_PI / 180.0;
    double lon_rad = lon * M_PI / 180.0;
    double ref_lat_rad = ref_lat * M_PI / 180.0;
    double ref_lon_rad = ref_lon * M_PI / 180.0;

    double sin_lat = sin(lat_rad), cos_lat = cos(lat_rad);
    double sin_lon = sin(lon_rad), cos_lon = cos(lon_rad);
    double N = a / sqrt(1 - e_sq * sin_lat * sin_lat);

    double x_ecef = (N + alt) * cos_lat * cos_lon;
    double y_ecef = (N + alt) * cos_lat * sin_lon;
    double z_ecef = (N * (1 - e_sq) + alt) * sin_lat;

    double sin_ref_lat = sin(ref_lat_rad), cos_ref_lat = cos(ref_lat_rad);
    double sin_ref_lon = sin(ref_lon_rad), cos_ref_lon = cos(ref_lon_rad);
    double N_ref = a / sqrt(1 - e_sq * sin_ref_lat * sin_ref_lat);

    double x_ref = (N_ref + ref_alt) * cos_ref_lat * cos_ref_lon;
    double y_ref = (N_ref + ref_alt) * cos_ref_lat * sin_ref_lon;
    double z_ref = (N_ref * (1 - e_sq) + ref_alt) * sin_ref_lat;

    double dx = x_ecef - x_ref;
    double dy = y_ecef - y_ref;
    double dz = z_ecef - z_ref;

    x = -sin_ref_lon * dx + cos_ref_lon * dy; // East
    y = -cos_ref_lon * sin_ref_lat * dx - sin_ref_lon * sin_ref_lat * dy + cos_ref_lat * dz; // North
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "gps_compare_node");
    ros::NodeHandle nh;

    double lat, lon, ref_lat, ref_lon;

    ROS_INFO("Nhap reference lat (do): "); std::cin >> ref_lat;
    ROS_INFO("Nhap reference lon (do): "); std::cin >> ref_lon;
    ROS_INFO("Nhap vi tri hien tai lat (do): "); std::cin >> lat;
    ROS_INFO("Nhap vi tri hien tai lon (do): "); std::cin >> lon;

    double x1, y1, x2, y2;
    convert_azimuthal(lat, lon, ref_lat, ref_lon, x1, y1);
    convert_ecef_enu(lat, lon, ref_lat, ref_lon, x2, y2);

    ROS_INFO("\nPhuong phap 1 (Azimuthal Approximation):");
    ROS_INFO("  East (x): %.6f m", x1);
    ROS_INFO("  North (y): %.6f m", y1);
    ROS_INFO("  Distance:  %.6f m", sqrt(x1*x1 + y1*y1));

    ROS_INFO("\nPhuong phap 2 (ECEF -> ENU):");
    ROS_INFO("  East (x): %.6f m", x2);
    ROS_INFO("  North (y): %.6f m", y2);
    ROS_INFO("  Distance:  %.6f m", sqrt(x2*x2 + y2*y2));

      // Ghi file CSV
    std::ofstream fout("/home/devbot/mybot_ws/gps_output.csv", std::ios::app);
    fout << lat << "," << lon << ",auto\n";
    fout.close();

    return 0;
}

