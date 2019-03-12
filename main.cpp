#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat findShape(Mat, int, float);
Mat preProcess(Mat, int);

int main(int argc, char **argv){

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	//namedWindow("Origin");
	//imshow("Origin", image);
	
	image = preProcess(image,0);
	
	namedWindow("Filtred");
	imshow("Filtred", image);
	
	Mat drawing =  findShape(image, 3, 0.03);
	
	Mat origin = imread(argv[1]);
	addWeighted(drawing, 0.7, origin, 0.3, 0.0, origin);
	
	char windowName[] = "Result";
	namedWindow(windowName);
	imshow(windowName, origin);
	while ((char) waitKey(0) != 'q');
	destroyWindow(windowName);

	return 0;
}

Mat preProcess(Mat image, int moreBackground){


	int histSize = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	Mat hist;
	calcHist( &image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

	int i,position=0;
	float compare = hist.at<float>(0);
	for(i = 0;i < histSize; i++){
		if (hist.at<float>(i) > compare){ 
			compare = hist.at<float>(i);
			position = i;
		}
	}
	
	//filtro gaussiano
	GaussianBlur(image, image, Size(5,5), 0);
		
	if(moreBackground){
	
		if(position > 150){
		//binariza a imagem
			threshold(image, image, position-75, 255, THRESH_BINARY | THRESH_OTSU);
			bitwise_not(image, image);
		}
		else {
			threshold(image, image, position+75, 255, THRESH_BINARY | THRESH_OTSU);
		}	
	}
	else {
		if(position > 150){
		//binariza a imagem
			threshold(image, image, position-75, 255, THRESH_BINARY | THRESH_OTSU);	
		}
		else {
			threshold(image, image, position+75, 255, THRESH_BINARY | THRESH_OTSU);
			bitwise_not(image, image);
		}
	}

	
	Mat kernel;
	
	kernel = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));
	dilate(image, image, kernel);
	erode(image, image, kernel);

	return image;
}

Mat findShape(Mat image, int shape, float epsilon){
	
	std::vector<std::vector<Point> > poligono;
    std::vector<Vec4i> hierarchy;
	
	bool closed; //Se a figura é fechada
	double perimetro;
	int i, objectQuantity = 0;
	
	Mat drawing = Mat::zeros( image.size(), CV_8UC3 ); //fundo preto
	
	findContours (image, poligono, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));
	
	for ( i = 0; i < poligono.size(); i++){
		perimetro = arcLength(poligono[i], closed);
		approxPolyDP(poligono[i], poligono[i], epsilon*perimetro,closed );
		
		if( (poligono[i].size() == shape) && closed ){
			drawContours( drawing, poligono, i, 255, 5, 8, hierarchy, 0, Point() );
			objectQuantity++;
		}
	}

	printf("Quantidades de objetos : %d\n", objectQuantity);
	return drawing;
}
