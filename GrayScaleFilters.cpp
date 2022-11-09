// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Filters.cpp
// Last Modification Date: 19/4/2022
// Author: Belal Ahmed Eid
// Purpose:This program allows user to load an image and choose filter to apply on Grayscale images with bmp extension

#include <iostream>
#include <cstring>
#include <set>
#include "bmplib.cpp"
#include <string>

using namespace std;

//------------- Variables -------------
string answer;
unsigned char image[SIZE][SIZE];
unsigned char editedImage[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

//------------- Functions  -------------
void loadImage();

void saveImage();

void blackWhiteFilter();

void invert();

void mergeImage();

void flipImage();

void rotate();

void darkenAndLighten();

void detectEdges();

void enlarge();

void shrinkImage();

void mirrorImage();

void shuffleImage();

void blurImage();

void copyImage();

int main() {
    // Set of strings user should input
    set<string> inputs = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "s"};
    string command;
    bool running = true;
    // Get image from user
    loadImage();
    // Main Loop
    while (running) {
        cout << "-------------------------------------------------" << endl;
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << "1- Black & White Filter\n2- Invert Filter\n"
                "3- Merge Filter\n4- Flip Image\n5- Darken and Lighten Image\n"
                "6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\n"
                "a- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image\ns- Save the Image to a File\n0- Exit" << endl;
        cin >> command;
        // Check if input is valid or not
        while (!inputs.count(command) || cin.fail()) {
            cout << "Invalid input. Please select a choice from [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, s]: ";
            cin.clear();
            cin.sync();
            cin >> command;
        }

        if (command == "1") {
            blackWhiteFilter();
        } else if (command == "2") {
            invert();
        } else if (command == "3") {
            mergeImage();
        } else if (command == "4") {
            flipImage();
        } else if (command == "5") {
            darkenAndLighten();
        } else if (command == "6") {
            rotate();
        } else if (command == "7") {
            detectEdges();
        } else if (command == "8") {
            enlarge();
        } else if (command == "9") {
            shrinkImage();
        } else if (command == "a") {
            mirrorImage();
        } else if (command == "b") {
            shuffleImage();
        } else if (command == "c") {
            blurImage();
        } else if (command == "0") {
            running = false;
        } else if (command == "s") {
            saveImage();
        }
    }
    cout << "Thanks for using FCAI Filters Application" << endl;
    return 0;
}

void loadImage() {
    char imageFileName[100];
    // Get gray scale image file name from user
    cout << "Ahlan ya user ya habibi" << endl << "Please enter file name of the image to process: " << endl;
    cin >> imageFileName;

    // Add image file name to .bmp extension and load image
    strcat(imageFileName, ".bmp");
    // Check if image is found or not
    while (readGSBMP(imageFileName, image)) {
        cout << "Image Not Found\nEnter the source image file name: ";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
}

// Function to put the edited image in the original image so user can apply more than one filter on image
// it will be called after applying each filter
void copyImage() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = editedImage[i][j];
        }
    }
}

void blackWhiteFilter() {
    long long average = 0;
    // Calculate average of pixels in image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            average += image[i][j];
        }
    }
    average /= (SIZE * SIZE);
    // pixel more than average ----> turn into white / pixel less than average ----> turn into black
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > average) {
                editedImage[i][j] = 255;
            } else {
                editedImage[i][j] = 0;
            }
        }
    }
    copyImage();
}

void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            editedImage[i][j] = 255 - image[i][j];
        }
    }
    copyImage();
}

void mergeImage() {
    char imageFileName2[100];

    // Get image from user
    cout << "Enter the file name of the image you want to merge\n";
    cin >> imageFileName2;
    strcat(imageFileName2, ".bmp");

    // Check if image is found or not
    while (readGSBMP(imageFileName2, image2)) {
        cout << "Image Not Found\nEnter the source image file name: ";
        cin >> imageFileName2;
        strcat(imageFileName2, ".bmp");
    }
    // Merge two images
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            editedImage[i][j] = image[i][j] / 2 + image2[i][j] / 3;
        }
    }
    copyImage();
}

void flipImage() {
    cout << "Enter 1 to flip horizontally or 2 to flip vertically: " << endl;
    cout << "1- Horizontally\n2- Vertically" << endl;
    cin >> answer;
    // Check if input is valid or not
    while (answer != "1" && answer != "2") {
        cout << "Please enter 1 to flip horizontally or 2 to flip vertically: " << endl;
        // Clear buffer before getting new input
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    // flip horizontally
    if (answer == "1") {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                editedImage[i][SIZE - j] = image[i][j];
            }
        }
    }
        // flip vertically
    else if (answer == "2") {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                editedImage[SIZE - i][j] = image[i][j];
            }
        }
    }
    copyImage();
}

