//MASKE TANIMA
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>
using namespace cv;
using namespace std;

///////////////  Project 3 - License Plate Detector //////////////////////

int main(int argc, char* argv[])
{
	Mat img;
	VideoCapture cap;

	CascadeClassifier plateCascade;
	plateCascade.load("haarcascade_smile.xml");

	//if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> plates;
	cap.open(0);
	while (cap.read(img)) {


		plateCascade.detectMultiScale(img, plates, 1.1, 50);//tespit etme

		for (int i = 0; i < plates.size(); i++)
		{
		
			//rectangle(img, plates[i].tl(), plates[i].br(), Scalar(0, 0, 255), 3);
			if (!plates.empty())
			{
				string frameNumberString = "MASKENIZI TAKINIZ!!!";
				putText(img, frameNumberString, cv::Point(15, 15), FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(255, 255, 255),2);
			}
			
		}
		
		imshow("Gulumseme", img);
		waitKey(1);
	}
	cout << img;

}






















//OBJE ÇEKİRDEĞİ SAYMA
/*
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>
using namespace cv;
using namespace std;
int main()
{
	vector<vector<Point>> kontur;
	vector<Vec4i> hiyerarsi;
	VideoCapture webcam(0);

	Mat kahve,orijinal;

	while (true)
	{
		webcam.read(kahve);
		cvtColor(kahve, orijinal, COLOR_BGR2GRAY);
		threshold(orijinal, orijinal, 100, 255, THRESH_BINARY);
		findContours(orijinal, kontur, hiyerarsi, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		RotatedRect dik;
		for (int i = 0; i < kontur.size(); i++) //kontur çevreleme
		{
			drawContours(orijinal, kontur, i, Scalar(0, 0, 0), 2);
			dik = minAreaRect(kontur[i]);
			putText(orijinal, format("%d", i + 1), dik.center, FONT_HERSHEY_TRIPLEX, 1, Scalar::all(0), 2);
			cout << "KAHVE" << endl;
			waitKey(50);
		}

		imshow("binary", kahve);
		imshow("binary", orijinal);
		waitKey(1);
	}



*/


/*
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>

using namespace cv;  //isim uzayı
using namespace std; //isim uzayı


#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture webcam(0);
	CascadeClassifier yuz;
	vector<Rect> yuz_tanima;
	vector<Rect> goz_tanima;
	yuz.load("haarcascade_frontalface_default.xml");
	stringstream fpsdeğeri;
	int sayi = 0;
	double fps;
	int i = 0;
	while (true)
	{
		Mat okuma, islenmis;
		Mat gri;

		webcam.read(okuma);

		string yazdir = to_string(sayi);//SAYİ YAZDİRMAK İÇİN DÖNÜŞÜM
		cvtColor(okuma, okuma, COLOR_BGR2GRAY);
		yuz.detectMultiScale(okuma, yuz_tanima);
		if (waitKey(20) == 27)break;

		for (int i = 0; i < yuz_tanima.size(); i++)
		{
				webcam.retrieve(okuma);//TANIMA OLMADIĞINDA GRİ EKRAN
				//YÜZ TANIMA
				Mat imgCrop = okuma(yuz_tanima[i]);
				rectangle(okuma, yuz_tanima[i], Scalar(255, 0, 0), 2);
				imwrite("Plates/" + to_string(i) + " İzinsiz Plaka " + ".png", imgCrop);

				//SAYI YAZDIRMA
				for (int j = 0; j < yazdir.size(); j++)
				{
					rectangle(okuma, cv::Point(10, 2), cv::Point(110, 20), cv::Scalar(255, 255, 255), -1);
					putText(okuma, yazdir, Point(10, 15), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 0, 255), 2);
				}
				sayi++;//SAYI ARTIR

				//TANIMA OLDUĞUNDA TRUE YAZDIRMA
				string frameNumberString = "TRUE";
				putText(okuma, frameNumberString, cv::Point(50, 15), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0));
			


		}
		imshow("aa", okuma);
	}
}
*/
//Oluşturulan Üçgenin Alanını Bulma ve Yazdırma
//px den  cm çevirme

/*
void ucgen(Mat gircik, Point2f birnok, Point2f ikinok, Point2f ucnok)//3 tane nokta
{
	line(gircik, birnok, ikinok, Scalar(0, 0, 255), 3);
	line(gircik, birnok, ucnok, Scalar(0, 0, 255), 3);
	line(gircik, ucnok, ikinok, Scalar(0, 0, 255), 3);

	Point2f agirlik_merkezi((birnok.x + ikinok.x + ucnok.x) / 3, (birnok.y + ikinok.y + ucnok.y) / 3);

	circle(gircik, agirlik_merkezi, 2, Scalar::all(255), 3);//AĞIRLIK MERKEZİ
	//1cm = 37.795275591

		float alan = ((birnok.x * ikinok.y) + (ikinok.x * ucnok.y) + (ucnok.x * birnok.y) - (ikinok.x * birnok.y) - (ucnok.x * ikinok.y) - (birnok.x * ucnok.y))/2;//Alan bulma
		alan = alan / 37.795275591;
		if (alan < 0)alan *= -1;
		cout << alan;
		string yazi=to_string(alan);
		putText(gircik, "Alan :" + yazi + " cm", Point(10, 20), FONT_HERSHEY_COMPLEX, 1, Scalar::all(255), 2);

}

int main()
{

	Mat resim(450, 450, CV_8UC3, Scalar::all(0));
	ucgen(resim, Point2f(120, 150), Point2f(12, 410), Point2f(300, 350));
	imshow("resim", resim);
	waitKey(0);
}


*/














//Üçgen Oluşturma ve Ağırlık Merkezini Bulma
/*
void ucgen(Mat gircik, Point2f birnok, Point2f ikinok, Point2f ucnok)//3 tane nokta
{
	line(gircik, birnok, ikinok, Scalar(0, 0, 255), 3);
	line(gircik, birnok, ucnok, Scalar(0, 0, 255), 3);
	line(gircik, ucnok, ikinok, Scalar(0, 0, 255), 3);

	Point2f agirlik_merkezi((birnok.x + ikinok.x + ucnok.x) / 3,(birnok.y+ ikinok.y + ucnok.y)/3);

	circle(gircik, agirlik_merkezi, 2, Scalar::all(255), 3);
}

int main()
{

	Mat resim(450, 450, CV_8UC3,Scalar::all(0));
	ucgen(resim, Point2f(120, 150), Point2f(12, 410), Point2f(300, 350));
	imshow("resim", resim);
	waitKey(0);
}
*/












//BİNARY DÖNÜŞTÜRME KENDİMİZ YAZMA
/*
void binary_donusum(Mat giris, Mat cikis, int esik, int maksimum)
{
	cvtColor(giris, cikis, COLOR_BGR2GRAY);
	for (int i = 0; i < cikis.rows; i++)
	{
		for (int j = 0; j < cikis.cols; j++)
		{
			if (maksimum > esik)
			{
				if (esik > cikis.at<uchar>(i, j)) cikis.at<uchar>(i, j) = 0;
				else cikis.at<uchar>(i, j) = 255;
			}
			else cikis.at<uchar>(i, j) = 0;
			

			
		}
	}
	imshow("son hal", cikis);
	waitKey(0);
}


int main()
{

	Mat resim = imread("yuzben.jpeg");
	resize(resim, resim, Size(500, 650));
	imshow("orijinal", resim);
	
	binary_donusum(resim, resim, 100,255);
	

}

*/









//MAKİNE POZİTİF RESİMLER
/*
int main()
{
	VideoCapture pozitif(0);
	if (!pozitif.isOpened())
	{
		cout << "webcam bulunamadı!";
		return-1;
	}
	int i = 0; //pozitif değerlerl için

	while (true)
	{
		Mat okuma;
		bool kontrol = pozitif.read(okuma);
		cvtColor(okuma, okuma, COLOR_BGR2GRAY);
		resize(okuma, okuma, Size(500, 500));
		if (!kontrol)
		{
			cout << "frame alınamadı";
			break;
		}
		imshow("webcam", okuma);
		if (waitKey(20) == 27) break;
		imwrite("p" + to_string(i) + ".jpg", okuma); //resim çekme
		waitKey(0);
		i++; //resimler için
	}


}
*/


