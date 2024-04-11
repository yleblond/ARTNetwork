#ifndef HEADER_IMAGE
#define HEADER_IMAGE

class Image
{
		float*	image;
		unsigned char	label;
	
	public:
		Image()
		{
		}
		void setData(float* data) {
			image = data;
		}
		void setLabel(unsigned char l) {
		    printf("setLabel %d\n", l);
			label = l;
		}
		float* getData() {
			return image;
		}
		unsigned char getLabel() {
			return label;
		}

};

#endif
