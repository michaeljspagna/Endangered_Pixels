#include <iostream>
#include <map>
#include <cmath>
#include <string>
/**
 * Below 2 files come from Sean Barrett's stb github repository
 * https://github.com/nothings/stb
 */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;


/**
* Calculates rgb using bitwise operatos
*
*  r = shift the bits of i to the right 16 times.
* 		Then & the result with 0x0ff (255) to set the bits poperly
* 	g = shift bits of i right 8 times
* 		Then & result with 0x0ff (255) to set bits properly
* 	b = & i with 0x0ff (255) to set bits properly
* @param i integer value representing rgb
* @param p a pointer to an int array of exactly size 3
*/
void itor(int i, int* p){
	int r,g,b;
	r = (i>>16)&0x0ff;
	g = (i>>8)&0x0ff;
	b = i&0x0ff;
	p[0] = (int)r;
	p[1] = (int)g;
	p[2] = (int)b;

}

/**
* Creates an int to represent an rgb value
*
* 	& r g and b with 0x0ff (255) individually
		* 	Shift r left 16 times
		* 	shift g left 8 times
* 	| all 3 values together
*
* @param r red value
* @param g green value
* @param b blue value
* @return an int representing the rgb value
*/
int rtoi(int r, int g, int b){
	return ((r&0x0ff)<<16) | ((g&0x0ff)<<8) | (b&0x0ff);
}

/**
 * Sets one of the larger pixels being created
 * @param pix = pointer to pixel colors
 * @param start = starting index in pix
 * @param block_width = number of pixels wide for each new pixel
 * @param block_height = number of pixels tall for each new pixel
 * @param jump_size = how many indexes to jump to get to next line
 * @param bpp = bits per pixel
 */
void subPix(unsigned char* pix, int start, int block_width, int block_height, int jump_size, int bpp){
	int h(0), w(0), idx(start), rgb, max(-1);
	map<int, int> counter;
	while(h < block_height){
		while(w < block_width){
			rgb = rtoi(pix[idx], pix[idx+1], pix[idx+2]); //get int-val from rgb
			if(counter.count(rgb)){
				++counter[rgb];
			}else{
				counter.insert(make_pair(rgb, 1));
			}
			++w;
			idx+=bpp;
		}
		w = 0;
		idx = start + (h*jump_size);
		++h;
	}

	for(pair<int,int> p: counter){
		if(max < p.second){
			max = p.second;
			rgb = p.first;
		}
	}

	h = 0;
	w = 0;
	idx = start;
	int arr[3];
	int *p = arr;
	itor(rgb, p);
	while(h < block_height){
		while(w < block_width){
			//set new rgb values
			pix[idx] = arr[0];
			pix[idx+1] = arr[1];
			pix[idx+2] = arr[2];
			++w;
			idx+=3;//increase to next pixel
		}
		w = 0;
		idx = start + (h*jump_size);
		++h;
	}

}

/**
 * pixelates picture
 * @param population = population of species
 * @param pix = pointer to pixel data
 * @param width = width of picture
 * @param height = height of picture
 * @param bpp = bits per pixel
 */
void pixelate(int population, unsigned char *pix, int width, int height, int bpp){

	int idx(0), div, length, start(0), pix_width, cur_width, width_add,
		pix_height, height_add, cur_height, row(0), column, jump;

	if(bpp == 3){
		jump = 3;
	}else{
		jump = 4;
	}
	div = sqrt(population); //how many blocks per row and how many rows
	if(div*div < population){
		++div;//Check to see if pixels need to be added
	}
	length = width * jump; //idxs to jump to get to next line
	pix_width = width / div; //how many times we will need to iterate to cover a block (*3 for block index width_
	width_add = width - (pix_width * div); //bonus pixels to last column
	pix_height = height / div; //how many rows for each base block
	height_add = height - (pix_height * div); //bonus rows to add to last row
	cur_height = pix_height; //height of current block


	while(row < div){ //loops down each row
		++row;
		if(row == div){ //checks to add bonus pixels to last line
			cur_height += height_add;
		}

		column = 0; //reset for each now
		cur_width = pix_width; //reset cur_width
		while(column < div){//loop through all columns in row
			++column;
			if(column == div){//check if its the last column to add bonus
				cur_width += width_add;
			}
			subPix(pix, start, cur_width, cur_height, length, jump); //set main color of sub block
			++idx;
			start += (cur_width * jump); // increase start to next block (66 pixels * 3 idx per pixel)
		}
		start = length * row * pix_height; //get new start. line length * current row * height of block
	}


}