void rotate() {
    cout << "Choose a number from [1,2,3]" << endl;
    cout << "1- Rotate 90\n2- Rotate 180\n3- Rotate 270" << endl;
    cin >> answer;
    while (answer != "1" && answer != "2" && answer != "3") {
        cout << "Please enter a valid number from [1, 2, 3]: " << endl;
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //to make photo rotate 90 degree
            if (answer == "1") {
                editedImage[255 - j][i] = image[i][j];
            }
                //to make photo rotate 180 degree
            else if (answer == "2") {
                editedImage[255 - i][255 - j] = image[i][j];
            }
                //to make photo rotate 270 degree
            else if (answer == "3") {
                editedImage[j][255 - i] = image[i][j];
            }
        }
    }
    copyImage();
}

void darkenAndLighten() {
    cout << "Enter 1 to darken or 2 to lighten: " << endl;
    cout << "1- Darken\n2- Lighten" << endl;
    cin >> answer;
    // Check if input is valid
    while (answer != "1" && answer != "2") {
        cout << "Please enter 1 to darken or 2 to lighten: " << endl;
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //to make the photo darken
            if (answer == "1") {
                editedImage[i][j] = image[i][j] / 2;
            }
                //to make the photo lighten
            else if (answer == "2") {
                editedImage[i][j] = (image[i][j] + 255) / 2;
            }
        }
    }
    copyImage();
}

void detectEdges() {
    // convert picture to black and white
    blackWhiteFilter();
    // Detect Edges
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            // Calculate the sum of pixels around the determined pixel then subtract (4 * the determined pixel) from the result
            editedImage[i][j] =
                    image[i + 1][j] + image[i][j + 1] + image[i - 1][j] + image[i][j - 1] - (4 * image[i][j]);
            // Invert the pixel
            editedImage[i][j] = 255 - editedImage[i][j];
        }
    }
    copyImage();
}

void enlarge() {
    cout << "1- first quarter\n2- second quarter\n3- third quarter\n4- fourth quarter" << endl;
    cin >> answer;
    while (answer != "1" && answer != "2" && answer != "3" && answer != "4") {
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    //Enlarge the first quarter
    if (answer == "1") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                editedImage[2 * i][2 * j] = image[i][j];
                editedImage[2 * i][2 * j + 1] = image[i][j];
                editedImage[2 * i + 1][2 * j] = image[i][j];
                editedImage[2 * i + 1][2 * j + 1] = image[i][j];
            }
        }
    }
        //Enlarge the second quarter
    else if (answer == "2") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = (SIZE / 2); j < SIZE; j++) {
                editedImage[2 * i][(j - 128) * 2] = image[i][j];
                editedImage[2 * i][(j - 128) * 2 + 1] = image[i][j];
                editedImage[2 * i + 1][(j - 128) * 2] = image[i][j];
                editedImage[2 * i + 1][(j - 128) * 2 + 1] = image[i][j];
            }
        }
    }
        //Enlarge the third quarter
    else if (answer == "3") {
        for (int i = (SIZE / 2); i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                editedImage[2 * (i - 128)][j * 2] = image[i][j];
                editedImage[2 * (i - 128)][j * 2 + 1] = image[i][j];
                editedImage[2 * (i - 128) + 1][j * 2] = image[i][j];
                editedImage[2 * (i - 128) + 1][j * 2 + 1] = image[i][j];
            }
        }
    }
        //Enlarge the fourth quarter
    else if (answer == "4") {
        for (int i = (SIZE / 2); i < SIZE; i++) {
            for (int j = (SIZE / 2); j < SIZE; j++) {
                editedImage[2 * (i - 128)][(j - 128) * 2] = image[i][j];
                editedImage[2 * (i - 128)][(j - 128) * 2 + 1] = image[i][j];
                editedImage[2 * (i - 128) + 1][(j - 128) * 2] = image[i][j];
                editedImage[2 * (i - 128) + 1][(j - 128) * 2 + 1] = image[i][j];
            }
        }
    }
    copyImage();
}

void shrinkImage() {
    //determine the size of shrink the user want
    cout << "Do you want to shrink image to 1/2 , 1/3 or 1/4\n";
    cin >> answer;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //shrinking according to the size
            if (answer == "1/2") {
                editedImage[i / 2][j / 2] = image[i][j];
            } else if (answer == "1/3") {
                editedImage[i / 3][j / 3] = image[i][j];
            } else if (answer == "1/4") {
                editedImage[i / 4][j / 4] = image[i][j];
            }
            //if user entered wrong option
            else {
                while (answer != "1/2" && answer != "1/3" && answer != "1/4") {
                    cout << "please enter valid option from [1/2 - 1/3 - 1/4]\n";
                    cin >> answer;
                }
            }
            //make the image black
            image[i][j] = 0;
            editedImage[i][j] = image[i][j];
        }
    }
    copyImage();
}

