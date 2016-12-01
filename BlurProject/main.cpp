#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int main()
{

	//ifstream file("roller1.raw");
	ifstream file("roller1.raw", std::ios::binary | std::ios::ate);
	ofstream outputFile("roller2.raw", std::ios::binary | std::ios::out);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	char* inBuffer = new char[size];
	char* outBuffer = new char[size];
	if (file.read(inBuffer, size))
	{
	}
	file.close();
	const int WIDTH = 251;
	const int HEIGHT = 256;
	int image[HEIGHT][WIDTH];
	int output[HEIGHT][WIDTH];
	int iterations = 0;
	int i = 0;
	int charCode = 0;
	for (int bufferIndex = 0; bufferIndex < size; bufferIndex++)
	{
		outBuffer[bufferIndex] = inBuffer[bufferIndex];
		/*if (bufferIndex < WIDTH || bufferIndex > WIDTH * HEIGHT - WIDTH || bufferIndex % HEIGHT == 0 || bufferIndex % HEIGHT == 0)
		{
			outBuffer[bufferIndex] = inBuffer[bufferIndex];
		}*/
		/*int x = bufferIndex % HEIGHT;
		int y = bufferIndex / HEIGHT;
		if (x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1)
		{
			outBuffer[bufferIndex] = inBuffer[bufferIndex];
		}*/
	}
	cout << endl;
	cout << "i = " << i << endl;
	cin >> iterations;
	for (int blurIteration = 0; blurIteration < iterations; blurIteration++)
	{
		for (int heightIndex = 1; heightIndex < HEIGHT - 1; heightIndex++)
		{
			for (int widthIndex = 1; widthIndex < WIDTH - 1; widthIndex++)
			{
				//The blur sum
				int sum = 0;
				//For every pixel in the data
				for (int heightOffset = -1; heightOffset < 2; heightOffset++)
				{
					for (int widthOffset = -1; widthOffset < 2; widthOffset++)
					{
						//Blur
						sum += (unsigned char)inBuffer[(heightIndex + heightOffset) * WIDTH + (widthIndex + widthOffset)];
						//sum += image[heightIndex + heightOffset][widthIndex + widthOffset];
					}
				}
				//Influence of pixel is equal to the influence of its neighbour. 1 for neighbour and 8 for pixel.
				outBuffer[heightIndex * WIDTH + widthIndex] = (sum + (unsigned char)inBuffer[heightIndex * WIDTH + widthIndex] * 7) / 16;
				//output[heightIndex][widthIndex] = (sum + image[heightIndex][widthIndex] * 7) / 16;
			}
			for (int k = 0; k < HEIGHT; k++)
			{
				for (int l = 0; l < WIDTH; l++)
				{
					int arrayIndex = k * WIDTH + l;
					inBuffer[arrayIndex] = outBuffer[arrayIndex];
					//image[k][l] = output[k][l];
				}
			}
			//Optimised. Tested and works.
			/*for (int l = 0; l < WIDTH; l++)
			{
				image[heightIndex][l] = output[heightIndex][l];
			}*/

		}
	}
	for (int i = 0; i < size; i++)
	{
		char ch = (char)outBuffer[i];
		outBuffer[i] = ch;
	}

	outputFile.write(outBuffer, size);
	outputFile.close();
	delete[] inBuffer;
	delete[] outBuffer;
	return 0;
}