//EN İYİ KAMERA GÖRÜNTÜSÜ
/*
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>

using namespace cv;  //isim uzayı
using namespace std; //isim uzayı

void detectAndDraw(Mat& img, CascadeClassifier& cascade,CascadeClassifier& nestedCascade,double scale)
{
	// Show Processed Image with detected faces
	imshow("Face Detection", img);
}




int main(int argc, const char** argv)
{
	// Yüzlerin algılanacağı videoyu oynatmak için VideoCapture sınıfı
	VideoCapture capture;
	Mat frame, image;

	// Yüz özelliklerine sahip önceden tanımlanmış eğitimli XML sınıflandırıcılar
	CascadeClassifier cascade, nestedCascade;



	//camera aç
	capture.open(0);
	if (capture.isOpened())
	{
		// Videodan kareler yakalayın ve yüzleri tespit edin
		cout << "Yuz Algilama Basladi...." << endl;
		while (true)
		{
			capture >> frame;
			if (frame.empty())
				break;
			Mat frame1 = frame.clone();
			detectAndDraw(frame1, cascade, nestedCascade, 1);
			char c = (char)waitKey(10);

			// Pencereden çıkmak için q tuşuna basın
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Kamera Açılamadı";
	return 0;
}
*/



//YÜZ GÖZ TANIMA
/*
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

int main(int argc, const char** argv)
{
	face_cascade.load("haarcascade_frontalface_default.xml");
	eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml");

	

	
	VideoCapture capture;
	//-- 2. Video akışını okuyun
	capture.open(0);

	Mat frame;
	while (capture.read(frame))
	{
		
		//-- 3. Sınıflandırıcıyı çerçeveye uygulayın
		
		detectAndDisplay(frame);
		
		if (waitKey(10) == 27)
		{
			break; // escape
		}
	}
	return 0;
}

//GÖZ VE YÜZ TANIMA
void detectAndDisplay(Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Yüzleri algıla
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);
	for (size_t i = 0; i < faces.size(); i++)//yüz tanıma
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);//YÜZ DAİRE BOYUT KONUMU
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 255, 255), 2);//YÜZ DAİRE RENK BOYUT VS.
		Mat faceROI = frame_gray(faces[i]);


		//-- Her yüzde, gözleri tanıma
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale(faceROI, eyes);
		for (size_t j = 0; j < eyes.size(); j++) //göz tanıma
		{
			
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height) * 0.20);
			circle(frame, eye_center, radius, Scalar(0, 255, 0), 2); //daire çizme
		}
	}
	//-- neye sahip olduğunu göster
	imshow("Capture - Face detection", frame);
}

*/
//YÜZ TANIMA KAYIT ETME-3



/*#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>
using namespace cv;
using namespace std;
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int main()
{


	VideoCapture webcam(0);
	if (!webcam.isOpened()) {
		//error in opening the video input

		return 0;
	}




	CascadeClassifier yuz;


	vector<Rect> yuz_tanima;
	vector<Rect> goz_tanima;
	yuz.load("haarcascade_frontalface_default.xml");
	stringstream fpsdeğeri;

	int sayi = 0;
	double fps;


	if (!webcam.isOpened()) {
		cout << "Webcam bulunamadı.";
		return -1;
	}
	int i = 0;
	while (true)
	{
		Mat okuma,islenmis;
		Mat gri;

		webcam.read(okuma);

		string yazdir = to_string(sayi);

		cvtColor(okuma, okuma, COLOR_BGR2GRAY);
		//threshold(okuma, okuma, 180, 255, THRESH_BINARY);
		yuz.detectMultiScale(okuma, yuz_tanima);
		//imshow("video", okuma);
		if (waitKey(20) == 27)break;

			for (int i = 0; i < yuz_tanima.size(); i++)
			{
				if (webcam.grab())
				{
					webcam.retrieve(okuma);





					Mat imgCrop = okuma(yuz_tanima[i]);
					rectangle(okuma, yuz_tanima[i], Scalar(255, 0, 0), 2);
					imwrite("Plates/" + to_string(i) + " İzinsiz Plaka " + ".png", imgCrop);
					for (int j = 0; j < yazdir.size(); j++)
					{
						rectangle(okuma, cv::Point(10, 2), cv::Point(110, 20), cv::Scalar(255, 255, 255), -1);
						putText(okuma, yazdir, Point(10, 15), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 0, 255), 2);
					}
					sayi++;






					string frameNumberString = "TRUE";
					putText(okuma, frameNumberString, cv::Point(50, 15), FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0));
				}


			}


		imshow("aa", okuma);

	}

}
*/


//YÜZ TANIMA KAYIT ETME-2
/*


#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int main()
{


	VideoCapture webcam(0);
	if (!webcam.isOpened()) {
		//error in opening the video input

		return 0;
	}




	CascadeClassifier yuz;


	vector<Rect> yuz_tanima;
	vector<Rect> goz_tanima;
	yuz.load("haarcascade_frontalface_default.xml");
	stringstream fpsdeğeri;

	int sayi = 0;
	double fps;


	if (!webcam.isOpened()) {
		cout << "Webcam bulunamadı.";
		return -1;
	}
	int i = 0;
	while (true)
	{
		Mat okuma,islenmis;
		Mat gri;

		webcam.read(okuma);

		string yazdir = to_string(sayi);

		cvtColor(okuma, okuma, COLOR_BGR2GRAY);
		//threshold(okuma, okuma, 180, 255, THRESH_BINARY);
		yuz.detectMultiScale(okuma, yuz_tanima);
		//imshow("video", okuma);
		if (waitKey(20) == 27)break;

			for (int i = 0; i < yuz_tanima.size(); i++)
			{
				if (webcam.grab())
				{
					webcam.retrieve(okuma);





					Mat imgCrop = okuma(yuz_tanima[i]);
					rectangle(okuma, yuz_tanima[i], Scalar(255, 0, 0), 2);
					imwrite("Plates/" + to_string(i) + " İzinsiz Plaka " + ".png", imgCrop);



				}
				for (int j = 0; j < yazdir.size(); j++)
				{
					putText(okuma, yazdir, Point(10, 15), FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 0, 255), 2);
				}
				sayi++;

			}


		imshow("aa", okuma);

	}

}


*/

 
//YÜZ TANIMA 
/*
int main()
{
	CascadeClassifier yuz;

	vector<Rect> yuz_tanima;
	yuz.load("haarcascade_frontalface_default.xml");
	Mat resim = imread("yuzben.jpeg");
	resize(resim, resim, Size(500, 700));
	Mat gri;
	cvtColor(resim, gri, COLOR_BGR2GRAY);
	yuz.detectMultiScale(gri, yuz_tanima);
	for (int i = 0; i < yuz_tanima.size(); i++)
	{
		rectangle(resim, yuz_tanima[i], Scalar(255, 0, 0), 3);
	}
	Mat papagan = imread("bahar.jpg");
	resize(papagan, papagan, Size(700, 700));

	imshow("ekran2", papagan);
	imshow("ekran", resim);
	waitKey(0);
}
*/





//VİDEO ŞERİT TAKİBİ


