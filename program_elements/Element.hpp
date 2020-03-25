#ifndef ELEMENT_H
#define ELEMENT_H


class Element{
	public:
		
		//methods
		virtual void run() = 0;
		virtual void _repr_() = 0;
		virtual void check_semantic() = 0;
};

#endif

