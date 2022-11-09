// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Filters.cpp
// Last Modification Date: 19/4/2022
// Author: Belal Ahmed Eid
// Purpose:This program allows user to load an image and choose filter to apply on RGB images with BMP extension

#include <iostream>
#include <cstring>
#include <set>
#include "bmplib.cpp"
#include <string>

using namespace std;

//------------- Variables -------------
string answer;
unsigned char image[SIZE][SIZE][RGB];
unsigned char editedImage[SIZE][SIZE][RGB];
unsigned char image2 [SIZE][SIZE][RGB];

//------------- Functions  -------------
void loadImage();
void saveImage();
void blackWhiteFilter();
void flipImage();
void mergeImage();
void darkenAndLighten();
void invert();
void rotate();
void detectEdges();
void mirrorImage();
void shrinkImage();
void BlurImage();
void Enlarge();
void shuffleImage();
void copyImage();

int main() {
    // Set of strings user should input
    set <string> inputs = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "s"};
    string command;
    bool running = true;
    // Get image from user
    loadImage();
    // Main Loop
    while(running){
        cout << "-------------------------------------------------" << endl;
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << "1- Black & White Filter\n2- Invert Filter\n"
                "3- Merge Filter\n4- Flip Image\n5- Darken and Lighten Image\n"
                "6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\n"
                "a- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image\ns- Save the Image to a File\n0- Exit"<<endl;
        cin >> command;
        // Check if input is valid or not
        while (!inputs.count(command) || cin.fail()){
            cout << "Invalid input. Please select a choice from [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, s]: ";
            cin.clear();
            cin.sync();
            cin >> command;
        }

        if (command == "1"){
            blackWhiteFilter();
        }
        else if (command == "2"){
            invert();
        }
        else if (command == "3"){
            mergeImage();
        }
        else if (command == "4"){
            flipImage();
        }
        else if (command == "5"){
            darkenAndLighten();
        }
        else if (command == "6"){
            rotate();
        }
        else if (command == "7"){
            detectEdges();
        }
        else if (command == "8"){
            Enlarge();
        }
        else if (command == "9"){
            shrinkImage();
        }
        else if (command == "a"){
            mirrorImage();
        }
        else if (command == "b"){
            shuffleImage();
        }
        else if (command == "c"){
            BlurImage();
        }
        else if (command == "0"){
            running = false;
        }
        else if (command == "s"){
            saveImage();
        }
    }
    cout << "Thanks for using FCAI Filters Application" << endl;
    return 0;
}

