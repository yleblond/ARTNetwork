#ifndef HEADER_IMAGE
#define HEADER_IMAGE

class Image
{
	private:
		float*	image;
		unsigned char	label;
		int width;
		int height;
		
	public:
		Image()
		{
		}
		void setData(float* data) {
			image = data;
		}
		void setLabel(unsigned char l) {
			label = l;
		}
		float* getData() {
			return image;
		}
		unsigned char getLabel() {
			return label;
		}
		void setDimensions(int w, int h) {
			width = w;
			height = h;
		}
		int getWidth() {
			return width;
		}
		int getHeigth() {
			return height;
		}


		void display(float threshold) {
			int size = width*height;
		    for (int i = 0; i < size; i++) {
				if (i%width) {
				} else {
					std::cout << "\n";
				}
                std::cout << ((image[i] > threshold) ? "X" : " ");
			}
			std::cout << "\n\n";
    	}
};

class ImageSet {
	public:
		int nExemples;

		int nEntrees;

		int imageSize;
		int width;
		int height;

		Image** learningFigure;

		ImageSet(){}

};

#endif