/*
Point2f noktalar[] = { Point2f(502, 533),Point2f(830, 533), Point2f(1162, 660), Point2f(245, 660) };//KORDİNATLAR
Point2f donusum[] = { Point2f(0,0),Point2f(600,0),Point2f(640,480),Point2f(0,480) };//KUŞ BAKIŞI KORDİNATLARI
vector<int> serit; //noktalar
Mat ilgili_bolge;
Mat sonuc;
int sol_konum, sag_konum;
int pid;
void renk_donusumu(Mat giris) //BINARY DÖNÜŞTÜRME İŞLEMİ
{
	Mat cikis;

	cvtColor(giris, giris, COLOR_BGR2GRAY);//binary için gray yapma
	threshold(giris, cikis, 140, 255, THRESH_BINARY);//binary işlemi
	Canny(giris, giris, 70, 175); //kenar tespiti
	add(giris, cikis, sonuc);//binary+canny birleştirme
	imshow("sonuc", sonuc);
}
void serit_bul()
{
	serit.resize(640);
	serit.clear();//diğer şeritleri bulabilmek için
	for (int i = 0; i < 640; i++)
	{
		ilgili_bolge = sonuc(Rect(i, 150, 1, 100));
		divide(255, ilgili_bolge, ilgili_bolge);
		serit.push_back((int)(sum(ilgili_bolge)[0]));//vector değer atama
	}
}
void serit_goster(Mat son)
{
	vector<int>::iterator sol;
	sol = max_element(serit.begin(), serit.begin() + 150);
	sol_konum = distance(serit.begin(), sol);

	vector<int>::iterator sag;
	sag = max_element(serit.begin() + 350, serit.end());
	sag_konum = distance(serit.begin(), sag);
	line(son, Point(sol_konum, 0), Point(sol_konum, 480), Scalar(0, 156, 157), 3);
	line(son, Point(sag_konum, 0), Point(sag_konum, 480), Scalar(0, 156, 157), 3);
	cout << "sag serit:" << sag_konum << endl; cout << "sol konum :" << sol_konum << endl;
	//imshow("serittest", son);
}

void seri_merkez_bul(Mat son)
{
	int kalibre = son.cols / 2 - 10;
	int serit_merkez = (sag_konum - sol_konum) / 2 + sol_konum;

	pid = serit_merkez - kalibre;

	line(son, Point(serit_merkez, 0), Point(serit_merkez, 480), Scalar(0, 0, 255), 5);
	line(son, Point(kalibre, 0), Point(kalibre, 480), Scalar(255, 0, 0), 3);
	imshow("serittest", son);
}
int main()
{

	//Mat resim = imread("serityol.jpg");
	VideoCapture serit("seritTakip.mp4");
	if (!serit.isOpened()) cout << "SERİT BULMA HATALI";
	else
	{
		while (true)
		{
			Mat oku;
			serit.read(oku);
			Mat pers = getPerspectiveTransform(noktalar, donusum);//KUS BAKIŞI
			Mat son(480, 640, CV_8UC3);
			warpPerspective(oku, son, pers, son.size());
			renk_donusumu(son);
			serit_bul();
			serit_goster(son);
			seri_merkez_bul(son);
			stringstream yazi;
			yazi.str(" ");
			yazi.clear();
			yazi << "PID Deger :" << pid;
			putText(oku, yazi.str(), Point(150, 150), FONT_HERSHEY_TRIPLEX, 2, Scalar(0, 125, 241), 3);

			imshow("seritt", son);
			imshow("orijinal", oku);
			if (waitKey(50) == 32)break;
		}
	}
}

*/

					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
					 
				 //RESİM ŞERİT BULMA
/*
Point2f noktalar[] = { Point2f(550, 526),Point2f(755, 526), Point2f(937, 630), Point2f(381, 630) };//KORDİNATLAR
Point2f donusum[] = { Point2f(0,0),Point2f(640,0),Point2f(640,480),Point2f(0,480) };//KUŞ BAKIŞI KORDİNATLARI
vector<int> serit; //noktalar
Mat ilgili_bolge;
Mat sonuc;
int sol_konum, sag_konum;
int pid;
void renk_donusumu(Mat giris) //BINARY DÖNÜŞTÜRME İŞLEMİ
{
	Mat cikis;

	cvtColor(giris, giris, COLOR_BGR2GRAY);//binary için gray yapma
	threshold(giris, cikis, 120, 255, THRESH_BINARY);//binary işlemi
	Canny(giris, giris, 150, 255); //kenar tespiti
	add(giris, cikis, sonuc);//binary+canny birleştirme
	imshow("sonuc", sonuc);
}
void serit_bul()
{
	serit.resize(640);
	serit.clear();//diğer şeritleri bulabilmek için
	for (int i = 0; i < 640; i++)
	{
		ilgili_bolge = sonuc(Rect(i, 150,1,100));
		divide(255, ilgili_bolge, ilgili_bolge);
		serit.push_back((int)(sum(ilgili_bolge)[0]));//vector değer atama
	}
}
void serit_goster(Mat son)
{
	vector<int>::iterator sol;
	sol = max_element(serit.begin(), serit.begin() + 150);
	sol_konum = distance(serit.begin(), sol);

	vector<int>::iterator sag;
	sag = max_element(serit.begin()+350 , serit.end());
	sag_konum = distance(serit.begin(), sag);
	line(son, Point(sol_konum, 0), Point(sol_konum, 480), Scalar(0, 156, 157), 3);
	line(son, Point(sag_konum, 0), Point(sag_konum, 480), Scalar(0, 156, 157), 3);
	cout << "sag serit:" << sag_konum << endl; cout << "sol konum :" << sol_konum << endl;
	//imshow("serittest", son);
}

void seri_merkez_bul(Mat son)
{
	int kalibre = son.cols / 2 -10;
	int serit_merkez = (sag_konum - sol_konum) / 2 + sol_konum;

	pid = serit_merkez - kalibre;

	line(son, Point(serit_merkez, 0), Point(serit_merkez, 480), Scalar(0, 0, 255), 5);
	line(son, Point(kalibre,0), Point(kalibre, 480), Scalar(255, 0, 0), 3);
	imshow("serittest", son);
}
int main()
{

	Mat resim = imread("yolresmi.png");
	Mat pers = getPerspectiveTransform(noktalar, donusum);//KUS BAKIŞI
	Mat son(480, 640, CV_8UC3);

	warpPerspective(resim, son, pers, son.size());
	renk_donusumu(son);
	serit_bul();
	serit_goster(son);
	seri_merkez_bul(son);
	stringstream yazi;
	yazi.str(" ");
	yazi.clear();
	yazi << "PID Deger :" << pid;
	putText(resim, yazi.str(), Point(150, 150), FONT_HERSHEY_TRIPLEX, 2, Scalar(0, 125, 241), 3);
	imshow("serit", son);
	imshow("orijinal", resim);
	waitKey(0);


}
*/









//ŞERİT KUŞ BAKIŞI İŞLEM YAPMA PART-2 + KENAR TESPİTİ


/*
Point2f noktalar[] = { Point2f(335,335),Point2f(820,330),Point2f(1100,470),Point2f(30,470) }; //yol noktaları
Point2f donusum[] = { Point2f(0,0),Point2f(640,0),Point2f(640,480),Point2f(0,480) };//kuş bakışı
void renk_donusumu(Mat giris) //BINARY DÖNÜŞTÜRME İŞLEMİ
{
	Mat cikis;
	Mat sonuc;
	cvtColor(giris, giris, COLOR_BGR2GRAY);//binary için gray yapma
	threshold(giris, cikis, 120, 255, THRESH_BINARY);//binary işlemi
	Canny(giris, giris, 150, 255); //kenar tespiti
	add(giris, cikis, sonuc);//binary+canny birleştirme
	imshow("sonuc", sonuc);
}
int main()
{

	Mat resim = imread("yoll.jpg");
	Mat pers = getPerspectiveTransform(noktalar, donusum);//KUS BAKIŞI
	Mat son(480, 640, CV_8UC3);

	warpPerspective(resim, son, pers, son.size());
	renk_donusumu(son);

	imshow("serit", son);
	imshow("orijinal", resim);
	waitKey(0);

}
*/




//ŞERİT KUŞ BAKIŞI İŞLEM YAPMA PART-1
/*
Point2f noktalar[] = { Point2f(335,335),Point2f(820,330),Point2f(1100,470),Point2f(30,470) }; //yol noktaları
Point2f donusum[] = { Point2f(0,0),Point2f(640,0),Point2f(640,480),Point2f(0,480)};//kuş bakışı
void renk_donusumu(Mat giris) //BINARY DÖNÜŞTÜRME İŞLEMİ
{
	cvtColor(giris, giris, COLOR_BGR2GRAY);
	threshold(giris, giris, 150, 255, THRESH_BINARY);
	imshow("BINARY", giris);
}
int main()
{

	Mat resim = imread("yoll.jpg");
	Mat pers = getPerspectiveTransform(noktalar, donusum);//KUS BAKIŞI
	Mat son(480, 640, CV_8UC3);

	warpPerspective(resim, son, pers, son.size());
	renk_donusumu(son);

	imshow("serit",son);
	imshow("orijinal", resim);
	waitKey(0);
}

*/