void loadImage(){
    char imageFileName[100];
    // Get color scale image file name from user
    cout << "Ahlan ya user ya habibi" << endl << "Please enter file name of the image to process: " << endl;
    cin >> imageFileName;

    // Add image file name to .bmp extension and load image
    strcat (imageFileName, ".bmp");
    // Check if image is found or not
    while(readRGBBMP(imageFileName, image)){
        cout << "Image Not Found\nEnter the source image file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
    }
}
// Function to put the edited image in the original image so user can apply more than one filter on image
// it will be called after applying each filter
void copyImage(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = editedImage[i][j][k];
        }
    }
}
void blackWhiteFilter(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // convert each RGB pixel to Grayscale
            long long average = 0;
            average = (image[i][j][0] * 0.299) + (image[i][j][1] * 0.587) + (image[i][j][2] * 0.114);
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = average;
            }
            // convert each Grayscale pixel to Black and White
            if (image[i][j][0] > 127){
                editedImage[i][j][0] = 255;
                editedImage[i][j][1] = 255;
                editedImage[i][j][2] = 255;
            }
            else{
                editedImage[i][j][0] = 0;
                editedImage[i][j][1] = 0;
                editedImage[i][j][2] = 0;
            }
        }
    }
    copyImage();
}
void mergeImage() {
    char imageFileName2[100];
    cout<<"enter the file name of the image you want to merge\n";
    cin>>imageFileName2;
    //recieve image that will be merged
    strcat (imageFileName2, ".bmp");
    while(readRGBBMP(imageFileName2, image2)){
        cout << "Image Not Found\nEnter the source image file name: ";
        cin >> imageFileName2;
        strcat (imageFileName2, ".bmp");
    }
    readRGBBMP(imageFileName2, image2);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k=0 ;k < RGB; k++){
                editedImage[i][j][k]=image2[i][j][k]/3+(image[i][j][k]+255)/3;
            }
        }
    }
    copyImage();
}
void darkenAndLighten() {
    cout<<"you want to\n 1-darken \n 2-lighten\n ";
    cin>>answer;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k=0 ;k < RGB; k++){
                if (answer=="1"){
                    editedImage[i][j][k] = image[i][j][k]/2;}
                    //to make the photo darken
                else if (answer=="2"){
                    editedImage[i][j][k] = (image[i][j][k]+255)/2;}
                    //to lighten the photo
                else
                    while(answer!= "2"&&answer!="1")
                    {cout<<"please enter valid answer\n";
                        cin>>answer;
                    }
            }
        }
    }
    copyImage();
}
void BlurImage() {

    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            for (int k = 0; k < RGB; k++) {
                editedImage[i][j][k]= (image[i - 1][j - 1][k] + image[i - 1][j][k] + image[i - 1][j + 1][k] + image[i][j - 1][k] +
                                       image[i][j + 1][k] + image[i + 1][j - 1][k] + image[i + 1][j][k] + image[i + 1][j + 1][k]) / 9;
            }
        }
    }
    copyImage();
}
void shrinkImage(){
    cout<<"Do you want to shrink image to 1/2 , 1/3 or 1/4\n";
    cin>>answer;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                if (answer=="1/2"){
                    editedImage[i/2][j/2][k]=image[i+1][j][k];}
                else if (answer=="1/3"){
                    editedImage[i/3][j/3][k]=image[i+1][j][k];}
                else if (answer=="1/4"){
                    editedImage[i/4][j/4][k]=image[i+1][j][k];}
                else {
                    while(answer!="1/2"&&answer!="1/3" && answer!="1/4"){
                        cout<<"please enter valid option\n";
                        cin>>answer;
                    }
                }
            }
        }
    }
    copyImage();
}
void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k <RGB; k++) {
                editedImage[i][j][k] = 255- image[i][j][k];
            }
        }
    }
    copyImage();
}
void rotate(){
    cout << "Choose a number from [1,2,3]" << endl;
    cout << "1- Rotate 90\n2- Rotate 180\n3- Rotate 270" << endl;
    cin >> answer;
    while (answer != "1" && answer != "2" && answer != "3"){
        cout << "Please enter a valid number from [1, 2, 3]: " << endl;
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; k++) {
                if (answer == "1") {
                    editedImage[255 - j][i][k] = image[i][j][k];
                    //to make photo rotate 90 degree
                }
                else if (answer == "2") {
                    editedImage[255 - i][255 - j][k] = image[i][j][k];
                    //to make photo rotate 180 degree
                }
                else if (answer == "3") {
                    editedImage[j][255 - i][k] = image[i][j][k];
                    //to make photo rotate 270 degree
                }
            }
        }
    }
    copyImage();
}
void Enlarge() {
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
                for (int k = 0; k < RGB; k++) {
                    editedImage[2 * i][2 * j][k] = image[i][j][k];
                    editedImage[2 * i][2 * j + 1][k] = image[i][j][k];
                    editedImage[2 * i + 1][2 * j][k] = image[i][j][k];
                    editedImage[2 * i + 1][2 * j + 1][k] = image[i][j][k];

                }
            }
        }
    }
        //Enlarge the second quarter
    else if(answer == "2") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = (SIZE / 2); j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    editedImage[2 * i][(j - 128) * 2][k] = image[i][j][k];
                    editedImage[2 * i][(j - 128) * 2 + 1][k] = image[i][j][k];
                    editedImage[2 * i + 1][(j - 128) * 2][k] = image[i][j][k];
                    editedImage[2 * i + 1][(j - 128) * 2 + 1][k] = image[i][j][k];
                }
            }
        }
    }
        //Enlarge the third quarter
    else if(answer == "3"){
        for (int i = (SIZE/2) ; i < SIZE; i++) {
            for (int j = 0; j < (SIZE/2); j++) {
                for (int k = 0; k < RGB; k++) {
                    editedImage[2 * (i - 128)][j * 2][k] = image[i][j][k];
                    editedImage[2 * (i - 128)][j * 2 + 1][k] = image[i][j][k];
                    editedImage[2 * (i - 128) + 1][j * 2][k] = image[i][j][k];
                    editedImage[2 * (i - 128) + 1][j * 2 + 1][k] = image[i][j][k];
                }
            }
        }
    }
        //Enlarge the fourth quarter
    else if(answer == "4"){
        for (int i = (SIZE/2) ; i < SIZE; i++) {
            for (int j = (SIZE/2); j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    editedImage[2 * (i - 128)][(j - 128) * 2][k] = image[i][j][k];
                    editedImage[2 * (i - 128)][(j - 128) * 2 + 1][k] = image[i][j][k];
                    editedImage[2 * (i - 128) + 1][(j - 128) * 2][k] = image[i][j][k];
                    editedImage[2 * (i - 128) + 1][(j - 128) * 2 + 1][k] = image[i][j][k];
                }
            }
        }
    }
    copyImage();
}
void shuffleImage(){
    int a,b,c,d;
    cout<<"please, choose the order you want:";
    //check 4 possibilities for the first quarter
    cin>>a;
    while (a != 1 && a != 2 && a != 3 && a!=4){
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> a;
    }
    for (int i = 0; i < (SIZE/2); i++) {
        for (int j = 0; j < (SIZE/2); j++) {
            for (int k = 0; k < RGB; k++) {
                if(a == 1){
                    editedImage[i][j][k] = image[i][j][k];
                }
                else if(a == 2){
                    editedImage[i][j][k] = image[i][j+128][k];
                }
                else if(a == 3){
                    editedImage[i][j][k] = image[i+128][j][k];
                }
                else{
                    editedImage[i][j][k] = image[i+128][j+128][k];
                }
            }
        }
    }
    //check 4 possibilities for the second quarter
    cin>>b;
    while (b != 1 && b != 2 && b != 3 && b!=4){
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> b;
    }
    while(a == b){
        cout<<"You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> b;
    }
    for (int i = 0; i < (SIZE/2); i++) {
        for (int j =(SIZE/2); j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                if (b == 2) {
                    editedImage[i][j][k] = image[i][j][k];
                }
                else if (b == 1) {
                    editedImage[i][j][k] = image[i][j-128][k];
                }
                else if (b == 3) {
                    editedImage[i][j][k] = image[i+128][j-128][k];
                }
                else {
                    editedImage[i][j][k] = image[i+128][j][k];
                }
            }
        }
    }
    //check 4 possibilities for the third quarter
    cin>>c;
    while (c != 1 && c != 2 && c != 3 && c!=4){
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> c;
    }
    while(c == a || c == b){
        cout<<"You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> c;
    }
    for (int i = (SIZE/2) ; i < SIZE; i++) {
        for (int j = 0; j < (SIZE/2); j++) {
            for (int k = 0; k < RGB; k++) {
                if (c == 3) {
                    editedImage[i][j][k] = image[i][j][k];
                }
                else if (c == 1) {
                    editedImage[i][j][k] = image[i-128][j][k];
                }
                else if (c == 2) {
                    editedImage[i][j][k] = image[i-128][j+128][k];
                }
                else {
                    editedImage[i][j][k] = image[i][j+128][k];
                }
            }
        }
    }
    //check 4 possibilities for the fourth quarter
    cin>>d;
    while (d != 1 && d != 2 && d != 3 && d!=4){
        cout << "Pleas enter a valid number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        cin >> d;
    }
    while(d == a || d == b || d ==c){
        cout<<"You have already chosen it, choose another one";
        cin.clear();
        cin.sync();
        cin >> d;
    }
    for (int i = (SIZE/2) ; i < SIZE; i++) {
        for (int j = (SIZE/2); j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                if (d == 4) {
                    editedImage[i][j][k] = image[i][j][k];
                }
                else if (d == 1) {
                    editedImage[i][j][k] = image[i-128][j-128][k];
                }
                else if (d == 2) {
                    editedImage[i][j][k] = image[i-128][j][k];
                }
                else {
                    editedImage[i][j][k] = image[i][j-128][k];
                }
            }
        }
    }
    copyImage();
}
void detectEdges(){
    // convert picture to black and white
    blackWhiteFilter();
    // Detect Edges
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                // Calculate the sum of pixels around the determined pixel then subtract (4 * the determined pixel) from the result
                editedImage[i][j][k] = image[i+1][j][k] + image[i][j+1][k] + image[i-1][j][k] + image[i][j-1][k] + image[i-1][j-1][k] +
                                       image[i-1][j+1][k] + image[i+1][j-1][k] + image[i+1][j+1][k] - (8 * image[i][j][k]);
                // Invert the pixel
                editedImage[i][j][k] = 255 - editedImage[i][j][k];
            }
        }
    }
    copyImage();
}
void mirrorImage(){
    cout << "Choose a number from [1,2,3,4]: " << endl;
    cout << "1- Left 1/2\n2- Right 1/2\n3- Upper 1/2\n4- Lower 1/2" << endl;
    cin >> answer;
    if (answer == "1"){
        // Mirror Left
        for (int i = 0; i < SIZE; ++i) {
            for (int j = SIZE/2; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    // loop through the right half of image and fill each pixel with the opposite pixel in the left half
                    image[i][j][k] = image[i][255-j][k];
                }
            }
        }
    }
    else if(answer == "2"){
        // Mirror Right
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    // loop through the left half of image and fill each pixel with the opposite pixel in the left right
                    image[i][j][k] = image[i][255-j][k];
                }
            }
        }
    }
    else if (answer == "3"){
        // Mirror Upper
        for (int i = SIZE/2; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    // loop through the lower half of image and fill each pixel with the opposite pixel in the upper half
                    image[i][j][k] = image[255-i][j][k];
                }
            }
        }
    }
    else if (answer == "4"){
        // Mirror Lower
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    // loop through the upper half of image and fill each pixel with the opposite pixel in the lower half
                    image[i][j][k] = image[255-i][j][k];
                }
            }
        }
    }
    else {
        cout << "Invalid input. Please enter a number from [1, 2, 3, 4]: " << endl;
        cin.clear();
        cin.sync();
        mirrorImage();
    }
    // Put the mirrored image in edited image to save it
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                editedImage[i][j][k] = image[i][j][k];
            }
        }
    }
}
void flipImage(){
    cout << "Enter 1 to flip horizontally or 2 to flip vertically: " << endl;
    cout << "1- Horizontally\n2- Vertically" << endl;
    cin >> answer;
    // Check if input is valid or not
    while (answer != "1" && answer != "2"){
        cout << "Pleas enter 1 to flip horizontally or 2 to flip vertically: " << endl;
        // Clear buffer before getting new input
        cin.clear();
        cin.sync();
        cin >> answer;
    }
    // flip horizontally
    if (answer == "1"){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    editedImage[i][SIZE-j][k] = image[i][j][k];
                }
            }
        }
    }
        // flip vertically
    else if (answer == "2"){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    editedImage[SIZE-i][j][k] = image[i][j][k];
                }
            }
        }
    }
    copyImage();
}
void saveImage(){
    char imageFileName[100];

    // Get color scale image target file name from user
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add image file name to .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, editedImage);
}
