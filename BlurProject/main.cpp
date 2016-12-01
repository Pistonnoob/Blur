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
	char* buffer = new char[size];
	//vector<char> buffer(size);
	if (file.read(buffer, size))
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
		charCode = (unsigned char)buffer[bufferIndex];
		int x = i % HEIGHT;
		int y = i / HEIGHT;
		i++;
		image[x][y] = charCode;
		/*if (x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1)
		{
			output[x][y] = charCode;
		}*/
	}
	//for (std::vector<char>::const_iterator iter = buffer.begin(); iter != buffer.end(); iter++)
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
						sum += image[heightIndex + heightOffset][widthIndex + widthOffset];
					}
				}
				//Influence of pixel is equal to the influence of its neighbour. 1 for neighbour and 8 for pixel.
				output[heightIndex][widthIndex] = (sum + image[heightIndex][widthIndex]*7)/16;
			}
			for (int k = 0; k < HEIGHT; k++)
			{
				for (int l = 0; l < WIDTH; l++)
				{
					image[k][l] = output[k][l];
				}
			}
			//Optimised. Tested and works.
			/*for (int l = 0; l < WIDTH; l++)
			{
				image[heightIndex][l] = output[heightIndex][l];
			}*/

		}
	}
	int w = 0;
	for (int k = 0; k < WIDTH; k++)
	{
		for (int l = 0; l < HEIGHT; l++)
		{
			buffer[w] = output[l][k];
			//outBuffer[w] = output[l][k];
			w++;
		}
	}
	outputFile.write(buffer, size);
	outputFile.close();
	return 0;
}