//RESİM 360 DERECE SÜREKLİ DÖNDÜRME

/*
int main()
{
	Mat resim = imread("resim.jpg");
	resize(resim, resim, Size(500, 350));
	Mat cikis;
	Point2f kordinat(resim.rows / 2, resim.cols / 2); //Kordinatlar
	int aci = 0;

	while (1)
	{
		if (aci == 360)aci == 0;
		cout << "ACI :" << aci<<endl;

		Mat dondurme = getRotationMatrix2D(kordinat, aci, 1); //Döndürme kordinat 30 derce döndürme ölçeklendirme 14
		Rect2f kutu = RotatedRect(Point2f(), resim.size(), aci).boundingRect2f(); // sınırları çevreleyecek dikdörtgen

		dondurme.at<double>(0, 2) += kutu.width / 2 - resim.cols / 2; //genişlik x
		dondurme.at<double>(1, 2) += kutu.height / 2 - resim.rows / 2; //yükseklik y
		//AFİN GEOMETRİSİ
		warpAffine(resim, cikis, dondurme, kutu.size()); //Döndürme işlemi.

		imshow("orijinal", resim);
		imshow("dondurulmus", cikis);
		waitKey(10);
		aci += 1;
	}
}
*/





//GÖRÜNTÜSÜ YARIM ÇIKAN RESİM DÜZELTEREK RESİM DÖNDÜRME
/*
int main()
{
	Mat resim = imread("resim.jpg");
	resize(resim, resim, Size(500, 350));
	Mat cikis;
	Point2f kordinat(resim.rows / 2, resim.cols / 2); //Kordinatlar
	Mat dondurme = getRotationMatrix2D(kordinat, 20, 1); //Döndürme kordinat 30 derce döndürme ölçeklendirme 14
	Rect2f kutu = RotatedRect(Point2f(), resim.size(), 20).boundingRect2f(); // sınırları çevreleyecek dikdörtgen

	dondurme.at<double>(0, 2) += kutu.width / 2 - resim.cols / 2; //genişlik x
	dondurme.at<double>(1, 2) += kutu.height / 2 - resim.rows / 2; //yükseklik y
	//AFİN GEOMETRİSİ
	warpAffine(resim, cikis, dondurme, kutu.size()); //Döndürme işlemi.

	imshow("orijinal", resim);
	imshow("dondurulmus", cikis);
	waitKey(0);


}

*/





//RESİM DÖNDÜRME
/*
int main()
{
	Mat resim = imread("resim.jpg");
	resize(resim, resim, Size(700, 500));
	Mat cikis;
	Point2f kordinat(resim.rows / 2, resim.cols / 2); //Kordinatlar
	Mat dondurme = getRotationMatrix2D(kordinat,30,1); //Döndürme kordinat 30 derce döndürme ölçeklendirme 1
	//AFİN GEOMETRİSİ
	warpAffine(resim, cikis, dondurme, resim.size()); //Döndürme işlemi.

	imshow("orijinal", resim);
	imshow("dondurulmus", cikis);
	waitKey(0);


}
*/

//PARA(DAİRE) TESPİT ETME
/*
int main()
{
	Mat resim = imread("tll.jpeg");
	Mat cikis;
	cvtColor(resim, cikis, COLOR_BGR2GRAY);

	const char* degerler[] = { "1 KRS","5 KRS","25 KRS","50 KRS","1 TL" };

	GaussianBlur(cikis, cikis, Size(3, 3), 1);//gürültü azaltma
	Canny(cikis, cikis, 10, 255);//Kenar tespiti boyut

	vector<Vec3f> cember_degerleri;
	HoughCircles(cikis, cember_degerleri, HOUGH_GRADIENT, 1,100);//çizgi tespiti için kullanılır
	for (int i = 0; i < cember_degerleri.size(); i++)
	{
		string degerlere_ulasma;
		Point merkez(cvRound(cember_degerleri[i][0]), cvRound(cember_degerleri[i][1]));//vektörün içerisindeki 0->x, 1->y, 2->yarıçap
		int yaricap = cvRound(cember_degerleri[i][2]);
		if (yaricap > 93)degerlere_ulasma = degerler[4];
		else if(yaricap>85)degerlere_ulasma = degerler[3];
		circle(resim, merkez, yaricap, Scalar(125, 50, 179), 3);//daire çizdirme
		putText(resim, degerlere_ulasma, Point(cvRound(cember_degerleri[i][0]-40), cvRound(cember_degerleri[i][1])+10),FONT_HERSHEY_TRIPLEX,1,Scalar::all(0),1);

	}
	imshow("son Hal", resim);
	imshow("işlemler", cikis);

	waitKey(0);
}

*/
//ÇİZGİ TESPİT NASIL YAPILIR
/*
int main()
{
	Mat resim = imread("dikdortgen.jpg", IMREAD_GRAYSCALE);
	resize(resim, resim, Size(700, 500));
	Canny(resim, resim, 200, 255); //KENAR TESPİT threshold da kullanılabilir.

	vector<Vec4i> tespit; //4 tane
	HoughLinesP(resim, tespit, 1, CV_PI / 180, 10, 100, 10); // TESPİT İŞLEMİ TANIMI
	cvtColor(resim, resim, COLOR_GRAY2BGR);
	for (int i = 0; i < tespit.size(); i++) //TESPİT İŞLEMİ
	{
		line(resim, Point(tespit[i][0], tespit[i][1]), Point(tespit[i][2], tespit[i][3]), Scalar(155, 10, 210), 1);
		cout << "Çizgi bulundu!" << endl;
		waitKey(1000);
		imshow("bulundu", resim);
		waitKey(2000);
		destroyWindow("bulundu");
	}
	imshow("son Hal", resim);
	waitKey(0);
}
*/

//KAHVE ÇEKİRDEĞİ SAYMA
/*
int main()
{
	Mat kahve = imread("kahve.jpg", IMREAD_GRAYSCALE);
	resize(kahve, kahve, Size(700, 500));
	threshold(kahve, kahve, 111, 255, THRESH_BINARY_INV);
	vector<vector<Point>> kontur;
	vector<Vec4i> hiyerarsi;
	findContours(kahve, kontur, hiyerarsi, RETR_EXTERNAL, CHAIN_APPROX_NONE); //konturları bulma
	RotatedRect dik;
	for (int i = 0; i < kontur.size(); i++) //kontur çevreleme
	{
		drawContours(kahve, kontur, i, Scalar(0, 0, 0), 2);
		dik = minAreaRect(kontur[i]);
		putText(kahve, format("%d", i+1), dik.center, FONT_HERSHEY_TRIPLEX, 1, Scalar::all(0), 2);
		cout << "KAHVE" << endl;
		waitKey(100);

	}
	imshow("binary", kahve);

	waitKey(0);


}
*/

//KONTURLAMA VE HATLARI BELLİ ETMEK
/*
int main()
{
	Mat resim = imread("elma.jpg", IMREAD_GRAYSCALE);
	resize(resim, resim,Size(700,500));
	threshold(resim, resim, 180, 255, THRESH_BINARY_INV);
	vector<vector<Point>> konturlama;
	vector<Vec4i> m;
	findContours(resim, konturlama, m, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	Mat cikis = Mat::zeros(resim.size(),CV_8UC3);
	for (int i = 0; i < konturlama.size(); i++)
	{
		drawContours(cikis, konturlama, i, Scalar(0, 125, 159), 3);
	}
	imshow("binary", resim);
	imshow("konturlu", cikis);
	waitKey(0);


 }
*/

















