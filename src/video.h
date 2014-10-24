#ifndef video_h
#define video_h

class video
{
	public:
		video();
		~video();
	
		void clear();
		void writestr(char *cp);
		void writenum(unsigned long long int n, int base);
		void writeaddr(unsigned long long int n);
		void put(char c);
		void newln();
	private:
		unsigned short *videomem;
		unsigned int off;
		unsigned int pos;
};

extern video __video;

#endif

