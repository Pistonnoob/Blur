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
	for (int bufferIndex = 0; bufferIndex < size; bufferIndex++)
	{
		int charCode = (unsigned char)inBuffer[bufferIndex];
		inBuffer[bufferIndex] = charCode;
		outBuffer[bufferIndex] = charCode;
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
		charCode = (unsigned char)inBuffer[bufferIndex];
		int x = i % HEIGHT;
		int y = i / HEIGHT;
		i++;
		image[x][y] = charCode;
		/*if (x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1)
		{
			output[x][y] = charCode;
		}*/
	}
	//for (std::vector<char>::const_iterator iter = inBuffer.begin(); iter != inBuffer.end(); iter++)
	//{
	//	charCode = (unsigned char)(*iter);
	//	int x = i % HEIGHT;
	//	int y = i / HEIGHT;
	//	image[x][y] = charCode;
	//	/*if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
	//	{
	//		output[y][x] = charCode;
	//	}*/
	//	i++;
	//}
	for (int k = 0; k < HEIGHT; k++)
	{
		for (int l = 0; l < WIDTH; l++)
		{
			output[k][l] = image[k][l];
		}
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
						sum += inBuffer[(heightIndex + heightOffset) * WIDTH + (widthIndex + widthOffset)];
						//sum += image[heightIndex + heightOffset][widthIndex + widthOffset];
					}
				}
				//Influence of pixel is equal to the influence of its neighbour. 1 for neighbour and 8 for pixel.
				outBuffer[heightIndex * WIDTH + widthIndex] = (sum + inBuffer[heightIndex * WIDTH + widthIndex] * 7) / 16;
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
	//int w = 0;
	//for (int k = 0; k < WIDTH; k++)
	//{
	//	for (int l = 0; l < HEIGHT; l++)
	//	{
	//		outBuffer[w] = output[l][k];
	//		//outBuffer[w] = output[l][k];
	//		w++;
	//	}
	//}
	outputFile.write(outBuffer, size);
	outputFile.close();
	delete[] inBuffer;
	delete[] outBuffer;
	return 0;
}