//DAİRE OLUŞTURMA
/*
int main()
{

	RNG& deger = theRNG();
	Mat goruntu(700, 700, CV_8UC3, Scalar::all(0)); //matris 3 kanal 8 bit


	for (;;)
	{
		int sayi = deger.uniform(1, 150);
		vector<Point> noktalar; //nokta göstermek için
		for (int i = 0; i < sayi; i++) //noktaları koyma
		{
			Point nokta; //satır ve sütun belirtmek için
			nokta.x = deger.uniform(goruntu.cols / 4, goruntu.cols * 3 / 4);
			nokta.y = deger.uniform(goruntu.rows / 4, goruntu.rows * 3 / 4);
			noktalar.push_back(nokta);//noktaları atama
		}
		//DİKDÖRTGEN İÇİN TANIMLAMALAR
		//**********************************
		Point2f nok[4];
		RotatedRect dik = minAreaRect(noktalar); //NOKTALAR ÜZERİNDE MİNİMUM ALAN BULMA
		dik.points(nok);
		//***********************************


		//ÜÇGEN İÇİN TANIMLAMALAR
		//**********************************
		vector < Point2f > uc;
		minEnclosingTriangle(noktalar, uc);
		//************************************


		//DAİRE İÇİN TANIMLAMALAR
		//**********************************
		Point2f merkez;
		float yaricap = 0;
		minEnclosingCircle(noktalar, merkez, yaricap);
		//************************************



		for (int j = 0; j < sayi; j++)circle(goruntu, noktalar[j], 1, Scalar::all(175), 2);//Daire oluşturma

		for (int i = 0; i < 4; i++)//DİKDÖRTGEN İÇİN DOĞRU PARÇASI ÇİZME
		{
			line(goruntu, nok[i], nok[(i + 1) % 4], Scalar(255, 0, 0), 2, 8);
		}
		for (int i = 0; i < 3; i++)//ÜÇGEN İÇİN DOĞRU PARÇASI
		{
			line(goruntu, uc[i], uc[(i + 1) % 3], Scalar(100, 200), 3, 8);
		}
		//cvRaund() floatı en yakın int dönüştürür.
		circle(goruntu, merkez, cvRound(yaricap), Scalar(0, 0, 2550, 3));


		imshow("noktalar", goruntu);
		cout << sayi << endl;
		waitKey(0);
		goruntu = Scalar::all(0);
	}

}

*/










//ÜÇGEN VE DİKDÖRTGEN ÇİZME
/*
int main()
{

	RNG& deger = theRNG();
	Mat goruntu(700, 700, CV_8UC3, Scalar::all(0)); //matris 3 kanal 8 bit


	for (;;)
	{
		int sayi = deger.uniform(1, 150);
		vector<Point> noktalar; //nokta göstermek için
		for (int i = 0; i < sayi; i++) //noktaları koyma
		{
			Point nokta; //satır ve sütun belirtmek için
			nokta.x = deger.uniform(goruntu.cols / 4, goruntu.cols * 3 / 4);
			nokta.y = deger.uniform(goruntu.rows / 4, goruntu.rows * 3 / 4);
			noktalar.push_back(nokta);//noktaları atama
		}
		//DİKDÖRTGEN İÇİN TANIMLAMALAR
		//**********************************
Point2f nok[4];
RotatedRect dik = minAreaRect(noktalar); //NOKTALAR ÜZERİNDE MİNİMUM ALAN BULMA
dik.points(nok);
//***********************************


//ÜÇGEN İÇİN TANIMLAMALAR
//**********************************
vector < Point2f > uc;
minEnclosingTriangle(noktalar, uc);
//************************************
for (int j = 0; j < sayi; j++)circle(goruntu, noktalar[j], 1, Scalar::all(175), 2);//Daire oluşturma

for (int i = 0; i < 4; i++)//DİKDÖRTGEN İÇİN DOĞRU PARÇASI ÇİZME
{
	line(goruntu, nok[i], nok[(i + 1) % 4], Scalar(255, 0, 0), 2, 8);
}
for (int i = 0; i < 3; i++)//ÜÇGEN İÇİN DOĞRU PARÇASI
{
	line(goruntu, uc[i], uc[(i + 1) % 3], Scalar(100, 200), 3, 8);
}

imshow("noktalar", goruntu);
cout << sayi << endl;
waitKey(0);
goruntu = Scalar::all(0);
	}

}

*/





//DİKDÖRTGEN ÇİZDİRME
/*
int main()
{

	RNG& deger = theRNG();
	Mat goruntu(700, 700, CV_8UC3, Scalar::all(0)); //matris 3 kanal 8 bit


	for (;;)
	{
		int sayi = deger.uniform(1, 150);
		vector<Point> noktalar; //nokta göstermek için
		for (int i = 0; i < sayi; i++) //noktaları koyma
		{
			Point nokta; //satır ve sütun belirtmek için
			nokta.x = deger.uniform(goruntu.cols / 4, goruntu.cols * 3 / 4);
			nokta.y = deger.uniform(goruntu.rows / 4, goruntu.rows * 3 / 4);
			noktalar.push_back(nokta);//noktaları atama
		}
		//DİKDÖRTGEN
		Point2f nok[4];
		RotatedRect dik = minAreaRect(noktalar); //NOKTALAR ÜZERİNDE MİNİMUM ALAN BULMA
		dik.points(nok);



		for (int j = 0; j < sayi; j++)circle(goruntu, noktalar[j], 1, Scalar::all(175), 2);//Daire oluşturma

		for (int i = 0; i < 4; i++)
		{
			line(goruntu, nok[i], nok[(i + 1) % 4],Scalar(255,0,0),2,8);
		}


		imshow("noktalar", goruntu);
		cout << sayi << endl;
		waitKey(0);
		goruntu = Scalar::all(0);
	}

}
*/




// RASTGELE NOKTA ÜRETME
/*
int main()
{

	RNG& deger = theRNG();
	Mat goruntu(700, 700, CV_8UC3, Scalar::all(0)); //matris 3 kanal 8 bit


	for (;;)
	{
		int sayi = deger.uniform(1, 150);
		vector<Point> noktalar; //nokta göstermek için
		for (int i = 0; i < sayi; i++) //noktaları koyma
		{
			Point nokta; //satır ve sütun belirtmek için
			nokta.x = deger.uniform(goruntu.cols / 4, goruntu.cols * 3 / 4);
			nokta.y = deger.uniform(goruntu.rows / 4, goruntu.rows * 3 / 4);
			noktalar.push_back(nokta);//noktaları atama
		}
		for (int j = 0; j < sayi; j++)circle(goruntu, noktalar[j], 1, Scalar::all(175), 2);//Daire oluşturma

		imshow("noktalar", goruntu);
		cout << sayi << endl;
		waitKey(0);
		goruntu = Scalar::all(0);
	}

}

*/





//RNG RASTGELE SAYİ YAZDIRMA
/*
int main()
{

	RNG& sayi = theRNG();

	for (;;)
	{
		int deger = sayi.uniform(1, 150);
		cout << deger << endl;
		waitKey(100);
	}

}
*/




























//HİSTOGRAM EŞİTLEMESİ RENKLİ RESİM
/*
Mat resim;
void renkliHistogram()
{
	resim = imread("rbg.png");//RESİM
	Mat donusum, cikis;
	cvtColor(resim, donusum, COLOR_BGR2YCrCb);
	vector<Mat> ayirma;
	split(donusum, ayirma);
	equalizeHist(ayirma[0], ayirma[0]);
	merge(ayirma, cikis);
	cvtColor(cikis, cikis, COLOR_YCrCb2BGR);
	imshow("sonhal", cikis);
}
int main()
{
	resim = imread("rbg.png");
	imshow("orijinal", resim);
	renkliHistogram();
	waitKey(0);
}
*/










//HİSTOGRAM RENK   SPLİT(AYIRMAK) VE MERGE(BİRLEŞTİRMEK)
/*
int main()
{
	Mat resim = imread("rbg.png");//RESİM
	imshow("resim",resim); //RESMİ GÖSTER
	Mat bgr[3]; //RESİM RENKLERİ MAVİ,YESİL,KİRMİZİ
	split(resim, bgr);//RESİMİ RENKLERE AYIRMAK İÇİN bgr ATIYORUZ
	imshow("mavi",bgr[0]);
	imshow("yesil", bgr[1]);
	imshow("kirmizi", bgr[2]);
	vector<Mat> birlesim;//TEKRAR  BİRLEŞTİRMEK İÇİN VECTOR KULLANIYORUZ.
	birlesim.push_back(bgr[0]);//PUSH_BACK ATIYORUZ.
	birlesim.push_back(bgr[1]);//PUSH_BACK ATIYORUZ.
	birlesim.push_back(bgr[2]);//PUSH_BACK ATIYORUZ.
	Mat cikis;
	merge(birlesim, cikis); //MERGE İLE BİRLEŞTİRİYORUZ.
	imshow("sonhal", cikis);
	waitKey(0);

}

*/