void mirrorImage() {
    cout << "Choose a number from [1,2,3,4]: " << endl;
    cout << "1- Left 1/2\n2- Right 1/2\n3- Upper 1/2\n4- Lower 1/2" << endl;
    cin >> answer;
    while (answer != "1" && answer != "2" && answer != "3" && answer != "4") {
        cout << "Pleas enter a valid input from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    if (answer == "1") {
        // Mirror Left
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE / 2; j < SIZE; ++j) {
                // loop through the right half of image and fill each pixel with the opposite pixel in the left half
                image[i][j] = image[i][255 - j];
            }
        }
    } else if (answer == "2") {
        // Mirror Right
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                // loop through the left half of image and fill each pixel with the opposite pixel in the right half
                image[i][j] = image[i][255 - j];
            }
        }
    } else if (answer == "3") {
        // Mirror Upper
        for (int i = SIZE / 2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                // loop through the lower half of image and fill each pixel with the opposite pixel in the upper half
                image[i][j] = image[255 - i][j];
            }
        }
    } else if (answer == "4") {
        // Mirror Lower
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                // loop through the upper half of image and fill each pixel with the opposite pixel in the lower half
                image[i][j] = image[255 - i][j];
            }
        }
    }
    // Put the mirrored image in edited image to save it
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            editedImage[i][j] = image[i][j];
        }
    }
}

void shuffleImage() {
    int a, b, c, d;
    cout << "please, choose the order you want:";
    //check 4 possibilities for the first quarter
    cin >> a;
    while (a != 1 && a != 2 && a != 3 && a != 4) {
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> a;
    }
    //check 4 possibilities for the first quarter
    for (int i = 0; i < (SIZE / 2); i++) {
        for (int j = 0; j < (SIZE / 2); j++) {
            if (a == 1) {
                editedImage[i][j] = image[i][j];
            } else if (a == 2) {
                editedImage[i][j] = image[i][j + 128];
            } else if (a == 3) {
                editedImage[i][j] = image[i + 128][j];
            } else {
                editedImage[i][j] = image[i + 128][j + 128];
            }
        }
    }
    //check 4 possibilities for the second quarter
    cin >> b;
    while (b != 1 && b != 2 && b != 3 && b != 4) {
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> b;
    }
    while (a == b) {
        cout << "You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> b;
    }
    for (int i = 0; i < (SIZE / 2); i++) {
        for (int j = (SIZE / 2); j < SIZE; j++) {
            if (b == 2) {
                editedImage[i][j] = image[i][j];
            } else if (b == 1) {
                editedImage[i][j] = image[i][j - 128];
            } else if (b == 3) {
                editedImage[i][j] = image[i + 128][j - 128];
            } else {
                editedImage[i][j] = image[i + 128][j];
            }
        }
    }
    //check 4 possibilities for the third quarter
    cin >> c;
    while (c != 1 && c != 2 && c != 3 && c != 4) {
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> c;
    }
    while (c == a || c == b) {
        cout << "You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> c;
    }
    for (int i = (SIZE / 2); i < SIZE; i++) {
        for (int j = 0; j < (SIZE / 2); j++) {
            if (c == 3) {
                editedImage[i][j] = image[i][j];
            } else if (c == 1) {
                editedImage[i][j] = image[i - 128][j];
            } else if (c == 2) {
                editedImage[i][j] = image[i - 128][j + 128];
            } else {
                editedImage[i][j] = image[i][j + 128];
            }
        }
    }
    //check 4 possibilities for the fourth quarter
    cin >> d;
    while (d != 1 && d != 2 && d != 3 && d != 4) {
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> d;
    }
    while (d == a || d == b || d == c) {
        cout << "You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> d;
    }
    for (int i = (SIZE / 2); i < SIZE; i++) {
        for (int j = (SIZE / 2); j < SIZE; j++) {
            if (d == 4) {
                editedImage[i][j] = image[i][j];
            } else if (d == 1) {
                editedImage[i][j] = image[i - 128][j - 128];
            } else if (d == 2) {
                editedImage[i][j] = image[i - 128][j];
            } else {
                editedImage[i][j] = image[i][j - 128];
            }
        }
    }
    copyImage();
}

void blurImage() {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            //to blur the image
            editedImage[i][j] =
                    (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] +
                     image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 9;
        }
    }
    copyImage();
}

void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name from user
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add image file name to .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, editedImage);

}
