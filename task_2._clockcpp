#include <opencv2/opencv.cpp>
#include <iostream>
#include <cmath>
using namespace std;

void invertColors(vector<vector<vector<unsigned char>>> &image, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

void grayscale(vector<vector<vector<unsigned char>>> &image, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float avg = static_cast<float>((image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3);

            for (int k = 0; k < 3; k++) {
                image[i][j][k] = static_cast<unsigned char>(round(avg));
            }
        }
    }
}

void blur(vector<vector<vector<unsigned char>>> &image, int height, int width) {
    vector<vector<vector<unsigned char>>> tempImage(image);

    const float kernel[3][3] = {
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0}
    };

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            float sum[3] = {0.0, 0.0, 0.0};

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    for (int k = 0; k < 3; k++) {
                        sum[k] += static_cast<float>(image[i + x][j + y][k]) * kernel[x + 1][y + 1];
                    }
                }
            }

            for (int k = 0; k < 3; k++) {
                tempImage[i][j][k] = static_cast<unsigned char>(sum[k]);
            }
        }
    }

    image = tempImage;
}

void rotateImage(vector<vector<vector<unsigned char>>> &image, int height, int width, float angleDegrees) {
    vector<vector<vector<unsigned char>>> tempImage(image);

    float angleRadians = angleDegrees * M_PI / 180.0;

    float centerX = static_cast<float>(width - 1) / 2.0;
    float centerY = static_cast<float>(height - 1) / 2.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float x = static_cast<float>(j) - centerX;
            float y = static_cast<float>(i) - centerY;
            float rotatedX = x * cos(angleRadians) - y * sin(angleRadians) + centerX;
            float rotatedY = x * sin(angleRadians) + y * cos(angleRadians) + centerY;

            int x1 = static_cast<int>(floor(rotatedX));
            int y1 = static_cast<int>(floor(rotatedY));
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            if (x1 < 0 || x2 >= width || y1 < 0 || y2 >= height) {
                continue;
            }

            float dx = rotatedX - x1;
            float dy = rotatedY - y1;

            for (int k = 0; k < 3; k++) {
                float interpolatedValue = (1.0 - dx) * (1.0 - dy) * static_cast<float>(image[y1][x1][k]) +
                                           dx * (1.0 - dy) * static_cast<float>(image[y1][x2][k]) +
                                           (1.0 - dx) * dy * static_cast<float>(image[y2][x1][k]) +
                                           dx * dy * static_cast<float>(image[y2][x2][k]);

                tempImage[i][j][k] = static_cast<unsigned char>(interpolatedValue);
            }
        }
    }

    image = tempImage;
}

void edgeDetection(vector<vector<vector<unsigned char>>> &image, int height, int width) {
    vector<vector<vector<unsigned char>>> tempImage(image);

    const int sobelKernelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int sobelKernelY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            int gradientX[3] = {0, 0, 0};
            int gradientY[3] = {0, 0, 0};

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    for (int k = 0; k < 3; k++) {
                        gradientX[k] += image[i + x][j + y][k] * sobelKernelX[x + 1][y + 1];
                        gradientY[k] += image[i + x][j + y][k] * sobelKernelY[x + 1][y + 1];
                    }
                }
            }

            for (int k = 0; k < 3; k++) {
                int edgeMagnitude = static_cast<int>(sqrt(gradientX[k] * gradientX[k] + gradientY[k] * gradientY[k]));
                edgeMagnitude = max(0, min(255, edgeMagnitude));
                tempImage[i][j][k] = static_cast<unsigned char>(edgeMagnitude);
            }
        }
    }

    image = tempImage;
}

int main() {
    cv::Mat image = cv::imread("input.png");
    int width = image.cols;
    int height = image.rows;

    std::vector<std::vector<std::vector<unsigned char>>> imageMatrix(height,
        std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(3)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) {
                imageMatrix[i][j][k] = pixel[k];
            }
        }
    }

    invertColors(imageMatrix, height, width);

    cv::Mat output(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                output.at<cv::Vec3b>(i, j)[k] = imageMatrix[i][j][k];
            }
        }
    }

    cv::imwrite("Inverted.jpg", output);

    std::vector<std::vector<std::vector<unsigned char>>> imageMatrix2(height,
        std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(3)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) {
                imageMatrix2[i][j][k] = pixel[k];
            }
        }
    }

    grayscale(imageMatrix2, height, width);

    cv::Mat output2(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                output2.at<cv::Vec3b>(i, j)[k] = imageMatrix2[i][j][k];
            }
        }
    }

    cv::imwrite("GrayScale.jpg", output2);

    std::vector<std::vector<std::vector<unsigned char>>> imageMatrix3(height,
        std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(3)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) {
                imageMatrix3[i][j][k] = pixel[k];
            }
        }
    }

    blur(imageMatrix3, height, width);

    cv::Mat output3(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                output3.at<cv::Vec3b>(i, j)[k] = imageMatrix3[i][j][k];
            }
        }
    }

    cv::imwrite("BlurredImage.jpg", output3);

    std::vector<std::vector<std::vector<unsigned char>>> imageMatrix4(height,
        std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(3)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) {
                imageMatrix4[i][j][k] = pixel[k];
            }
        }
    }

    rotateImage(imageMatrix4, height, width, 180);

    cv::Mat output4(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                output4.at<cv::Vec3b>(i, j)[k] = imageMatrix4[i][j][k];
            }
        }
    }

    cv::imwrite("RotatedImage.jpg", output4);

    std::vector<std::vector<std::vector<unsigned char>>> imageMatrix5(height,
        std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(3)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) {
                imageMatrix5[i][j][k] = pixel[k];
            }
        }
    }

    edgeDetection(imageMatrix5, height, width);

    cv::Mat output5(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < 3; ++k) {
                output5.at<cv::Vec3b>(i, j)[k] = imageMatrix5[i][j][k];
            }
        }
    }

    cv::imwrite("EdgeDetection.jpg", output5);

    cv::imwrite("output.jpg", image);
    return 0;
}