/**
 * Adds _ep to filenam
 * @param filename
 * @return new filenam
 */
string renameFile(string filename){
	int idx(filename.length()-4);
	string rep = "_ep.png";
	filename.replace(idx, 5, rep);
	return filename;
}
/**
 * Creates the new image
 * @param filename
 * @param width = pixel width (from original)
 * @param height = pixel height (from original)
 * @param bpp = bits per pixel
 * @param pix = pixel pointer
 * @param stride = width*bpp
 */
void printImage(string filename, int width, int height, int bpp, unsigned char* pix, int stride){
	filename = renameFile(filename);
	stbi_write_png(filename.c_str(), width, height, bpp, pix, stride);
}

void amur(){
	int width, height, bpp, pop(70);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/amur_leopard.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void rhino(){
	int width, height, bpp, pop(60);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/javan_rhino.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void wolf(){
	int width, height, bpp, pop(300);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/red_wolf.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void fox(){
	int width, height, bpp, pop(250);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/darwin_fox.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void gorilla(){
	int width, height, bpp, pop(250);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/cross_river_gorilla.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void ele(){
	int width, height, bpp, pop(2500);
	string filename;
	filename = "/Users/michaelspagna/Programming/C++/Endangered_Pixels/images/sumatran_elephant.png";
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	pixelate(pop, pix, width, height, bpp);
	printImage(filename, width, height, bpp, pix, width*bpp);
	cout << "Your picture is in the folder" << endl;
}

void self(){

	int width, height, bpp, pop;
	string filename;
	cout << "Enter File Path" << endl;
	cout << "Be sure to use .png but not 32-Bit" << endl;
	cin >> filename;
	cin.clear();

	cout << "Enter Population" << endl;
	cin >> pop;
	unsigned char  *pix = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
	if(pix== nullptr){
		cout << "Error: Bad File / File Path" << endl;
	}else if(pop > 10000){
		cout << "Population too  large" << endl;
	}else{
		pixelate(pop, pix, width, height, bpp);
		printImage(filename, width, height, bpp, pix, width*bpp);
		cout << "Your image is in your folder.\nRemember to recycle" << endl;
	}
}

/**
 * Logic control function
 */
void endangeredPixels(){
	cout << "Welcome to Endangered Pixels" << endl;
	int i(2);
	while(i!=1){
		cout << "Please select one of the options below" << endl;
		cout << 1 << ": Amur Leopard" << endl;
		cout << 2 << ": Darwin Fox" << endl;
		cout << 3 << ": Javan Rhino" << endl;
		cout << 4 << ": Cross River Gorilla" << endl;
		cout << 5 << ": Red Wolf" << endl;
		cout << 6 << ": Sumatran Elephant" << endl;
		cout << 7 << ": Pick Your Own" << endl;

		int pick;

		cin >>pick;

		switch(pick){
			case 1:
				amur();
				break;
			case 2:
				fox();
				break;
			case 3:
				rhino();
				break;
			case 4:
				gorilla();
				break;
			case 5:
				wolf();
				break;
			case 6:
				ele();
				break;
			case 7:
				self();
				break;
			default:
				cout << "Invalid Choice" << endl;
				break;

		}
		cout << "1: to end\n0: to go again" << endl;
		cin >> i;
	}

}


/**
 * Main
 * gcc -std=c++14 main.cpp
 * ./a.out
 * @return 0 for success
 */
int main() {

	endangeredPixels();


	return 0;
}