//HİSTOGRAM EŞİTLEMESİ
/*
int main()
{
	Mat esit_histogram;
	Mat resim = imread("resim.jpg");

	resize(resim, resim, Size(700, 500));
	cvtColor(resim, resim, COLOR_BGR2GRAY);

	string pencere_bir = "once";
	string pencere_iki = "sonra";

	namedWindow(pencere_bir, WINDOW_AUTOSIZE);
	namedWindow(pencere_iki, WINDOW_AUTOSIZE);

	equalizeHist(resim, esit_histogram);

	imshow(pencere_bir, resim);
	imshow(pencere_iki, esit_histogram);
	waitKey(0);
}
*/











//HİSTOGRAM[0,255]
/*
int degerler[255];
int main()
{

	Mat resim=imread("resim.jpg");
	resize(resim, resim, Size(700, 500));
	Mat griResim;
	cvtColor(resim, griResim, COLOR_BGR2GRAY);

	for (int i = 0; i < griResim.rows; i++) //satır
	{

		for (int j = 0; j < griResim.cols; j++) //sütun
		{
			for (int n = 0; n < 255; n++) //değer döndürme
			{
				if (griResim.at<uchar>(i, j) == n)degerler[n] += 1;

			}
		}

	}

	int ali = 0;
	while (ali<255) //indisi yansıtma
	{
		cout << ali << ". indisi= " << degerler[ali] << endl;
		ali += 1;
	}
	imshow("Gri", griResim);
	waitKey(0);
}

*/





















//VEKTOR SWAP(TAKAS) İŞLEMİ
/*
int main()
{
	vector<int> vektor1{ 2,4,6 };
	vector<int> vektor2{ 1,3,5,7,9 };
	vektor1.swap(vektor2);
	cout << "vektor1 =";
	for (int i = 0; i < vektor1.size(); i++)
	{
		cout << " " << vektor1[i];
	}
	cout << endl;
	cout << "vektor2 =";
	for (int j = 0; j < vektor2.size(); j++)
	{
		cout << " " << vektor2[j];
	}
}

*/











//VECTOR İNT TEK SAYILARI EKRANA YAZDIRMA.
/*
int main()
{
	vector<int> sayilar{ 1,2,3,4,5,6,7,8,9,10 };
	//cout << sayilar.at(2);
	for (int i = 0; i < sayilar.size(); i+=2)
	{
		cout << sayilar.at(i)<<endl;
	}

}
*/


















//VECTOR STRİNG EKRANA YAZDIRMA.
/*
int main()
{
	vector<string> isimler{ "furkan","firdevs","eren","yagmur" };
	for (auto i = isimler.begin(); i < isimler.end(); i++)
	{
		cout << *i << endl;
	}
}
*/
















//ERASE BEGİN DEN END E HEPSİNİ SİLME.
/*
int main()
{
	vector<int> ali(10);
	ali.erase(ali.begin()+5, ali.end());//+5 EKLERSEN 5 TANE SİLMEZ.
	cout << ali.size() << endl;
}

*/



//PUSH_BACK() VE POP_BACK()
/*
int main()
{
	vector<int> ali(10);
	ali.push_back(80);
	cout << ali.back()<<endl;
	cout << ali.size() << endl;
	ali.pop_back(); //push_bak ile yazılanı silme.
	cout << ali.back() << endl;
	cout << ali.size() << endl;
}


*/


/*
//vector<degisken_tipi> vector_isim; 
//vector<degisken_tipi> vector_isim(eleman);
//vector<degisken_tipi> vector_isim(Adet,değer);
//vector<degisken_tipi> vector_isimfarkli(vec_isim);

int main()
{
	vector<int> ali;
	ali.insert(ali.begin(), 12);
	ali.insert(ali.end(),52);
	cout << ali.size()<<endl;
	//begin ve end iteratördür pointer dir. * koy
	cout << *ali.begin()<<endl;
	cout << ali.back();
}
*/






//KENAR BULMA + BINNARY KULLANIMI
/*
int main()
{
		Mat once, sonra;
		once = imread("yol.jpeg");
		cvtColor(once, sonra, COLOR_BGR2GRAY);

		Mat binary;
		threshold(sonra, binary, 150, 255, THRESH_BINARY);
		imshow("binary", binary);
		Canny(sonra, sonra, 70, 170);

		Mat son;
		add(binary, sonra, son);
		imshow("sonra", sonra);
		imshow("son", son);
		waitKey(0);
}

*/








//KENAR TESPİTİ
/*
int main()
{
	Mat once, sonra;
	once = imread("yol.jpeg");
	cvtColor(once, sonra, COLOR_BGR2GRAY);
	Canny(sonra, sonra, 70, 170);
	imshow("once", once);
	imshow("sonra", sonra);
	waitKey(0);

}
*/



//LATERAL GÖRÜNTÜ BİLATERALFİLTRE
/*
int main()
{
	Mat resim, gaus,bilateral;
	resim = imread("resim.jpg");
	resize(resim, resim, Size(700, 500));
	GaussianBlur(resim, gaus, Size(37, 37),1);
	bilateralFilter(resim, bilateral, 17, 80, 80);
	imshow("normal", resim);
	imshow("bilateral", bilateral);
	imshow("gaus", gaus);
	waitKey(0);
}
*/







//BULANIKLAŞTIRMA VE KARINCALANDIRMA GİDERME
/*
int main()
{

	Mat once, sonra;
	once = imread("resim.png");
	resize(once, once, Size(700, 500));
	GaussianBlur(once, sonra, Size(3, 3),3 );
	imshow("Gercek", once);
	imshow("Medyan", sonra);
	waitKey(0);
}


*/




//GÜRÜLTÜLÜ(KARINCALANMA) YOK ETME
/*
int main()
{

	Mat gercek, medyan;
	gercek = imread("resim.png");
	//resize(gercek, gercek, Size(700, 500));
	medianBlur(gercek, medyan, 3);
	imshow("Gercek", gercek);
	imshow("Medyan", medyan);
	waitKey(0);
}

*/










//BULANIKLAŞTIRMA
/*
int main()
{
	Mat normal, bulanık;
	normal = imread("resim.jpg");
	resize(normal, normal, Size(700, 500));
	blur(normal, bulanık, Size(7, 7));
	imshow("normal", normal);
	imshow("bulanık", bulanık);
	waitKey(0);
}

*/






















//TRACKBAR KULLANIMI.

/*
int a = 0;
int mavi, yesil, kirmizi;
void kirmiziRenk(int, void*)
{
	kirmizi++;
}
void maviRenk(int, void*)
{
	mavi++;
}
void yesilRenk(int, void*)
{
	yesil++;
}
void goster()
{
	namedWindow("Track", WINDOW_AUTOSIZE);
	createTrackbar("M", "Track", &mavi, 255,maviRenk);
	createTrackbar("K", "Track", &kirmizi, 255, kirmiziRenk);
	createTrackbar("Y", "Track", &yesil, 255, yesilRenk);

	Mat x(400, 400, CV_8UC3, Scalar(mavi, yesil, kirmizi));
	imshow("Goruntu", x);
}
void yenile(int, void*)
{
	cout << a << endl;
	if (a == 1) {
		goster();
	}
	else {
		destroyWindow("Goruntu");
	}
}
int main()
{

	namedWindow("Track", WINDOW_AUTOSIZE);
	createTrackbar("Trackbar", "Track", &a, 10, yenile);
	waitKey(0);
}
*/

	//YAZI HATLARINI BELİRGİNLEŞTİRME
/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;

	cvtColor(x, y, COLOR_BGR2GRAY);
	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme

	morphologyEx(z, z, MORPH_GRADIENT, getStructuringElement(MORPH_RECT, Size(2, 2)), Point(-1, -1), 1);

	imshow("BINARY", z);
	waitKey(0);
*/





	//AÇMADAN ORJİNAL ÇIKARMA -KAPAMADAN ORJİNAL ÇIKARMA

