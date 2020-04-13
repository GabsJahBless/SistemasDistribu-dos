#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <locale.h>

using namespace std;
using namespace cv;
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 6;
Mat src; Mat dst;
char window_name[] = "Smoothing";
int display_caption(const char* caption);
int display_dst(int delay);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");
	int opc;
	namedWindow(window_name, WINDOW_AUTOSIZE);
	const char* filename = argc >= 2 ? argv[1] : "C:/opencv/sources/samples/data/lena.jpg";
	src = imread(filename, IMREAD_COLOR);
	if (src.empty())
	{
		printf(" Error opening image\n");
		printf(" Usage: ./Smoothing [image_name -- default ../data/lena.jpg] \n");
		return -1;
	}
	if (display_caption("Imagem Original") != 0)
	{
		return 0;
	}
	dst = src.clone();
	if (display_dst(DELAY_CAPTION) != 0)
	{
		return 0;
	}

	printf("ESCOLHA UMA OPÇÃO:\n");
	printf("1 - Média\n");
	printf("2 - Mediana\n");
	printf("Digite um número das opções: ");
	scanf_s("%d", &opc);

	if (opc == 1) {
		if (display_caption("Media Blur") != 0)
		{
			return 0;
		}
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			//printf("%d", i);
			blur(src, dst, Size(i, i), Point(-1, -1));
			if (display_dst(DELAY_BLUR) != 0)
			{
				break;
			}
		}
	}

	else {
		if (display_caption("Mediana Blur") != 0)
		{
			return 0;
		}
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			medianBlur(src, dst, i);
			if (display_dst(DELAY_BLUR) != 0)
			{
				break;
			}
		}
	}
	system("pause");
	return 0;
}

int display_caption(const char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	return display_dst(DELAY_CAPTION);
}
int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}