/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;

	cvtColor(x, y, COLOR_BGR2GRAY);
	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme
	//morphologyEx(z, z, MORPH_TOPHAT, getStructuringElement(MORPH_RECT, Size(20, 20)), Point(-1, -1), 1);
	morphologyEx(z, z, MORPH_BLACKHAT, getStructuringElement(MORPH_RECT, Size(20, 20)), Point(-1, -1), 1);

	imshow("BINARY", z);
	waitKey(0);


*/






	//AÇMA

	/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;
	
	cvtColor(x, y, COLOR_BGR2GRAY);
	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme
	morphologyEx(z, z, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(7, 7)), Point(-1, -1), 1);
	
	imshow("BINARY", z);
	waitKey(0);
	*/





	//ÖNCE YAYMA SONRA AŞINDIRMA 
	/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;

	cvtColor(x, y, COLOR_BGR2GRAY);

	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme

	morphologyEx(z, z, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)), Point(-1, -1), 1);

	imshow("BINARY", z);
	waitKey(0);

	*/








	//KAPAMA İŞLEMİ
	/*
	//ÖNCE YAYMA SONRA AŞINDIRMA 
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;

	cvtColor(x, y, COLOR_BGR2GRAY);

	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme
	
	morphologyEx(z, z, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE,Size(7, 7)), Point(-1, -1), 1);

	imshow("BINARY", z);
	waitKey(0);


	*/



	//YAYMA İŞLEMİ
	/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;

	cvtColor(x, y, COLOR_BGR2GRAY);

	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme
	dilate(z, z, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));//yayma işlemi
	//erode(z, z, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));//aşındırma
	imshow("BINARY", z);
	waitKey(0);
	*/





	//AŞINDIRMA YÖNTEMİ BEYAZLARI VS YOK EDEBİLİYORSUN
	/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;
	 
    cvtColor(x, y, COLOR_BGR2GRAY); 
	
	threshold(y, z, 190, 255, THRESH_BINARY);//BINARY çevirme
	erode(z, z, getStructuringElement(MORPH_RECT, Size(1, 1)));//aşındırma
	imshow("BINARY", z);
	waitKey(0);


	*/









	//BİNARY DÖNÜŞÜMÜ
	/*
	Mat x = imread("resim.jpg",IMREAD_GRAYSCALE);
	resize(x, x, Size(700, 500));

	inRange(x, Scalar(0), Scalar(150), x);
	imshow("Resim", x);
	waitKey(0);
	*/
















	//BİNARY DÖNÜŞÜMÜ
	/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	Mat y, z;
	cvtColor(x, y, COLOR_BGR2GRAY); //BINARY çevirme
	imshow("GRI", y);
	threshold(y, z, 100, 255,THRESH_BINARY);

	imshow("BINARY", z);
	waitKey(0);
	*/





















	//GORUNTUYU NEGATİF HALA DÖNÜŞTÜRME
/*
	Mat resim = imread("resim.jpg");
	resize(resim, resim, Size(700, 500));
	Mat sonHal;
	bitwise_not(resim, sonHal);
	imshow("orijinal :", resim);
	imshow("Negatif hal :", sonHal);
	waitKey(0);


*/




	//RGB FORMATTAKİ RENKLERE ULAŞMAK VE İŞLEMEK
/*
	Mat resim = imread("resim.jpg");
	resize(resim, resim, Size(700, 500));

	for (int i = 0; i < resim.rows; i++) {
		for (int j = 0; j < resim.cols; j++) {
			resim.at<Vec3b>(i, j)[0] = resim.at<Vec3b>(i, j)[0]+100;
			resim.at<Vec3b>(i, j)[1] = resim.at<Vec3b>(i, j)[1] ;
			resim.at<Vec3b>(i, j)[2] = resim.at<Vec3b>(i, j)[2] + 100;

		}
	}
	imshow("orijinal", resim);
	waitKey(0);

*/








	//GRİ FORMATDAKİ RESMİN YOĞUNLUK İŞLEMİ
/*

	Mat resim = imread("resim.jpg",IMREAD_GRAYSCALE);
	resize(resim, resim, Size(700, 500));
	Mat degisim= imread("resim.jpg", IMREAD_GRAYSCALE);
	resize(degisim, degisim, Size(700, 500));
	for (int i = 0; i < degisim.rows; i++) {
		for (int j=0; j < degisim.cols; j++) {
			degisim.at<uint8_t>(i, j)=degisim.at<uint8_t>(i,j)*2.5;
		}
	}
	imshow("orijinal", resim);
	imshow("Yogunluk", degisim);
	waitKey(0);
*/










	//MATRİS ÜZERİNDE ÖLÇEKLENDİRME İŞLEMİ (ones)
	/*
	Mat a;
	//a = Mat::eye(5, 5, CV_8UC1);
	a = Mat::eye(5, 5, CV_8UC1)*5;
	cout << "Mat x: " << endl << a ;

	*/

	
	//MATRİS ÜZERİNDE BİR DEĞERİ EKLEME İŞLEMİ (ones)
/*

	Mat y;
	y=Mat::ones(5, 5, CV_8UC1);
	cout << "Mat x: " << y << endl;
*/

	//MATRİS ÜZERİNDE SIFIRLAMA İŞLEMİ (zeros)
/*
	Mat x;
	x = Mat::zeros(5, 5, CV_8UC3);
	cout << "Mat x: " << x << endl;

*/







	//RESİM PİKSELİ İÇERİSİNDEKİ RENK YOĞUNLUĞU BULMA
/*
	Mat x = imread("resim.jpg");
	resize(x, x, Size(700, 500));
	double mavi = x.at<Vec3b>(12, 12)[0];
	double yesil = x.at<Vec3b>(12, 12)[1];
	double kirmizi = x.at<Vec3b>(12, 12)[2];

	cout <<"mavi" <<mavi<<endl;
	cout <<"yesil" <<yesil << endl;
	cout << "kirmizi"<<kirmizi << endl;

	imshow("Renkli", x);
	waitKey(0);
*/














	//RESİMDEKİ GRİ FORMATLI RESMİN RENK KODUNU GİREREK YOĞUNLUGUNA ULAŞMA
	/*
	Mat x = imread("resim.jpg");
	Mat y;
	cvtColor(x, y, COLOR_BGR2GRAY);
	double deger = y.at<uchar>(10, 205);
	cout << deger;
	resize(x, x, Size(700, 500));
	resize(y, y, Size(700, 500));
	imshow("RENK", y);
	imshow("Renkli", x);
	waitKey(0);

	*/













	//VİDEODA DEĞİŞKEN GÖSTERME VE DEĞERİNİ ANLIK ARTTIRMA
/*

	VideoCapture video("adana.mp4");
	stringstream fpsdeğeri;

	int sayi = 0;
	double fps;
	if (video.isOpened()) {

		while (1)
		{
			Mat y;
			video.read(y);
			string yazdir = "Sayinin degeri :" + to_string(sayi);
			putText(y,yazdir, Point(15, 50), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255), 2);


			if (waitKey(100) == 32) {
				break;
			}
			sayi++;
			imshow("video", y);
		}
	}

*/






	//FPS DEĞERİ PENCEREYE YAZDIRMA
	/*
	VideoCapture video("adana.mp4");
	stringstream fpsdeğeri;
	double fps;
	if (video.isOpened()) {

		while (1)
		{
			Mat y;
			video.read(y);
			fps = video.get(CAP_PROP_FPS);
			fpsdeğeri.str(" ");
			fpsdeğeri.clear();
			fpsdeğeri << "FPS: " << fps;
			putText(y, fpsdeğeri.str(), Point(15, 150), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255), 2);

			imshow("video", y);
			if (waitKey(100) == 32) {
				break;
			}
		}
	}
	*/



	





	//WEBCAM AÇMA
/*
	VideoCapture webcam(0);
	if (!webcam.isOpened()) {
		cout << "Webcam bulunamadı.";
		return -1;
	}
	while (true)
	{
		Mat okuma;
		 webcam.read(okuma);
		



		imshow("video", okuma);
		if (waitKey(20) == 27)break;
	}
*/












	//VİDEO OYNATMA
	/*
	VideoCapture video("adana.mp4");
	if (video.isOpened()) {
		
		while (1)
		{
			Mat x;
			video.read(x);
			imshow("video", x);
			if (waitKey(100) == 32) {
				break;
			}
		}
	}

	*/


	//RENK UZAY DEĞİŞİMİ
	/*
	Mat ali = imread("unnamed.jpg");
	Mat x;
	resize(ali, ali, Size(300, 300));
	cvtColor(ali, x, COLOR_BGR2HSV);
	imshow("ilk", ali);
	imshow("son", x);
	waitKey(0);

	*/







	//RESİM KALİTESİ DEĞİŞTİRME
/*

	Mat ali = imread("unnamed.jpg");
	resize(ali, ali, Size(300, 300));
	vector<int> kalite;
	kalite.push_back(IMWRITE_JPEG_LUMA_QUALITY);
	kalite.push_back(150);
	imwrite("unnamed.jpg", ali, kalite);
	waitKey(0);
*/














	//RESİM KALİTESİ DEĞİŞTİRME

/*
	Mat ali = imread("unnamed.jpg");
	resize(ali, ali, Size(300, 300));
	vector<int> kalite;
	kalite.push_back(IMWRITE_JPEG_LUMA_QUALITY);
	kalite.push_back(150);
	imwrite("unnamed.jpg", ali, kalite);
	waitKey(0);
*/








	//RESİM FORMATI DEĞİŞTİRME
	/*
		Mat ali = imread("unnamed.jpg");
	resize(ali, ali, Size(300, 300));
	imwrite("unnamed.bmp",ali); //resim formatı değiştirme
	waitKey(0);

	*/


	//RESİM EKLEME
/*
	Mat ali = imread("unnamed.jpg");
	resize(ali, ali, Size(300, 300)); 
	imshow("Resim", ali);
	waitKey(0);
*/







	//RANDU FONKSİYONU KARINCALI EKRAN YAPMA
	/*
	Mat ali(450, 450, CV_8UC3, Scalar(0, 0, 0)); // 450x250 matris ,8 bit 3 kanal , renk
	randu(ali, Scalar(0, 0, 0), Scalar(255, 255, 255));
	imshow("PENCERE", ali);
	waitKey(0);
	*/



	//MATRİS BOYUTLANDIRMA
	/*
	Mat x(450, 450, CV_8UC3, Scalar(0, 255, 0)); // 450x250 matris ,8 bit 3 kanal , renk
	resize(x, x, Size(300, 150));  //Boyut ayarlama
	imshow("x", x);
	waitKey(0);
	*/







	//ANİMASYON YAZI YAPMA
/*
	Mat x(450, 450, CV_8UC3, Scalar(0, 255, 0)); // 450x250 matris ,8 bit 3 kanal , renk
	Mat animasyon=x.clone();
	for (int i = 0; i < 250; i += 10) {

		putText(animasyon, "merhaba", Point(20+i, 50+i), FONT_HERSHEY_TRIPLEX, 2, Scalar(255, 0, 0), 2);

		waitKey(500);
		imshow("Animasyon", animasyon);

		animasyon = x.clone();
	}
	for (int i = 250; i > 0; i -= 10) {

		putText(animasyon, "merhaba", Point(20 + i, 50 + i), FONT_HERSHEY_TRIPLEX, 2, Scalar(255, 0, 0), 2);

		waitKey(500);
		imshow("Animasyon", animasyon);

		animasyon = x.clone();
	}
	*/



	
//=======================================================================



	//KOPYALAMA ATAMA İŞLEMLERİ

/*
	Mat goruntu(450, 450, CV_8UC3, Scalar(255, 0, 0)); // 450x250 matris ,8 bit 3 kanal , renk

	Mat y = goruntu.clone(); //yenini içine klonlama

	goruntu.copyTo(y);//Y nin içine kopyalama

	Mat y = goruntu; // y değerine eşitleyerek atama


	imshow("Y", y);
	waitKey(0);*/



//=======================================================================

	//MATRİS İÇİNDE BELİRLİ YERLERDE İŞLEM YAPMA
/*
Mat goruntu(450, 450, CV_8UC3, Scalar(255,0,0)); // 450x250 matris ,8 bit 3 kanal , renk

	//rowRange -> y ekseni
	//colRange -> x ekseni

	//goruntu.colRange(110, 150).setTo(CV_8UC1);  //x ekseninde başlangıç ve x son;
	//goruntu.colRange(110, 150).setTo(Scalar(0,0,255));

	//goruntu.rowRange(110, 150).setTo(CV_8UC1); y ekseninde başlangıç ve x son;
	//goruntu.rowRange(110, 150).setTo(Scalar(0, 0, 255));


	goruntu.rowRange(0, 150).setTo(Scalar(0, 0, 255));
	goruntu.rowRange(151, 300).setTo(Scalar(255, 255, 255));
	goruntu.rowRange(301, 450).setTo(Scalar(190, 0, 0));


	imshow("PENCERE", goruntu); // yansıtma
	waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler
*/




//=======================================================================





//RESİM SATIR VE SÜTUN BULMA

/*Mat goruntu(450, 250, CV_8UC3, Scalar(150, 210, 15)); // 450x250 matris ,8 bit 3 kanal , renk

cout <<"Satir sayisi :"<< goruntu.rows<<endl; //rows=Satır
cout << "Satir sayisi :" << goruntu.cols << endl; //cols=sütun

imshow("PENCERE", goruntu); // yansıtma
waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler
*/



//=======================================================================




//EKRANA YAZI YAZMA
/*
//YAZI STİLLERİ
//FONT_HERSHEY_SIMPLEX
//FONT_HERSHEY_PLAIN
//FONT_HERSHEY_DUPLEX
//FONT_ITALIC
//FONT_HERSHEY_SCRIPT_SIMPLEX

Mat goruntu(450, 450, CV_8UC3, Scalar(255, 0, 0)); // 450x450 matris ,8 bit 3 kanal , renk

putText(goruntu, "hello word",Point(120,150), FONT_HERSHEY_SCRIPT_SIMPLEX,2,Scalar(0,0,255),3); //Yazı yazdırma



imshow("PENCERE", goruntu); // yansıtma
waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler





*/



//=======================================================================



//DİKDÖRTGEN OLUŞTURMA
/*
Mat goruntu(450, 450, CV_8UC3, Scalar(255, 0, 0)); // 450x450 matris ,8 bit 3 kanal , renk

	Rect diktdortgen(150, 50, 145, 80);  //Dikdörtgen oluşturma x,y,genişlik,yükseklik

	rectangle(goruntu, diktdortgen, Scalar(0, 255, 0), 3);


	imshow("merhaba", goruntu); // yansıtma
	waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler
	*/


//=======================================================================


	//DAİRE OLUŞTURMA
/*
	Mat dogruparcasi(450, 450, CV_8UC3, Scalar(255, 0, 0)); // 450x450 matris ,8 bit 3 kanal , renk

	circle(dogruparcasi, Point(375, 390), 150, Scalar(0, 255, 0), 3);  //Daire oluşturma

	imshow("merhaba", dogruparcasi); // yansıtma
	waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler
	*/


//=======================================================================

	//DOĞRU PARÇASI
/*
	Mat dogruparcasi(450, 450, CV_8UC3, Scalar(255, 0, 0)); // 450x450 matris ,8 bit 3 kanal , renk
	line(dogruparcasi,Point(92,100),Point(410,400),Scalar(0,0,0),3);  //Doğru parçası çizimi ilk x,y sonra ikinci x,y

	imshow("merhaba", dogruparcasi); // yansıtma
	waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler

	cout << dogruparcasi;
	*/



//=======================================================================


	//MATRİS
/*
//Mat goruntu(450, 450, CV_8UC3, Scalar(0, 0, 255)); // 450x450 matris ,8 bit 3 kanal , renk
	Mat goruntu(4, 4, CV_8UC1,Scalar(150)); // 4x4 matris ,8 bit 1kanal , renk

	namedWindow("merhaba", WINDOW_AUTOSIZE); //PENCERE
	imshow("merhaba", goruntu); // yansıtma
	waitKey(0); // pencereyi kaç saniye kalması gerektiğini söyler

	cout << goruntu;

*/



